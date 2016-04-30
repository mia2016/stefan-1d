#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "problem.h"
#include "error.h"
#include "interpolate.h"



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


void problem_iterate(problem_t * p, double untilTime) {

    // Copy values from struct (for cleaner code)
    //double * temps = p->temperatures;
    //double * mats  = p->materials;
    //double * bords = p->borders; 
    //double * b     = p->beta;

    double dt = p->dt;
	double t;

    /* Heat fluxes [W/m²]
     * p->borders[0].q = q_betong/is (Constant)
     * p->borders[1].q = q_snø/is
     * p->borders[2].q = q_overflate
     * 
     * TODO: q_frys on borders[1], but only on ice side
     */
    double q_sens, q_lat, q_kort, q_lang;
        
    p->borders[0].q = -115.0;
    
    // TODO: Should these be struct variables?
    double h_ls = 0.0;  // h_luft/snø (Convective heat transfer) 
    double y    = 0.0;  // γ            
    double e_o  = 0.0;  // e_overflate (Vapor pressure)
    double e_l  = 0.0;  // e_luft (Vapor pressure)
    double emm_s= 0.0;  // e_snø (Emissivity)
    double emm_a= 0.0;  // e_atmosfære (Emissivity)
    double C    = 0.0;  // Skydekket 1-10
    double sigma= 0.0;  // Stefan-Boltzmann constant //TODO: Should be defined as constant
    double v_luft=0.0;  // Kinematisk viskositet

    // Main loop
	printf("Starting...\n");
	for (t = p->time; t <= untilTime; t += dt) {
		printf("\r\33[2KProgress: %.2lf%%", 100 * (t - p->time) / (untilTime - p->time));

        
        // Heat fluxes
        // q_snø/is (TODO: Numerator should be: (u_1snø-u_nis)
        p->borders[1].q = 1.0/(p->borders[1].position/p->materials[0].kappa
                +(1-p->borders[1].position/p->materials[0].kappa));

		//q_overflate (TODO: Calculate parts separately for cleaner code?)
        q_sens = h_ls*(p->borders[2].u[0]-p->borders[2].u[1]);
        q_lat = (1/y)*h_ls*(e_o-e_l);
        q_kort = 0.0;
        q_lang = emm_s*sigma*(emm_a*(1+0.22*C*C))*(pow(p->borders[2].u[1], 4)-pow(p->borders[2].u[0], 4)); 
        p->borders[2].q = q_sens+q_lat+q_kort+q_lang;

		//Calculate boundary movements
		double ds[2];
        
        if (p->borders[3].u[0] >= 0.0){    // If temperature of snow at air/snow interface is >= 0
            ds[1] = -p->borders[2].q/(p->materials[1].rho*p->materials[1].L);
        }
        else{
            ds[1] = 0.0;
        }
    
	    ds[0] = -p->beta*p->materials[0].rho/p->materials[1].rho*ds[1];


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
		for (unsigned i = 1; i < 3; i++) {

			// We assume a border never crosses more than a single point
			if (ds[i] >= 1.0) {
				error_fatal("A border is moving too fast.");
			}

			double next_s = p->borders[i].position + ds[i - 1];
			unsigned movement = (unsigned) next_s - (unsigned) p->borders[i].position;

			// Move point between phases
			if (movement > 0) {

				// New point in phase i
				p->temperatures[(unsigned) p->borders[i].position] = 0.0; //TODO: Interpolation using above method

			} else if (movement < 0) {

				// Lost point in phase i - it ends up in i+1
				p->temperatures[(unsigned) p->borders[i].position] = 0.0; //TODO: Interpolation

			}

			p->borders[i].position = next_s;
		}


    }

    // Update problem
    p->time = t;
    p->dt = dt;

	printf("\r\33[2KDone\n\n");

}
