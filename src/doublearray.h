#pragma once

typedef double ** doublearray_t;

/**
 * Allocate a 2D double array.
 *
 * @param columns Number of columns
 * @param values Number of values in each column
 * @return Pointer to array of columns
 */
doublearray_t doublearray_create(unsigned n_columns, unsigned n_values);

/**
 * Destroy a 2D double array and free its resources.
 *
 * @param array Pointer to double array
 * @param n_columns Number of columns in array
 */
void doublearray_destroy(doublearray_t array);


/**
 * Resize a 2D double array to the given dimentions.
 * Note that the column count cannot be changed.
 *
 * @param array Pointer to array of arrays
 * @param n_columns Number of columns in the given array (before resize)
 * @param n_values Number of values after resize
 */
void doublearray_resize(
		doublearray_t array,
		unsigned n_values
	);

