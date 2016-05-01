#include <math.h>
#include <stdlib.h>
#include "doublearray.h"
#include "dataset.h"
#include "error.h"


double dataset_interpolate(dataset_t * dataset, unsigned column, double position) {

	double * values = dataset->columns[column];

    // Extrapolation if necessary
    if (position <= dataset->start) {
        return values[0];
    }

    if (position >= dataset->end) {
        return values[dataset->n_values - 1];
    }

    // Interpolation
    double relative_position = (dataset->n_values - 1) *
        (position - dataset->start)/(dataset->end - dataset->start);

    double weight = relative_position - floor(relative_position);

    return (1 - weight) * values[(unsigned) floor(relative_position)]
        + weight * values[(unsigned) ceil(relative_position)];
}


dataset_t * dataset_create(unsigned n_columns) {

	dataset_t * dataset = malloc(sizeof(dataset_t));

	dataset->n_values = 1;
	dataset->start = 0.0;
	dataset->end = 1.0;

	dataset->columns = doublearray_create(n_columns, dataset->n_values);

	for (unsigned i = 0; i < n_columns; i++) {
		dataset->columns[i][0] = 1.0;
	}

	return dataset;
}

dataset_t * dataset_read(FILE * stream, unsigned n_columns) {

	dataset_t * dataset = malloc(sizeof(dataset_t));

	if (dataset == NULL) {
		error_fatal("Could not allocate memory for dataset");
	}

	// Read start and end
	unsigned values_read = fscanf(
			stream,
			"%lf %lf",
			&dataset->start,
			&dataset->end
		);


	if (!values_read) {
		error_fatal("Dataset file must contain start and end values");
	}


	// Read the rest
	char isDone = 0;
	unsigned n_allocated = 16;
	int n_values = -1;
	dataset->columns = doublearray_create(n_columns, n_allocated);
	dataset->n_values = 0;

	while (!isDone) {
		n_values++;

		// Check whether our arrays of values are big enough
		if (n_allocated == n_values) {
			n_allocated *= 2;
			doublearray_resize(dataset->columns, n_allocated);
		}

		// Read each column
		for (unsigned column = 0; column < n_columns; column++) {
			double value;
			int value_read = fscanf(stream, "%lf", &value);
			
			if (value_read != 1) {
				// Are we in the middle of a line?
				if (column > 0) {
					error_fatal("Not enough values in datafile");
				}

				isDone = 1;
				break;
			}

			dataset->columns[column][n_values] = value;
		}
	}


	// Resize arrays to fit
	doublearray_resize(dataset->columns, n_values);

	dataset->n_values = n_values;
	return dataset;
}
