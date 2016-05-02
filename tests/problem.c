#include <tinytest/tinytest.h>
#include "../src/problem.c"
#include "compare.h"


/**
 * Tests the problem module.
 */


// MOCK FUNCTIONS
void error_fatal(char * m) {};
void error_warning(char * m) {};
void phase_update(border_t * a, border_t * b, double * u, material_t * material) {};
constants get_constants() {return (constants) {0.0};};
#include "../src/interpolate.c"


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


void test_move_last_border() {
    problem_t p;
    p.resolution = 10;
    p.temperatures = malloc(sizeof(double) * p.resolution);

    for (unsigned i = 0; i < p.resolution; i++) {
        p.temperatures[i] = i;
    }

    p.borders[2].position = 5.4;
    p.borders[2].u[0] = 7.0;

    // Move border sligtly
    move_border(&p, 2, -0.6);

    ASSERT(
        "Outside point should have temperature 0",
        double_equal(p.temperatures[5], 0.0)
    );
}


int main(int argc, char ** argv) {

	RUN(test_move_border);
	RUN(test_move_last_border);

	return TEST_REPORT();
}
