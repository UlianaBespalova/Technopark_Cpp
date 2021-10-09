#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "shapes.h"


double get_value(char *str) {
    char *ptr;
    double value;
    value = strtod(str, &ptr);
    if (*ptr != '\0') {
//        printf("please, input number\n");
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

    if (input_side_a<=0 || input_side_b<=0 || input_side_c<=0) {
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
    if (triangle->side_a<=0 || triangle->side_b<=0 || triangle->side_c<=0) {
        return -1;
    }
    double p = (triangle->side_a+triangle->side_b+triangle->side_c)/2;
    double radius = (triangle->side_a*triangle->side_b*triangle->side_c)/
                    (4*sqrt(p*(p-triangle->side_a)*(p-triangle->side_b)*(p-triangle->side_c)));
    return radius;
}

double get_polygon_side_by_inscribed_circle(const Circle* circle, const int side_num) {
    if (circle == NULL || side_num == 0 || circle->radius<=0) {
        return -1;
    }
    double side = 2*circle->radius*tan(M_PI/(double)side_num);
    return side;

}

double get_polygon_area(const Regular_polygon* polygon) {
    if (polygon == NULL) {
        return -1;
    }
    double area = ((double)polygon->side_num/4)*polygon->side*polygon->side/tan(M_PI/polygon->side_num);
    return area;
}