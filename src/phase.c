#include "phase.h"
#include "error.h"
#include "interpolate.h"

#define SMALL_VALUE 0.0001


/**
 * Calculates the heat equation.
 * Assuming dx = 1 and dt = 1.
 *
 * @param ul Temperature in point to the left
 * @param u Temperature in point to calculate
 * @param ur Temperature in point to the right
 * @param a Materials thermal diffusivity
 * @return Approximation of heat equation for the given point
 */
static inline double heat_equation(double a, double ul, double u, double ur) {
    return a * (ul - 2.0 * u + ur) + u;
}

/**
 * Same as above, but with a custom dx.
 * TODO
 */
static inline double a_heat_equation(double a, double ul, double u, double ur, double dx) {
    return a * (ul - 2.0 * u + ur) / (dx * dx) + u;
}


void phase_update(border_t * a, border_t * b, double * u, material_t * material) {

    if ((int) b->position - (int) a->position < 2) {
        error_fatal("Phase two small (less than two points)");
    }

    double alpha = material->alpha;
    double kappa = material->kappa;

    double prev_u = a->u[1];
    double du;

    // Split border positions into integer and fractional parts (TODO: improve)
    unsigned end_points[] = {a->position + 1, b->position}; //TODO: Use pointers?


    double
        //TODO: Better names (array?)
        a_f = 1.0 - (a->position - end_points[0]),
        b_f = b->position - end_points[1];


    // Calculate next border temperatures
    if (a_f < SMALL_VALUE) {
        // Use regular heat equation
        a->u[1] = heat_equation(
                alpha,
                a->q / kappa,
                2 * a->u[1],
                2 * u[end_points[0]]
            );

        // a->u and u[end_points[0]] are the same point
        prev_u = u[end_points[0]];
        u[end_points[0]] = a->u[1];

        end_points[0]++;

    } else {
        // Use special heat equation with dx = a_f
        a->u[1] = a_heat_equation(
                alpha,
                a_f * a->q / kappa,
                a->u[1],
                u[end_points[0]],
                a_f
            );

    }

    // Interpolate for near-border point
    du = alpha * interpolate_sd(
            a_f,
            prev_u,
            u[end_points[0]],
            u[end_points[0] + 1]
        );

    prev_u = u[end_points[0]];
    u[end_points[0]] += du;

    // We may want to stop a little before
    if(b_f < SMALL_VALUE) {
        end_points[1]--;
    }

    // Handle interior
	for (unsigned i = end_points[0] + 1; i < end_points[1]; i++) {

        //TODO: Simplify (-u[i] is not really required because it is added ^)
		du = heat_equation(alpha, u[i - 1], u[i], u[i + 1]) - u[i];

		// Update u
		prev_u = u[i];
		u[i] += du;
	}

    // Interpolate for near-border point
    du = alpha * interpolate_sd(
            a_f,
            prev_u,
            u[end_points[1]],
            b->u[0]
        );

    prev_u = u[end_points[1]];
    u[end_points[1]] += du;


    if (b_f < SMALL_VALUE) {
        // Use regular heat equation
        b->u[0] = heat_equation(
                alpha,
                2 * u[end_points[1] + 1],
                2 * b->u[0],
                b->q / kappa
            );

        // b->u and u[end_points[0]] are the same point
        prev_u = u[end_points[1] + 1];
        u[end_points[1] + 1] = b->u[0];

    } else {
        // Use special heat equation with dx = b_f
        b->u[1] = a_heat_equation(
                alpha,
                prev_u,
                b->u[0],
                b_f * b->q / kappa,
                b_f
            );
    }
}


