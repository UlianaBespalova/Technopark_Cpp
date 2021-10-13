// Copyright 2021 UlianaBespalova
#include "gtest/gtest.h"

extern "C" {
#include "shapes.h"
}

TEST(Shapes, TestGetValue) {
    const int iter = 4;
    char *input[iter] = {"5", "-27", "055", "notNumber"};
    double expected[iter] = {5, -27, 55, -1};

    for (int i = 0; i < iter; i++) {
        EXPECT_EQ(get_value(input[i]), expected[i]);
    }
}

TEST(Shapes, GetRadiusByInscribedTriangle) {
    const int iter = 3;
    double input[iter][3] = {{3, 3, 3}, {3, 6, 4}, {1.5, 2, 2.7}};
    double expected[iter] = {1.732, 3.375, 1.371};

    for (int i = 0; i < iter; i++) {
        Triangle tr = {input[i][0], input[i][1], input[i][2]};
        EXPECT_NEAR(get_radius_by_inscribed_triangle(&tr), expected[i], 0.001);
    }
}

TEST(Shapes, GetRadiusByInscribedTriangleNegative) {
    EXPECT_EQ(get_radius_by_inscribed_triangle(nullptr), -1);
}

TEST(Shapes, GetPolygonSideByInscribedCircle) {
    const int iter = 4;
    int input[iter][2] = {{3, 3}, {4, 4}, {5, 5}, {10, 10}};
    double expected[iter] = {10.392, 8, 7.265, 6.498};

    for (int i = 0; i < iter; i++) {
        Circle ci = {(double)input[i][0]};
        EXPECT_NEAR(get_polygon_side_by_inscribed_circle(&ci, input[i][1]),
                    expected[i], 0.001);
    }
}

TEST(Shapes, GetPolygonSideByInscribedCircleNegative) {
    EXPECT_EQ(get_polygon_side_by_inscribed_circle(nullptr, 10), -1);
}

TEST(Shapes, GetPolygonArea) {
    const int iter = 4;
    int input[iter][2] = {{3, 3}, {4, 4}, {5, 5}, {5, -3}};
    double expected[iter] = {3.897, 16, 43.012, 10.825};

    for (int i = 0; i < iter; i++) {
        Regular_polygon sq = {(double)input[i][0], input[i][1]};
        EXPECT_NEAR(get_polygon_area(&sq), expected[i], 0.001);
    }
}

TEST(Shapes, GetPolygonAreaNegative) {
    EXPECT_EQ(get_polygon_area(nullptr), -1);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

