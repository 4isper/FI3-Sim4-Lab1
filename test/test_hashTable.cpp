#include "HashTable.h"
#include "MyString.h"
#include <gtest.h>


TEST(THashTable, can_create_hashtable)
{
	try
	{
		THashTable<char, int> ht();
	}
	catch (...)
	{
		ADD_FAILURE();
	}
}

TEST(THashTable, can_create_hashtable_with_positive_size)
{
	try
	{
		THashTable<char, int> ht(5);
	}
	catch (...)
	{
		ADD_FAILURE();
	}
}

TEST(THashTable, throws_when_create_hashtable_with_negative_length)
{
	bool f;
	try
	{
		THashTable<char, int> ht(-3);
		f = false;
	}
	catch (...)
	{
		f = true;
	}
	EXPECT_EQ(true, f);
}

TEST(THashTable, can_add_elem_in_not_full_hashtable)
{
	THashTable<char, int> ht(3);
	char c = 'a';
	int x = 1;

	ASSERT_NO_THROW(ht.Add(&c, &x));
}

TEST(THashTable, can_add_elem_in_full_hashtable)
{
	THashTable<char, int> ht(2);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	ht.Add(&c1, &x1);
	ht.Add(&c2, &x2);

	ASSERT_ANY_THROW(ht.Add(&c3, &x3));
}

TEST(THashTable, can_add_elem_with_equal_key)
{
	THashTable<char, int> ht(3);
	char c = 'a';
	int x = 1;
	ht.Add(&c, &x);

	ASSERT_ANY_THROW(ht.Add(&c, &x));
}

TEST(THashTable, can_find_elem_in_hashtable1)
{
	THashTable<char, int> ht(3);
	char c = 'a';
	int x = 1;
	ht.Add(&c, &x);

	EXPECT_EQ(x, *ht.Find(&c));
}

TEST(THashTable, can_find_elem_in_hashtable2)
{
	THashTable<char, int> ht(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	ht.Add(&c1, &x);

	ASSERT_ANY_THROW(ht.Find(&c2));
}

TEST(THashTable, can_find_elem_in_hashtable3)
{
	THashTable<char, int> ht(3);
	char c = 'a';
	int x = 1;
	ht.Add(&c, &x);

	EXPECT_EQ(x, *ht[&c]);
}

TEST(THashTable, can_find_elem_in_hashtable4)
{
	THashTable<char, int> ht(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	ht.Add(&c1, &x);

	ASSERT_ANY_THROW(ht[&c2]);
}

TEST(THashTable, can_delete_elem_in_hashtable1)
{
	THashTable<char, int> ht(3);
	char c = 'a';
	int x = 1;
	ht.Add(&c, &x);

	ASSERT_NO_THROW(ht.Delete(&c));
}

TEST(THashTable, can_delete_elem_in_hashtable2)
{
	THashTable<char, int> ht(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	ht.Add(&c1, &x);

	ASSERT_ANY_THROW(ht.Delete(&c2));
}

TEST(THashTable, check_empty_hashtable)
{
	THashTable<char, int> ht(3);

	EXPECT_EQ(true, ht.IsEmpty());
}

TEST(THashTable, check_not_empty_hashtable)
{
	THashTable<char, int> ht(3);
	char c = 'a';
	int x = 1;
	ht.Add(&c, &x);

	EXPECT_EQ(false, ht.IsEmpty());
}

TEST(THashTable, check_full_hashtable)
{
	THashTable<char, int> ht(3);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	ht.Add(&c1, &x1);
	ht.Add(&c2, &x2);
	ht.Add(&c3, &x3);

	EXPECT_EQ(true, ht.IsFull());
}

TEST(THashTable, check_not_full_hashtable)
{
	THashTable<char, int> ht(3);
	char c = 'a';
	int x = 1;
	ht.Add(&c, &x);

	EXPECT_EQ(false, ht.IsFull());
}

TEST(THashTable, check_hash_matching)
{
	THashTable<TString, int> t1(5);
	TString strKeys[5] = { "One","Two","Three","Four","Five" };
	int values[5] = { 1,2,3,4,5 };
	t1.Add(&strKeys[0], &values[0]);
	t1.Add(&strKeys[1], &values[1]);
	t1.Add(&strKeys[2], &values[2]);
	EXPECT_EQ(true, t1.CheckCollision(&strKeys[3]));
}
