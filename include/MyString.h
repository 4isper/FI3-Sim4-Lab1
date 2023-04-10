#ifndef __MyString_H__
#define __MyString_H__

#include <iostream>
#include <cstring>

class TString
{
public:
  TString(int n = 0, char c = ' ');
  TString(const char* s);
  TString(const TString& s);
  TString(int k, char* s); // 1
  ~TString();

  void SetString(int n, char c = ' ');
  void SetString(const char*);
  void SetString(const TString&);
  void SetString(int k, char* s); // 1
  const char* GetString(void) const;
  int GetLen(void) const;
  void FixBufferSize(void);
  TString* Split(char c, int &n); // array
  int FirstStrEnt(char s);
  int FirstStrEnt(char* s);
  int FirstStrEnt(TString& s);
  int* StrEnt(char* s, int& n) const; // 2
  int* StrEnt(TString& s, int& n) const; // 2
  char MostSymb(void) const; // 3
  char* SymbList(int& n) const; // 4
  int SymbCountDict(char** symbs, int** count) const; // 5
  bool IsCorrectLen(void) const;
  bool IsCorrectBuffer(void) const;
  bool IsCorrectProp(void) const;
  bool IsNumber(void) const;

  TString& operator=(const TString& s);
  TString& operator=(const char* s);
  TString& operator=(const char& s);
  TString& operator+=(const TString& s);
  TString& operator+=(const char* s);
  TString& operator+=(const char& s);
  char& operator[](int i);
  const char& operator[](int i) const;

  friend std::ostream& operator<<(std::ostream& os, const TString& s);
  friend std::istream& operator>>(std::istream& is, TString& s);

  friend TString operator+(const TString& s1, const TString& s2);
  friend TString operator+(const TString& s1, const char* s2);
  friend TString operator+(const char* s1, const TString& s2);
  friend TString operator+(const TString& s1, const char& s2);
  friend TString operator+(const char& s1, const TString& s2);

  friend bool operator==(const TString& s1, const TString& s2);
  friend bool operator==(const TString& s1, const char* s2);
  friend bool operator==(const char* s1, const TString& s2);
  friend bool operator==(const TString& s1, const char& s2);
  friend bool operator==(const char& s1, const TString& s2);
  friend bool operator>(const TString& s1, const TString& s2);
  friend bool operator>(const TString& s1, const char* s2);
  friend bool operator>(const char* s1, const TString& s2);
  friend bool operator>(const TString& s1, const char& s2);
  friend bool operator>(const char& s1, const TString& s2);
  friend bool operator<(const TString& s1, const TString& s2);
  friend bool operator<(const TString& s1, const char* s2);
  friend bool operator<(const char* s1, const TString& s2);
  friend bool operator<(const TString& s1, const char& s2);
  friend bool operator<(const char& s1, const TString& s2);
  friend bool operator>=(const TString& s1, const TString& s2);
  friend bool operator>=(const TString& s1, const char* s2);
  friend bool operator>=(const char* s1, const TString& s2);
  friend bool operator>=(const TString& s1, const char& s2);
  friend bool operator>=(const char& s1, const TString& s2);
  friend bool operator<=(const TString& s1, const TString& s2);
  friend bool operator<=(const TString& s1, const char* s2);
  friend bool operator<=(const char* s1, const TString& s2);
  friend bool operator<=(const TString& s1, const char& s2);
  friend bool operator<=(const char& s1, const TString& s2);
private:
  int buffer = 0;
  int len;
  char* s;
  void SetBuffer(int n, bool force = false);
  void ExtendBuffer(int n);
  int CStrLen(const char*) const;
  void Free(void);
};

#endif