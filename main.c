#include <stdio.h>  //  printf
#include <string.h> //  strcmp

#include "splines.h"

#define STEP 0.1
point in_points[] = {{-8.0, 7.0}, {-5.0, 2.0}, {0.0, 5.0}, {4.0, -4.0}, {7.0, 0.0}};
const size_t n_in_points = sizeof(in_points) / sizeof(point);

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        printf("A print parameter has been missed. (akima, cubic, points)\n");
        return 0;
    }

    int result = -1;
    size_t n_out_points = 0;
    point* out_points = NULL;

    if(strcmp(argv[1], "akima") == 0)
    {
        result = akima_spline(in_points, n_in_points, STEP, &out_points, &n_out_points);
    }
    else if(strcmp(argv[1], "cubic") == 0)
    {
        result = cubic_spline(in_points, n_in_points, STEP, &out_points, &n_out_points);
    }
    else if(strcmp(argv[1], "points") == 0)
    {
        result = 0;
        out_points = in_points;
        n_out_points = n_in_points;
    }
    else
    {
        printf("A print parameter isn't recognized. (akima, cubic, points)\n");
    }

    if(result == 0)
    {
        //printf("%s\n", argv[1]);
        for(size_t i = 0; i < n_out_points; ++i)
        {
            printf("%f,%f\n", out_points[i].x, out_points[i].y);
        }
    }

    if(!out_points)
        free(out_points);

    return 0;
}

