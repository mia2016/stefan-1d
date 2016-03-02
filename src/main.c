#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argv, char ** argc) {

    int nTemperatures = 10;
    double endTime = 0.01;
    double dt = 0.001;
    double s = 1.0;
    double ds = 0.0;
    double initialTemperature = 1.0;

    // Create an fill array of temperatures
    double * temperatures = malloc(sizeof(double) * nTemperatures);

    for (int i = 0; i < nTemperatures; i++) {
        temperatures[i] = initialTemperature;
    }

    // Print header for csv output
    printf("t");
    for (int i = 0; i < nTemperatures; i++) {
        printf(", u[%i]", i);
    }
    printf(", s\n");

    // Step forward in time
    for (double t = 0.0; t < endTime; t += dt) {
        double h = s / nTemperatures;
        double r = dt / (h * h);

        // Cache previous temperature thorugh the loop
        double prev_u = temperatures[0];

        // Boundary
        temperatures[0] = (1 - 2 * r) + 2 * r * temperatures[1]
                + (2 * r * h) * exp(t);


        // Interior
        for (int i = 1; i < nTemperatures; i++) {

            double du = ((temperatures[i + 1] - prev_u) * dt * ds * i)
                    / (2 * s * dt)
                + (
                    temperatures[i + 1]
                    - 2 * temperatures[i]
                    + prev_u
                ) * r;

            // Update temperatures
            prev_u = temperatures[i];
            temperatures[i] += du;
        }


        // Update boundary position
        double ds = -(
                    dt * nTemperatures * (
                        3 * temperatures[nTemperatures - 1]
                        -4 * temperatures[nTemperatures - 2]
                       + temperatures[nTemperatures - 3]
                    )
                ) / (2 * s);

        s += ds;

        // Check condition for stability
        if (dt > (2 * h * h) / (4 + (h * ds * ds)/(dt * dt))) {
            fprintf(stderr, "WARNING: Condition for stability not fulfilled.\n");
        }

        // Print temperatures
        printf("%f", t);
        for (int i = 0; i < nTemperatures; i++) {
            printf(", %f", temperatures[i]);
        }
        printf(", %f\n", s);
    }

    // Clean up and return
    free(temperatures);
    return 0;
}
