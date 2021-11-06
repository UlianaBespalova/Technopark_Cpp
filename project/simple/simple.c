// Copyright 2021 UlianaBespalova
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simple.h"

position_t *get_positions_from_file(const char *file_name, int *size_positions) {
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        return NULL;
    }
    if (fscanf(fptr, "%d\n", size_positions) != 1) {
        fclose(fptr);
        return NULL;
    }

    position_t *positions =
            (position_t *)malloc(sizeof(position_t) * (*size_positions));
    if (positions == NULL) {
        fclose(fptr);
        return NULL;
    }
    for (int i = 0; i < *size_positions; i++) {
        if (fscanf(fptr, "%24s\n", positions[i].position) != 1) {
            free(positions);
            fclose(fptr);
            return NULL;
        }
    }
    fclose(fptr);
    return positions;
}

employee_t *get_employees_from_file(const char *file_name, int *size_employees) {
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        return NULL;
    }
    if (fscanf(fptr, "%d\n", size_employees) != 1) {
        fclose(fptr);
        return NULL;
    }

    employee_t *employees =
            (employee_t *)malloc(sizeof(employee_t) * (*size_employees));
    if (employees == NULL) {
        fclose(fptr);
        return NULL;
    }

    const char *EMPLOYEE_FORMAT = "%u %u %u %u %16s %24s %c\n";
    for (int i = 0; i < *size_employees; i++) {
        if (fscanf(fptr, EMPLOYEE_FORMAT,
                   &employees[i].position_id, &employees[i].salary,
                   &employees[i].experience, &employees[i].age,
                   employees[i].name, employees[i].surname,
                   &employees[i].gender) != NUM_EMPLOYEES) {
            free(employees);
            fclose(fptr);
            return NULL;
        }
    }
    fclose(fptr);
    return employees;
}

average_salary_t *count_average_salaries(const employee_t *employees,
                                       int size_employees,
                                       const position_t *positions,
                                       int size_positions) {
    if (!employees || !positions) return NULL;

    count_average_t *count_average =
            (count_average_t *)malloc(sizeof(count_average_t) * (size_positions));
    if (count_average == NULL) {
        return NULL;
    }
    for (int i = 0; i < size_positions; i++) {
        count_average[i].total = 0;
        count_average[i].count = 0;
    }
    for (int i = 0; i < size_employees; i++) {
        int pos_id = (int)employees[i].position_id;
        count_average[pos_id].count++;
        count_average[pos_id].total += employees[i].salary;
    }

    average_salary_t *aver_salaries =
            (average_salary_t *)malloc(sizeof(average_salary_t) * (size_positions));
    if (aver_salaries == NULL) {
        free(count_average);
        return NULL;
    }

    for (int i = 0; i < size_positions; i++) {
        strcpy(aver_salaries[i].position, positions[i].position);
        if (count_average[i].count > 0) {
            aver_salaries[i].salary =
                    (int)(count_average[i].total / count_average[i].count);
        }
    }
    free(count_average);
    return aver_salaries;
}
