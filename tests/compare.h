#pragma once

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
