#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
    TDynamicMatrix<int> m(5);

    ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = i * 10 + j;

    TDynamicMatrix<int> m1(m);

    EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = i * 10 + j;

    TDynamicMatrix<int> m1(m);
    m1[0][0] = 100;

    // Копия глубокая: изменение m1 не должно влиять на m
    EXPECT_EQ(0, m[0][0]);
    EXPECT_EQ(100, m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(4);

    // size() возвращает size_t, сравнение с int даёт C4389 — приводим явно
    EXPECT_EQ(static_cast<size_t>(4), m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(4);
    m[1][2] = 5;

    EXPECT_EQ(5, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(4);

    // at() проверяет границы, operator[] — нет. Для -1 проверяем именно at():
    // -1 преобразуется в SIZE_MAX, и at() обязан бросить out_of_range.
    ASSERT_ANY_THROW(m.at(static_cast<size_t>(-1)));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(4);

    ASSERT_ANY_THROW(m.at(static_cast<size_t>(4)));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            m[i][j] = i * 10 + j;

    // Присваивание самому себе не должно портить данные и ронять программу
    TDynamicMatrix<int>& ref = m;
    m = ref;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(i * 10 + j, m[i][j]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(3), m2(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            m1[i][j] = i * 10 + j;
            m2[i][j] = (i * 10 + j) + 100;
        }

    m1 = m2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            EXPECT_EQ(m2[i][j], m1[i][j]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(3), m2(5);

    m1 = m2;

    EXPECT_EQ(static_cast<size_t>(5), m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(3), m2(5);
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            m2[i][j] = i * 10 + j;

    m1 = m2;

    // ASSERT_EQ, а не EXPECT_EQ: если размер не совпал, цикл ниже прочитает
    // за границей m1, и мы получим UB вместо диагностики. ASSERT прерывает тест.
    ASSERT_EQ(static_cast<size_t>(5), m1.size());
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            EXPECT_EQ(m2[i][j], m1[i][j]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(3), m2(3);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            m1[i][j] = i * 10 + j;
            m2[i][j] = i * 10 + j;
        }

    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(3);

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(3), m2(5);

    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            m1[i][j] = i + j;
            m2[i][j] = (i + j) * 10;
        }

    TDynamicMatrix<int> r = m1 + m2;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            EXPECT_EQ((i + j) * 11, r[i][j]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);
    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(2);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            m1[i][j] = (i + j) * 10;
            m2[i][j] = i + j;
        }

    TDynamicMatrix<int> r = m1 - m2;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            EXPECT_EQ((i + j) * 9, r[i][j]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2), m2(3);

    ASSERT_ANY_THROW(m1 - m2);
}