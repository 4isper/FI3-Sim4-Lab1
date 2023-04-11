#include <iostream>
#include "Tree.h"

int main()
{
  TTree<char, int> tr1(10);
  char c1 = 'a', c2 = 'b', c3 = 'c';
  int x = 1, y = 2, z = 3;

  tr1.Add(&c1, &x);
  tr1.Add(&c2, &y);
  tr1.Add(&c3, &z);

  std::cout << *tr1[&c1] << "\t" << *tr1.Find(&c1) << "\n";
  std::cout << *tr1[&c2] << "\t" << *tr1.Find(&c2) << "\n";
  std::cout << *tr1[&c3] << "\t" << *tr1.Find(&c3) << "\n";

  tr1.Delete(&c3);

  std::cout << *tr1[&c1] << "\t" << *tr1.Find(&c1) << "\n";
  std::cout << *tr1[&c2] << "\t" << *tr1.Find(&c2) << "\n";

  TTree<char, int> tr2(tr1);

  tr1.Delete(&c1);

  std::cout << *tr2[&c1] << "\n";
}