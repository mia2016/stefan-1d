#include "interpolate.h"

double interpolate_sd(double d, double u1, double u2, double u3) {
	return 2 * (
            u3 / (1.0 + d)
            - u2 / d
            + u1 / (d * (1.0 + d))
        );
}

double interpolate_value(point_t a, point_t b, point_t c, double x) {
	return (a.y * (x - b.x) * (x - c.x)) / ((a.x - b.x) * (a.x - c.x))
		+ (b.y * (x - a.x) * (x - c.x)) / ((b.x - a.x) * (b.x - c.x))
		+ (c.y * (x - b.x) * (x - a.x)) / ((c.x - b.x) * (c.x - a.x));
}
