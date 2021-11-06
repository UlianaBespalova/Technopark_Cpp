// Copyright 2021 UlianaBespalova
#ifndef HOMEWORK_2_STRUCTS_H
#define HOMEWORK_2_STRUCTS_H

#define LENGTH_NAME 16
#define LENGTH_SURNAME 24
#define LENGTH_POSITION 24
#define NUM_EMPLOYEES 7

typedef enum gender {
    MALE,
    FEMALE
} gender_t;

typedef struct position {
    char position[LENGTH_POSITION];
    unsigned int id;
} position_t;

typedef struct employee {
    unsigned int position_id;
    unsigned int salary;
    unsigned int experience;
    unsigned int age;
    char name[LENGTH_NAME];
    char surname[LENGTH_SURNAME];
    gender_t gender;
} employee_t;

typedef struct average_salary {
    char position[LENGTH_POSITION];
    unsigned int salary;
} average_salary_t;

typedef struct count_average_t {
    unsigned int total;
    unsigned int count;
} count_average_t;

#endif  // HOMEWORK_2_STRUCTS_H
