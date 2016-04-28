#pragma once

//TODO document or unused?
typedef struct {
	double x, y;
} point_t;


/**
 * Calculates an approximation to the second derivative using lagrange
 * interpolation.
 *
 * The two first points are expected to be d units apart, while the two last
 * points are expected to be 1 unit apart. Something like:
 * 
 *  u1    u2      u3
 *  |-----|--------|
 *     d      1
 *
 * @param u1 First function value
 * @param u2 Second function value
 * @param u3 Third function value
 * @param d Distance between the two first points
 * @return Approximation to the second derivative
 */
double interpolate_sd(double d, double u1, double u2, double u3);


/**
 * Calculates the interpolated value of a point x given three other points.
 * TODO: Is this used anywhere?
 *
 * @param a Point 1
 * @param b Point 2
 * @param c Point 3
 * @param x Point at which to calculate interpolated value
 * @return Interpolated value
 */
double interpolate_value(point_t a, point_t b, point_t c, double x);


/**
 * Calculates the next value in a set of equally spaced points using langrange
 * interpolation.
 *
 *  p1    p2    p3    p4
 *   |-----|-----|-----|
 *      d     d     d
 *
 * @param a Value at point 1
 * @param b Value at point 2
 * @param c Value at point 3
 * @return Value at point 4
 */
double interpolate_next(double a, double b, double c);
