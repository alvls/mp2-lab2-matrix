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
	TMatrix<int> m2(5);
	EXPECT_EQ(m2,m);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(m);
	EXPECT_NE(&m[1], &m2[1]);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(7);
	ASSERT_NO_THROW(m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(7);
	m[0][0] = 1;
	ASSERT_NO_THROW(m[0][0] = 1);
	ASSERT_NO_THROW(m[0][0]);
	EXPECT_EQ(m[0][0], 1);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> m(7);
	ASSERT_ANY_THROW(m[-1][0] = 2);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> m(7);
	ASSERT_ANY_THROW(m[MAX_MATRIX_SIZE + 10][2] = 2);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(7);
	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(7);
	ASSERT_NO_THROW(m = m2);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(1);
	m2 = m;
	EXPECT_EQ(m2.GetSize(),m.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(1);
	ASSERT_NO_THROW(m = m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(7);
	m = m2;
	ASSERT_EQ(m == m2, true);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(7);
	ASSERT_EQ(m == m, true);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(3);
	ASSERT_EQ(m == m2, false);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(7);
	ASSERT_NO_THROW(m + m2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(2);
	ASSERT_ANY_THROW(m + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(7);
	ASSERT_NO_THROW(m - m2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m(7);
	TMatrix<int> m2(2);
	ASSERT_ANY_THROW(m - m2);
}

