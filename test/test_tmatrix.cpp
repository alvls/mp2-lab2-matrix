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
	TDynamicMatrix<int> a(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> b(a);
	ASSERT_TRUE(a == b);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> a(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = i + j;
		}
	}
	TDynamicMatrix<int> b(a);
	int old1 = b[0][0];
	a[0][0] = -10;
	ASSERT_EQ(b[0][0], old1);
	int old2 = a[0][0];
	b[0][0] = -20;
	ASSERT_EQ(a[0][0], old2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> a(5);
	ASSERT_EQ(a.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> a(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = i + j;
		}
	}
	a[0][0] = 20;
	ASSERT_EQ(a[0][0], 20);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> a(5);
	ASSERT_ANY_THROW(a.at(-1,2));
	ASSERT_ANY_THROW(a.at(-1, -32)) ;
	ASSERT_ANY_THROW(a.at(1, -2));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	int sz = 6;
	TDynamicMatrix<int> a(sz);
	ASSERT_ANY_THROW(a.at(sz + 1, sz - 2));
	ASSERT_ANY_THROW(a.at(sz, sz - 1));
	ASSERT_ANY_THROW(a.at(sz -1, sz + 2));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = i + j;
		}
	}
	b = a;
	a = a;
	ASSERT_TRUE(a == b);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = i + j;
		}
	}
	b = a;
	ASSERT_TRUE(a == b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(3);
	b = a;
	ASSERT_EQ(5, b.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(3);
	b = a;
	ASSERT_NO_THROW(a.size(), b.size());
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = i + j;
			b[i][j] = i + j;
		}
	}
	ASSERT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> a(5);
	ASSERT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(2);
	ASSERT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(5);
	TDynamicMatrix<int> c(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = 2* i + 10 * j;
			b[i][j] = i + j;
		}
	}
	c = a + b;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			ASSERT_EQ(c[i][j], a[i][j] + b[i][j]);
		}
	}
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(2);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(5);
	TDynamicMatrix<int> c(5);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			a[i][j] = 2 * i + 3 * j;
			b[i][j] = i + j;
		}
	}
	c = a - b;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			ASSERT_EQ(c[i][j], a[i][j] - b[i][j]);
		}
	}
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> a(5);
	TDynamicMatrix<int> b(2);
	ASSERT_ANY_THROW(a - b);
}


