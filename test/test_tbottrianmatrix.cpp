#include "TBotTrianMatrix.h"
#include "..\src\TBotTrianMatrix.cpp"

#include <gtest.h>

using testing::Types;

template <class T>
class TDynamicBotTrianMatrixTest : public testing::Test {};
typedef Types<int, double> Implementations;

TYPED_TEST_CASE(TDynamicBotTrianMatrixTest, Implementations);

TYPED_TEST(TDynamicBotTrianMatrixTest, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicBotTrianMatrix<TypeParam> mat(3));
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_not_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicBotTrianMatrix<TypeParam> mat(-1));
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_get_matrix_size)
{
  TDynamicBotTrianMatrix<TypeParam> mat(3);

  EXPECT_EQ(3, mat.GetSize());
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_compare_matrix_equivalence)
{
  TDynamicBotTrianMatrix<TypeParam> mat1(2);
  TDynamicBotTrianMatrix<TypeParam> mat2(2);
  mat1[0][0] = 0;
  mat1[0][1] = 1;
  mat1[1][0] = 2;
  mat2[0][0] = 0;
  mat2[0][1] = 1;
  mat2[1][0] = 2;
  EXPECT_EQ(mat1 == mat2, true);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_compare_matrix_nonequivalence)
{
  TDynamicBotTrianMatrix<TypeParam> mat1(2);
  TDynamicBotTrianMatrix<TypeParam> mat2(2);
  mat1[0][0] = 0;
  mat1[0][1] = 1;
  mat1[1][0] = 2;
  mat2[0][0] = 1;
  mat2[0][1] = 1;
  mat2[1][0] = 2;
  EXPECT_EQ(mat1 != mat2, true);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_not_compare_empty_matrix_equivalence)
{
  TDynamicBotTrianMatrix<TypeParam> mat1;
  TDynamicBotTrianMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(mat1 == mat2);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_not_compare_empty_matrix_nonequivalence)
{
  TDynamicBotTrianMatrix<TypeParam> mat1;
  TDynamicBotTrianMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(mat1 != mat2);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_sum_matrixes)
{
  TDynamicBotTrianMatrix<TypeParam> mat1(2);
  TDynamicBotTrianMatrix<TypeParam> mat2(2);
  mat1[0][0] = 0;
  mat1[0][1] = 1;
  mat1[1][0] = 2;
  mat2[0][0] = 1;
  mat2[0][1] = 1;
  mat2[1][0] = 2;
  TDynamicBotTrianMatrix<TypeParam> mat3 = mat1 + mat2;
  EXPECT_EQ(mat3[0][0], 1);
  EXPECT_EQ(mat3[0][1], 2);
  EXPECT_EQ(mat3[1][0], 4);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_substract_matrixes)
{
  TDynamicBotTrianMatrix<TypeParam> mat1(2);
  TDynamicBotTrianMatrix<TypeParam> mat2(2);
  mat1[0][0] = 3;
  mat1[0][1] = 5;
  mat1[1][0] = 7;
  mat2[0][0] = 1;
  mat2[0][1] = 1;
  mat2[1][0] = 2;
  TDynamicBotTrianMatrix<TypeParam> mat3 = mat1 - mat2;
  EXPECT_EQ(mat3[0][0], 2);
  EXPECT_EQ(mat3[0][1], 4);
  EXPECT_EQ(mat3[1][0], 5);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_not_sum_empty_matrixes)
{
  TDynamicBotTrianMatrix<TypeParam> mat1;
  TDynamicBotTrianMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(TDynamicBotTrianMatrix<TypeParam> mat3 = mat1 + mat2);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_not_substract_empty_matrixes)
{
  TDynamicBotTrianMatrix<TypeParam> mat1;
  TDynamicBotTrianMatrix<TypeParam> mat2;
  ASSERT_ANY_THROW(TDynamicBotTrianMatrix<TypeParam> mat3 = mat1 - mat2);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_not_sum_matrixes_differrent_sizes)
{
  TDynamicBotTrianMatrix<TypeParam> mat1(1);
  TDynamicBotTrianMatrix<TypeParam> mat2(2);
  ASSERT_ANY_THROW(TDynamicBotTrianMatrix<TypeParam> mat3 = mat1 + mat2);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_not_substract_matrixes_differrent_sizes)
{
  TDynamicBotTrianMatrix<TypeParam> mat1(1);
  TDynamicBotTrianMatrix<TypeParam> mat2(2);
  ASSERT_ANY_THROW(TDynamicBotTrianMatrix<TypeParam> mat3 = mat1 - mat2);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_mult_matrixes)
{
  TDynamicBotTrianMatrix<TypeParam> mat1(2);
  TDynamicBotTrianMatrix<TypeParam> mat2(2);
  mat1[0][0] = 3;
  mat1[0][1] = 5;
  mat1[1][0] = 7;
  mat2[0][0] = 1;
  mat2[0][1] = 1;
  mat2[1][0] = 2;
  TDynamicBotTrianMatrix<TypeParam> mat3 = mat1 * mat2;
  EXPECT_EQ(mat3[0][0], 3);
  EXPECT_EQ(mat3[0][1], 12);
  EXPECT_EQ(mat3[1][0], 14);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_mult_matrix_on_vector)
{
  TDynamicBotTrianMatrix<TypeParam> mat(2);
  TDynamicVector<TypeParam> vec1(2);
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  vec1[0] = 1;
  vec1[1] = 2;
  TDynamicVector<TypeParam> vec2 = mat * vec1;
  EXPECT_EQ(vec2[0], 1);
  EXPECT_EQ(vec2[1], 8);
}

TYPED_TEST(TDynamicBotTrianMatrixTest, can_mult_matrix_on_scalar)
{
  TDynamicBotTrianMatrix<TypeParam> mat(2);
  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[1][0] = 3;
  TDynamicBotTrianMatrix<TypeParam> res = mat * 2;
  EXPECT_EQ(res[0][0], 2);
  EXPECT_EQ(res[0][1], 4);
  EXPECT_EQ(res[1][0], 6);
}