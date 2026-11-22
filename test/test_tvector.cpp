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
	TDynamicVector<int> v(10);
	v[1] = 5;

	TDynamicVector<int> copy(v);

	EXPECT_EQ(v, copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(10);
	v[1] = 5;

	TDynamicVector<int> copy(v);
	copy[1] = 2;

	EXPECT_NE(v[1], copy[1]);
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

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(v.at(-2) = 4;);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(v.at(5) = 4;);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	v[1] = 5;

	ASSERT_NO_THROW(v = v);

	EXPECT_EQ(v[1], 5);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(10), v2(10);
	v[1] = 5;

	ASSERT_NO_THROW(v2 = v);

	EXPECT_EQ(v[1], v2[1]);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(10), v2(20);
	v[1] = 5;

	ASSERT_NO_THROW(v2 = v);

	EXPECT_EQ(v.size(), v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(10), v2(20);
	v[1] = 5;

	ASSERT_NO_THROW(v2 = v);

	EXPECT_EQ(v[1], v2[1]);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(10), v2(10);
	v[1] = 5; v2[1] = 5;

	EXPECT_EQ(v == v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(10);
	v[1] = 5;

	EXPECT_EQ(v == v, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(10), v2(1);

	EXPECT_NE(v, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(3);
	v[1] = 5;

	TDynamicVector<int> result = v + 5;

	TDynamicVector<int> test(3);
	test[0] = 5; test[1] = 10; test[2] = 5;

	EXPECT_EQ(result, test);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(3);
	v[1] = 5;

	TDynamicVector<int> result = v - 5;

	TDynamicVector<int> test(3);
	test[0] = -5; test[1] = 0; test[2] = -5;

	EXPECT_EQ(result, test);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(3);
	v[0] = 1;
	v[1] = 5;

	TDynamicVector<int> result = v * 5;

	TDynamicVector<int> test(3);
	test[0] = 5; test[1] = 25; test[2] = 0;

	EXPECT_EQ(result, test);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(3), v2(3);
	v[0] = 1; v[1] = 5;
	v2[1] = 10; v2[2] = 13;

	TDynamicVector<int> result = v + v2;

	TDynamicVector<int> test(3);
	test[0] = 1; test[1] = 15; test[2] = 13;

	EXPECT_EQ(result, test);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v2(4);

	ASSERT_ANY_THROW(TDynamicVector<int> result = v + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(3), v2(3);
	v[0] = 1; v[1] = 5;
	v2[1] = 10; v2[2] = 13;

	TDynamicVector<int> result = v - v2;

	TDynamicVector<int> test(3);
	test[0] = 1; test[1] = -5; test[2] = -13;

	EXPECT_EQ(result, test);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v2(4);

	ASSERT_ANY_THROW(TDynamicVector<int> result = v - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(3), v2(3);
	v[0] = 1; v[1] = 5;
	v2[1] = 10; v2[2] = 13;

	int result = v * v2;

	EXPECT_EQ(result, 50);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(3), v2(4);

	ASSERT_ANY_THROW(int result = v * v2);
}

TEST(TDynamicVector, can_output_vector) {
	TDynamicVector<int> v(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	std::ostringstream str;
	str << v;

	EXPECT_EQ(str.str(), "1 2 3 ");
}

TEST(TDynamicVector, can_input_vector) {
	std::string str1 = "1 2 3";
	TDynamicVector<int> v(3), v1(3);
	v[0] = 1; v[1] = 2; v[2] = 3;

	std::istringstream str(str1);
	str >> v1;

	EXPECT_EQ(v, v1);
}

