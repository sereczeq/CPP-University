//
// Created by jakub on 18.01.2021.
//
#include "gtest/gtest.h"

#include "Matrix.h"

TEST(MatrixInitialization, IntegerEmptyMatrix)
{
    Matrix<int> matrix(5, 5);
    testing::internal::CaptureStdout();
    std::cout << matrix;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 5, height: 5, array:\n"
                      "[0,\t0,\t0,\t0,\t0]\n"
                      "[0,\t0,\t0,\t0,\t0]\n"
                      "[0,\t0,\t0,\t0,\t0]\n"
                      "[0,\t0,\t0,\t0,\t0]\n"
                      "[0,\t0,\t0,\t0,\t0]\n"
                      "}");
}

TEST(MatrixInitialization, IntegerSquareMatrix)
{
    int** array = new int*[]{new int[]{1, 2, 3},
                             new int[]{4, 5, 6},
                             new int[]{7, 8, 9}};
    Matrix<int> matrix(array, 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[1,\t2,\t3]\n"
                      "[4,\t5,\t6]\n"
                      "[7,\t8,\t9]\n"
                      "}");
}

TEST(MatrixInitialization, BooleanSquareMatrix)
{
    bool** array = new bool*[]{new bool[]{true, true, true},
                             new bool[]{true, false, true},
                             new bool[]{true, true, true}};
    Matrix<bool> matrix(array, 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[1,\t1,\t1]\n"
                      "[1,\t0,\t1]\n"
                      "[1,\t1,\t1]\n"
                      "}");
}

TEST(MatrixInitialization, IntegerSimpleMatrix)
{
    int** array = new int*[]{new int[]{1, 2, 3, 4},
                             new int[]{4, 5, 6, 7},
                             new int[]{7, 8, 9, 10}};
    Matrix<int> matrix(array, 4, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 4, height: 3, array:\n"
                      "[1,\t2,\t3,\t4]\n"
                      "[4,\t5,\t6,\t7]\n"
                      "[7,\t8,\t9,\t10]\n"
                      "}");
}
TEST(MatrixInitialization, IntegerFileMatrix)
{
    Matrix<int> matrix("../text/MatrixInteger.txt", 10, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 10, height: 3, array:\n"
                      "[1,\t2,\t3,\t4,\t5,\t6,\t7,\t8,\t9,\t10]\n"
                      "[11,\t12,\t13,\t14,\t15,\t16,\t17,\t18,\t19,\t110]\n"
                      "[21,\t22,\t23,\t24,\t25,\t26,\t27,\t28,\t29,\t210]\n"
                      "}");
}

TEST(MatrixTranspose, SquareTranspose)
{
    int** array = new int*[]{new int[]{1, 2, 3},
                             new int[]{4, 5, 6},
                             new int[]{7, 8, 9}};
    Matrix<int> matrix(array, 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix.transpose();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[1,\t4,\t7]\n"
                      "[2,\t5,\t8]\n"
                      "[3,\t6,\t9]\n"
                      "}");
}

TEST(MatrixTranspose, IntegerSquareFileMatrixTranspose)
{
    Matrix<int> matrix("../text/MatrixTestInteger", 4, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix.transpose();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 4, array:\n"
                      "[1,\t4,\t7]\n"
                      "[2,\t5,\t8]\n"
                      "[3,\t6,\t9]\n"
                      "[4,\t7,\t10]\n"
                      "}");
}

TEST(MatrixDeterminant, Integer66Matrix)
{
    Matrix<int> matrix("../text/determinant1.txt", 6, 6);
    EXPECT_EQ(matrix.calculateDeterminant(), -39168);
}

TEST(MatrixDeterminant, Integer88Matrix)
{
    Matrix<int> matrix("../text/determinant2.txt", 8, 8);
    EXPECT_EQ(matrix.calculateDeterminant(), 1773641);
}

TEST(MatrixDeterminant, IntegerNonSquareMatrix)
{
    Matrix<int> matrix("../text/determinant2.txt", 6, 8);
    EXPECT_THROW(matrix.calculateDeterminant(), MatrixException);
}

TEST(MatrixDeterminant, FloatMatrix)
{
    Matrix<float> matrix("../text/determinant3.txt", 5, 5);
    EXPECT_NEAR(matrix.calculateDeterminant(), 55249.2f, 1);
}

TEST(MatrixInverse, IntegerSquareMatrix)
{
    Matrix<int> matrix("../text/inverse1.txt", 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix.inverse();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                "width: 3, height: 3, array:\n"
                "[-0.333333,\t-1.77778,\t1.11111]\n"
                "[0.666667,\t0.888889,\t-0.555556]\n"
                "[-0.333333,\t0.555556,\t-0.222222]\n"
                "}");
}
TEST(MatrixInverse, BoolSquareMatrix)
{
    Matrix<bool> matrix("../text/inverse2.txt", 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix.inverse();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[-1,\t1,\t1]\n"
                      "[1,\t-1,\t-0]\n"
                      "[1,\t-0,\t-1]\n"
                      "}");
}

TEST(MatrixInverse, ErrorNonSquare)
{
    Matrix<int> matrix("../text/determinant2.txt", 6, 8);
    EXPECT_THROW(matrix.inverse(), MatrixException);
}

TEST(MatrixInverse, ErrorDeterminant0)
{
    Matrix<int> matrix("../text/array.txt", 3, 3);
    EXPECT_THROW(matrix.inverse(), MatrixException);
}


TEST(MatrixAdd, IntegerSquareMatrix)
{
    Matrix<int> matrix("../text/array.txt", 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix + matrix;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[2,\t4,\t6]\n"
                      "[8,\t10,\t12]\n"
                      "[14,\t16,\t18]\n"
                      "}");
}

TEST(MatrixAdd, Error)
{
    Matrix<int> matrix("../text/array.txt", 3, 3);
    Matrix<int> matrix1("../text/MatrixTestInteger", 3, 4);
    EXPECT_THROW(matrix + matrix1, MatrixException);
}

TEST(MatrixMultiplyByNumber, IntegerSquareMatrix)
{
    int** array = new int*[]{new int[]{1, 2, 3},
                             new int[]{4, 5, 6},
                             new int[]{7, 8, 9}};
    Matrix<int> matrix(array, 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix*2;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[2,\t4,\t6]\n"
                      "[8,\t10,\t12]\n"
                      "[14,\t16,\t18]\n"
                      "}");
}

TEST(MatrixMultiplyByNumber, IntegerSquareMatrixByFraction)
{
    int** array = new int*[]{new int[]{1, 2, 3},
                             new int[]{4, 5, 6},
                             new int[]{7, 8, 9}};
    Matrix<int> matrix(array, 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix*(0.5);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[0.5,\t1,\t1.5]\n"
                      "[2,\t2.5,\t3]\n"
                      "[3.5,\t4,\t4.5]\n"
                      "}");
}

TEST(MatrixMultiplyByMatrix, IntegerSquareMatrix)
{
    int** array = new int*[]{new int[]{1, 2, 3},
                             new int[]{4, 5, 6},
                             new int[]{7, 8, 9}};
    Matrix<int> matrix(array, 3, 3);
    testing::internal::CaptureStdout();
    std::cout << matrix * matrix;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[30,\t36,\t42]\n"
                      "[66,\t81,\t96]\n"
                      "[102,\t126,\t150]\n"
                      "}");
}

TEST(MatrixMultiplyByMatrix, IntegerMatrix)
{
    Matrix<float> matrix("../text/MatrixTestInteger", 4, 3);
    testing::internal::CaptureStdout();
    std::cout << (matrix * matrix.transpose());
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 3, height: 3, array:\n"
                      "[30,\t60,\t90]\n"
                      "[60,\t126,\t192]\n"
                      "[90,\t192,\t294]\n"
                      "}");
}

TEST(MatrixMultiplyByVector, IntegerMatrixIntegerVector)
{
    Matrix<int> matrix("../text/MatrixTestInteger", 4, 3);
    Matrix<int> matrix1("../text/multiplyVector1.txt", 1, 4);
    testing::internal::CaptureStdout();
    std::cout << matrix * matrix1;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 1, height: 3, array:\n"
                      "[30]\n"
                      "[60]\n"
                      "[90]\n"
                      "}");
}

TEST(MatrixMultiplyByVector, DoubleSquareMatrixDoubleVector)
{
    Matrix<double> matrix("../text/multiply", 5, 3);
    Matrix<double> matrix1("../text/multiplyVector2.txt", 1, 5);
    testing::internal::CaptureStdout();
    std::cout << matrix * matrix1;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "{Matrix:\n"
                      "width: 1, height: 3, array:\n"
                      "[60.0673]\n"
                      "[60.0673]\n"
                      "[60.0673]\n"
                      "}");
}

TEST(MatrixMultiplyByVector, Error)
{
    Matrix<double> matrix("../text/multiply", 5, 3);
    Matrix<double> matrix1("../text/multiplyVector2.txt", 1, 5);
    EXPECT_THROW(matrix1 * matrix, MatrixException);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

