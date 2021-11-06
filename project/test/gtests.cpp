// Copyright 2021 UlianaBespalova
#include <gtest/gtest.h>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>

extern "C" {
#include "parallel.h"
#include "simple.h"
}

void compare_algorithms(const char *file_name) {
    const char *pos_file_name = "project/test/data/positions.txt";
    using namespace std::chrono;

    unsigned int time1 =
            duration_cast<milliseconds>(system_clock::now().time_since_epoch())
                    .count();
    int size_positions = 0;
    position_t *positions = get_positions_from_file(pos_file_name,
                                                  &size_positions);
    int size_employees = 0;
    employee_t *employees = get_employees_from_file(file_name,
                                                  &size_employees);

    average_salary_t *aver_salaries_simple = count_average_salaries(
            employees, size_employees, positions, size_positions);

    unsigned int time2 =
            duration_cast<milliseconds>(system_clock::now().time_since_epoch())
                    .count();
    average_salary_t *aver_salaries_parallel = parallel_count_average_salaries(
            pos_file_name, file_name, &size_positions);
    unsigned int time3 =
            duration_cast<milliseconds>(system_clock::now().time_since_epoch())
                    .count();

    free(positions);
    free(employees);
    free(aver_salaries_simple);
    free(aver_salaries_parallel);

    std::cout << "Simple algorithm time: " << time2 - time1 << "ms" << std::endl;
    std::cout << "Parallel algorithm time: " << time3 - time2 << "ms" << std::endl;
}

TEST(simple_get_positions_from_file, null_file_name) {
    int size_positions = 0;
    EXPECT_TRUE(get_positions_from_file("project/test/data/no_such_file.txt",
                                        &size_positions) == nullptr);
    EXPECT_EQ(size_positions, 0);
}

TEST(simple_get_positions_from_file, wrong_file_data) {
    int size_positions = 0;
    EXPECT_TRUE(get_positions_from_file("project/test/data/no_such_file.txt",
                                        &size_positions) == nullptr);
    EXPECT_EQ(size_positions, 0);
}

TEST(simple_get_positions_from_file, get_data_from_file) {
    int size_positions = 0;
    position_t *positions = get_positions_from_file(
            "project/test/data/positions.txt", &size_positions);
    EXPECT_TRUE(positions != nullptr);
    EXPECT_EQ(size_positions, 6);
    free(positions);
}

TEST(get_employees_from_file, null_file_name) {
    int size_employees = 0;
    EXPECT_TRUE(get_employees_from_file("project/test/data/no_such_file.txt",
                                        &size_employees) == nullptr);
    EXPECT_EQ(size_employees, 0);
}

TEST(simple_get_employees_from_file, wrong_file_data) {
    int size_employees = 0;
    EXPECT_TRUE(get_employees_from_file("project/test/data/no_such_file.txt",
                                        &size_employees) == nullptr);
    EXPECT_EQ(size_employees, 0);
}

TEST(simple_get_employees_from_file, get_data_from_file) {
    int size_employees = 0;
    employee_t *employees = get_employees_from_file(
            "project/test/data/input_1000.txt", &size_employees);
    EXPECT_TRUE(employees != nullptr);
    EXPECT_EQ(size_employees, 1000);
    free(employees);
}

TEST(simple_count_average_salaries, null_input) {
    EXPECT_TRUE(count_average_salaries(nullptr, 6, nullptr, 1000) == nullptr);
}

TEST(simple_count_average_salaries, get_aver_salaries) {
    int size_employees = 0;
    employee_t *employees = get_employees_from_file(
            "project/test/data/input_1000.txt", &size_employees);
    int size_positions = 0;
    position_t *positions = get_positions_from_file(
            "project/test/data/positions.txt", &size_positions);

    average_salary_t *aver_salaries = count_average_salaries(
            employees, size_employees, positions, size_positions);

    EXPECT_TRUE(aver_salaries != nullptr);
    for (int i = 0; i < size_positions; i++) {
        EXPECT_EQ(aver_salaries[i].salary, (i + 1) * 10000);
    }
    free(positions);
    free(employees);
    free(aver_salaries);
}

TEST(parallel_get_k_employees_from_file, null_input) {
    EXPECT_TRUE(get_k_employees_from_fileptr(nullptr, 6) == nullptr);
}

TEST(parallel_get_positions_from_fileptr, null_input) {
    int size_positions = 0;
    EXPECT_TRUE(get_positions_from_fileptr(nullptr, &size_positions) == nullptr);
    EXPECT_EQ(size_positions, 0);
}

TEST(parallel_get_positions_from_fileptr, get_positions) {
    int size_positions = 0;
    FILE *fptr_positions = fopen("project/test/data/positions.txt", "r");
    position_t *positions = get_positions_from_fileptr(fptr_positions, &size_positions);

    EXPECT_TRUE(positions != nullptr);
    EXPECT_EQ(size_positions, 6);
    fclose(fptr_positions);
    free(positions);
}

TEST(parallel_count_average_salary, count_average) {
    int size_positions = 0;
    position_t *positions = get_positions_from_file(
            "project/test/data/positions.txt", &size_positions);
    auto *count_aver = (count_average_t *)malloc(sizeof(count_average_t) * 6);
    for (int i = 0; i < 6; i++) {
        count_aver[i].count = 10;
        count_aver[i].total = 1000;
    }
    average_salary_t *aver_salary =
            count_average_salary(count_aver, positions, size_positions);
    EXPECT_TRUE(aver_salary != nullptr);
    EXPECT_EQ(aver_salary[0].salary, 100);

    free(positions);
    free(count_aver);
    free(aver_salary);
}

TEST(parallel_count_average_salaries, wrong_empl_file_name) {
    int size_positions = 0;
    EXPECT_TRUE(parallel_count_average_salaries(
            "project/test/data/no_such_file.txt",
            "project/test/data/positions.txt",
            &size_positions) == nullptr);
}

TEST(parallel_count_average_salaries, wrong_pos_file_name) {
    int size_positions = 0;
    EXPECT_TRUE(parallel_count_average_salaries(
                    "project/test/data/input_1000.txt",
                    "project/test/data/no_such_file.txt",
                    &size_positions) == nullptr);
}

TEST(parallel_count_salaries_for_positions, count_average) {
    int size_positions = 0;
    average_salary_t *aver_salary = parallel_count_average_salaries(
            "project/test/data/input_1000.txt",
            "project/test/data/positions.txt",
            &size_positions);
    EXPECT_EQ(size_positions, 6);
    EXPECT_EQ(aver_salary[0].salary, 10000);
    free(aver_salary);
}

// 1000 employees
TEST(count_average_salaries, compare) {
    std::cout << std::endl << "Case 1, 10000 employees" << std::endl;
    compare_algorithms("project/test/data/input_10000.txt");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
