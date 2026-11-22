#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(m);

    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(5);
    TDynamicMatrix<int> m1(m);

    m[1][1] = 5;

    EXPECT_EQ(m1[1][1], 0);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5);

    EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 4;

    EXPECT_EQ(4, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(5);

    ASSERT_ANY_THROW(m.at(-2).at(0) = 4);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(5);

    ASSERT_ANY_THROW(m.at(10001).at(0) = 4);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 4;

    ASSERT_NO_THROW(m = m);

    EXPECT_EQ(m[0][0], 4);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m(5), m2(5);
    m[0][0] = 4;

    ASSERT_NO_THROW(m2 = m);

    EXPECT_EQ(m2[0][0], 4);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m(5), m2(10);
    m[0][0] = 4;

    ASSERT_NO_THROW(m2 = m);

    EXPECT_EQ(m2.size(), m.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m(5), m2(10);
    m[0][0] = 4;

    ASSERT_NO_THROW(m2 = m);

    EXPECT_EQ(m2[0][0], 4);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 4;

    TDynamicMatrix<int> m2(m);

    EXPECT_EQ(m, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(5);
    m[0][0] = 4;

    EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m(5), m2(10);

    EXPECT_NE(m, m2);
}

TEST(TDynamicMatrix, can_add_scalar_to_matrix) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 2; m[0][1] = 4; m[1][0] = 8; m[1][1] = 16;
    m1[0][0] = 7; m1[0][1] = 9; m1[1][0] = 13; m1[1][1] = 21;

    ASSERT_NO_THROW(m = m + 5);

    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_subtract_scalar_to_matrix) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 2; m[0][1] = 4; m[1][0] = 8; m[1][1] = 16;
    m1[0][0] = -3; m1[0][1] = -1; m1[1][0] = 3; m1[1][1] = 11;

    ASSERT_NO_THROW(m = m - 5);

    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_multiply_scalar_to_matrix) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 2; m[0][1] = 4; m[1][0] = 8; m[1][1] = 16;
    m1[0][0] = 10; m1[0][1] = 20; m1[1][0] = 40; m1[1][1] = 80;

    ASSERT_NO_THROW(m = m * 5);

    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_transpos) {
    TDynamicMatrix<int> m(2), m1(2);
    m[0][0] = 2; m[0][1] = 4; m[1][0] = 8; m[1][1] = 16;
    m1[0][0] = 2; m1[0][1] = 8; m1[1][0] = 4; m1[1][1] = 16;

    ASSERT_NO_THROW(m = m.Transpos());

    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(5), m2(5), m3(5);
    m[0][0] = 4;
    m2[0][0] = 5;
    m3[0][0] = 9;

    TDynamicMatrix<int> result;

    ASSERT_NO_THROW(result = m + m2);

    EXPECT_EQ(result, m3);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(5), m2(6);

    ASSERT_ANY_THROW(m + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(5), m2(5), m3(5);
    m[0][0] = 4;
    m2[0][0] = 5;
    m3[0][0] = -1;

    TDynamicMatrix<int> result;

    ASSERT_NO_THROW(result = m - m2);

    EXPECT_EQ(result, m3);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m(5), m2(6);

    ASSERT_ANY_THROW(m - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(5), m2(5), m3(5);
    m[0][0] = 4;
    m2[0][0] = 5;
    m3[0][0] = 20;

    TDynamicMatrix<int> result;

    ASSERT_NO_THROW(result = m * m2);

    EXPECT_EQ(result, m3);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(5), m2(6);

    ASSERT_ANY_THROW(m * m2);
}

TEST(TDynamicMatrix, can_output_matrix) {
    TDynamicMatrix<int> m(3);
    m[0][0] = 1; m[1][1] = 2; m[2][2] = 3;

    std::ostringstream str;
    str << m;

    EXPECT_EQ(str.str(), "1 0 0 \n0 2 0 \n0 0 3 \n");
}

TEST(TDynamicMatrix, can_input_matrix) {
    std::string str1 = "1 0 0\n0 2 0\n0 0 3";
    TDynamicMatrix<int> m(3), m1(3);
    m[0][0] = 1; m[1][1] = 2; m[2][2] = 3;

    std::istringstream str(str1);
    str >> m1;

    EXPECT_EQ(m, m1);
}
