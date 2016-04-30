#include "phase.h"
#include "error.h"
#include "interpolate.h"

#define SMALL_VALUE 0.0001



void phase_update(border_t * a, border_t * b, double * u, material_t * material) {

    double alpha = material->alpha;
    double kappa = material->kappa;
    double du, prev_u;

    unsigned i = a->position + 1,
             end = b->position;

    double
        a_f = 1.0 - (a->position - i),
        b_f = b->position - end;


    // Handle edge case
    if (a_f < SMALL_VALUE) {
        a_f += 1.0;
        i++;
    }

    if (b_f < SMALL_VALUE) {
        end--;
        b_f += 1.0;
    }

    // Sanity check
    if (end - i < 1) {
        error_fatal("Phase contains two few points");
    }

    // ----- Left border -----

    // Update border value
    prev_u = a->u[1];
    a->u[1] += alpha * (
            a_f * a->q[1] / kappa +
            2 * a->u[1] +
            2 * u[i]
        ) / (a_f * a_f);

    if (a_f >= 1.0) {
        u[i - 1] = a->u[1];
    }


    // Interpolate for near-border point
    du = alpha * interpolate_sd(
            a_f,
            prev_u,
            u[i],
            u[i + 1]
        );

    prev_u = u[i];
    u[i] += du;

    i++;

    // We may want to stop a little before


    // ---- Interior -----
	while (i < end) {

		du = alpha * (u[i - 1] - 2.0 * u[i] + u[i + 1]);

		// Update u
		prev_u = u[i];
		u[i] += du;

        i++;
	}


    // ------ Right border ------

    // Interpolate for near-border point
    du = alpha * interpolate_sd(
            b_f,
            prev_u,
            u[i],
            b->u[0]
        );

    prev_u = u[i];
    u[i] += du;

    // Update border value
    b->u[0] += alpha * (
            2 * prev_u +
            2 * b->u[0] +
            b_f * (- b->q[0]) / kappa
        ) / (b_f * b_f);


    if (b_f >= 1.0) {
        u[i + 1] = b->u[0];
    }

}


