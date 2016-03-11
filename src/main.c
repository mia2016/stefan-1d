#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "problem.h"

/**
 * Prints the temperatures as a function of the position x.
 */
void printCsv(problem_t * problem) {
    printf("x, u\n");
    for (int i = 0; i < problem->nTemperatures; i++) {
        printf("%f, %f\n", i * problem->s / (problem->nTemperatures - 1), problem->temperatures[i]);
    }
}

int main(int argv, char ** argc) {

    problem_t problem = {
        .nTemperatures = 80,
        .time = 0.1,
        .dt = 0.0000001
    };

    // For the example problem, this hold true
    problem.ds = problem.dt;
    problem.s = problem.time;

    // Create an fill array of temperatures
    problem.temperatures = malloc(sizeof(double) * problem.nTemperatures);

    for (int i = 0; i < problem.nTemperatures - 1; i++) {
        problem.temperatures[i] = exp(
                problem.time - i * problem.s / (problem.nTemperatures - 1)
            ) - 1;
    }

    problem.temperatures[problem.nTemperatures - 1] = 0.0;


    // Iterate to solution
    problem_iterate(&problem, 0.5);

    // Print and clean up
    printCsv(&problem);
    free(problem.temperatures);

    return EXIT_SUCCESS;
}
