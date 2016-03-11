#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "problem.h"

void problem_iterate(problem_t * problem, double untilTime) {

    // Copy values from struct (for cleaner code)
    int n = problem->nTemperatures;
    double * temps = problem->temperatures;

    double t = problem->time;
    double dt = problem->dt;
    double s = problem->s;
    double ds = problem->ds;


    // Main loop
    while (t <= untilTime) {

        double dx = s / (n - 1);
        double dx2 = dx * dx;
        double r = dt / dx2;

        // Cache values to avoid copying entire array
        double prev_u = temps[0];
        double next_ds = -(
                    dt * (3 * temps[n - 1] -4 * temps[n - 2] + temps[n - 3])
                ) / (2 * dx);

        // Boundary
        temps[0] = (1 - 2 * r) * temps[0] + 2 * r * temps[1]
                + 2 * dx * r * exp(t);


        // Interior
        for (int i = 1; i < n - 1; i++) {

            double du = ((temps[i + 1] - prev_u) * i * ds) / (2 * s)
                + (temps[i + 1] - 2 * temps[i] + prev_u) * r;

            // Update temps
            prev_u = temps[i];
            temps[i] += du;
        }



        // Check condition for stability
        if (dt > (2 * dx2) / (4 + (dx2 * ds * ds)/(dt * dt))) {
            fprintf(stderr, "ERROR: Condition for stability not fulfilled.\n");
            exit(EXIT_FAILURE);
        }

        // Integrate
        ds = next_ds;
        s += ds;
        t += dt;
    }

    // Update problem
    problem->time = t;
    problem->dt = dt;
    problem->s = s;
    problem->ds = ds;
}
