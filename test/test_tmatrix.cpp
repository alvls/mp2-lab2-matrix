#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length){
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix){
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length){
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix){
  TMatrix<int> m(5);
  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one){
	TMatrix<int> m1(5);
	TMatrix<int> m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory){
	TMatrix<int> m1(10);
	TMatrix<int> m2(m1);
	EXPECT_NE(&m1[0], &m2[0]);
}

TEST(TMatrix, can_get_size){
	TMatrix<int> m(10);
	EXPECT_EQ(10,m.GetSize());
}

TEST(TMatrix, can_set_and_get_element){
	TMatrix<int> m(10);
	TVector<int> v(15);
	for (int i = 0; i < v.GetSize(); i++) { v[i] = 15; }
	m[0] = v;
	EXPECT_EQ(v, m[0]);
}

TEST(TMatrix, throws_when_set_element_with_negative_index){
	TMatrix<int> m(10);
	ASSERT_ANY_THROW(m[-1]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index){
	TMatrix<int> m(10);
	ASSERT_ANY_THROW(m[10+1]);
}

TEST(TMatrix, can_assign_matrix_to_itself){
	TMatrix<int> m(10);
	ASSERT_NO_THROW(m = m);
}

TEST(TMatrix, can_assign_matrices_of_equal_size){
	TMatrix<int> m1(10);
	TMatrix<int> m2(10);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TMatrix, assign_operator_change_matrix_size){
	TMatrix<int> m1(10);
	TMatrix<int> m2(15);
	TMatrix<int> m3(m1);
	m1 = m2;
	EXPECT_NE(m1.GetSize(), m3.GetSize());
}

TEST(TMatrix, can_assign_matrices_of_different_size){
	TMatrix<int> m1(10);
	TMatrix<int> m2(15);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TMatrix, compare_equal_matrices_return_true){
	TMatrix<int> m1(10);
	TMatrix<int> m2(10);
	EXPECT_EQ(m1, m2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true){
	TMatrix<int> m(10);
	EXPECT_EQ(m, m);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal){
	TMatrix<int> m1(15);
	TMatrix<int> m2(10);
	EXPECT_NE(m1, m2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> m1(10);
	TMatrix<int> m2(10);
	ASSERT_NO_THROW(m1 + m2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> m1(15);
	TMatrix<int> m2(10);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> m1(10);
	TMatrix<int> m2(10);
	ASSERT_NO_THROW(m1 - m2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> m1(15);
	TMatrix<int> m2(10);
	ASSERT_ANY_THROW(m1 - m2);
}