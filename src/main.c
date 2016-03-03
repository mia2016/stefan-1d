#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * Prints the temperatures as a function of the position x.
 */
void printCsv(double * temperatures, int nTemperatures, double s) {
    printf("x, u\n");
    for (int i = 0; i < nTemperatures; i++) {
        printf("%f, %f\n", i * s / (nTemperatures - 1), temperatures[i]);
    }
}


int main(int argv, char ** argc) {

    // Start values
    int nTemperatures = 80;
    double t = 0.1;
    double endTime = 0.5;
    double dt = 0.0000001;
    double s = t;
    double ds = dt;

    // Create an fill array of temperatures
    double * temperatures = malloc(sizeof(double) * nTemperatures);

    for (int i = 0; i < nTemperatures - 1; i++) {
        temperatures[i] = exp(t - i * s / (nTemperatures - 1)) - 1;
    }

    temperatures[nTemperatures - 1] = 0.0;


    // Main loop
    while (t <= endTime) {

        double dx = s / (nTemperatures - 1);
        double dx2 = dx * dx;
        double r = dt / dx2;

        // Cache values to avoid copying entire array
        double prev_u = temperatures[0];
        double next_ds = -(
                    dt * (
                        3 * temperatures[nTemperatures - 1]
                        -4 * temperatures[nTemperatures - 2]
                       + temperatures[nTemperatures - 3]
                    )
                ) / (2 * dx);

        // Boundary
        temperatures[0] = (1 - 2 * r) * temperatures[0] + 2 * r * temperatures[1]
                + 2 * dx * r * exp(t);


        // Interior
        for (int i = 1; i < nTemperatures - 1; i++) {

            double du = ((temperatures[i + 1] - prev_u) * i * ds) / (2 * s)
                + (temperatures[i + 1] - 2 * temperatures[i] + prev_u) * r;

            // Update temperatures
            prev_u = temperatures[i];
            temperatures[i] += du;
        }



        // Check condition for stability
        if (dt > (2 * dx2) / (4 + (dx2 * ds * ds)/(dt * dt))) {
            fprintf(stderr, "ERROR: Condition for stability not fulfilled.\n");
            return EXIT_FAILURE;
        }

        // Integrate
        ds = next_ds;
        s += ds;
        t += dt;
    }


    // Print and clean up
    printCsv(temperatures, nTemperatures, s);
    free(temperatures);

    return EXIT_SUCCESS;
}
