// Copyright 2021 UlianaBespalova
#ifndef HOMEWORK_2_PARALLEL_PARALLEL_H_
#define HOMEWORK_2_PARALLEL_PARALLEL_H_

#include <stdio.h>

#include "structs.h"

position_t *get_positions_from_fileptr(FILE *fptr, int *size_positions);

employee_t *get_k_employees_from_fileptr(FILE *fptr, int k);

average_salary_t *count_average_salary(const count_average_t *count_salary,
                                     const position_t *positions,
                                     int size_positions);

average_salary_t *parallel_count_average_salaries(const char *employees_file_name,
                                                const char *positions_file_name,
                                                int *size_positions);

#endif  // HOMEWORK_2_PARALLEL_PARALLEL_H_
