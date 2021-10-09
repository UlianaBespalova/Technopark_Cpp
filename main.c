#include <stdio.h>
#include "shapes.h"


int main()
{
    Triangle triangle;
    int err = input_triangle(&triangle);
    if (err != 0) {
        printf("Error: incorrect input\n");
        return 0;
    }

    double circle_radius = get_radius_by_inscribed_triangle(&triangle);
    if (circle_radius <= 0) {
        printf("Error: smth went wrong while calculating the radius\n");
        return 0;
    }
    Circle circle = {circle_radius};

    int side_num = 4;
    double polygon_side = get_polygon_side_by_inscribed_circle(&circle, side_num);
    if (polygon_side <= 0) {
        printf("Error: smth went wrong while calculating the square\n");
        return 0;
    }
    Regular_polygon polygon_square = {polygon_side, side_num};


    double square_area = get_polygon_area(&polygon_square);
    if (square_area <= 0) {
        printf("Error: smth went wrong while calculating the square area\n");
        return 0;
    }
    printf("Square area = %.5lf\n", square_area);
    return 0;
}