#include "Queue.h"

#include <gtest.h>

TEST(TStack, can_create_queue_with_positive_length)
{
  ASSERT_NO_THROW(TQueue<int> st(3));
}

TEST(TStack, throws_when_create_queue_with_negative_length)
{
  ASSERT_ANY_THROW(TQueue<int> st(-3));
}

TEST(TStack, compare_equal_queue_of_equal_size)
{
  TQueue<int> q1(3), q2(3);
  q1.Push(1);
  q1.Push(2);
  q1.Push(3);
  q2 = q1;

  EXPECT_EQ(q1, q2);
}

TEST(TStack, compare_not_equal_queue_of_equal_size)
{
  TQueue<int> q1(3), q2(3);
  q1.Push(1);
  q1.Push(2);
  q1.Push(3);
  q2.Push(1);
  q2.Push(2);
  q2.Push(4);

  EXPECT_NE(q1, q2);
}

TEST(TStack, check_empty_queue)
{
  TQueue<int> q(3);

  EXPECT_EQ(true, q.isEmpty());
}

TEST(TStack, check_not_empty_queue)
{
  TQueue<int> q(3);
  q.Push(1);

  EXPECT_EQ(false, q.isEmpty());
}

TEST(TStack, check_full_queue)
{
  TQueue<int> q(3);
  q.Push(1);
  q.Push(2);
  q.Push(3);

  EXPECT_EQ(true, q.isFull());
}

TEST(TStack, check_not_full_queue)
{
  TQueue<int> q(3);
  q.Push(1);

  EXPECT_EQ(false, q.isFull());
}

TEST(TStack, can_set_elem_in_not_full_queue)
{
  TQueue<int> q(3);
  q.Push(1);

  ASSERT_NO_THROW(q.Push(2));
}

TEST(TStack, throws_when_set_elem_in_full_queue)
{
  TQueue<int> q(3);
  q.Push(1);
  q.Push(2);
  q.Push(3);

  ASSERT_ANY_THROW(q.Push(4));
}

TEST(TStack, can_get_elem_in_not_empty_queue)
{
  TQueue<int> q(3);
  q.Push(1);

  ASSERT_NO_THROW(q.Pop());
}

TEST(TStack, throws_when_get_elem_in_empty_queue)
{
  TQueue<int> q(3);

  ASSERT_ANY_THROW(q.Pop());
}