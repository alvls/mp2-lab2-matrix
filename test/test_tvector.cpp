#include "TVector.h"
#include "..\src\TVector.cpp"

#include <gtest.h>

using testing::Types;

template <class>
class TDynamicVectorTest : public testing::Test {};
typedef Types<int, double> Implementations;
TYPED_TEST_CASE(TDynamicVectorTest, Implementations);

TYPED_TEST(TDynamicVectorTest, can_create_vector_with_positive_size)
{
  ASSERT_NO_THROW(TDynamicVector<TypeParam> vec(3));
}

TYPED_TEST(TDynamicVectorTest, can_not_create_vector_with_negative_size)
{
  ASSERT_ANY_THROW(TDynamicVector<TypeParam> vec(-1));
}

TYPED_TEST(TDynamicVectorTest, can_create_vector_from_other_vector)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 0;
  vec1[1] = 1;
  TDynamicVector<TypeParam> vec2(vec1);
  EXPECT_EQ(vec1.GetSize(), vec2.GetSize());
  EXPECT_EQ(vec1[0], vec2[0]);
  EXPECT_EQ(vec1[1], vec2[1]);
}

TYPED_TEST(TDynamicVectorTest, can_not_create_vector_from_vector_with_zero_size_or_nullptr_pmem)
{
  TDynamicVector<TypeParam> vec1;
  ASSERT_ANY_THROW(TDynamicVector<TypeParam> vec2(vec1));
}

TYPED_TEST(TDynamicVectorTest, can_get_size)
{
  TDynamicVector<TypeParam> vec(3);
  EXPECT_EQ(3, vec.GetSize());
}

TYPED_TEST(TDynamicVectorTest, can_resize_vector)
{
  TDynamicVector<TypeParam> vec1(1);
  vec1[0] = 0;
  vec1.Resize(2);
  vec1[1] = 1;
  EXPECT_EQ(vec1.GetSize(), 2);
  EXPECT_EQ(vec1[0], 0);
  EXPECT_EQ(vec1[1], 1);
}

TYPED_TEST(TDynamicVectorTest, can_not_resize_vector_to_negative_size)
{
  TDynamicVector<TypeParam> vec1(1);
  ASSERT_ANY_THROW(vec1.Resize(-1));
}

TYPED_TEST(TDynamicVectorTest, can_copy_vector)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 0;
  vec1[1] = 1;
  TDynamicVector<TypeParam> vec2 = vec1;
  EXPECT_EQ(vec1.GetSize(), vec2.GetSize());
  EXPECT_EQ(vec1[0], vec2[0]);
  EXPECT_EQ(vec1[1], vec2[1]);
}

TYPED_TEST(TDynamicVectorTest, can_not_copy_vector_to_itself)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 0;
  vec1[1] = 1;
  ASSERT_ANY_THROW(vec1 = vec1);
}

TYPED_TEST(TDynamicVectorTest, can_check_vector_equivalence)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 0;
  vec1[1] = 1;
  TDynamicVector<TypeParam> vec2(2);
  vec2[0] = 0;
  vec2[1] = 1;
  EXPECT_EQ(vec1 == vec2, true);
}

TYPED_TEST(TDynamicVectorTest, can_check_vector_nonequivalence)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 0;
  vec1[1] = 1;
  TDynamicVector<TypeParam> vec2(2);
  vec2[0] = 0;
  vec2[1] = 1;
  EXPECT_EQ(vec1 != vec2, false);
}

TYPED_TEST(TDynamicVectorTest, can_not_check_vector_equivalence_with_nullptr)
{
  TDynamicVector<TypeParam> vec1;
  TDynamicVector<TypeParam> vec2;
  ASSERT_ANY_THROW(vec1 == vec2);
}

TYPED_TEST(TDynamicVectorTest, can_not_check_vector_nonequivalence_with_nullptr)
{
  TDynamicVector<TypeParam> vec1;
  TDynamicVector<TypeParam> vec2;
  ASSERT_ANY_THROW(vec1 != vec2);
}

TYPED_TEST(TDynamicVectorTest, can_sum_vectors)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 1;
  vec1[1] = 2;
  TDynamicVector<TypeParam> vec2(2);
  vec2[0] = 1;
  vec2[1] = 2;
  TDynamicVector<TypeParam> vec3 = vec1 + vec2;
  EXPECT_EQ(vec3.GetSize(), 2);
  EXPECT_EQ(vec3[0], 2);
  EXPECT_EQ(vec3[1], 4);
}

TYPED_TEST(TDynamicVectorTest, can_substract_vectors)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 5;
  vec1[1] = 7;
  TDynamicVector<TypeParam> vec2(2);
  vec2[0] = 1;
  vec2[1] = 2;
  TDynamicVector<TypeParam> vec3 = vec1 - vec2;
  EXPECT_EQ(vec3.GetSize(), 2);
  EXPECT_EQ(vec3[0], 4);
  EXPECT_EQ(vec3[1], 5);
}

TYPED_TEST(TDynamicVectorTest, can_scalar_multiply_vectors)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 5;
  vec1[1] = 7;
  TDynamicVector<TypeParam> vec2(2);
  vec2[0] = 1;
  vec2[1] = 2;
  TypeParam res = vec1 * vec2;
  EXPECT_EQ(res, 5 * 1 + 7 * 2);
}

TYPED_TEST(TDynamicVectorTest, can_sum_vector_with_scalar)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 1;
  vec1[1] = 2;
  TDynamicVector<TypeParam> vec2 = vec1 + 6;
  EXPECT_EQ(vec2.GetSize(), 2);
  EXPECT_EQ(vec2[0], 7);
  EXPECT_EQ(vec2[1], 8);
}

TYPED_TEST(TDynamicVectorTest, can_substract_scalar_from_vector)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 5;
  vec1[1] = 7;
  TDynamicVector<TypeParam> vec2 = vec1 - 2;
  EXPECT_EQ(vec2.GetSize(), 2);
  EXPECT_EQ(vec2[0], 3);
  EXPECT_EQ(vec2[1], 5);
}

TYPED_TEST(TDynamicVectorTest, can_multiply_vector_on_scalar)
{
  TDynamicVector<TypeParam> vec1(2);
  vec1[0] = 5;
  vec1[1] = 7;
  TDynamicVector<TypeParam> vec2 = vec1 * 2;
  EXPECT_EQ(vec2[0], 5 * 2);
  EXPECT_EQ(vec2[1], 7 * 2);
}