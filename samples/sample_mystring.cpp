#include <iostream>
#include "MyString.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
  TString test(3, "breaking news ");
  cout << test << endl;
  cout << test[0] << endl;
  int n;
  TString* spl = test.Split('a', n);
  for (int i = 0; i < n; i++)
    cout << spl[i] << endl;
  TString test2("12112123");
  cout << test2.FirstStrEnt("1212") << endl;
  cout << test.MostSymb() << endl << endl;
  int* sub_str_arr = test.StrEnt("new", n);
  for (int i = 0; i < n; i++)
    cout << sub_str_arr[i] << " ";
  cout << endl;
  char* symb_for_test;
  int* count_for_test;
  n = test.SymbCountDict(&symb_for_test, &count_for_test);
  for (int i = 0; i < n; i++)
    cout << symb_for_test[i] << ":" << count_for_test[i] << "\t";
  cout << endl;
  cin >> test2;
  cout << test2 << endl;
  TString test3(3, "abreaking news ");
  cout << (test < test3) << endl;
  TString test4(3, "breaking news ");
  cout << (test == test4) << ' ' << (test <= test4) << endl;
  TString test5("abcd");
  cout << (test5 < "abcde") << endl;
  cout << (test5 + "abcde") << endl;
  delete[] symb_for_test;
  delete[] count_for_test;
  delete[] spl;
  delete[] sub_str_arr;
  return 0;
}