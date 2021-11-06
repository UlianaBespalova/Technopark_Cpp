// Copyright 2021 UlianaBespalova
#ifndef HOMEWORK_2_SIMPLE_SIMPLE_H_
#define HOMEWORK_2_SIMPLE_SIMPLE_H_

#include "structs.h"

position_t *get_positions_from_file(const char *file_name, int *size_positions);
employee_t *get_employees_from_file(const char *file_name, int *size_employees);

average_salary_t *count_average_salaries(const employee_t *employees,
                                       int size_employees,
                                       const position_t *positions,
                                       int size_positions);

#endif  // HOMEWORK_2_SIMPLE_SIMPLE_H_
