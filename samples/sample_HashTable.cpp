#include "HashTable.h"
#include <iostream>
#include <string>
#include <locale>
using namespace std;
int main() 
{
	
	setlocale(LC_ALL, "rus");
	THashTable<string,int>t1(10);
	string Keys[10] = { "star","platinum","za","wardo","mudamuda","oraoraora","bites","the","dust","bruh"};
	int ch[10] = { 1,27,3,42,51 ,23,64,123,55,212};
	cout << "В таблице - " << t1.GetCount() << " строк" << endl;
	for (int i = 0; i < 10; i++)
		t1.Add(&Keys[i], &ch[i]);
	for (int i = 0; i < 10; i++)
		cout << "Ключ - " << Keys[i] << " " << "Значение - " << *t1.Find(&Keys[i]) << " "  << "Индекс - " << t1.FindInd(&Keys[i]) << endl;
	cout << "В таблице - " << t1.GetCount() << " строк" << endl;
	THashTable<string, int>t2(t1);
	t1.Delete(&Keys[0]);
	t1.Delete(&Keys[9]);
	for (int i = 1; i < 9; i++)
		cout << "Ключ - " << Keys[i] << " " << "Значение - " << *t1.Find(&Keys[i]) << " " << "Индекс - " << t1.FindInd(&Keys[i]) << endl;
	cout << "В таблице - " << t1.GetCount() << " строк" << endl;
	cout << "Таблица t2" << endl;
	for (int i = 0; i < 10; i++)
		cout << "Ключ - " << Keys[i] << " " << "Значение - " << *t2.Find(&Keys[i]) << " " << "Индекс - " << t2.FindInd(&Keys[i]) << endl;
	cout << "В таблице - " << t2.GetCount() << " строк" << endl;
	cout << *t2[&Keys[3]] << " " << *t2.Find(&Keys[3]) << endl;
	THashTable<string, int>t3(3);
	t3.Add(&Keys[0], &ch[3]);
	t3.Add(&Keys[1], &ch[4]);
	t3.Delete(&Keys[1]);
	cout << *t3.Find(&Keys[0]) << endl;
	t3.Add(&Keys[4], &ch[8]);
	cout << t3.FindInd(&Keys[0]) << endl;
	cout << t3.FindInd(&Keys[4]) << endl;
	return 0;
	
}