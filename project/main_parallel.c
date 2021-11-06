// Copyright 2021 UlianaBespalova
#include <stdio.h>
#include <stdlib.h>

#include "parallel.h"

int main() {
    int size_positions = 0;
    average_salary_t *aver_salaries = parallel_count_average_salaries(
            "project/test/data/input_1000.txt",
            "project/test/data/positions.txt",
            &size_positions);
    if (aver_salaries == NULL) {
        return 1;
    }
    for (int i = 0; i < size_positions; i++) {
        printf("%s - %dр\n", aver_salaries[i].position,
               aver_salaries[i].salary);
    }
    free(aver_salaries);
    return 0;
}
