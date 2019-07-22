#ifndef SPLINES_H
#define SPLINES_H

#include <stdlib.h>
#include "basic_structs.h"

//  in_points must be sorted
int akima_spline(const point* in_points, const size_t n_in_points, double step,
                  point** out_points, size_t* n_out_points);

int cubic_spline(const point* in_points, const size_t n_in_points, double step,
                  point** out_points, size_t* n_out_points);

#endif // SPLINES_H
