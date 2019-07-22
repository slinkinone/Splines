#include "basic_functions.h"

#include <float.h>  // DBL_MAX

extremum find_extremum(const point* points, const size_t n_points,
                     extremum_targer extr_target)
{
    double x_min = DBL_MAX, y_min = DBL_MAX;
    double x_max = -DBL_MAX, y_max = -DBL_MAX;

    for(size_t i = 0; i < n_points; ++i)
    {
        if(points[i].x > x_max)
            x_max = points[i].x;

        if(points[i].x < x_min)
            x_min = points[i].x;

        if(points[i].y > y_max)
            y_max = points[i].y;

        if(points[i].y < y_min)
            y_min = points[i].y;
    }

    switch (extr_target)
    {
        case X: return (extremum){x_min, x_max};
        case Y: return (extremum){y_min, y_max};

        default:
            return (extremum){-DBL_MAX, DBL_MAX};

    }
}

int tridiagonal_matrix_algorithm(const point* points, const size_t n_points,
                                    spline** splines, const size_t n_splines)
{
    if( (n_points == 0) || (n_splines < n_points - 1) )
        return -1;

    // forward

    double *alpha = (double*)malloc( (n_points - 1) * sizeof(double) );
    double *beta = (double*)malloc( (n_points - 1) * sizeof(double) );
    double a = 0.0, b = 0.0, c = 0.0, f = 0.0, z = 0.0;

    alpha[0] = beta[0] = 0.;
    for (size_t i = 1; i < n_points - 1; ++i)
    {
        a = points[i].x - points[i - 1].x;
        b = points[i + 1].x - points[i].x;
        c = 2. * (a + b);
        f = 6. * ((points[i + 1].y - points[i].y) / b - (points[i].y - points[i - 1].y) / a);
        z = (a * alpha[i - 1] + c);
        alpha[i] = -b / z;
        beta[i] = (f - a * beta[i - 1]) / z;
    }

    (*splines)[n_points - 1].c = (f - a * beta[n_points - 2]) / (c + a * alpha[n_points - 2]);

    // backward
    for (size_t i = n_points - 2; i > 0; --i)
        (*splines)[i].c = alpha[i] * (*splines)[i + 1].c + beta[i];

    free(beta);
    free(alpha);
    return 0;
}
