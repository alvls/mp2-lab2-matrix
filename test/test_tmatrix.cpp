#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> m(5);
	TMatrix<int> m2(m);

	EXPECT_EQ(m, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(5);
	m[0][0] = 1; m[1][1] = 2;
	TMatrix<int> m2(m);
	m2[0][0] = 3; m2[1][1] = 4;

	EXPECT_NE(m, m2);
}

TEST(TMatrix, can_get_size)
{
	int size = 50;
	TMatrix<int> m(size);
	EXPECT_EQ(size, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	int size = 10;
	TMatrix<int> m(size);
	int i = 5;
	m[i][i] = i;
	EXPECT_EQ(m[i][i], i);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	int size = 10;
	TMatrix<int> m(size);
	int i = 5;
	ASSERT_ANY_THROW(m[-1][0] = i);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	int size = 10;
	TMatrix<int> m(size);

	ASSERT_ANY_THROW(m[100][9] = 5);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	int size = 10;
	TMatrix<int> m(size);

	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	int size = 7;
	TMatrix<int> m(size);
	TMatrix<int> m2(size);
	ASSERT_NO_THROW(m = m2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	int size = 7, size2 = 10;
	TMatrix<int> m(size);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(size2);
	m2[0][0] = 3; m2[9][9] = 4;
	m = m2;
	EXPECT_EQ(m.GetSize(), size2);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	int size = 7, size2 = 10;
	TMatrix<int> m(size);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(size2);
	m2[0][0] = 3; m2[9][9] = 4;
	ASSERT_NO_THROW(m = m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m(10);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(10);
	m2[0][0] = 1; m2[6][6] = 2;

	EXPECT_EQ(m == m2, true);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(10);
	m[0][0] = 1; m[6][6] = 2;
	EXPECT_EQ(m == m, true);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	int size = 7, size2 = 10;
	TMatrix<int> m(size);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(size2);
	m2[0][0] = 3; m2[9][9] = 4;
	EXPECT_EQ(m == m2, false);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m(10);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(10);
	m2[1][1] = 1; m2[9][9] = 2;
	ASSERT_NO_THROW(m + m2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m(10);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(15);
	m2[1][1] = 1; m2[9][9] = 2;
	ASSERT_ANY_THROW(m + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m(10);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(10);
	m2[1][1] = 1; m2[9][9] = 2;
	ASSERT_NO_THROW(m - m2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m(10);
	m[0][0] = 1; m[6][6] = 2;
	TMatrix<int> m2(15);
	m2[1][1] = 1; m2[9][9] = 2;
	ASSERT_ANY_THROW(m - m2);
}

