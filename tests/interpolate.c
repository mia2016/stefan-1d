#include <tinytest/tinytest.h>
#include "../src/interpolate.c"

/**
 * Tests the problem module.
 */


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


void test_interpolate_value() {

	point_t
		a = {0.0, 0.0},
		b = {1.0, 1.0},
		c = {2.0, 2.0},
		d = {2.0, 0.0};

	double r[4];
	for (unsigned i = 0; i < 4; i++) {
		r[i] = interpolate_value(a, b, c, i);
	}

	ASSERT(
		"Should handle linear interpolation one step ahead",
		double_equal(r[3], 3.0)
	);

	ASSERT(
		"Given points should return their values",
		double_equal(r[0], a.y) &&
		double_equal(r[1], b.y) &&
		double_equal(r[2], c.y)
	);

	ASSERT(
		"Should do second order interpolation",
		double_equal(
			interpolate_value(a, b, d, 3.0),
			-3.0
		)
	);

}


void test_interpolate_sd() {

    ASSERT(
        "Gives 0 for linear points",
        double_equal(interpolate_sd(1.0, 2.0, 3.0, 4.0), 0.0)
    );

    ASSERT(
        "Is positive when smiling",
        interpolate_sd(1.0, 4.0, 3.0, 4.0) > 0.0
    );

    ASSERT(
        "Is negative when frowning",
        interpolate_sd(1.0, 1.0, 3.0, 1.0) < 0.0
    );

    ASSERT(
        "Handles a couple of examples",
        double_equal(interpolate_sd(1.0, 1.0, 2.0, 2.0), -1.0) &&
        double_equal(interpolate_sd(1.0, 3.0, 2.0, 2.0), 1.0)
    );

    ASSERT(
        "Gives right result at other distances",
        double_equal(interpolate_sd(0.5, 3.0, 2.0, 2.0), 8.0/3.0) &&
        double_equal(interpolate_sd(0.5, 0.0, 1.0, 1.0), -8.0/3.0)
    );


}


int main(int argc, char ** argv) {

	RUN(test_interpolate_value);
    RUN(test_interpolate_sd);

	return TEST_REPORT();
}

