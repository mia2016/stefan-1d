#pragma once
#include "material.h"
#include "phase.h"


/**
 * Represents the state of a stefan problem with 2 moving boundaries.
 */
typedef struct {

    // Array of temperatures (and its length)
    unsigned resolution;
    double * temperatures;

    // Current time and timestep
    double time;
    double dt;

    // Current boundaries
	border_t borders[3];

	// Material properties of the two phases
	material_t materials[2];

	//TODO: Description and better name
	double beta;

} problem_t;


/**
 * Allocate resources for a new problem.
 *
 * @param resolution Number of grid points to use (in total)
 * @param temperature Initial temperature (of all grid points)
 * @return Constructed problem
 */
problem_t problem_create(unsigned resolution, double temperature);


/**
 * Free the resources used in the given problem.
 *
 * @param problem Problem to destroy
 */
void problem_destroy(problem_t * problem);


/**
 * Prints the temperatures as a function of the position x.
 *
 * @param problem Problem to print
 */
void problem_print(problem_t * problem);

/**
 * Iterates the given problem repeatedly.
 *
 * @param problem Problem to iterate
 * @param untilTime Simulation time at which to stop the iteration
 */
void problem_iterate(problem_t * problem, double untilTime);
