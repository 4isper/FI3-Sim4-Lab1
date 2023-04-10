#include "List.h"

#include <gtest.h>

TEST(TList, can_create_copied_list)
{
	TList<int> l1;
	l1.PushStart(21);
	ASSERT_NO_THROW(TList<int> l2(l1));
	ASSERT_NO_THROW(TList<int> l3 = l1);
}

TEST(TList, copied_list_is_equal_to_source_one)
{
	TList<int> l1;
	l1.PushEnd(2);
	l1.PushEnd(5);
	l1.PushEnd(11);
	l1.PushEnd(15);
	l1.Push(21, 2);
	l1.Pop(2);
	TList<int> l2(l1);
	l1 == l2;
	EXPECT_EQ(true, l1 == l2);
}

TEST(TList, copied_list_has_its_own_memory)
{
	TList<int> l1;
	for (int i = 0; i < 3; i++)
		l1.PushEnd(i);
	TList<int> l2(l1);
	l2.PopEnd();
	l2.PushEnd(123);
	EXPECT_EQ(true, l1 != l2);
}

TEST(TList, correct_push)
{
	TList<size_t> l;
	size_t sz = 5;
	l.PushEnd(1);
	l.PushEnd(3);
	l.PushEnd(4);
	l.PushStart(0);
	l.Push(2, 2);
	for (size_t i = 0; i < sz; i++)
		EXPECT_EQ(i, l.Get(i));
}

TEST(TList, correct_pop)
{
	TList<size_t> l;
	l.PushEnd(0);
	l.PushEnd(1);
	l.PopEnd();
	EXPECT_EQ(0, l.GetEnd());
	EXPECT_EQ(0, l.GetStart());
	l.PushEnd(1);
	l.PushEnd(2);
	l.PopStart();
	EXPECT_EQ(2, l.GetEnd());
	EXPECT_EQ(1, l.GetStart());
	l.PushStart(0);
	l.PushEnd(3);
	l.PushEnd(4);
	l.Pop(2);
	size_t i;
	for (i = 0; i < 2; i++)
		EXPECT_EQ(i, l.Get(i));
	for (; i < 4; i++)
		EXPECT_EQ(i + 1, l.Get(i));
}

TEST(TList, knows_if_empty)
{
	TList<size_t> l;
	EXPECT_EQ(true, l.IsEmpty());
	l.PushEnd(1);
	EXPECT_EQ(false, l.IsEmpty());
	l.PushEnd(2);
	EXPECT_EQ(false, l.IsEmpty());
	l.PopStart();
	EXPECT_EQ(false, l.IsEmpty());
	l.PopStart();
	EXPECT_EQ(true, l.IsEmpty());
	ASSERT_ANY_THROW(l.PopStart());
}