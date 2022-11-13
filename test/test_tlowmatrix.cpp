#include "tmatrix.h"
#include <gtest.h>

TEST(TDynamicLowMatrix, can_create_matrix_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicLowMatrix<int> m(5));
}
TEST(TDynamicLowMatrix, cant_create_too_large_matrix)
{
    ASSERT_ANY_THROW(TDynamicLowMatrix<int> m(MAX_MATRIX_SIZE + 1));
}
TEST(TDynamicLowMatrix, throws_when_create_matrix_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicLowMatrix<int> m(-5));
}
TEST(TDynamicLowMatrix, can_create_copied_matrix)
{
    TDynamicLowMatrix<int> m(5);
    ASSERT_NO_THROW(TDynamicLowMatrix<int> m1(m));
}

TEST(TDynamicLowMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicLowMatrix<int>m1(8);
    m1[0][0] = 5;
    m1[5][3] = -18;
    TDynamicLowMatrix<int>m2(m1);
    EXPECT_EQ(m1, m2);
}

TEST(TDynamicLowMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicLowMatrix<int>m1(5);
    m1[2][1] = 3;
    m1[4][3] = -1;
    TDynamicLowMatrix<int>m2(m1);
    m2[2][1] = -8;
    EXPECT_NE(m1, m2);
}

TEST(TDynamicLowMatrix, can_get_size)
{
    TDynamicLowMatrix<int>m1(5);
    int size = m1.size();
    EXPECT_EQ(5, size);
}

TEST(TDynamicLowMatrix, can_set_and_get_element)
{
    TDynamicLowMatrix<int>m1(8);
    m1[6][3] = -9;
    m1[6][3] = m1[6][3] + 5;
    EXPECT_EQ(m1[6][3], -4);
}

TEST(TDynamicLowMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicLowMatrix<int>m1(5);
    EXPECT_ANY_THROW(m1[-1][3]);
}

TEST(TDynamicLowMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicLowMatrix<int>m1(5);
    EXPECT_ANY_THROW(m1[6][2]);
}

TEST(TDynamicLowMatrix, can_assign_matrix_to_itself)
{
    TDynamicLowMatrix<int>m1(4);
    EXPECT_NO_THROW(m1 = m1);
}

TEST(TDynamicLowMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicLowMatrix<int>m1(7);
    TDynamicLowMatrix<int>m2(7);
    EXPECT_NO_THROW(m1 = m2);
}

TEST(TDynamicLowMatrix, assign_operator_change_matrix_size)
{
    TDynamicLowMatrix<int>m1(6);
    TDynamicLowMatrix<int>m2(3);
    m1 = m2;
    EXPECT_EQ(m1.size(), 3);
}

TEST(TDynamicLowMatrix, can_assign_matrices_of_different_size)
{
    TDynamicLowMatrix<int>m1(5);
    TDynamicLowMatrix<int>m2(2);
    EXPECT_NO_THROW(m1 = m2);
}

TEST(TDynamicLowMatrix, compare_equal_matrices_return_true)
{
    TDynamicLowMatrix<int>m1(5);
    TDynamicLowMatrix<int>m2(m1);
    EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicLowMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicLowMatrix<int>m1(4);
    EXPECT_TRUE(m1 == m1);
}

TEST(TDynamicLowMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicLowMatrix<int>m1(4);
    TDynamicLowMatrix<int>m2(6);
    EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicLowMatrix, can_add_matrices_with_equal_size)
{
    TDynamicLowMatrix<int>m1(3);
    TDynamicLowMatrix<int>m2(3);
    m1[0][0] = 1;
    m1[1][0] = 2;
    m1[1][1] = 3;
    m1[2][0] = 4;
    m1[2][1] = 5;
    m1[2][2] = 6;
    m2[0][0] = 1;
    m2[1][0] = 2;
    m2[1][1] = 3;
    m2[2][0] = 4;
    m2[2][1] = 5;
    m2[2][2] = 6;
  
 
    TDynamicLowMatrix<int>tmp1(3);
    tmp1 = m1 + m2;
    TDynamicLowMatrix<int>tmp2(3);
    tmp2[0][0] = 2;
    tmp2[1][0] = 4;
    tmp2[1][1] = 6;
    tmp2[2][0] = 8;
    tmp2[2][1] = 10;
    tmp2[2][2] = 12;
    EXPECT_EQ(tmp1, tmp2);
}

TEST(TDynamicLowMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicLowMatrix<int>m1(7);
    TDynamicLowMatrix<int>m2(4);
    EXPECT_ANY_THROW(m1 + m2);
}

TEST(TDynamicLowMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicLowMatrix<int>m1(3);
    TDynamicLowMatrix<int>m2(3);
    m1[0][0] = 1;
    m1[1][0] = 1;
    m1[1][1] = 3;
    m1[2][0] = 3;
    m1[2][1] = 5;
    m1[2][2] = 5;
    m2[0][0] = 1;
    m2[1][0] = 2;
    m2[1][1] = 3;
    m2[2][0] = 4;
    m2[2][1] = 5;
    m2[2][2] = 6;
    TDynamicLowMatrix<int>tmp1(3);
    tmp1 = m1 - m2;
    TDynamicLowMatrix<int>tmp2(3);
    tmp2[0][0] = 0;
    tmp2[1][0] = -1;
    tmp2[1][1] = 0;
    tmp2[2][0] = -1;
    tmp2[2][1] = 0;
    tmp2[2][2] = -1;
    EXPECT_EQ(tmp1, tmp2);
}

TEST(TDynamicLowMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicLowMatrix<int>m1(7);
    TDynamicLowMatrix<int>m2(10);
    EXPECT_ANY_THROW(m1 - m2);
}

//new tests
TEST(TDynamicLowMatrix, can_multiply_matrixes_with_equal_size)
{
    TDynamicLowMatrix<int>m1(3);
    TDynamicLowMatrix<int>m2(3);
    m1[0][0] = 1;
    m1[1][0] = 2;
    m1[1][1] = 3;
    m1[2][0] = 4;
    m1[2][1] = 5;
    m1[2][2] = 6;
    m2[0][0] = 1;
    m2[1][0] = 2;
    m2[1][1] = 3;
    m2[2][0] = 4;
    m2[2][1] = 5;
    m2[2][2] = 6;
    TDynamicLowMatrix<int>res(3);
    res = m1 * m2;
    TDynamicLowMatrix<int>tmp(3);
    tmp[0][0] = 1;
    tmp[1][0] = 8;
    tmp[1][1] = 9;
    tmp[2][0] = 38;
    tmp[2][1] = 45;
    tmp[2][2] = 36;
    EXPECT_EQ(res, tmp);
}

TEST(TDynamicLowMatrix, can_multiply_matrix_on_vector)
{
    TDynamicLowMatrix<int>m1(3);
    m1[0][0] = 1;
    m1[1][0] = 2;
    m1[1][1] = 3;
    m1[2][0] = 4;
    m1[2][1] = 5;
    m1[2][2] = 6;
    TDynamicVector<int>v(3);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    TDynamicVector<int>res(3);
    res = m1 * v;
    TDynamicVector<int>tmp(3);
    tmp[0] = 1;
    tmp[1] = 8;
    tmp[2] = 32;
    EXPECT_EQ(res, tmp);
}