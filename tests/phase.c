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



void fill_array(unsigned nu, double * u, double v) {
	for (unsigned i = 0; i < nu; i++) {
		u[i] = 0.0;
	}
}



void test_basic_diffusion() {

	// Create an array of temperatures with a spike in the middle
	double u[100];
	fill_array(100, u, 0.0);
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


void test_near_borders() {

	// Create an array of temperatures...
	double u[100];
	fill_array(100, u, 0.0);

	// Create borders
	border_t a = {10.5, {0.0, 100.0}, {0.0}},
			 b = {20.5, {100.0, 0.0}, {0.0}};


	// Run an iteration
	phase_update(&a, &b, u, &material);



	ASSERT(
		"Temperatures spread correctly near borders",
		double_equal(u[11], 800.0/3.0) &&
		double_equal(u[20], 800.0/3.0)
	);

	ASSERT(
		"No other temperatures changed",
		double_equal(u[10], 0.0) &&
		double_equal(u[12], 0.0) &&
		double_equal(u[19], 0.0) &&
		double_equal(u[21], 0.0)
	);


	// Reset border temperatures and do second iteration
	a.u[1] = 100.0;
	b.u[0] = 100.0;

	phase_update(&a, &b, u, &material);


	ASSERT(
		"Temperatures spread correctly near borders",
		double_equal(u[11], -1600.0/3.0) &&
		double_equal(u[20], -1600.0/3.0)
	);

	ASSERT(
		"No other temperatures changed",
		double_equal(u[10], 0.0) &&
		double_equal(u[13], 0.0) &&
		double_equal(u[18], 0.0) &&
		double_equal(u[21], 0.0)
	);

}


void test_border_temperatures() {

	// Create an array of temperatures...
	double u[100];
	fill_array(100, u, 0.0);

	// Create borders
	border_t a = {10.5, {0.0, 0.0}, {0.0}},
			 b = {20.5, {0.0, 0.0}, {0.0}};


	// Run an iteration
	phase_update(&a, &b, u, &material);


	ASSERT(
		"Temperatures not changed",
		double_equal(a.u[1], 0.0) &&
		double_equal(b.u[0], 0.0)
	);


	// Set temperatures to something else and run an iteration
	a.u[1] = 100.0;
	b.u[0] = 100.0;
	phase_update(&a, &b, u, &material);

	ASSERT(
		"Border temperatures updated correctly",
		double_equal(a.u[1], -700) &&
		double_equal(b.u[0], -700)
	);


	// Set the temperatures in nearby points
	u[11] = 100;
	u[20] = 100;

	// Run another iteration
	phase_update(&a, &b, u, &material);

	ASSERT(
		"Border temperatures updated correctly",
		double_equal(a.u[1], 5700.0) &&
		double_equal(b.u[0], 5700.0)
	);
}


void test_on_border_edge_case() {

	// Create an array of temperatures...
	double u[50];
	fill_array(50, u, 0.0);

	// Create borders
	border_t a = {10.0, {0.0, 100.0}, {0.0}},
			 b = {20.0, {100.0, 0.0}, {0.0}};


	// Run an iteration
	phase_update(&a, &b, u, &material);


	ASSERT(
		"Correct temperatures for near-border points",
		double_equal(u[11], 100.0) &&
		double_equal(u[19], 100.0)
	);


	// Try again with a slighly different position
	fill_array(50, u, 0.0);
	a.position = 10.0 - SMALL_VALUE / 100.0;
	a.u[1] = 100.0;
	b.u[0] = 100.0;

	phase_update(&a, &b, u, &material);

	ASSERT(
		"Temperatures have been updated correctly",
		double_approx_equal(u[11], 100.0, 0.01) &&
		double_equal(u[19], 100.0)
	);


	// Try again, but now with the other border.
	fill_array(50, u, 0.0);
	a.position = 10.0;
	b.position = 20.0 + SMALL_VALUE / 100.0;
	a.u[1] = 100.0;
	b.u[0] = 100.0;

	phase_update(&a, &b, u, &material);

	ASSERT(
		"Temperatures have been updated correctly",
		double_equal(u[11], 100.0) &&
		double_approx_equal(u[19], 100.0, 0.01)
	);
}


int main(int argc, char ** argv) {

	RUN(test_basic_diffusion);
	RUN(test_near_borders);
	RUN(test_border_temperatures);
	RUN(test_on_border_edge_case);

	return TEST_REPORT();
}
