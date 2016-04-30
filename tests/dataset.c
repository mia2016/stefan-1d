#include <tinytest/tinytest.h>
#include "../src/dataset.c"
#include "compare.h"

/**
 * Test dataset module
 */

// Mock function...
void error_fatal(char * w) {
	printf("%s", w);
	exit(EXIT_FAILURE);
};
#include "../src/doublearray.c"


void test_dataset() {

	// Create file with data
	FILE * file = tmpfile();
	fprintf(file, "100.0 300.0\n1 10 20\n2 20 40\n3 25 20\n4 20 20\n5 100 100\n");
	rewind(file);

	// Read file as dataset
	dataset_t * dataset = dataset_read(file, 3);

	ASSERT(
		"Should have read correct start and end values",
		double_equal(dataset->start, 100.0) &&
		double_equal(dataset->end, 300.0)
	);

	ASSERT(
		"Should have read correct data for column 1",
		double_equal(dataset->columns[0][0], 1.0) &&
		double_equal(dataset->columns[0][1], 2.0) &&
		double_equal(dataset->columns[0][2], 3.0) &&
		double_equal(dataset->columns[0][3], 4.0) &&
		double_equal(dataset->columns[0][4], 5.0)
	);

	ASSERT(
		"Should have read correct data for column 2",
		double_equal(dataset->columns[1][0], 10.0) &&
		double_equal(dataset->columns[1][1], 20.0) &&
		double_equal(dataset->columns[1][2], 25.0) &&
		double_equal(dataset->columns[1][3], 20.0) &&
		double_equal(dataset->columns[1][4], 100.0)
	);


	ASSERT(
		"Should have read correct data for column 3",
		double_equal(dataset->columns[2][0], 20.0) &&
		double_equal(dataset->columns[2][1], 40.0) &&
		double_equal(dataset->columns[2][2], 20.0) &&
		double_equal(dataset->columns[2][3], 20.0) &&
		double_equal(dataset->columns[2][4], 100.0)
	);


	// Test interpolation part
	ASSERT(
		"Selects correct point from data when interpolating",
		double_equal(dataset_interpolate(dataset, 0, 100), 1.0) &&
		double_equal(dataset_interpolate(dataset, 0, 150), 2.0) &&
		double_equal(dataset_interpolate(dataset, 0, 200), 3.0) &&
		double_equal(dataset_interpolate(dataset, 0, 250), 4.0) &&
		double_equal(dataset_interpolate(dataset, 0, 300), 5.0)
	);


	ASSERT(
		"Correcly interpolates between points",
		double_equal(dataset_interpolate(dataset, 0, 125), 1.5) &&
		double_equal(dataset_interpolate(dataset, 0, 175), 2.5) &&
		double_equal(dataset_interpolate(dataset, 0, 225), 3.5) &&
		double_equal(dataset_interpolate(dataset, 0, 275), 4.5)
	);

	ASSERT(
		"Interpolates correctly for other columns as well",
		double_equal(dataset_interpolate(dataset, 1, 125), 15) &&
		double_equal(dataset_interpolate(dataset, 2, 125), 30)
	);


}


int main(int argc, char ** argv) {

	RUN(test_dataset);

	return TEST_REPORT();
}
