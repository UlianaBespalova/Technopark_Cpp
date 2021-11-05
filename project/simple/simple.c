// Copyright 2021 UlianaBespalova
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simple.h"

Position *get_positions_from_file(const char *file_name, int *size_positions) {
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        return NULL;
    }
    if (fscanf(fptr, "%d\n", size_positions) != 1) {
        fclose(fptr);
        return NULL;
    }

    Position *positions =
            (Position *)malloc(sizeof(Position) * (*size_positions));
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

Employee *get_employees_from_file(const char *file_name, int *size_employees) {
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL) {
        return NULL;
    }
    if (fscanf(fptr, "%d\n", size_employees) != 1) {
        fclose(fptr);
        return NULL;
    }

    Employee *employees =
            (Employee *)malloc(sizeof(Employee) * (*size_employees));
    if (employees == NULL) {
        fclose(fptr);
        return NULL;
    }
    for (int i = 0; i < *size_employees; i++) {
        if (fscanf(fptr, "%u %u %u %u %16s %24s %c\n",
                   &employees[i].position_id, &employees[i].salary,
                   &employees[i].experience, &employees[i].age,
                   employees[i].name, employees[i].surname,
                   &employees[i].sex) != 7) {
            free(employees);
            fclose(fptr);
            return NULL;
        }
    }
    fclose(fptr);
    return employees;
}

Average_salary *count_average_salaries(const Employee *employees,
                                       int size_employees,
                                       const Position *positions,
                                       int size_positions) {
    if (!employees || !positions) return NULL;

    Count_average *count_average =
            (Count_average *)malloc(sizeof(Count_average) * (size_positions));
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

    Average_salary *aver_salaries =
            (Average_salary *)malloc(sizeof(Average_salary) * (size_positions));
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
