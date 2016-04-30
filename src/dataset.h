#pragma once
#include <stdio.h>

/**
 * A set of points, evenly distributed along one dimension.
 * It may be used to e.g. represent a sequence of temperature measurements.
 */
typedef struct {
    double start;
    double end;
    double ** columns;
    unsigned int n_values;
} dataset_t;


/**
 * Destroy a dataset and free its resources.
 *
 * @param dataset Pointer to dataset which should be destroyed
 */
void dataset_destroy(dataset_t * dataset);


/**
 * Uses linear interpolation to find a value not present in the dataset.
 *
 * @param dataset Dataset to gather information from
 * @param column Column to find value in
 * @param position The position to find the (interpolated) value for.
 * @return Interpolated value
 */
double dataset_interpolate(dataset_t * dataset, unsigned column, double position);


/**
 * Read a dataset from a stream.
 * The dataset is expected to be a list of values separated by spaces.
 *
 * @param file File stream to read from
 * @param n_columns Number of columns to read
 * @return Dataset with data from file
 */
dataset_t * dataset_read(FILE * stream, unsigned n_columns);
