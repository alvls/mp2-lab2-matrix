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

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(10);
    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < 5; i++) v[i] = int(i * 10);
    TDynamicVector<int> v1(v);
    EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(5);
    v[0] = 42;
    TDynamicVector<int> v1(v);
    v1[0] = 999;
    EXPECT_EQ(42, v[0]);
    EXPECT_EQ(999, v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    EXPECT_EQ(4u, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
    TDynamicVector<int> v(4);
    v[0] = 4;
    EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[static_cast<size_t>(-1)] = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);
    ASSERT_ANY_THROW(v[10] = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(5);
    for (size_t i = 0; i < 5; i++) v[i] = int(i);
    v = v;
    for (size_t i = 0; i < 5; i++) EXPECT_EQ(int(i), v[i]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> a(5), b(5);
    for (size_t i = 0; i < 5; i++) { a[i] = int(i); b[i] = int(i * 100); }
    a = b;
    EXPECT_EQ(b, a);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> a(3), b(7);
    a = b;
    EXPECT_EQ(7u, a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> a(3), b(6);
    for (size_t i = 0; i < 6; i++) b[i] = int(i);
    a = b;
    EXPECT_EQ(6u, a.size());
    EXPECT_EQ(b, a);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> a(4), b(4);
    for (size_t i = 0; i < 4; i++) { a[i] = int(i); b[i] = int(i); }
    EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(4);
    EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> a(3), b(5);
    EXPECT_TRUE(a != b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(3);
    for (size_t i = 0; i < 3; i++) v[i] = int(i);
    TDynamicVector<int> r = v + 10;
    EXPECT_EQ(10, r[0]); EXPECT_EQ(11, r[1]); EXPECT_EQ(12, r[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(3);
    for (size_t i = 0; i < 3; i++) v[i] = int(i * 10);
    TDynamicVector<int> r = v - 5;
    EXPECT_EQ(-5, r[0]); EXPECT_EQ(5, r[1]); EXPECT_EQ(15, r[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(3);
    for (size_t i = 0; i < 3; i++) v[i] = int(i + 1);
    TDynamicVector<int> r = v * 3;
    EXPECT_EQ(3, r[0]); EXPECT_EQ(6, r[1]); EXPECT_EQ(9, r[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> a(3), b(3);
    for (size_t i = 0; i < 3; i++) { a[i] = int(i); b[i] = int(i * 10); }
    TDynamicVector<int> c = a + b;
    EXPECT_EQ(0, c[0]); EXPECT_EQ(11, c[1]); EXPECT_EQ(22, c[2]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(3), b(5);
    ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> a(3), b(3);
    for (size_t i = 0; i < 3; i++) { a[i] = int(i * 10); b[i] = int(i); }
    TDynamicVector<int> c = a - b;
    EXPECT_EQ(0, c[0]); EXPECT_EQ(9, c[1]); EXPECT_EQ(18, c[2]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(3), b(5);
    ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> a(3), b(3);
    for (size_t i = 0; i < 3; i++) { a[i] = int(i + 1); b[i] = int(i + 4); }
    EXPECT_EQ(32, a * b);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> a(3), b(5);
    ASSERT_ANY_THROW(a * b);
}