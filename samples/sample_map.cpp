#include <iostream>
#include "Map.h"

int main()
{
	TMap<char, int> mp1(10);
	char c1 = 'a', c2 = 'b', c3 = 'c';
	int x1 = 1, x2 = 2, x3 = 3;

	mp1.Add(&c1, &x1);
	mp1.Add(&c3, &x3);
	mp1.Add(&c2, &x2);

	std::cout << mp1 << "\n";

	mp1.Delete(&c1);

	std::cout << mp1 << "\n";

	std::cout << *mp1[&c3] << " " << *mp1.Find(&c2) << "\n";

	TMap<char, int> mp2(mp1);

	std::cout << mp2 << "\n";

	mp2.Add(&c1, &x1);

	std::cout << mp1 << "\n" << mp2 << "\n";

	return 0;
}