// Copyright 2021 UlianaBespalova
#include "shapes.h"
#include <stdio.h>

int main() {
    Triangle triangle;
    int err = input_triangle(&triangle);
    if (err != 0) {
        printf("Error: incorrect input\n");
        return 0;
    }

    double square_area = get_square_by_inscribed_triangle(&triangle);
    if (square_area <= 0) {
        printf("Error: smth went wrong while calculating the square area\n");
        return 0;
    }
    printf("Square area = %.5lf\n", square_area);
    return 0;
}
