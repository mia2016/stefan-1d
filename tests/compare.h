#pragma once

#define SMALL_VALUE 0.0001


/**
 * Small utility function for comparing doubles.
 *
 * @param a First double
 * @param b Other double
 * @return True if a is approximately equal to b
 */
char double_equal(double a, double b) {
	return a < b + SMALL_VALUE && a > b - SMALL_VALUE;
}


/**
 * Small utility function checking whether two doubles are within an error
 * margin from each other.
 *
 * @param a First double
 * @param b Other double
 * @param e Max error
 * @return True if abs(a-b) < e
 */
char double_approx_equal(double a, double b, double e) {
	return abs(a - b) < e;
}
