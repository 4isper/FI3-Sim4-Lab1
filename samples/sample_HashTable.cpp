#include "HashTable.h"
#include "HashTableIterator.h"
#include <iostream>
#include <string>
int main() 
{
	
	THashTable<std::string, int> t1(5);
	THashTable<char, int> t2(5);
	THashTable<int, int> t3(5);
	THashTable<double, int> t4(5);
	int values[5] = { 1,2,3,4,5 };

	//string key table
//==================================================================================
	std::string strKeys[5] = { "One","Two","Three","Four","Five" };
	for (int i = 0; i < 5; i++)
		t1.Add(&strKeys[i], &values[i]);
	for (auto j = t1.Begin(); j < t1.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;
	t1.Delete(&strKeys[2]);
	t1.Add(&strKeys[2], &values[3]);
	for (auto j = t1.Begin(); j < t1.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;

//==================================================================================
		
	// char key table
//==================================================================================
	char chKeys[5] = { 'a','b','c','d','e' };
	for (int i = 0; i < 5; i++)
		t2.Add(&chKeys[i], &values[i]);
	for (auto j = t2.Begin(); j < t2.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;
	t2.Delete(&chKeys[2]);
	t2.Add(&chKeys[2], &values[3]);
	for (auto j = t2.Begin(); j < t2.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;
//==================================================================================
	
	// int key table
//==================================================================================
	int intKeys[5] = { 10,20,30,40,50 };
	for (int i = 0; i < 5; i++)
		t3.Add(&intKeys[i], &values[i]);
	for (auto j = t3.Begin(); j < t3.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;
	t3.Delete(&intKeys[2]);
	t3.Add(&intKeys[2], &values[3]);
	for (auto j = t3.Begin(); j < t3.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;

//==================================================================================

	// double key table
//==================================================================================
	double dobKeys[5] = { 1.01,1.02,1.03,1.04,1.05 };
	for (int i = 0; i < 5; i++)
		t4.Add(&dobKeys[i], &values[i]);
	for (auto j = t4.Begin(); j < t4.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;
	t4.Delete(&dobKeys[2]);
	t4.Add(&dobKeys[2], &values[3]);
	for (auto j = t4.Begin(); j < t4.End(); ++j)
		std::cout << *j << std::endl;
	std::cout << "\n" << std::endl;
	
	return 0;
	
}