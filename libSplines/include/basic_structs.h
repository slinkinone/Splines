#ifndef BASIC_STRUCTS_H
#define BASIC_STRUCTS_H

typedef struct spline
{
    double a, b, c, d, x;
} spline;

typedef struct point
{
    double x, y;
} point;

typedef enum
{
    X,
    Y,
} extremum_targer;

typedef struct extremum
{
    double min, max;
} extremum;

#endif // BASIC_STRUCTS_H
