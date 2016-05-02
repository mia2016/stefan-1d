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
    int movement = (int) next_position - (int) bp;

    // Move point between phases?
    if (movement < 0) {

        // New point in phase i
        p->temperatures[bp + 1] = interpolate_value(
                (point_t) {bp - 1, p->temperatures[bp - 1]},
                (point_t) {bp, p->temperatures[bp]},
                (point_t) {next_position, p->borders[i].u[0]},
                bp + 1
            );
        

    } else if (movement < 0) {

        // Lost point in phase i - it ends up in i+1
        p->temperatures[bp] = i == 2 ? 0.0 : interpolate_value(
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

	problem.dataset = NULL;

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
	for (unsigned i = 0; i < 3; i++) {
		problem.borders[i].u[0] = temperature;
		problem.borders[i].u[1] = temperature;
	}

	return problem;
}


void problem_destroy(problem_t * problem) {
	free(problem->temperatures);
}

void problem_print_header(problem_t * problem){
    FILE * log_file, * flux_file, * temp_file;
    log_file  = fopen("log.out", "w");
    flux_file = fopen("flux.out", "w");
    temp_file = fopen("temp.out", "w");

    fclose(log_file);
    fclose(flux_file);
    fclose(temp_file);
}

void problem_print(problem_t * problem) {
    FILE * log_file, * flux_file, * temp_file;
    constants konst = get_constants();
    log_file  = fopen("log.out", "a");
    flux_file = fopen("flux.out", "a");
    temp_file = fopen("temp.out", "a");

    // Printing temperaturs
    fprintf(log_file, "%.5f\t", problem->time*konst.dt/86400.0);
    for (unsigned i = 0; i < problem->resolution; i++) {
        fprintf(
            log_file,
			"%.6f\t",
			problem->temperatures[i]
		);
        fprintf(
            temp_file,
            "%.6f\t",
            problem->temperatures[i]
            );
    }
    fprintf(temp_file, "\n");

    // Border temperature and position
    for (unsigned i = 0; i < 3; i++){
        fprintf(log_file,"%.1f\t%f\t%f\t", 
                problem->borders[i].u[0], 
                problem->borders[i].u[1], 
                problem->borders[i].position//*konst.dx
               );
    }
    fprintf(log_file, "\n");
    
    // Printing heat fluxes
    fprintf(flux_file, "%f\t", problem->time*konst.dt);
    for (unsigned i = 0; i < 7; i++){
        fprintf(
            flux_file,
            "%.6f\t",
            problem->q[i]
        );
    }
    fprintf(flux_file, "%.6f", problem->borders[0].q[1]);
    fprintf(flux_file, "\n");

    fclose(log_file);
    fclose(flux_file);
    fclose(temp_file);
}


void problem_iterate(problem_t * p, unsigned untilTime) {
    constants konst = get_constants();

    // Checking stability
    for (int i = 0; i < 2; i++){
        if (p->materials[i].alpha*konst.dt/(konst.dx*konst.dx) > 0.5)
            error_warning("Stability criteria not met.");
    }
    
    // Scaling material variables to reduced
    for (int i = 0; i < 2; i++){
        p->materials[i].alpha   *= konst.dt/(konst.dx*konst.dx);
        p->materials[i].L       *= konst.dt*konst.dt/(konst.dx*konst.dx);
        p->materials[i].rho     *= pow(konst.dx, 3.0);
        p->materials[i].kappa   *= pow(konst.dt, 3.0)/konst.dx;
    }
    
    //problem_print_header(p);

    // Precalculate some constants needed later
    double k[] = {
        -p->beta / (p->materials[0].rho * p->materials[1].L),
        1.0 / (p->materials[1].rho * p->materials[1].L),
        konst.em_s*konst.sigma,
        0.0296*pow(konst.clength/konst.v_luft, 4.0/5.0)*pow(konst.v_luft*konst.rho_l*konst.cp_luft
                /konst.k_luft, 1.0/3.0)*(konst.k_luft/konst.clength),
        konst.xi*konst.ls/konst.R
    };

    p->borders[0].q[1] = konst.q_bi;

    // Border positions
    int p_i     = (int)p->borders[1].position;
    double p_d  = p->borders[1].position-(int)p->borders[1].position;

    // Main loop
	printf("Starting...\n");
	while (p->time <= untilTime) {

        // Update progress in command line interface
        if (p->time % 10000 == 0) {
            printf("\r\33[2KProgress: %.2f%%", 100 * (float) p->time / untilTime);
            fflush(stdout);
        }

        // TODO: Update variables dependant on weather 
		double time = p->time * konst.dt;
        konst.cover         = 10.0 * dataset_interpolate(p->dataset, 3, time);                          // Cloud cover
        konst.windspeed     = dataset_interpolate(p->dataset, 0, time) * konst.dt/konst.dx;        // Wind speed
        konst.Rf            = dataset_interpolate(p->dataset, 2, time);                          // Relative humidity
        konst.q_sol         = -27.3*pow(konst.dt, 3.0);     // February [W/m²] 
        p->borders[2].u[1]  = dataset_interpolate(p->dataset, 1, time) + 273.15;                       // Air temperature

        // Calculate variables needed in heat flux calculation
        konst.e_l     = 0.611*konst.Rf*
            exp(k[4]*(1.0/p->borders[2].u[0]-1.0/p->borders[2].u[1]))*konst.dx*pow(konst.dt, 2.0);
        konst.h_ls    = k[3]*pow(konst.windspeed, 4.0/5.0);

        // Heat flux calculation
        p->q[0] = konst.h_ls*(p->borders[2].u[0]-p->borders[2].u[1]);
        p->q[1] = (1.0/konst.y)*konst.h_ls*(konst.e_l-konst.e_o);
        p->q[2] = (1-konst.albedo)*konst.q_sol;
        p->q[3] = k[2]*(0.642*konst.e_l*pow(p->borders[2].u[1], 3.0)-pow(p->borders[2].u[0], 4.0));
        p->q[4] = 0.0;
        for (unsigned i = 0; i < 4; i++){
            p->q[4] += p->q[i];
        }

        if (p->borders[2].u[0] >= 273.15 && p->borders[1].u[0] < 273.15){
            p->q[5] = -p->beta*(p->q[4]);
        }
        else{
            p->q[5] = 0.0;  
        }
        
        p->q[6] = (p->temperatures[p_i+1]-p->temperatures[p_i])
            /(p_d/p->materials[0].kappa+(1.0-p_d/p->materials[1].kappa));
       
        // Asigning heat fluxes
        p->borders[1].q[0] = -p->q[5]-p->q[6];  // q_snø/is+q_frys
        p->borders[1].q[1] = p->q[6];           // q_snø/is
        p->borders[2].q[0] = p->q[4];           // q_overflate
        
        if (p->borders[2].q[0] > 0) {
            error_warning("Energy flowing from snow to air not modelled");
        }

        // Calculate boundary movements
		double ds[2] = {0};

        if (p->borders[2].u[0] >= 273.15) {

            // Freeze som water
            if (p->borders[1].u[0] < 273.15){
                ds[0] = k[0] * p->borders[2].q[0];
            }
            
            // Melt some snow
            ds[1] = k[1] * p->borders[2].q[0];

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

        // Print tempeatures
        if (p->time%(konst.dump_rate) == 0)
            problem_print(p);
    }
    printf("\nDone!\n");
}
