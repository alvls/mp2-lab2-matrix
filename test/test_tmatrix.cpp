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
	const int size = 5;
	TMatrix<int> m(size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i; j < size; j++)
		{
			m[i][j] = j;
		}
	}
	TMatrix<int> copy = m;

	EXPECT_EQ(m, copy);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	const int size = 5;
	TMatrix<int> m(size);
	TMatrix<int> copy(m);

	EXPECT_NE(&m[0], &copy[0]);
}

TEST(TMatrix, can_get_size)
{
	const int size = 5;
	TMatrix<int> m(size);

	EXPECT_EQ(size, m.GetSize());
}

TEST(TMatrix, can_set_and_get_element)
{
	const int size = 5;
	TMatrix<int> m(size);
	m[1][2] = 3;

	EXPECT_EQ(3, m[1][2]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	const int size = 5;
	TMatrix<int> m(size);

	ASSERT_ANY_THROW(m[2][-3] = 7);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	const int size = 5;
	TMatrix<int> m(size);
	
	ASSERT_ANY_THROW(m[size + 1][size + 100] = 7);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	const int size = 5;
	TMatrix<int> m(size);

	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	const int size = 5;
	TMatrix<int> m1(size);
	TMatrix<int> m2(size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i; j < size; j++)
		{
			m1[i][j] = j;
		}
	}
	m2 = m1;

	EXPECT_EQ(1, m2[1][1]);
	EXPECT_EQ(4, m2[1][4]);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	const int size1 = 5;
	const int size2 = 7;
	TMatrix<int> m1(size1);
	TMatrix<int> m2(size2);
	m2 = m1;

	EXPECT_EQ(5, m2.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	const int size1 = 5;
	const int size2 = 7;
	TMatrix<int> m1(size1);
	TMatrix<int> m2(size2);
	for (size_t i = 0; i < size1; i++)
	{
		for (size_t j = i; j < size1; j++)
		{
			m1[i][j] = j;
		}
	}
	m2 = m1;
	
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	const int size = 5;
	TMatrix<int> m1(size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i; j < size; j++)
		{
			m1[i][j] = j;
		}
	}
	TMatrix<int> m2 = m1;

	EXPECT_EQ(true, m1 == m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	const int size = 5;
	TMatrix<int> m(size);
	EXPECT_EQ(true, m == m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	const int size1 = 5;
	const int size2 = 7;
	TMatrix<int> m1(size1);
	TMatrix<int> m2(size2);

	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	const int size = 5;
	TMatrix<int> m1(size);
	TMatrix<int> m2(size);
	TMatrix<int> result(size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i; j < size; j++)
		{
			m1[i][j] = m2[i][j] = j;
			result[i][j] = m1[i][j] + m2[i][j];
		}
	}

	EXPECT_EQ(result, m1 + m2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	const int size1 = 5;
	const int size2 = 7;
	TMatrix<int> m1(size1);
	TMatrix<int> m2(size2);
	
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	const int size = 5;
	TMatrix<int> m1(size);
	TMatrix<int> m2(size);
	TMatrix<int> result(size);
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = i; j < size; j++)
		{
			m1[i][j] = m2[i][j] = j;
			result[i][j] = m1[i][j] - m2[i][j];
		}
	}

	EXPECT_EQ(result, m1 - m2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	const int size1 = 5;
	const int size2 = 7;
	TMatrix<int> m1(size1);
	TMatrix<int> m2(size2);

	ASSERT_ANY_THROW(m1 - m2);
}

