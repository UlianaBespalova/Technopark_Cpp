// Copyright 2021 UlianaBespalova
#ifndef HOMEWORK_2_SIMPLE_SIMPLE_H_
#define HOMEWORK_2_SIMPLE_SIMPLE_H_

#include "structs.h"

Position *get_positions_from_file(const char *file_name, int *size_positions);
Employee *get_employees_from_file(const char *file_name, int *size_employees);

Average_salary *count_average_salaries(const Employee *employees,
                                       int size_employees,
                                       const Position *positions,
                                       int size_positions);

#endif  // HOMEWORK_2_SIMPLE_SIMPLE_H_
