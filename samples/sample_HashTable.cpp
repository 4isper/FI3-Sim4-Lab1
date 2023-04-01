#include "HashTable.h"
#include <iostream>
#include <string>
int main() 
{
	
	THashTable<std::string,int>t1(10);
	std::string Keys[10] = { "star","platinum","za","wardo","mudamuda","oraoraora","bites","the","dust","bruh"};
	int ch[10] = { 1,27,3,42,51 ,23,64,123,55,212};
	std::cout << "In table " << t1.GetCount() << " lines" << std::endl;
	for (int i = 0; i < 10; i++)
		t1.Add(&Keys[i], &ch[i]);
	for (int i = 0; i < 10; i++)
		std::cout << "Key - " << Keys[i] << " " << "Value - " << *t1.Find(&Keys[i]) << " "  << "Index - " << t1.FindInd(&Keys[i]) << std::endl;
	std::cout << "In table " << t1.GetCount() << " lines" << std::endl;
	THashTable<std::string, int>t2(t1);
	t1.Delete(&Keys[0]);
	t1.Delete(&Keys[9]);
	for (int i = 1; i < 9; i++)
		std::cout << "Key - " << Keys[i] << " " << "Value - " << *t1.Find(&Keys[i]) << " " << "Index - " << t1.FindInd(&Keys[i]) << std::endl;
	std::cout << "In table - " << t1.GetCount() << " lines" << std::endl;
	std::cout << "Table t2" << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << "Key - " << Keys[i] << " " << "Value - " << *t2.Find(&Keys[i]) << " " << "Index - " << t2.FindInd(&Keys[i]) << std::endl;
	std::cout << "In table - " << t2.GetCount() << " lines" << std::endl;
	std::cout << *t2[&Keys[3]] << " " << *t2.Find(&Keys[3]) << std::endl;
	THashTable<std::string, int>t3(3);
	t3.Add(&Keys[0], &ch[3]);
	t3.Add(&Keys[1], &ch[4]);
	t3.Delete(&Keys[1]);
	std::cout << *t3.Find(&Keys[0]) << std::endl;
	t3.Add(&Keys[4], &ch[8]);
	std::cout << t3.FindInd(&Keys[0]) << std::endl;
	std::cout << t3.FindInd(&Keys[4]) << std::endl;
	return 0;
	
}