// Copyright 2021 UlianaBespalova
#include "shapes.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double get_value(char *str) {
    char *ptr;
    double value;
    value = strtod(str, &ptr);
    if (*ptr != '\0') {
        return -1;
    }
    return value;
}

int input_triangle(Triangle *triangle) {
    if (triangle == NULL) {
        return -1;
    }
    double input_side_a, input_side_b, input_side_c;
    char value_str[10];
    scanf("%9s", value_str);
    input_side_a = get_value(value_str);
    scanf("%9s", value_str);
    input_side_b = get_value(value_str);
    scanf("%9s", value_str);
    input_side_c = get_value(value_str);

    if (input_side_a <= 0 || input_side_b <= 0 || input_side_c <= 0) {
        return -1;
    }
    triangle->side_a = input_side_a;
    triangle->side_b = input_side_b;
    triangle->side_c = input_side_c;
    return 0;
}

double get_radius_by_inscribed_triangle(const Triangle *triangle) {
    if (triangle == NULL) {
        return -1;
    }
    if (triangle->side_a <= 0 || triangle->side_b <= 0 || triangle->side_c <= 0) {
        return -1;
    }
    double p = (triangle->side_a + triangle->side_b + triangle->side_c) / 2;
    double radius = (triangle->side_a * triangle->side_b * triangle->side_c) /
                    (4 * sqrt(p* (p - triangle->side_a) * (p - triangle->side_b) *
                    (p - triangle->side_c)));
    return radius;
}

double get_polygon_side_by_inscribed_circle(const Circle* circle,
                                            const int side_num) {
    if (circle == NULL || side_num == 0 || circle->radius <= 0) {
        return -1;
    }
    double side = 2 * circle->radius * tan(M_PI / (double)side_num);
    return side;
}

double get_polygon_area(const Regular_polygon* polygon) {
    if (polygon == NULL) {
        return -1;
    }
    double area = ((double)polygon->side_num / 4) * polygon->side * polygon->side/
            tan(M_PI / polygon->side_num);
    return area;
}

double get_square_by_inscribed_triangle(const Triangle *triangle) {
    if (triangle == NULL) {
        return -1;
    }
    if (triangle->side_a <= 0 || triangle->side_b <= 0 || triangle->side_c <= 0) {
        return -1;
    }
    double circle_radius = get_radius_by_inscribed_triangle(triangle);
    if (circle_radius <= 0) {
        printf("Error: smth went wrong while calculating the radius\n");
        return -1;
    }
    Circle circle = {circle_radius};

    int side_num = 4;
    double polygon_side = get_polygon_side_by_inscribed_circle(&circle, side_num);
    if (polygon_side <= 0) {
        printf("Error: smth went wrong while calculating the square\n");
        return -1;
    }
    Regular_polygon polygon_square = {polygon_side, side_num};

    double square_area = get_polygon_area(&polygon_square);
    if (square_area <= 0) {
        printf("Error: smth went wrong while calculating the square area\n");
        return -1;
    }
    return square_area;
}
