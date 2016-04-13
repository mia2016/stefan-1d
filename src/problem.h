#pragma once

/**
 * Represents the state of a stefan problem with 2 moving boundaries.
 *
 * The domain of the problem runs from 0 to s[3] and is modelled using n points,
 * where n is the problem's resolution.
 *	
 *	0       s[0]            s[1]             s[3]
 *	|--------|--- Phase 1 ---|---- Phase 2 ----|
 *
 */
typedef struct {

    // Array of temperatures (and its length)
    unsigned resolution;
    double * temperatures;

    // Current time and timestep
    double time;
    double dt;

    // Current boundary positions. Note that s[2] is assumed stationary.
    double s[3];

	// Temperatures on each side of the middle boundary and top
	float boundary_temperature[3];

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
