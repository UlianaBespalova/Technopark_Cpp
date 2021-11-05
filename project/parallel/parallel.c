// Copyright 2021 UlianaBespalova
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parallel.h"

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

Employee *get_k_employees_from_file(FILE *fptr, int k) {
    if (fptr == NULL) {
        return NULL;
    }
    Employee *employees = (Employee *)malloc(sizeof(Employee) * (k));
    if (employees == NULL) {
        return NULL;
    }
    for (int i = 0; i < k; i++) {
        if (fscanf(fptr, "%u %u %u %u %16s %24s %c\n",
                   &employees[i].position_id, &employees[i].salary,
                   &employees[i].experience, &employees[i].age,
                   employees[i].name, employees[i].surname,
                   &employees[i].sex) != 7) {
            free(employees);
            return NULL;
        }
    }
    return employees;
}

Average_salary *count_average_salary(const Count_average *count_salary,
                                     const Position *positions,
                                     int size_positions) {
    if (count_salary == NULL || positions == NULL) {
        return NULL;
    }
    Average_salary *aver_salaries =
            (Average_salary *)malloc(sizeof(Average_salary) * (size_positions));
    if (aver_salaries == NULL) {
        return NULL;
    }

    for (int i = 0; i < size_positions; i++) {
        strcpy(aver_salaries[i].position, positions[i].position);
        if (count_salary[i].count > 0) {
            aver_salaries[i].salary =
                    (int)(count_salary[i].total / count_salary[i].count);
        }
    }
    return aver_salaries;
}

Average_salary *parallel_count_average_salaries(const char *employees_file_name,
                                                const char *positions_file_name,
                                                int *size_positions) {
    Position *positions =
            get_positions_from_file(positions_file_name, size_positions);
    if (positions == NULL) {
        return NULL;
    }

    FILE *fptr = fopen(employees_file_name, "r");
    if (fptr == NULL) {
        free(positions);
        return NULL;
    }
    int fd[2];
    if (pipe(fd) < 0) {
        free(positions);
        fclose(fptr);
        return NULL;
    }
    int size_employees = 0;
    if (fscanf(fptr, "%d\n", &size_employees) != 1) {
        free(positions);
        fclose(fptr);
        return NULL;
    }

    const int process_number = 4;
    int n_per_process = size_employees / process_number;

    int employees_per_process[process_number];
    for (int i = 0; i < process_number - 1; i++) {
        employees_per_process[i] = n_per_process;
    }
    employees_per_process[process_number - 1] =
            n_per_process + size_employees % process_number;

    Count_average *count_salary =
            (Count_average *)malloc(sizeof(Count_average) * (*size_positions));
    if (count_salary == NULL) {
        free(positions);
        fclose(fptr);
        return NULL;
    }
    for (int i = 0; i < *size_positions; i++) {
        count_salary[i].total = 0;
        count_salary[i].count = 0;
    }
    size_t count_salary_size = sizeof(Count_average) * (*size_positions);

    pid_t pid;
    for (size_t i = 0; i < process_number; i++) {
        Employee *employees =
                get_k_employees_from_file(fptr, employees_per_process[i]);
        pid = fork();
        if (pid == -1 || employees == NULL) {
            close(fd[0]);
            close(fd[1]);
            free(positions);
            free(count_salary);
            fclose(fptr);
            return NULL;
        }
        if (pid == 0) {
            for (int j = 0; j < employees_per_process[i]; j++) {
                int pos_id = (int)employees[j].position_id;
                count_salary[pos_id].count++;
                count_salary[pos_id].total += employees[j].salary;
            }
            write(fd[1], count_salary, count_salary_size);
            close(fd[0]);
            close(fd[1]);
            free(employees);
            free(count_salary);
            fclose(fptr);
            exit(0);
        }
        free(employees);
    }

    Count_average *count_average_final =
            (Count_average *)malloc(sizeof(Count_average) * (*size_positions));

    for (size_t i = 0; i < process_number; i++) {
        read(fd[0], count_average_final, count_salary_size);
        for (int j = 0; j < *size_positions; j++) {
            count_salary[j].count += count_average_final[j].count;
            count_salary[j].total += count_average_final[j].total;
        }
    }
    Average_salary *average_salary =
            count_average_salary(count_salary, positions, *size_positions);

    close(fd[0]);
    close(fd[1]);
    fclose(fptr);
    free(positions);
free(count_salary);
    free(count_average_final);
    int status = 0;
    wait(&status);

    return average_salary;
}
