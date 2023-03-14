#include <iostream>
#include "SMap.h"

int main()
{
  TSMap<char, int> smap1(10);
  char c1 = 'a', c2 = 'b', c3 = 'c', c4 = 'd', c5 = 'e';
  int x = 1, y = 2, z = 3, v = 4, u = 5;

  smap1.Add(&c3, &z);
  smap1.Add(&c5, &u);
  smap1.Add(&c1, &x);

  std::cout << smap1 << "\n";

  smap1.Add(&c4, &v);
  smap1.Add(&c2, &y);

  std::cout << smap1 << "\n";

  smap1.Delete(&c1);
  smap1.Delete(&c5);

  std::cout << smap1 << "\n";

  std::cout << *smap1.Find(&c4) << " " << *smap1[&c3] << "\n";

  TSMap<char, int> smap2(smap1);

  std::cout << smap2 << "\n";

  smap2.Add(&c1, &x);

  std::cout << smap1 << "\n" << smap2 << "\n";

  return 0;
}