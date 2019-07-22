#include "splines.h"

#include <math.h>
#include <float.h>  // DBL_MAX

#include "basic_functions.h"

double akima_function(const double x, spline* splines, const size_t n_splines)
{
    if (!splines)
        goto exit;

    spline* s = NULL;

    for(size_t i = 0; i < n_splines; ++i)
        if(x >= splines[i].x)
            s = splines + i;

    if(!s)
        goto exit;

    double dx = (x - s->x);
    return s->a + (s->b * dx) + (s->c * pow(dx, 2.0) ) + (s->d * pow(dx, 3.0) );

exit:
    return DBL_MAX;
}

int akima_spline(const point* in_points, const size_t n_in_points, double step,
                  point** out_points, size_t* n_out_points)
{
    if(n_in_points < 3)
        return -1;

    double m[n_in_points + 3];
    double difX[n_in_points - 1], difY[n_in_points - 1];
    double t[n_in_points];

    // spline initialization
    size_t n_splines = (n_in_points - 1);
    spline* splines = (spline*)malloc( n_splines * sizeof(spline) );

    splines[n_in_points - 2].x = in_points[n_in_points - 1].x;
    splines[n_in_points - 2].a = in_points[n_in_points - 1].y;

    for (size_t i = 0; i < n_in_points - 1; ++i)
    {
        splines[i].x = in_points[i].x;
        splines[i].a = in_points[i].y;
        difX[i] = in_points[i + 1].x - in_points[i].x;
        difY[i] = in_points[i + 1].y - in_points[i].y;
    }

    for(size_t i = 2; i < n_in_points + 1; ++i)
        m[i] = difY[i - 2] / difX[i - 2];

    m[1] = 2 * m[2] - m[3];
    m[0] = 2 * m[1] - m[2];
    m[n_in_points + 1] = 2 * m[n_in_points] - m[n_in_points - 1];
    m[n_in_points + 2] = 2 * m[n_in_points + 1] - m[n_in_points];

    for(size_t i = 2; i < n_in_points + 2; ++i)
        t[i - 2] = (abs(m[i + 1]-m[i])*m[i - 1] + abs(m[i - 1] - m[i - 2])*m[i]) /
                (abs(m[i + 1] - m[i]) + abs(m[i - 1] - m[i - 2]));

    for(size_t i = 0; i < n_in_points - 1; ++i)
    {
        splines[i].b = t[i];
        splines[i].c = (3*m[i + 2] - 2*t[i] - t[i + 1]) / difX[i];
        splines[i].d = (t[i] + t[i + 1] - 2*m[i + 2]) / pow(difX[i], 2.0);
    }

    extremum extr = find_extremum(in_points, n_in_points, X);
    (*n_out_points) = (abs(extr.min) + abs(extr.max)) / step + 1;
    *out_points = (point*)malloc( (*n_out_points) * sizeof(point));

    double iter = extr.min;
    size_t index = 0;
    while(iter <= extr.max && index < *n_out_points)
    {
        (*out_points)[index] = (point){iter, akima_function(iter, splines, n_splines)};
        ++index;
        iter += step;
    }

    free(splines);
    return 0;
}

double cubic_function(const double x, spline* splines, const size_t n_splines)
{
    if (!splines)
        goto exit;

    spline* s = NULL;

    if (x <= splines[0].x)
    {
            s = splines + 1;
    }
    else
    {
        if (x >= splines[n_splines - 1].x)
        {
            s = splines + n_splines - 1;
        }
        else
        {
            size_t i = 0;
            size_t j = n_splines - 1;
            while (i + 1 < j)
            {
                size_t k = i + (j - i) / 2;
                if (x <= splines[k].x)
                    j = k;
                else
                    i = k;
            }
            s = splines + j;
        }
    }

    double dx = (x - s->x);
    return s->a + (s->b + (s->c / 2. + s->d * dx / 6.) * dx) * dx;

exit:
    return DBL_MAX;
}


int cubic_spline(const point* in_points, const size_t n_in_points, double step,
                  point** out_points, size_t* n_out_points)
{
    // spline initialization
    size_t n_splines = (n_in_points);
    spline* splines = (spline*)malloc( n_splines * sizeof(spline) );

    for (size_t i = 0; i < n_in_points; i++)
    {
        splines[i].x = in_points[i].x;
        splines[i].a = in_points[i].y;
    }
    splines[0].c = 0.;

    tridiagonal_matrix_algorithm(in_points, n_in_points, &splines, n_splines);

    // finding b[i] and d[i] by c[i]
    for (size_t i = n_in_points - 1; i > 0; --i)
    {
        double difX = in_points[i].x - in_points[i - 1].x;
        splines[i].d = (splines[i].c - splines[i - 1].c) / difX;
        splines[i].b = difX * (2. * splines[i].c + splines[i - 1].c)
                / 6. + (in_points[i].y - in_points[i - 1].y) / difX;
    }

    extremum extr = find_extremum(in_points, n_in_points, X);
    (*n_out_points) = (abs(extr.min) + abs(extr.max)) / step + 1;
    *out_points = (point*)malloc( (*n_out_points) * sizeof(point));

    double iter = extr.min;
    size_t index = 0;
    while(iter <= extr.max && index < *n_out_points)
    {
        (*out_points)[index] = (point){iter, cubic_function(iter, splines, n_splines)};
        ++index;
        iter += step;
    }

    free(splines);
    return 0;
}
