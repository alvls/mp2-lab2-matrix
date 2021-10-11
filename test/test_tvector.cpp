
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
	TVector<int> v(7);
	TVector<int> tmp(v);
	EXPECT_EQ(v, tmp);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> v(7);
	TVector<int> tmp(v);
	EXPECT_NE(&v[0], &tmp[0]);
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
	ASSERT_ANY_THROW(v[-1]);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(4);
	ASSERT_ANY_THROW(v[6]);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> v(4);
	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> v(7);
	TVector<int> temp(7);
	ASSERT_NO_THROW(v = temp);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> v(7), temp(10);
	v = temp;
	EXPECT_EQ(10, v.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> v(7), temp(10);
	ASSERT_NO_THROW(v = temp);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> v(7), temp(7);
	for (int i = 0; i < 7; i++)
	{
		v[i] = i;
		temp[i] = i;
	}
	EXPECT_NO_THROW(v == temp);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> v(7);
	for (int i = 0; i < 7; i++)
	{
		v[i] = i;
	}
	EXPECT_NO_THROW(v == v);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> v(7), temp(8);
	EXPECT_NE(v.GetSize(), temp.GetSize());
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> v(7), temp(7);
	int a = 5;
	for (int i = 0; i < 7; i++)
	{
		v[i] = i;
		temp[i] = a + i;
	}
	v = v + a;
	EXPECT_NO_THROW(v == temp);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> v(7), temp(7);
	int a = 5;
	for (int i = 0; i < 7; i++)
	{
		v[i] = i;
		temp[i] = i - a;
	}
	v = v - a;
	EXPECT_NO_THROW(v == temp);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> v(7), temp(7);
	int a = 5;
	for (int i = 0; i < 7; i++)
	{
		v[i] = i;
		temp[i] = a * i;
	}
	v = v * a;
	EXPECT_NO_THROW(v == temp);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> v(3), temp(3), sum(3);
	for (int i = 0; i < 3; i++)
	{
		v[i] = i;
		temp[i] = i;
		sum[i] = v[i] + temp[i];
	}
	EXPECT_EQ(0, sum[0]);
	EXPECT_EQ(2, sum[1]);
	EXPECT_EQ(4, sum[2]);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> v(7), temp(8);
	EXPECT_ANY_THROW(v + temp);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> v(3), temp(3), sub(3);
	for (int i = 0; i < 3; i++)
	{
		v[i] = i;
		temp[i] = i * (i + 2);
		sub[i] = v[i] - temp[i];
	}
	EXPECT_EQ(0, sub[0]);
	EXPECT_EQ(-2, sub[1]);
	EXPECT_EQ(-6, sub[2]);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> v(7), temp(8);
	EXPECT_ANY_THROW(v - temp);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> v(3), temp(3), mul(3);
	for (int i = 0; i < 3; i++)
	{
		v[i] = i;
		temp[i] = i + 5;
		mul[i] = v[i] * temp[i];
	}
	EXPECT_EQ(0, mul[0]);
	EXPECT_EQ(6, mul[1]);
	EXPECT_EQ(14, mul[2]);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> v(7), temp(8);
	EXPECT_ANY_THROW(v * temp);
}

