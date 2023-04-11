#include "Tree.h"

#include <gtest.h>

TEST(TTree, can_create_tree)
{
	try
	{
		TTree<char, int> tr();
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TTree, can_create_tree_with_positive_size)
{
	try
	{
		TTree<char, int> tr(5);
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TTree, throws_when_create_tree_with_negative_length)
{
	bool f;
	try
	{
		TTree<char, int> tr(-3);
		f = false;
	}
	catch (...)
	{
		f = true;
	}
	EXPECT_EQ(true, f);
}

TEST(TTree, can_add_elem_in_not_full_tree)
{
	TTree<char, int> tr(3);
	char c = 'a';
	int x = 1;

	ASSERT_NO_THROW(tr.Add(&c, &x));
}

TEST(TTree, can_add_elem_in_full_tree)
{
	TTree<char, int> tr(2);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	tr.Add(&c1, &x1);
	tr.Add(&c2, &x2);

	ASSERT_ANY_THROW(tr.Add(&c3, &x3));
}

TEST(TTree, can_add_elem_with_equal_key)
{
	TTree<char, int> tr(3);
	char c = 'a';
	int x = 1;
	tr.Add(&c, &x);

	ASSERT_ANY_THROW(tr.Add(&c, &x));
}

TEST(TTree, can_find_elem_in_tree1)
{
	TTree<char, int> tr(3);
	char c = 'a';
	int x = 1;
	tr.Add(&c, &x);

	EXPECT_EQ(x, *tr.Find(&c));
}

TEST(TTree, can_find_elem_in_tree2)
{
	TTree<char, int> tr(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	tr.Add(&c1, &x);

	ASSERT_ANY_THROW(tr.Find(&c2));
}

TEST(TTree, can_find_elem_in_tree3)
{
	TTree<char, int> tr(3);
	char c = 'a';
	int x = 1;
	tr.Add(&c, &x);

	EXPECT_EQ(x, *tr[&c]);
}

TEST(TTree, can_find_elem_in_tree4)
{
	TTree<char, int> tr(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	tr.Add(&c1, &x);

	ASSERT_ANY_THROW(tr[&c2]);
}

TEST(TTree, can_delete_elem_in_tree1)
{
	TTree<char, int> tr(3);
	char c = 'a';
	int x = 1;
	tr.Add(&c, &x);

	ASSERT_NO_THROW(tr.Delete(&c));
}

TEST(TTree, can_delete_elem_in_tree2)
{
	TTree<char, int> tr(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	tr.Add(&c1, &x);

	ASSERT_ANY_THROW(tr.Delete(&c2));
}

TEST(TTree, check_empty_tree)
{
	TTree<char, int> tr(3);

	EXPECT_EQ(true, tr.IsEmpty());
}

TEST(TTree, check_not_empty_tree)
{
	TTree<char, int> tr(3);
	char c = 'a';
	int x = 1;
	tr.Add(&c, &x);

	EXPECT_EQ(false, tr.IsEmpty());
}

TEST(TTree, check_full_tree)
{
	TTree<char, int> tr(3);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	tr.Add(&c1, &x1);
	tr.Add(&c2, &x2);
	tr.Add(&c3, &x3);

	EXPECT_EQ(true, tr.IsFull());
}

TEST(TTree, check_not_full_tree)
{
	TTree<char, int> tr(3);
	char c = 'a';
	int x = 1;
	tr.Add(&c, &x);

	EXPECT_EQ(false, tr.IsFull());
}