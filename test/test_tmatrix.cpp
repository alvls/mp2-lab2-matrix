#include "utmatrix.h"

#include <gtest.h>

TEST (TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW (TMatrix<int> m(5));
} 

TEST (TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW (TMatrix<int> m(MAX_MATRIX_SIZE + 1));
} 

TEST (TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW (TMatrix<int> m(-5));
} 

TEST (TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW (TMatrix<int> m1(m));
}

TEST (TMatrix, copied_matrix_is_equal_to_source_one)
{
  TMatrix<int> mt1(5), mt2(mt1);

  EXPECT_EQ (true, mt2 == mt1);
}

TEST (TMatrix, copied_matrix_has_its_own_memory)
{
  TMatrix<int> mt1(5), mt2(mt1);

  EXPECT_NE (&mt1[0], &mt2[0]);
}

TEST (TMatrix, can_get_size)
{
  TMatrix<int> mt(5);

  EXPECT_EQ (5, mt.GetSize());
} 

TEST (TMatrix, can_set_and_get_element)
{
  TMatrix<int> mt(4);
  TVector<int> v(5);
  for (int i = 0; i < v.GetSize(); i++)
      v[i] = 7;
  mt[0] = v;

  EXPECT_EQ (v, mt[0]);
}

TEST (TMatrix, throws_when_set_element_with_negative_index)
{
  TVector<int> v(10);
  TMatrix<int> mt(4);

  ASSERT_ANY_THROW (mt[-1] = v);
}

TEST (TMatrix, throws_when_set_element_with_too_large_index)
{
  TMatrix<int> mt(4);

  ASSERT_ANY_THROW (mt[5]);
} 

TEST (TMatrix, can_assign_matrix_to_itself)
{
  TMatrix<int> mt(5);

  ASSERT_NO_THROW (mt = mt);
}

TEST (TMatrix, can_assign_matrices_of_equal_size)
{
  TMatrix<int> mt1(5), mt2(5);

  ASSERT_NO_THROW (mt1 = mt2);
}

TEST (TMatrix, assign_operator_change_matrix_size)
{
  TMatrix<int> mt1(4), mt2(5);
  mt1 = mt2;

  EXPECT_EQ (mt2.GetSize(), mt1.GetSize());
}

TEST (TMatrix, can_assign_matrices_of_different_size)
{
  TMatrix<int> mt1(4), mt2(5);
  
  ASSERT_NO_THROW (mt1 = mt2);
}

TEST (TMatrix, compare_equal_matrices_return_true)
{
  TMatrix<int> mt1(5), mt2(5);
  TVector<int> v1(6), v2(6);
  for (int i = 0; i < v1.GetSize(); i++)
  {
    v1[i] = i;
    v2[i] = i;
  } 
  for (int i = 0; i < mt1.GetSize(); i++)
  {
    mt1[i] = v1;
    mt2[i] = v2;
  } 
  
  EXPECT_EQ (true, mt1 == mt2);
}

TEST (TMatrix, compare_matrix_with_itself_return_true)
{
  TMatrix<int> mt(5);
  TVector<int> v(4);
  for (int i = 0; i < v.GetSize(); i++)
    v[i] = i;
  for (int i = 0; i < mt.GetSize(); i++)
    mt[i] = v;
  
  EXPECT_EQ (true, mt == mt);
} 

TEST (TMatrix, matrices_with_different_size_are_not_equal)
{
  TMatrix<int> mt1(4), mt2(5);

  EXPECT_EQ (true, mt1 != mt2);
} 

TEST (TMatrix, can_add_matrices_with_equal_size)
{
  TMatrix<int> mt1(5), mt2(5), mt3(5);
  TVector<int> v1(6), v2(6), v3(6);
  for (int i = 0; i < v1.GetSize(); i++)
  {
    v1[i] = 2;
    v2[i] = 5;
    v3[i] = 7;
  } 
  for (int i = 0; i < mt1.GetSize(); i++)
  {
    mt1[i] = v1;
    mt2[i] = v2;
    mt3[i] = v3;
  }

  EXPECT_EQ (mt3, mt1 + mt2);
}

TEST (TMatrix, cant_add_matrices_with_not_equal_size)
{
  TMatrix<int> mt1(4), mt2(5);

  ASSERT_ANY_THROW (mt1 + mt2);
} 

TEST (TMatrix, can_subtract_matrices_with_equal_size)
{
  TMatrix<int> mt1(5), mt2(5), mt3(5);
  TVector<int> v1(6), v2(6), v3(6);
  for (int i = 0; i < v1.GetSize(); i++)
  {
    v1[i] = 7;
    v2[i] = 2;
    v3[i] = 5;
  } 
  for (int i = 0; i < mt1.GetSize(); i++)
  {
    mt1[i] = v1;
    mt2[i] = v2;
    mt3[i] = v3;
  }

  EXPECT_EQ (mt3, mt1 - mt2);
} 

TEST (TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TMatrix<int> mt1(4), mt2(5);

  ASSERT_ANY_THROW (mt1 - mt2);
} 
