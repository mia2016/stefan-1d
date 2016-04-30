#include <tinytest/tinytest.h>
#include "../src/phase.c"
#include "compare.h"

/**
 * Test phase module
 */

// Mock required functions...
void error_fatal(char * m) {};
#include "../src/interpolate.c"

// Mock material....
material_t material = {
	.alpha = 1.0,
	.rho = 1.0,
	.L = 1.0,
	.kappa = 1.0
};




void test_basic_diffusion() {

	// Create an array of temperatures with a spike in the middle
	double u[100];

	for (unsigned i = 0; i < 100; i++) {
		u[i] = 0.0;
	}

	u[50] = 100.0;


	// Create borders
	border_t a = {0.0, {0.0}, {0.0}},
			 b = {99.0, {0.0}, {0.0}};


	// Run an iteration
	phase_update(&a, &b, u, &material);


	// Check temperatures
	ASSERT(
		"Should not change unrelated temperatures",
		double_equal(u[25], 0.0) &&
		double_equal(u[75], 0.0) &&
		double_equal(u[48], 0.0) &&
		double_equal(u[52], 0.0)
	);

	ASSERT(
		"Spreads temperature in accordance with the numeric heat equation",
		double_equal(u[49], 100.0) &&
		double_equal(u[50], -100.0) &&
		double_equal(u[51], 100.0)
	);


	// Run another iteration!
	phase_update(&a, &b, u, &material);

	ASSERT(
		"Should not change unrelated temperatures",
		double_equal(u[25], 0.0) &&
		double_equal(u[75], 0.0) &&
		double_equal(u[47], 0.0) &&
		double_equal(u[53], 0.0)
	);

	ASSERT(
		"Spreads temperature in accordance with the numeric heat equation",
		double_equal(u[48], 100.0) &&
		double_equal(u[49], -200.0) &&
		double_equal(u[50], 300.0) &&
		double_equal(u[51], -200.0) &&
		double_equal(u[52], 100.0)
	);

}



int main(int argc, char ** argv) {

	RUN(test_basic_diffusion);

	return TEST_REPORT();
}
