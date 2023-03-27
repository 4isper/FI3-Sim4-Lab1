#include <iostream>
#include "AVLTree.h"

int main()
{
  TAVLTree<char, int> tree1(10);
  char c1 = 'a', c2 = 'b', c3 = 'c', c4 = 'd', c5 = 'e';
  int x = 1, y = 2, z = 3, v = 4, u = 5;

  tree1.Add(&c3, &z);
  tree1.Add(&c5, &u);
  tree1.Add(&c1, &x);

  std::cout << tree1 << "\n";

  tree1.Add(&c4, &v);
  tree1.Add(&c2, &y);

  std::cout << tree1 << "\n";

  tree1.DrawTree();

  tree1.Delete(&c1);
  tree1.Delete(&c5);

  std::cout << tree1 << "\n";

  tree1.DrawTree();

  std::cout << *tree1.Find(&c4) << " " << *tree1[&c3] << "\n";

  TAVLTree<char, int> tree2(tree1);

  std::cout << tree2 << "\n";

  tree2.DrawTree();

  tree2.Add(&c1, &x);

  std::cout << tree1 << "\n" << tree2 << "\n";

  tree2.DrawTree();
  char yes[] = " - ";
  tree2.ForEachKey([&](char* k, int* d) {
    std::cout << *k << yes << *d << std::endl;
  });
  std::cout << std::endl;
  bool doPrint = false;
  tree2.ForEachKey([&](char* k, int* d) {
    if (doPrint)
      std::cout << *k << yes << *d << std::endl;
    doPrint = !doPrint;
  });
  return 0;
}