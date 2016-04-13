#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "problem.h"

typedef struct {
	double x, y;
} point_t;

/**
 * Calculates the next iteration using the heat equations.
 * Boundaries are assumed to already have been calculated, thus the first and
 * last point is left alone. The range of points to consider is calculated using
 * the bounds array.
 *
 * @param u Array of temperatures
 * @param bounds Start and end positions of phase (array of length 2)
 * @param c Constant used in heat equation (TODO)
 */
void calculate_interior(double * u, double * bounds, double c) {
	double prev_u = u[0];

	for (unsigned i = bounds[0]; i < bounds[1]; i++) {
		//TODO: Update code to match problem...
		double du = 0.0 * prev_u;

		// Update u
		prev_u = u[i];
		u[i] += du;
	}
}

/**
 * TODO
 */
double interpolate_double_differentiated() {
	return 0.0;
}


/**
 * Calculates the interpolated value of a point x given three other points.
 *
 * @param a Point 1
 * @param b Point 2
 * @param c Point 3
 * @param x Point at which to calculate interpolated value
 * @return Interpolated value
 */
double interpolate_value(point_t a, point_t b, point_t c, double x) {
	return (a.y * (x - b.x) * (x - c.x)) / ((a.x - b.x) * (a.x - c.x))
		+ (b.y * (x - a.x) * (x - c.x)) / ((b.x - a.x) * (b.x - c.x))
		+ (c.y * (x - b.x) * (x - a.x)) / ((c.x - b.x) * (c.x - a.x));
}


problem_t problem_create(unsigned resolution, double temperature) {
	problem_t problem = {0};

	// Allocate memory for temperatures
	problem.resolution = resolution;
	problem.temperatures = malloc(sizeof(double) * resolution);
	
	if (problem.temperatures == NULL) {
		fprintf(stderr, "Failed to allocate memory for temperatures\n");
		exit(EXIT_FAILURE);
	}

	for (unsigned i = 0; i < resolution; i++) {
		problem.temperatures[i] = temperature;
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


void problem_iterate(problem_t * problem, double untilTime) {

    // Copy values from struct (for cleaner code)
    double * temps = problem->temperatures;

    double t = problem->time;
    double dt = problem->dt;
    double * s = problem->s;

	// Check condition for stability
	if (0 /*TODO*/) {
		fprintf(stderr, "ERROR: Condition for stability not fulfilled.\n");
		exit(EXIT_FAILURE);
	}


    // Main loop
	for (double t = problem->time; t <= untilTime; t += dt) {


        // Calculate ds now to avoid copying entire array
        double ds[] = {
			0.0, //TODO
			0.0	//TODO
		};


        // Boundary conditions
			// Including boundary temperatures


		// Interior for each phase
		calculate_interior(temps, s, 1.234);
		calculate_interior(temps, s + 1, 1.234);


		// Update boundaries (including checking for points crossing it)
		for (unsigned i = 0; i < 2; i++) {
			// Check assumption
			if (ds[i] >= 1.0) {
				fprintf(stderr, "ERROR: Interface %u is moving too fast!", i);
				exit(EXIT_FAILURE);
			}

			double next_s = s[i] + ds[i];
			unsigned movement = (unsigned) next_s - (unsigned) s[i];

			// Move point between phases
			if (movement > 0 && i > 0) {

				// New point in phase i
				temps[(unsigned) s[i]] = 0.0; //TODO: Interpolation

			} else if (movement < 0) {

				// Lost point in phase i - it ends up in i+1
				temps[(unsigned) s[i]] = 0.0; //TODO: Interpolation

			}

			s[i] = next_s;
		}

    }

    // Update problem
    problem->time = t;
    problem->dt = dt;

	for (unsigned i = 0; i < 3; i++) {
		problem->s[i] = s[i];
	}
}
