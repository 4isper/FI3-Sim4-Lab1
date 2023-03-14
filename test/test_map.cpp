#include "Map.h"

#include <gtest.h>

TEST(TMap, can_create_map)
{
	try
	{
		TMap<char, int> mp();
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TMap, can_create_map_with_positive_size)
{
	try
	{
		TMap<char, int> mp(5);
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TMap, throws_when_create_map_with_negative_length)
{
	bool f;
	try
	{
		TMap<char, int> mp(-3);
		f = false;
	}
	catch (...)
	{
		f = true;
	}
	EXPECT_EQ(true, f);
}

TEST(TMap, can_add_elem_in_not_full_map)
{
	TMap<char, int> mp(3);
	char c = 'a';
	int x = 1;

	ASSERT_NO_THROW(mp.Add(&c, &x));
}

TEST(TMap, can_add_elem_in_full_map)
{
	TMap<char, int> mp(2);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	mp.Add(&c1, &x1);
	mp.Add(&c2, &x2);

	ASSERT_ANY_THROW(mp.Add(&c3, &x3));
}

TEST(TMap, can_add_elem_with_equal_key)
{
	TMap<char, int> mp(3);
	char c = 'a';
	int x = 1;
	mp.Add(&c, &x);

	ASSERT_ANY_THROW(mp.Add(&c, &x));
}

TEST(TMap, can_find_elem_in_map1)
{
	TMap<char, int> mp(3);
	char c = 'a';
	int x = 1;
	mp.Add(&c, &x);

	EXPECT_EQ(x, *mp.Find(&c));
}

TEST(TMap, can_find_elem_in_map2)
{
	TMap<char, int> mp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	mp.Add(&c1, &x);

	ASSERT_ANY_THROW(mp.Find(&c2));
}

TEST(TMap, can_find_elem_in_map3)
{
	TMap<char, int> mp(3);
	char c = 'a';
	int x = 1;
	mp.Add(&c, &x);

	EXPECT_EQ(x, *mp[&c]);
}

TEST(TMap, can_find_elem_in_map4)
{
	TMap<char, int> mp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	mp.Add(&c1, &x);

	ASSERT_ANY_THROW(mp[&c2]);
}

TEST(TMap, can_delete_elem_in_map1)
{
	TMap<char, int> mp(3);
	char c = 'a';
	int x = 1;
	mp.Add(&c, &x);

	ASSERT_NO_THROW(mp.Delete(&c));
}

TEST(TMap, can_delete_elem_in_map2)
{
	TMap<char, int> mp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	mp.Add(&c1, &x);

	ASSERT_ANY_THROW(mp.Delete(&c2));
}

TEST(TMap, check_empty_map)
{
	TMap<char, int> mp(3);

	EXPECT_EQ(true, mp.IsEmpty());
}

TEST(TMap, check_not_empty_map)
{
	TMap<char, int> mp(3);
	char c = 'a';
	int x = 1;
	mp.Add(&c, &x);

	EXPECT_EQ(false, mp.IsEmpty());
}

TEST(TMap, check_full_map)
{
	TMap<char, int> mp(3);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	mp.Add(&c1, &x1);
	mp.Add(&c2, &x2);
	mp.Add(&c3, &x3);

	EXPECT_EQ(true, mp.IsFull());
}

TEST(TMap, check_not_full_map)
{
	TMap<char, int> mp(3);
	char c = 'a';
	int x = 1;
	mp.Add(&c, &x);

	EXPECT_EQ(false, mp.IsFull());
}