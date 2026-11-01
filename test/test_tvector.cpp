#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, throws_when_create_vector_with_zero_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(0));
}

TEST(TDynamicVector, can_create_vector_from_array)
{
  int arr[3] = { 1, 2, 3 };
  TDynamicVector<int> v(arr, 3);

  EXPECT_EQ(3, v.size());
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(5);
  for (int i = 0; i < 5; i++)
    v[i] = i * 2;
  TDynamicVector<int> v1(v);

  EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(5);
  v[0] = 1;
  TDynamicVector<int> v1(v);

  v1[0] = 100;

  EXPECT_EQ(1, v[0]);
  EXPECT_NE(&v[0], &v1[0]);
}

TEST(TDynamicVector, can_move_vector)
{
  TDynamicVector<int> v(3);
  v[0] = 7;
  TDynamicVector<int> v1(std::move(v));

  EXPECT_EQ(3, v1.size());
  EXPECT_EQ(7, v1[0]);
}

TEST(TDynamicVector, can_move_assign_vector)
{
  TDynamicVector<int> v(3), v1(5);
  v[2] = 4;

  v1 = std::move(v);

  EXPECT_EQ(3, v1.size());
  EXPECT_EQ(4, v1[2]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, can_set_and_get_element_with_at)
{
  TDynamicVector<int> v(4);
  v.at(3) = 9;

  EXPECT_EQ(9, v.at(3));
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(4);

  ASSERT_ANY_THROW(v.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);

  ASSERT_ANY_THROW(v.at(4) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  ASSERT_NO_THROW(v = v);
  EXPECT_EQ(3, v.size());
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 5;
  v1[2] = 6;

  v2 = v1;

  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v1(3), v2(6);

  v2 = v1;

  EXPECT_EQ(3, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v1(3), v2(6);
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

  v2 = v1;

  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[1] = 8;
  v2[1] = 8;

  EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(3);
  v[0] = 2;

  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v1(3), v2(4);

  EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, vectors_with_different_elements_are_not_equal)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[2] = 1;

  EXPECT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3), expV(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  expV[0] = 6;
  expV[1] = 7;
  expV[2] = 8;

  EXPECT_EQ(expV, v + 5);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3), expV(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  expV[0] = -1;
  expV[1] = 0;
  expV[2] = 1;

  EXPECT_EQ(expV, v - 2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3), expV(3);
  v[0] = 1;
  v[1] = 2;
  v[2] = 3;
  expV[0] = 3;
  expV[1] = 6;
  expV[2] = 9;

  EXPECT_EQ(expV, v * 3);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3), expV(3);
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;
  v2[0] = 10;
  v2[1] = 20;
  v2[2] = 30;
  expV[0] = 11;
  expV[1] = 22;
  expV[2] = 33;

  EXPECT_EQ(expV, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3), v2(4);

  ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3), expV(3);
  v1[0] = 5;
  v1[1] = 5;
  v1[2] = 5;
  v2[0] = 1;
  v2[1] = 2;
  v2[2] = 3;
  expV[0] = 4;
  expV[1] = 3;
  expV[2] = 2;

  EXPECT_EQ(expV, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3), v2(4);

  ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v1(3), v2(3);
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;
  v2[0] = 4;
  v2[1] = 5;
  v2[2] = 6;

  EXPECT_EQ(32, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v1(3), v2(4);

  ASSERT_ANY_THROW(v1 * v2);
}
