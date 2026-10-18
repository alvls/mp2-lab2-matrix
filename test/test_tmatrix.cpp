#include "tmatrix.h"
#include <gtest.h>
#include <sstream>
#include <utility>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) { ASSERT_NO_THROW(TDynamicMatrix<int> m(5)); }
TEST(TDynamicMatrix, cant_create_too_large_matrix) { ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1)); }
TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) { ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5)); }
TEST(TDynamicMatrix, can_create_copied_matrix) { TDynamicMatrix<int> m(5); ASSERT_NO_THROW(TDynamicMatrix<int> m1(m)); }
TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) { TDynamicMatrix<int> a(2); a[0][1] = 7; TDynamicMatrix<int> b(a); EXPECT_TRUE(a == b); }
TEST(TDynamicMatrix, copied_matrix_has_its_own_memory) { TDynamicMatrix<int> a(2); a[0][1] = 7; TDynamicMatrix<int> b(a); b[0][1] = 8; EXPECT_EQ(7, a[0][1]); }
TEST(TDynamicMatrix, can_get_size) { TDynamicMatrix<int> a(3); EXPECT_EQ(3u, a.size()); }
TEST(TDynamicMatrix, can_set_and_get_element) { TDynamicMatrix<int> a(2); a[1][0] = 7; EXPECT_EQ(7, a[1][0]); }
TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) { TDynamicMatrix<int> a(2); EXPECT_ANY_THROW(a[-1][0] = 1); }
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) { TDynamicMatrix<int> a(2); EXPECT_ANY_THROW(a[2][0] = 1); }
TEST(TDynamicMatrix, can_assign_matrix_to_itself) { TDynamicMatrix<int> a(2); a[0][0] = 7; a = a; EXPECT_EQ(7, a[0][0]); }
TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) { TDynamicMatrix<int> a(2), b(2); b[1][1] = 8; a = b; EXPECT_EQ(8, a[1][1]); }
TEST(TDynamicMatrix, assign_operator_change_matrix_size) { TDynamicMatrix<int> a(2), b(3); a = b; EXPECT_EQ(3u, a.size()); }
TEST(TDynamicMatrix, can_assign_matrices_of_different_size) { TDynamicMatrix<int> a(2), b(3); b[2][2] = 9; a = b; EXPECT_EQ(9, a[2][2]); }
TEST(TDynamicMatrix, compare_equal_matrices_return_true) { TDynamicMatrix<int> a(2), b(2); EXPECT_TRUE(a == b); }
TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) { TDynamicMatrix<int> a(2); EXPECT_TRUE(a == a); }
TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) { TDynamicMatrix<int> a(2), b(3); EXPECT_FALSE(a == b); }
TEST(TDynamicMatrix, can_add_matrices_with_equal_size) { TDynamicMatrix<int> a(2), b(2); a[0][0] = 2; b[0][0] = 3; EXPECT_EQ(5, (a + b)[0][0]); }
TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) { TDynamicMatrix<int> a(2), b(3); EXPECT_ANY_THROW(a + b); }
TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) { TDynamicMatrix<int> a(2), b(2); a[0][0] = 5; b[0][0] = 3; EXPECT_EQ(2, (a - b)[0][0]); }
TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) { TDynamicMatrix<int> a(2), b(3); EXPECT_ANY_THROW(a - b); }
TEST(TDynamicMatrix, can_multiply_matrix_by_scalar) { TDynamicMatrix<int> a(2); a[0][1] = 3; EXPECT_EQ(9, (a * 3)[0][1]); }
TEST(TDynamicMatrix, can_multiply_matrix_by_vector) { TDynamicMatrix<int> a(2); a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4; TDynamicVector<int> v(2); v[0] = 5; v[1] = 6; auto r = a * v; EXPECT_EQ(17, r[0]); EXPECT_EQ(39, r[1]); }
TEST(TDynamicMatrix, cant_multiply_matrix_by_wrong_size_vector) { TDynamicMatrix<int> a(2); TDynamicVector<int> v(3); EXPECT_ANY_THROW(a * v); }
TEST(TDynamicMatrix, can_multiply_matrices) { TDynamicMatrix<int> a(2), b(2); a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4; b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8; auto c = a * b; EXPECT_EQ(19, c[0][0]); EXPECT_EQ(22, c[0][1]); EXPECT_EQ(43, c[1][0]); EXPECT_EQ(50, c[1][1]); }
TEST(TDynamicMatrix, cant_multiply_matrices_of_different_size) { TDynamicMatrix<int> a(2), b(3); EXPECT_ANY_THROW(a * b); }
TEST(TDynamicMatrix, stream_roundtrip) { TDynamicMatrix<int> a(2); std::istringstream in("1 2 3 4"); in >> a; std::ostringstream out; out << a; EXPECT_EQ("1 2 \n3 4 \n", out.str()); }
TEST(TDynamicMatrix, move_assignment_works) { TDynamicMatrix<int> a(2), b(3); a[1][1] = 9; b = std::move(a); EXPECT_EQ(9, b[1][1]); }
