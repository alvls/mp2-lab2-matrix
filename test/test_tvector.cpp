#include "tmatrix.h"
#include <gtest.h>
#include <sstream>
#include <utility>

TEST(TDynamicVector, can_create_vector_with_positive_length) { ASSERT_NO_THROW(TDynamicVector<int> v(5)); }
TEST(TDynamicVector, cant_create_too_large_vector) { ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1)); }
TEST(TDynamicVector, throws_when_create_vector_with_negative_length) { ASSERT_ANY_THROW(TDynamicVector<int> v(-5)); }
TEST(TDynamicVector, can_create_copied_vector) { TDynamicVector<int> v(10); ASSERT_NO_THROW(TDynamicVector<int> v1(v)); }
TEST(TDynamicVector, copied_vector_is_equal_to_source_one) { TDynamicVector<int> a(3); a[0] = 7; TDynamicVector<int> b(a); EXPECT_TRUE(a == b); }
TEST(TDynamicVector, copied_vector_has_its_own_memory) { TDynamicVector<int> a(3); a[0] = 7; TDynamicVector<int> b(a); b[0] = 8; EXPECT_EQ(7, a[0]); }
TEST(TDynamicVector, can_get_size) { TDynamicVector<int> v(4); EXPECT_EQ(4u, v.size()); }
TEST(TDynamicVector, can_set_and_get_element) { TDynamicVector<int> v(4); v[0] = 4; EXPECT_EQ(4, v[0]); }
TEST(TDynamicVector, throws_when_set_element_with_negative_index) { TDynamicVector<int> v(4); EXPECT_ANY_THROW(v[-1] = 5); }
TEST(TDynamicVector, throws_when_set_element_with_too_large_index) { TDynamicVector<int> v(4); EXPECT_ANY_THROW(v[4] = 5); }
TEST(TDynamicVector, can_assign_vector_to_itself) { TDynamicVector<int> v(2); v[0] = 9; v = v; EXPECT_EQ(9, v[0]); }
TEST(TDynamicVector, can_assign_vectors_of_equal_size) { TDynamicVector<int> a(2), b(2); b[1] = 7; a = b; EXPECT_EQ(7, a[1]); }
TEST(TDynamicVector, assign_operator_change_vector_size) { TDynamicVector<int> a(2), b(3); a = b; EXPECT_EQ(3u, a.size()); }
TEST(TDynamicVector, can_assign_vectors_of_different_size) { TDynamicVector<int> a(2), b(3); b[2] = 8; a = b; EXPECT_EQ(8, a[2]); }
TEST(TDynamicVector, compare_equal_vectors_return_true) { TDynamicVector<int> a(2), b(2); EXPECT_TRUE(a == b); }
TEST(TDynamicVector, compare_vector_with_itself_return_true) { TDynamicVector<int> a(2); EXPECT_TRUE(a == a); }
TEST(TDynamicVector, vectors_with_different_size_are_not_equal) { TDynamicVector<int> a(2), b(3); EXPECT_TRUE(a != b); }
TEST(TDynamicVector, can_add_scalar_to_vector) { TDynamicVector<int> a(2); a[0] = 3; EXPECT_EQ(5, (a + 2)[0]); }
TEST(TDynamicVector, can_subtract_scalar_from_vector) { TDynamicVector<int> a(2); a[0] = 3; EXPECT_EQ(1, (a - 2)[0]); }
TEST(TDynamicVector, can_multiply_scalar_by_vector) { TDynamicVector<int> a(2); a[0] = 3; EXPECT_EQ(6, (a * 2)[0]); }
TEST(TDynamicVector, can_add_vectors_with_equal_size) { TDynamicVector<int> a(2), b(2); a[0] = 2; b[0] = 4; EXPECT_EQ(6, (a + b)[0]); }
TEST(TDynamicVector, cant_add_vectors_with_not_equal_size) { TDynamicVector<int> a(2), b(3); EXPECT_ANY_THROW(a + b); }
TEST(TDynamicVector, can_subtract_vectors_with_equal_size) { TDynamicVector<int> a(2), b(2); a[0] = 5; b[0] = 2; EXPECT_EQ(3, (a - b)[0]); }
TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size) { TDynamicVector<int> a(2), b(3); EXPECT_ANY_THROW(a - b); }
TEST(TDynamicVector, can_multiply_vectors_with_equal_size) { TDynamicVector<int> a(2), b(2); a[0] = 2; a[1] = 3; b[0] = 4; b[1] = 5; EXPECT_EQ(23, a * b); }
TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size) { TDynamicVector<int> a(2), b(3); EXPECT_ANY_THROW(a * b); }
TEST(TDynamicVector, move_constructor_transfers_elements) { TDynamicVector<int> a(2); a[1] = 12; TDynamicVector<int> b(std::move(a)); EXPECT_EQ(12, b[1]); }
TEST(TDynamicVector, move_assignment_transfers_elements) { TDynamicVector<int> a(2), b(3); a[1] = 12; b = std::move(a); EXPECT_EQ(12, b[1]); }
TEST(TDynamicVector, at_checks_bounds) { TDynamicVector<int> a(2); EXPECT_ANY_THROW(a.at(2)); }
TEST(TDynamicVector, stream_roundtrip) { TDynamicVector<int> a(2); std::istringstream in("4 5"); in >> a; std::ostringstream out; out << a; EXPECT_EQ("4 5 ", out.str()); }
