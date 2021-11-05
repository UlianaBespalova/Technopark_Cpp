// Copyright 2021 UlianaBespalova
#ifndef HOMEWORK_2_STRUCTS_H
#define HOMEWORK_2_STRUCTS_H

typedef struct Position {
    char position[24];
    unsigned int id;
} Position;

typedef struct Employee {
    unsigned int position_id;
    unsigned int salary;
    unsigned int experience;
    unsigned int age;
    char name[16];
    char surname[24];
    char sex;
} Employee;

typedef struct Average_salary {
    char position[24];
    unsigned int salary;
} Average_salary;

typedef struct Count_average {
    unsigned int total;
    unsigned int count;
} Count_average;

#endif  // HOMEWORK_2_STRUCTS_H
