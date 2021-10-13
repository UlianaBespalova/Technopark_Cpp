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

int log_validate_triangle(const Triangle *triangle) {
    if (triangle == NULL) {
        printf("LOG: log_validate_triangle: null pointer\n");
        return -1;
    }
    if (triangle->side_a <= 0 || triangle->side_b <= 0 || triangle->side_c <= 0) {
        printf("LOG: log_validate_triangle: incorrect value of the triangle side\n");
        return -1;
    }
    return 0;
}

Triangle create_triangle() {
    double input_side_a, input_side_b, input_side_c;
    char value_str[10];
    scanf("%9s", value_str);
    input_side_a = get_value(value_str);
    scanf("%9s", value_str);
    input_side_b = get_value(value_str);
    scanf("%9s", value_str);
    input_side_c = get_value(value_str);

    Triangle triangle;
    triangle.side_a = input_side_a;
    triangle.side_b = input_side_b;
    triangle.side_c = input_side_c;

    int validation = log_validate_triangle(&triangle);
    if (validation!=0) {
        triangle.side_a = 0;
        triangle.side_b = 0;
        triangle.side_c = 0;
    }
    return triangle;
}

double get_radius_by_inscribed_triangle(const Triangle *triangle) {
    if (triangle == NULL) {
        return -1;
    }
    const int TWO = 2;
    const int FOUR = 4;
    double p = (triangle->side_a + triangle->side_b + triangle->side_c) / TWO;
    double radius = (triangle->side_a * triangle->side_b * triangle->side_c) /
                    (FOUR * sqrt(p* (p - triangle->side_a) * (p - triangle->side_b) *
                              (p - triangle->side_c)));
    return radius;
}

double get_polygon_side_by_inscribed_circle(const Circle* circle,
                                            const int side_num) {
    if (circle == NULL || side_num == 0) {
        return -1;
    }
    const int TWO = 2;
    double side = TWO * circle->radius * tan(M_PI / (double)side_num);
    return side;
}

double get_polygon_area(const Regular_polygon* polygon) {
    if (polygon == NULL) {
        return -1;
    }
    const int FOUR = 4;
    double area = ((double)polygon->side_num / FOUR) * polygon->side * polygon->side/
                  tan(M_PI / polygon->side_num);
    return area;
}

double get_square_by_inscribed_triangle(const Triangle *triangle) {
    if (triangle == NULL) {
        return -1;
    }
    double circle_radius = get_radius_by_inscribed_triangle(triangle);
    Circle circle = {circle_radius};

    const int SIDE_NUM = 4;
    double polygon_side = get_polygon_side_by_inscribed_circle(&circle, SIDE_NUM);
    Regular_polygon polygon_square = {polygon_side, SIDE_NUM};

    double square_area = get_polygon_area(&polygon_square);
    return square_area;
}
