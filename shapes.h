#ifndef SHAPES_H
#define SHAPES_H

# define M_PI           3.14159265358979323846  /* pi */

typedef struct {
    double side_a;
    double side_b;
    double side_c;
} Triangle;

typedef struct {
    double radius;
} Circle;

typedef struct {
    double side;
    int side_num;
} Regular_polygon;


double get_value(char *str);

int input_triangle(Triangle *triangle);

double get_polygon_side_by_inscribed_circle(const Circle* circle, int side_num);

double get_radius_by_inscribed_triangle(const Triangle *triangle);

double get_polygon_area(const Regular_polygon* polygon);

double get_square_by_inscribed_triangle(const Triangle *triangle);

#endif