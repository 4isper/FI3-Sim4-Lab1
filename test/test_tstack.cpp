#include "Stack.h"

#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(3));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> st(-3));
}

TEST(TStack, compare_equal_stack_of_equal_size)
{
  TStack<int> st1(3), st2(3);
  st1.Push(1);
  st1.Push(2);
  st1.Push(3);
  st2 = st1;

  EXPECT_EQ(st1, st2);
}

TEST(TStack, compare_not_equal_stack_of_equal_size)
{
  TStack<int> st1(3), st2(3);
  st1.Push(1);
  st1.Push(2);
  st1.Push(3);
  st2.Push(1);
  st2.Push(2);
  st2.Push(4);

  EXPECT_NE(st1, st2);
}

TEST(TStack, check_empty_stack)
{
  TStack<int> st(3);

  EXPECT_EQ(1, st.IsEmpty());
}

TEST(TStack, check_not_empty_stack)
{
  TStack<int> st(3);
  st.Push(1);

  EXPECT_EQ(0, st.IsEmpty());
}

TEST(TStack, check_full_stack)
{
  TStack<int> st(3);
  st.Push(1);
  st.Push(2);
  st.Push(3);

  EXPECT_EQ(1, st.IsFull());
}

TEST(TStack, check_not_full_stack)
{
  TStack<int> st(3);
  st.Push(1);

  EXPECT_EQ(0, st.IsFull());
}

TEST(TStack, can_set_elem_in_not_full_stack)
{
  TStack<int> st(3);
  st.Push(1);

  ASSERT_NO_THROW(st.Push(2));
}

TEST(TStack, throws_when_set_elem_in_full_stack)
{
  TStack<int> st(3);
  st.Push(1);
  st.Push(2);
  st.Push(3);

  ASSERT_ANY_THROW(st.Push(4));
}

TEST(TStack, can_get_elem_in_not_empty_stack)
{
  TStack<int> st(3);
  st.Push(1);

  ASSERT_NO_THROW(st.Pop());
}

TEST(TStack, throws_when_get_elem_in_empty_stack)
{
  TStack<int> st(3);

  ASSERT_ANY_THROW(st.Pop());
}