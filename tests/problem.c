
#include <tinytest/tinytest.h>
#include "../src/problem.c"

/**
 * Tests the problem module.
 */


// MOCK FUNCTIONS
void error_fatal(char * m) {};
void error_warning(char * m) {};
void phase_update(border_t * a, border_t * b, double * u, material_t * material) {};

#include "../src/interpolate.c"


/**
 * Small utility function for comparing doubles.
 *
 * @param a First double
 * @param b Other double
 * @return True if a is approximately equal to b
 */
#define SMALL_VALUE 0.0001

char double_equal(double a, double b) {
	return a < b + SMALL_VALUE && a > b - SMALL_VALUE;
}



void test_move_border() {

    problem_t p;
    p.resolution = 10;
    p.temperatures = malloc(sizeof(double) * p.resolution);

    for (unsigned i = 0; i < p.resolution; i++) {
        p.temperatures[i] = i;
    }

    p.borders[1].position = 5.4;
    p.borders[1].u[0] = 7.0;

    // Move border sligtly
    move_border(&p, 1, 0.1);

    ASSERT(
        "Nearby temperatures should be unchanged",
        double_equal(p.temperatures[5], 5.0) &&
        double_equal(p.temperatures[6], 6.0)
    );

    ASSERT(
        "Border position should have been updated",
        double_equal(p.borders[1].position, 5.5)
    );

    // Move border on top of point
    move_border(&p, 1, 0.5);

    ASSERT(
        "Value of point should have been interpolated",
        double_equal(p.borders[1].u[0], p.temperatures[6])
    );


    // Move border across next point
    move_border(&p, 1, 0.5);
    move_border(&p, 1, 0.7);

    ASSERT(
        "Correct value interpolated",
        double_equal(p.temperatures[7], 79.0/11.0)
    );
}


int main(int argc, char ** argv) {

	RUN(test_move_border);

	return TEST_REPORT();
}
