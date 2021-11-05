// Copyright 2021 UlianaBespalova
#ifndef HOMEWORK_2_PARALLEL_PARALLEL_H_
#define HOMEWORK_2_PARALLEL_PARALLEL_H_

#include <stdio.h>

#include "structs.h"

Position *get_positions_from_file(const char *file_name, int *size_positions);

Employee *get_k_employees_from_file(FILE *fptr, int k);

Average_salary *count_average_salary(const Count_average *count_salary,
                                     const Position *positions,
                                     int size_positions);

Average_salary *parallel_count_average_salaries(const char *employees_file_name,
                                                const char *positions_file_name,
                                                int *size_positions);

#endif  // HOMEWORK_2_PARALLEL_PARALLEL_H_
