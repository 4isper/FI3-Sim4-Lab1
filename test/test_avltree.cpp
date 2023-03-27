#include "AVLTree.h"

#include <gtest.h>

TEST(TAVLTree, can_create_avltree)
{
	try
	{
		TAVLTree<char, int> smp();
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TAVLTree, can_create_avltree_with_positive_size)
{
	try
	{
		TAVLTree<char, int> smp(5);
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TAVLTree, throws_when_create_avltree_with_negative_length)
{
	bool f;
	try
	{
		TAVLTree<char, int> mp(-3);
		f = false;
	}
	catch (...)
	{
		f = true;
	}
	EXPECT_EQ(true, f);
}

TEST(TAVLTree, can_add_elem_in_not_full_avltree)
{
	TAVLTree<char, int> smp(3);
	char c = 'a';
	int x = 1;

	ASSERT_NO_THROW(smp.Add(&c, &x));
}

TEST(TAVLTree, can_add_elem_in_full_avltree)
{
	TAVLTree<char, int> smp(2);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	smp.Add(&c1, &x1);
	smp.Add(&c2, &x2);

	ASSERT_ANY_THROW(smp.Add(&c3, &x3));
}

TEST(TAVLTree, can_add_elem_with_equal_key)
{
	TAVLTree<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	ASSERT_ANY_THROW(smp.Add(&c, &x));
}

TEST(TAVLTree, can_find_elem_in_avltree1)
{
	TAVLTree<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(x, *smp.Find(&c));
}

TEST(TAVLTree, can_find_elem_in_avltree2)
{
	TAVLTree<char, int> smp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	smp.Add(&c1, &x);

	ASSERT_ANY_THROW(smp.Find(&c2));
}

TEST(TAVLTree, can_find_elem_in_avltree3)
{
	TAVLTree<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(x, *smp[&c]);
}

TEST(TAVLTree, can_find_elem_in_avltree4)
{
	TAVLTree<char, int> smp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	smp.Add(&c1, &x);

	ASSERT_ANY_THROW(smp[&c2]);
}

TEST(TAVLTree, can_delete_elem_in_avltree1)
{
	TAVLTree<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);
	
	ASSERT_NO_THROW(smp.Delete(&c));
}

TEST(TAVLTree, can_delete_elem_in_avltree2)
{
	TAVLTree<char, int> smp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	smp.Add(&c1, &x);

	ASSERT_ANY_THROW(smp.Delete(&c2));
}

TEST(TAVLTree, check_empty_avltree)
{
	TAVLTree<char, int> smp(3);

	EXPECT_EQ(true, smp.IsEmpty());
}

TEST(TAVLTree, check_not_empty_avltree)
{
	TAVLTree<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(false, smp.IsEmpty());
}

TEST(TAVLTree, check_full_avltree)
{
	TAVLTree<char, int> smp(3);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	smp.Add(&c1, &x1);
	smp.Add(&c2, &x2);
	smp.Add(&c3, &x3);

	EXPECT_EQ(true, smp.IsFull());
}

TEST(TAVLTree, check_not_full_avltree)
{
	TAVLTree<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(false, smp.IsFull());
}

TEST(TAVLTree, balance_stress_test_1)
{
  // https://al.cs.msu.ru/system/files/Балансировка+при+включении+в+AVL+дерево.pdf
  // page 11
	TAVLTree<int, int> smp(10);
  int keys[10];
  int value = 0;
  for (int i = 0; i < 10; i++)
  {
    keys[i] = i;
  }
  smp.Add(&keys[4], &value);
  smp.Add(&keys[5], &value);
  smp.Add(&keys[7], &value);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Add(&keys[2], &value);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Add(&keys[1], &value);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Delete(&keys[2]);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Add(&keys[2], &value);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Add(&keys[3], &value);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Add(&keys[6], &value);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Delete(&keys[3]);
  EXPECT_EQ(true, smp.IsTreeBalanced());
  smp.Delete(&keys[6]);
  EXPECT_EQ(true, smp.IsTreeBalanced());
}