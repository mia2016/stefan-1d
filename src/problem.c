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


void problem_iterate(problem_t * p, unsigned untilTime) {

    // Precalculate some constants needed later
    double k[] = {
        p->beta / (p->materials[0].rho * p->materials[1].L),
        - 1.0 / (p->materials[1].rho * p->materials[1].L)
    };

    // Main loop
	printf("Starting...\n");
	while (p->time <= untilTime) {

        // Update progress in command line interface
        if (p->time % 10000 == 0) {
            printf("\r\33[2KProgress: %.2f%%", 100 * (float) p->time / untilTime);
            fflush(stdout);
        }


		//TODO: Calculate heat fluxes


        //TODO: Fix this
        if (p->borders[2].q < 0) {
            error_warning("Energy flowing from snow to air not modelled");
        }

		// Calculate boundary movements
		double ds[2] = {0};

        if (p->borders[2].u[0] >= 0.0) {

            // Melt some snow
            ds[0] = k[0] * p->borders[2].q;
            ds[1] = (k[0] + k[1]) * p->borders[2].q;

            // Don't count this heat later
            p->borders[2].q = 0;
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


        p->time++;
    }

	printf("\r\33[2KDone\n\n");

}
