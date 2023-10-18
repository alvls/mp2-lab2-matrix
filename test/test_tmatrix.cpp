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
	TMatrix<int> sourceMatrix(3);
	TMatrix<int> copiedMatrix(sourceMatrix);
	EXPECT_EQ(sourceMatrix, copiedMatrix);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> mx1(2);
	mx1[0][0] = 1;
	TMatrix<int> mx2(mx1);
	mx2[0][0] = 2;
	EXPECT_NE(mx1, mx2);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> mx1(1);

	EXPECT_EQ(1, mx1.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> mx1(2);

	int i = 1;
	mx1[i][i] = i;

	EXPECT_EQ(mx1[i][i], i);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> mx(2);
	int i = 1;

	ASSERT_ANY_THROW(mx[-1][0] = i);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> mx(2);

	ASSERT_ANY_THROW(mx[10000][10000] = 1);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> mx(2);
	ASSERT_NO_THROW(mx = mx);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> mx1(2);
	TMatrix<int> mx2(2);
	ASSERT_NO_THROW(mx1 = mx2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	int size1 = 5, size2 = 10;
	TMatrix<int> mx1(size1);
	TMatrix<int> mx2(size2);

	mx1 = mx2;

	EXPECT_EQ(mx1.GetSize(), mx2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> mx1(5);
	TMatrix<int> mx2(10);

	mx1[0][0] = 1;

	ASSERT_NO_THROW(mx1 = mx2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> mx1(2);
	TMatrix<int> mx2(2);

	mx1[0][0] = 10; mx1[1][0] = 11;
	mx2[0][0] = 10; mx2[1][0] = 11;

	EXPECT_EQ(mx1, mx2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> mx(2);

	mx[0][0] = 1;

	EXPECT_EQ(mx, mx);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> mx1(1);
	TMatrix<int> mx2(2);

	EXPECT_NE(mx1, mx2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> mx1(1);
	TMatrix<int> mx2(1);

	mx1[0][0] = 1;
	mx2[0][0] = 2;

	EXPECT_NO_THROW(mx1 + mx2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> mx1(3);
	TMatrix<int> mx2(7);

	ASSERT_ANY_THROW(mx1 + mx2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> mx1(1);
	TMatrix<int> mx2(1);

	mx1[0][0] = 1;
	mx2[0][0] = 2;

	EXPECT_NO_THROW(mx1 - mx2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> mx1(2);
	TMatrix<int> mx2(6);

	ASSERT_ANY_THROW(mx1 - mx2);
}

