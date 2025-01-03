#include <gtest/gtest.h>
#include <math/Matrix.hpp>

TEST(MatrixTest, Dimension) {
    math::matrix A{{0, 1}, {2, 3}};
    std::pair<int,int> expected = {2,2};
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

TEST(MatrixTest, LowerTriangular) {
    math::LowerTriangular<double> L{1, 2, 3, 4, 5, 6};
    math::Vector<double> v{7,8,9};
    math::Vector<double> expected{7, 38, 122};
    ASSERT_EQ(L*v, expected);

    std::cout << L << std::endl;

    math::LowerTriangular<double> zeros = math::LowerTriangular<double>::zeros(5);
    std::cout << zeros << std::endl;

    math::LowerTriangular<double> eye = math::LowerTriangular<double>::eye(5);
    std::cout << eye << std::endl;
}

TEST(MatrixTest, UpperTriangular) {
    math::UpperTriangular<double> U{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    math::Vector<double> v{4,3,2,1};
    math::Vector<double> expected{20, 34, 25, 10};
    ASSERT_EQ(U*v, expected);
    
    math::UpperTriangular<double> zeros = math::UpperTriangular<double>::zeros(5);
    std::cout << zeros << std::endl;

    math::UpperTriangular<double> eye = math::UpperTriangular<double>::eye(5);
    std::cout << eye << std::endl;
}

TEST(MatrixTest, CroutFactorization) {
    math::matrix A{
        {2,-1,0,0},
        {-1,2,-1,0},
        {0,-1,2,-1},
        {0,0,-1,2}
    };
    math::vector b{1,0,0,1};
    math::vector x{1,1,1,1};
    auto [L,U] = A.crout();
    std::cout << L << std::endl;
    std::cout << U << std::endl;
    std::cout << A.crout(b) << std::endl;
}

TEST(MatrixTest, AllAssignment) {
    math::matrix A{
        {1, 2, 3},
        {5, 6, 7}
    };
    math::matrix expected{
        {4, 4, 4},
        {4, 4, 4}
    };
    A = 4;
    ASSERT_EQ(A, expected);
}

TEST(MatrixTest, BandMatrixIndex) {
    math::BandMatrix<double> A{
        {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43},
        8,4,2
    };
    std::cout << A << std::endl;
}

TEST(MatrixTest, BandMatrixCrout) {
    math::BandMatrix<double> A{
        {2,-1,-1,2,-1,-1,2,-1,-1,2},
        4, 1, 1
    };
    math::vector b{1,0,0,1};
    math::vector x{1,1,1,1};
    auto [L,U] = A.crout();
    std::cout << L << std::endl;
    std::cout << U << std::endl;
    std::cout << A.crout(b) << std::endl;
}