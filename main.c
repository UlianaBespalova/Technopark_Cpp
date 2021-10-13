// Copyright 2021 UlianaBespalova
#include "shapes.h"
#include <stdio.h>

int main() {
    Triangle triangle = create_triangle();
    double square_area = get_square_by_inscribed_triangle(&triangle);
    printf("Square area = %.5lf\n", square_area);
    return 0;
}
