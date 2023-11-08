#include <gtest/gtest.h>
#include <math/Matrix.hpp>

TEST(MatrixTest, Dimension) {
    math::matrix A{{0, 1}, {2, 3}};
    math::vector expected{2, 2};
    ASSERT_EQ(A.dim(), expected);
}

TEST(MatrixTest, Zeros) {
    auto A = math::matrix::zeros(3, 4);
    math::matrix expected{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    ASSERT_EQ(A, expected);
}

TEST(MatrixTest, Sum) {
    math::matrix A{{0, 1, 2, -1}, {3, 4, 5, 0}, {6, 7, 8, 9}};
    math::matrix B{{3, 6, 1, 2}, {0, -2, 3, 4}, {10, -5, -2, -1}};
    math::matrix sum{{3, 7, 3, 1}, {3, 2, 8, 4}, {16, 2, 6, 8}};
    ASSERT_EQ(A+B, sum);
}

TEST(MatrixTest, Difference) {
    math::matrix A{{0, 1, 2, -1}, {3, 4, 5, 0}, {6, 7, 8, 9}};
    math::matrix B{{3, 6, 1, 2}, {0, -2, 3, 4}, {10, -5, -2, -1}};
    math::matrix diff{{-3, -5, 1, -3}, {3, 6, 2, -4}, {-4, 12, 10, 10}};
    ASSERT_EQ(A-B, diff);
}

TEST(MatrixTest, Transpose) {
    math::matrix A{{0, 1, 2, -1}, {3, 4, 5, 0}, {6, 7, 8, 9}};
    math::matrix T{{0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {-1, 0, 9}};
    ASSERT_EQ(A.T(), T);
}

TEST(MatrixTest, Product) {
    math::matrix A{{0, 1, 2, -1}, {3, 4, 5, 0}, {6, 7, 8, 9}};
    math::matrix B{{3, 2, 1}, {0, 3, -4}, {-2, -2, 1}, {5, 6, 3}};
    math::matrix product{{-1, 1, -9}, {-1, 8, -8}, {47, 80, 13}};
}

TEST(MatrixTest, ElementWiseDot) {
    math::matrix A{{0, 1, 2, -1}, {3, 4, 5, 0}, {6, 7, 8, 9}};
    math::matrix B{{3, 6, 1, 2}, {0, -2, 3, 4}, {10, -5, -2, -1}};
    math::matrix product{{0, 6, 2, -2}, {0, -8, 15, 0}, {60, -35, -16, -9}};
    ASSERT_EQ(A.dot(B), product);
}

TEST(MatrixTest, VectorProduct) {
    math::matrix A{{0, 1, -2, -1}, {3, 4, 5, 0}, {6, 7, 8, 9}};
    math::vector v{3, 1, -2, 4};
    math::vector result{1, 3, 45};
    ASSERT_EQ(A*v, result);    
}

TEST(MatrixTest, Cout) {
    math::matrix A{{0, 1, -2, -1}, {3, 4, 5, 0}, {6, 7, 8, 9}};
    std::cout << A;
}