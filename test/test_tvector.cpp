#include "utmatrix.h"

#include <gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
  TVector<int> v(10);

  ASSERT_NO_THROW(TVector<int> v1(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> source(3);
	for (size_t i = 0; i < 3; i++)
	{
		source[i] = i;
	}
	TVector<int> copy(source);

	EXPECT_EQ(source,copy);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v(7);
	TVector<int> copy(v);

	EXPECT_NE(&v[0], &copy[0]);
}

TEST(TVector, can_get_size)
{
	TVector<int> v(4);

	EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
  TVector<int> v(4, 2);

  EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(4);

	ASSERT_ANY_THROW(v[-2] = 3);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(4);

	ASSERT_ANY_THROW(v[7] = 3);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(3);

	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	const int size = 4;
	TVector<int> v1(size);
	TVector<int> v2(size);
	for (size_t i = 0; i < size; i++)
	{
		v1[i] = i;
	}
	v2 = v1;

	EXPECT_EQ(v2, v1);
}

TEST(TVector, assign_operator_change_vector_size)
{
	const int sizeV1 = 7;
	const int sizeV2 = 3;
	TVector<int> v1(sizeV1);
	TVector<int> v2(sizeV2);
	v1 = v2;

	EXPECT_EQ(sizeV2, v1.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	const int sizeV1 = 5;
	const int sizeV2 = 3;
	TVector<int> v1(sizeV1);
	TVector<int> v2(sizeV2);
	for (size_t i = 0; i < sizeV1; i++)
	{
		v1[i] = i;
	}
	v2 = v1;

	EXPECT_EQ(v2, v1);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	const int size = 7;
	TVector<int> v1(size);
	for (size_t i = 0; i < size; i++)
	{
		v1[i] = i;
	}
	TVector<int> v2(v1);

	EXPECT_EQ(true, v1 == v2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	const int size = 7;
	TVector<int> v(size);
	for (size_t i = 0; i < size; i++)
	{
		v[i] = i;
	}

	EXPECT_EQ(true, v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	const int sizeV1 = 5;
	const int sizeV2 = 3;
	TVector<int> v1(sizeV1);
	TVector<int> v2(sizeV2);

	EXPECT_NE(v1, v2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	const int size = 4;
	int scalar = 7;
	TVector<int> v(size);
	TVector<int> result(size);
	for (size_t i = 0; i < size; i++)
	{
		v[i] = i;
		result[i] = v[i] + scalar;
	}
	
	EXPECT_EQ(result, v + scalar);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	const int size = 4;
	int scalar = 7;
	TVector<int> v(size);
	TVector<int> result(size);
	for (size_t i = 0; i < size; i++)
	{
		v[i] = i;
		result[i] = v[i] - scalar;
	}

	EXPECT_EQ(result, v - scalar);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	const int size = 4;
	int scalar = 7;
	TVector<int> v(size);
	TVector<int> result(size);
	for (size_t i = 0; i < size; i++)
	{
		v[i] = i;
		result[i] = v[i] * scalar;
	}

	EXPECT_EQ(result, v * scalar);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	const int size = 7;
	TVector<int> v1(size);
	TVector<int> v2(size);
	TVector<int> result(size);
	for (size_t i = 0; i < size; i++)
	{
		v1[i] = v2[i] = i;
		result[i] = v1[i] + v2[i];
	}
	
	EXPECT_EQ(result, v1 + v2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	const int size1 = 7;
	const int size2 = 3;
	TVector<int> v1(size1);
	TVector<int> v2(size2);
	
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	const int size = 7;
	TVector<int> v1(size);
	TVector<int> v2(size);
	TVector<int> result(size);
	for (size_t i = 0; i < size; i++)
	{
		v1[i] = i * 5;
		v2[i] = i * 3;
		result[i] = v1[i] - v2[i];
	}

	EXPECT_EQ(result, v1 - v2);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	const int size1 = 7;
	const int size2 = 3;
	TVector<int> v1(size1);
	TVector<int> v2(size2);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	const int size = 7;
	TVector<int> v1(size);
	TVector<int> v2(size);
	int result = 0;
	for (size_t i = 0; i < size; i++)
	{
		v1[i] = v2[i] = i;
		result += v1[i] * v2[i];
	}

	EXPECT_EQ(result, v1 * v2);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	const int size1 = 7;
	const int size2 = 3;
	TVector<int> v1(size1);
	TVector<int> v2(size2);

	ASSERT_ANY_THROW(v1 * v2);
}

