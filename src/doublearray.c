#include "doublearray.h"
#include "error.h"
#include <stdlib.h>

double ** doublearray_create(unsigned n_columns, unsigned n_values) {
	double ** array = malloc(sizeof(double *) * (1 + n_columns));

	//TODO: Copy out
	if (array == NULL) {
		error_fatal("Could not allocate memory for double array");
	}

	for (unsigned i = 0; i < n_columns; i++) {
		array[i] = malloc(sizeof(double *) * n_values);

		if (array[i] == NULL) {
			error_fatal("Could not allocate memory for double array");
		}
	}

    array[n_columns] = NULL;

	return array;
}

void doublearray_destroy(doublearray_t array) {

    for (unsigned i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }

    free(array);
}


void doublearray_resize(doublearray_t array, unsigned n_values) {
    for (unsigned i = 0; array[i] != NULL; i++) {
		array[i] = realloc(array[i], n_values);
        
        if (array[i] == NULL) {
            error_fatal("Failed to allocate more memory for dobule array");
        }
	}
}

