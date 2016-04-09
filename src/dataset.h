/**
 * A set of points, evenly distributed along one dimension.
 * It may be used to e.g. represent a sequence of temperature measurements.
 */
typedef struct {
    double start;
    double end;
    double * values;
    unsigned int n_values;
} dataset_t;


/**
 * Uses linear interpolation to find a value not present in the dataset.
 *
 * @param position The position to find the (interpolated) value for.
 * @return Interpolated value
 */
double dataset_interpolate(dataset_t * dataset, double position);
