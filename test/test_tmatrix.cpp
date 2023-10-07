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
	EXPECT_EQ(TMatrix<int>(m), m);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> m(5);
	EXPECT_NE(TMatrix<int>(m).GetVector(), m.GetVector());;
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> m(5);
	ASSERT_NO_THROW(m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> m(5);
	ASSERT_NO_THROW(m[1][1]);
	ASSERT_NO_THROW(m[1][1] = 0);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(TMatrix<int>(5)[-2]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(TMatrix<int>(5)[6]);;
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> m(5), c(5);
	ASSERT_NO_THROW(m = c);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> m(5), c(3);
	m = c;
	EXPECT_EQ(m.GetSize(), 3);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> m(5), c(3);
	ASSERT_NO_THROW(m = c);;
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
  TMatrix<int> m(5), c(m);
  EXPECT_EQ(m == c, true);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> m(5);
	EXPECT_EQ(m == m, true);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> m(5), c(3);
	EXPECT_NE(m, c);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m(5), c(5);
	ASSERT_NO_THROW(m + c);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m(5), c(3);
	ASSERT_ANY_THROW(m + c);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m(5), c(5);
	ASSERT_NO_THROW(m - c);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m(5), c(3);
	ASSERT_ANY_THROW(m - c);
}

TEST(TMatrix, test)
{
	TMatrix<int> a(2), b(2), c(2), res(2);
	a[1][1] = 1; b[1][1] = 1; res[1][1] = 2;
	c = a + b;
	EXPECT_EQ(c, res);
}

