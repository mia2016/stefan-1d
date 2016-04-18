#pragma once
#include "material.h"

/**
 * A phase is defined by its two borders.
 */
typedef struct {

    // Position of border
    double position;

    // Temperature on each side of border
    double u[2];

    // Heat flow across border
    double q;

} border_t;


/**
 * Calculates the next iterations of the values for the given phase.
 *
 * @param a First border. The right temperature will be updated.
 * @param b Second border. The left temperature will be updated.
 * @param u Array of temperatures to update
 * @param material Pointer to material
 */
void phase_update(border_t * a, border_t * b, double * u, material_t * material);
