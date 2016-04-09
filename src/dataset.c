#include <math.h>
#include "dataset.h"

double dataset_interpolate(dataset_t * dataset, double position) {

    // Extrapolation if necessary
    if (position <= dataset->start) {
        return dataset->values[0];
    }

    if (position >= dataset->end) {
        return dataset->values[dataset->n_values - 1];
    }

    // Interpolation
    double relative_position = (dataset->n_values - 1) *
        (position - dataset->start)/(dataset->end - dataset->start);

    double weight = relative_position - floor(relative_position);

    return (1 - weight) * dataset->values[(int) floor(relative_position)]
        + weight * dataset->values[(int) ceil(relative_position)];
}
