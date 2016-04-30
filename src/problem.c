#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "problem.h"
#include "error.h"
#include "interpolate.h"
#include "constants.h"


/**
 * Moves a border and migrates points across phases if necessary.
 *
 * @param p Problem containing border to move
 * @param i Index of border to move (in problem)
 * @param distance Distance to move border (can be negative)
 */
void move_border(problem_t * p, unsigned i, double distance) {

    // We assume a border never crosses more than a single point
    if (abs(distance) >= 1.0) {
        error_fatal("A border is moving too fast.");
    }

    unsigned bp = p->borders[i].position;
    double next_position = p->borders[i].position + distance;
    unsigned movement = (unsigned) next_position - bp;

    // Move point between phases?
    if (movement > 0) {

        // New point in phase i
        p->temperatures[bp + 1] = interpolate_value(
                (point_t) {bp - 1, p->temperatures[bp - 1]},
                (point_t) {bp, p->temperatures[bp]},
                (point_t) {next_position, p->borders[i].u[0]},
                bp + 1
            );

    } else if (movement < 0) {

        // Lost point in phase i - it ends up in i+1
        p->temperatures[bp] = interpolate_value(
                (point_t) {bp + 2, p->temperatures[bp + 2]},
                (point_t) {bp + 1, p->temperatures[bp + 1]},
                (point_t) {next_position, p->borders[i].u[1]},
                bp
            );

    }

    p->borders[i].position = next_position;
}


problem_t problem_create(unsigned resolution, double temperature) {
	problem_t problem = {0};

	// Allocate and initialize temperatures
	problem.resolution = resolution;
	problem.temperatures = malloc(sizeof(double) * resolution);
	
	if (problem.temperatures == NULL) {
		fprintf(stderr, "Failed to allocate memory for temperatures\n");
		exit(EXIT_FAILURE);
	}

	for (unsigned i = 0; i < resolution; i++) {
		problem.temperatures[i] = temperature;
	}

	// Initialize boundary temperatures
	for (unsigned i = 0; i < 4; i++) {
		problem.borders[i].u[0] = temperature;
		problem.borders[i].u[1] = temperature;
	}

	return problem;
}


void problem_destroy(problem_t * problem) {
	free(problem->temperatures);
}


void problem_print(problem_t * problem) {
	// Headers
    printf("x, u\n");

	// Values
    for (unsigned i = 0; i < problem->resolution; i++) {
        printf(
			"%u, %f\n",
			i,
			problem->temperatures[i]
		);
    }

	//TODO: Print boundaries
}


void problem_iterate(problem_t * p, unsigned untilTime) {

    // Copy values from struct (for cleaner code)
    //double * temps = p->temperatures;
    //double * mats  = p->materials;
    //double * bords = p->borders; 
    //double * b     = p->beta;

    constants konst = get_constants();
    
    // Precalculate some constants needed later
    double k[] = {
        p->beta / (p->materials[0].rho * p->materials[1].L),
        - 1.0 / (p->materials[1].rho * p->materials[1].L),
        konst.em_s*konst.sigma,
        0.0296*pow(konst.clength/konst.v_luft, 4.0/3.0)
            *pow(konst.v_luft/konst.k_luft, 1.0/3.0)*konst.clength*(1.0/konst.k_luft),
        konst.xi*konst.ls/konst.R
    };

        
    /* Heat fluxes [W/m²]
     * p->borders[0].q[1] = q_betong/is (Constant)
     * p->borders[1].q[0] = q_snø/is+qfrys
     * p->borders[1].q[1] = q_snø/is
     * p->borders[2].q[0] = q_overflate
     */

    p->borders[0].q[1] = konst.q_bs;
    
    double q[] = {
        0.0,    // q_sens
        0.0,    // q_lat
        0.0,    // q_kort
        0.0,    // q_lang
        0.0,    // q_overflate
        0.0,    // q_frys
        0.0     // q_snø/is
    };

    // Borders
    unsigned p_border = p->borders[1].position-(int)p->borders[1].position;
    unsigned v_border = p->borders[2].position-(int)p->borders[2].position;

    // Main loop
	printf("Starting...\n");
	while (p->time <= untilTime) {

        // Update progress in command line interface
        if (p->time % 10000 == 0) {
            printf("\r\33[2KProgress: %.2f%%", 100 * (float) p->time / untilTime);
            fflush(stdout);
        }

        // TODO: Update variables dependant on weather 
        konst.cover         = 0.0;
        konst.windspeed     = 0.0;
        konst.Rf            = 0.0;
        konst.q_sol         = 27.3;  // February [W/m²] 


        konst.e_l     = 0.611*konst.Rf*exp(k[4]*(1.0/273.15-1.0/p->borders[2].u[1]));
        konst.h_ls    = k[3]*pow(konst.windspeed, 4.0/3.0);

        // Heat fluxes
        q[0] = konst.h_ls*(p->borders[2].u[0]-p->borders[2].u[1]);
        q[1] = (1.0/konst.y)*konst.h_ls*(konst.e_o-konst.e_l);
        q[2] = (1-konst.albedo)*konst.q_sol;
        q[3] = k[2]*(0.642*konst.e_l*(1+0.22*konst.cover*konst.cover)
                *pow(p->borders[2].u[1], 3.0)-pow(p->borders[2].u[0], 4.0));
        q[4] = q[0]+q[1]+q[2]+q[3];

        if (p->borders[2].u[1] >= 273.15){
            q[5] = -p->beta*(p->borders[2].q[0]);
        }
        else{
            q[5] = 0.0;  
        }
        
        q[6] = (p->temperatures[p_border+1]-p->temperatures[p_border])
            /(p_border/p->materials[0].kappa+(1.0-p_border/p->materials[0].kappa));

        p->borders[1].q[0] = q[5]+q[6]; // q_snø/is+q_frys
        p->borders[1].q[1] = q[6];      // q_snø/is
        p->borders[2].q[0] = q[4];      // q_overflate


        //TODO: Fix this
        if (p->borders[2].q[0] < 0) {
            error_warning("Energy flowing from snow to air not modelled");
        }

		// Calculate boundary movements
		double ds[2] = {0};

        if (p->borders[2].u[0] >= 0.0) {

            // Melt some snow
            ds[0] = k[0] * p->borders[2].q[0];
            ds[1] = (k[0] + k[1]) * p->borders[2].q[0];

            // Don't count this heat later
            p->borders[2].q[0] = 0;
        }

		// Update each phase
		for (unsigned i = 0; i < 2; i++) {
			phase_update(
				p->borders + i,
				p->borders + i + 1,
				p->temperatures,
				p->materials + i
			);
		}


		// Update boundaries (including checking for points crossing it)
        move_border(p, 1, ds[0]);
        move_border(p, 2, ds[1]);


        p->time++;
    }

	printf("\r\33[2KDone\n\n");

}
