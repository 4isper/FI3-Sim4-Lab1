#include "SMap.h"

#include <gtest.h>

TEST(TSMap, can_create_smap)
{
	try
	{
		TSMap<char, int> smp();
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TSMap, can_create_smap_with_positive_size)
{
	try
	{
		TSMap<char, int> smp(5);
	}
	catch (char*)
	{
		ADD_FAILURE();
	}
}

TEST(TSMap, throws_when_create_smap_with_negative_length)
{
	bool f;
	try
	{
		TSMap<char, int> mp(-3);
		f = false;
	}
	catch (...)
	{
		f = true;
	}
	EXPECT_EQ(true, f);
}

TEST(TSMap, can_add_elem_in_not_full_smap)
{
	TSMap<char, int> smp(3);
	char c = 'a';
	int x = 1;

	ASSERT_NO_THROW(smp.Add(&c, &x));
}

TEST(TSMap, can_add_elem_in_full_smap)
{
	TSMap<char, int> smp(2);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	smp.Add(&c1, &x1);
	smp.Add(&c2, &x2);

	ASSERT_ANY_THROW(smp.Add(&c3, &x3));
}

TEST(TSMap, can_add_elem_with_equal_key)
{
	TSMap<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	ASSERT_ANY_THROW(smp.Add(&c, &x));
}

TEST(TSMap, can_find_elem_in_smap1)
{
	TSMap<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(x, *smp.Find(&c));
}

TEST(TSMap, can_find_elem_in_smap2)
{
	TSMap<char, int> smp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	smp.Add(&c1, &x);

	ASSERT_ANY_THROW(smp.Find(&c2));
}

TEST(TSMap, can_find_elem_in_smap3)
{
	TSMap<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(x, *smp[&c]);
}

TEST(TSMap, can_find_elem_in_smap4)
{
	TSMap<char, int> smp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	smp.Add(&c1, &x);

	ASSERT_ANY_THROW(smp[&c2]);
}

TEST(TSMap, can_delete_elem_in_smap1)
{
	TSMap<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	ASSERT_NO_THROW(smp.Delete(&c));
}

TEST(TSMap, can_delete_elem_in_smap2)
{
	TSMap<char, int> smp(3);
	char c1 = 'a', c2 = 'b';
	int x = 1;
	smp.Add(&c1, &x);

	ASSERT_ANY_THROW(smp.Delete(&c2));
}

TEST(TSMap, check_empty_smap)
{
	TSMap<char, int> smp(3);

	EXPECT_EQ(true, smp.IsEmpty());
}

TEST(TSMap, check_not_empty_smap)
{
	TSMap<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(false, smp.IsEmpty());
}

TEST(TSMap, check_full_smap)
{
	TSMap<char, int> smp(3);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;
	smp.Add(&c1, &x1);
	smp.Add(&c2, &x2);
	smp.Add(&c3, &x3);

	EXPECT_EQ(true, smp.IsFull());
}

TEST(TSMap, check_not_full_smap)
{
	TSMap<char, int> smp(3);
	char c = 'a';
	int x = 1;
	smp.Add(&c, &x);

	EXPECT_EQ(false, smp.IsFull());
}