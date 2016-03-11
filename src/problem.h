
/**
 * Represents the state of a stefan problem.
 */
typedef struct {

    // Array of temperatures (and its length)
    int nTemperatures;
    double * temperatures;

    // Current time and timestep
    double time;
    double dt;

    // Current boundary position and speed
    double s;
    double ds;

} problem_t;


/**
 * Iterates the given problem repeatedly.
 *
 * @param problem Problem to iterate
 * @param untilTime Simulation time at which to stop the iteration
 */
void problem_iterate(problem_t * problem, double untilTime);
