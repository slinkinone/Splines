#ifndef BASIC_FUNCTIONS_H
#define BASIC_FUNCTIONS_H

#include <stdlib.h>
#include "basic_structs.h"

int tridiagonal_matrix_algorithm(const struct point* points, const size_t n_points,
                                  struct spline** splines, const size_t n_splines);

extremum find_extremum(const struct point* points, const size_t n_points,
                     extremum_targer extr_target);

#endif // BASIC_FUNCTIONS_H
