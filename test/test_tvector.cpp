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
	TVector<int> v(10);
	for (int i = 0; i < 10; i++) {
		v[i] = 1;
	}
	TVector<int> tmp(v);
  EXPECT_EQ(v,tmp);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int>tmp1(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
	}
	TVector<int> tmp2(tmp1);
	tmp1[0] = 3;
	EXPECT_EQ(0, tmp2[0]);
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
	TVector<int>tmp(4);
	ASSERT_ANY_THROW(tmp[-1] = 1);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int>tmp(4);
	ASSERT_ANY_THROW(tmp[5] = 1);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int>tmp(2);
	for (int i = 0; i < 2; i++) {
		tmp[i] = i;
	}
	tmp = tmp;
	EXPECT_EQ(0, tmp[0]);
	EXPECT_EQ(1, tmp[1]);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
	}
	tmp2 = tmp1;
	EXPECT_EQ(0, tmp1[0]);
	EXPECT_EQ(1, tmp1[1]);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(5);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
	}
	tmp2 = tmp1;
	EXPECT_EQ(2, tmp2.GetSize());
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(5);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
	}
	tmp2 = tmp1;
	EXPECT_EQ(0, tmp1[0]);
	EXPECT_EQ(1, tmp1[1]);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
		tmp2[i] = i;
	}
	EXPECT_EQ(true, tmp1 == tmp2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int>tmp1(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
	}
	EXPECT_EQ(true, tmp1 == tmp1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(5);
	EXPECT_EQ(false, tmp1 == tmp2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int>tmp1(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
	}
	tmp1 =tmp1+ 3;
	EXPECT_EQ(3, tmp1[0]);
	EXPECT_EQ(4, tmp1[1]);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int>tmp1(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i;
	}
	tmp1 = tmp1 - 3;
	EXPECT_EQ(-3, tmp1[0]);
	EXPECT_EQ(-2, tmp1[1]);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int>tmp1(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i+1;
	}
	tmp1 = tmp1 * 3;
	EXPECT_EQ(3, tmp1[0]);
	EXPECT_EQ(6, tmp1[1]);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i+1;
		tmp2[i] = i;
	}
	TVector<int> tmp3 = tmp1 + tmp2;
	EXPECT_EQ(1, tmp3[0]);
	EXPECT_EQ(3, tmp3[1]);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> tmp1(2), tmp2(5);
	ASSERT_ANY_THROW(tmp1+tmp2);
}


TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i + 1;
		tmp2[i] = i;
	}
	TVector<int> tmp3 = tmp1 - tmp2;
	EXPECT_EQ(1, tmp3[0]);
	EXPECT_EQ(1, tmp3[1]);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> tmp1(2), tmp2(5);
	ASSERT_ANY_THROW(tmp1 - tmp2);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int>tmp1(2);
	TVector<int>tmp2(2);
	for (int i = 0; i < 2; i++) {
		tmp1[i] = i + 1;
		tmp2[i] = i;
	}
	int tmp3;
	tmp3 = tmp1 * tmp2;
	EXPECT_EQ(2, tmp3);	
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> tmp1(2), tmp2(5);
	ASSERT_ANY_THROW(tmp1 * tmp2);
}

