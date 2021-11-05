// Copyright 2021 UlianaBespalova
#include <stdio.h>
#include <stdlib.h>

#include "simple.h"

int main() {
    int size_positions = 0;
    Position *positions = get_positions_from_file(
            "project/test/data/positions.txt", &size_positions);
    if (positions == NULL) {
        return 1;
    }
    int size_employees = 0;
    Employee *employees = get_employees_from_file(
            "project/test/data/input_10000.txt", &size_employees);
    if (employees == NULL) {
        return 1;
    }

    Average_salary *aver_salaries = count_average_salaries(
            employees, size_employees, positions, size_positions);
    if (aver_salaries == NULL) {
        return 1;
    }
    for (int i = 0; i < size_positions; i++) {
        printf("%s - %dр\n", aver_salaries[i].position,
               aver_salaries[i].salary);
    }

    free(positions);
    free(employees);
    free(aver_salaries);
    return 0;
}
