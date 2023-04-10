#include "MyString.h"
#include <cctype>

TString::TString(int n, char c)
{
  SetString(n, c);
}

TString::TString(const char* s)
{
  SetString(s);
}

TString::TString(const TString& s)
{
  SetString(s);
}

TString::TString(int k, char* s)
{
  SetString(k, s);
}

TString::~TString()
{
  Free();
  //if (buffer)
    //delete[] s;
}

void TString::SetString(int n, char c)
{
  n = (n < 0) ? 0 : n;
  SetBuffer(n + 1);
  for (int i = 0; i < n; i++)
  {
    s[i] = c;
  }
  s[n] = '\0';
  len = n;
}

void TString::SetString(const char* s)
{
  int n = CStrLen(s);
  SetBuffer(n + 1);
  for (int i = 0; i < n; i++)
  {
    this->s[i] = s[i];
  }
  this->s[n] = '\0';
  len = n;
}

void TString::SetString(const TString& s)
{
  SetBuffer(s.buffer);
  for (int i = 0; i < s.len; i++)
  {
    this->s[i] = s.s[i];
  }
  this->s[s.len] = '\0';
  len = s.len;
}

void TString::SetString(int k, char* s)
{
  k = (k < 0) ? 0 : k;
  int n = CStrLen(s);
  SetBuffer(n*k + 1);
  for (int i = 0; i < k; i++)
  {
    //int temp = i > 0;
    for (int j = 0; j < n; j++)
    {
      this->s[i*n + j] = s[j];
    }
  }
  this->s[n*k] = '\0';
  len = n*k;
}

const char* TString::GetString() const
{
  return s;
}

int TString::GetLen() const
{
  return len;
}

void TString::FixBufferSize()
{
  if (buffer > len + 1)
  {
    char* new_s = new char[len + 1];
    for (int i = 0; i < len + 1; i++)
    {
      new_s[i] = s[i];
    }
    Free();
    buffer = len + 1;
    s = new_s;
  }
}

TString* TString::Split(char c, int& n)
{
  int k = 1;
  for (int i = 0; i < len; i++)
  {
    if (s[i] == c)
      k++;
  }
  if (k == 1)
  {
    TString* arr = new TString[1];
    arr[0] = *this;
    n = 1;
    return arr;
  }
  TString* arr = new TString[k];
  n = k;
  k = 0;
  int start = 0;
  for (int i = 0; i < len; i++)
  {
    if (s[i] == c)
    {
      TString temp(i - start, '!');
      for (int j = 0; j < i - start; j++)
      {
        temp.s[j] = s[start + j];
      }
      arr[k++] = temp;
      i++;
      start = i;
    }
  }
  TString temp(len - start, '!');
  for (int i = 0; i < len - start; i++)
  {
    temp.s[i] = s[start + i];
  }
  arr[k] = temp;
  return arr;
}

int TString::FirstStrEnt(char s)
{
  for (int i = 0; i < len; i++)
    if (this->s[i] == s)
      return i;
  return -1;
}

int TString::FirstStrEnt(char* s)
{
  int j = 0;
  int s_len = CStrLen(s);
  if (s_len > len || s_len == 0 || s[0] == '\0')
    return -1;
  for (int i = 0; i < len; i++)
  {
    if (this->s[i] == s[j])
      j++;
    else
    {
      j = 0;
      if (this->s[i] == s[j])
        j++;
    }
    if (j == s_len)
      return i - j + 1;
  }
  return -1;
}

int TString::FirstStrEnt(TString& s)
{
  int j = 0;
  if (s.len > len || s.len == 0 || s[0] == '\0')
    return -1;
  for (int i = 0; i < len; i++)
  {
    if (this->s[i] == s[j])
      j++;
    else
    {
      j = 0;
      if (this->s[i] == s[j])
        j++;
    }
    if (j == s.len)
      return i - j + 1;
  }
  return -1;
}

int* TString::StrEnt(char* s, int& n) const
{
  int s_len = CStrLen(s);
  if (s_len > len || s_len == 0 || s[0] == '\0')
  {
    n = 0;
    return nullptr;
  }
  int k = 0;
  int j = 0;
  for (int i = 0; i < len; i++)
  {
    if (this->s[i] == s[j])
      j++;
    else
    {
      j = 0;
      if (this->s[i] == s[j])
        j++;
    }
    if (j == s_len)
    {
      k++;
      i = i - j + 1;
      j = 0;
    }
  }
  n = k;
  if (k == 0)
    return nullptr;
  int* res = new int[k];
  k = 0;
  j = 0;
  for (int i = 0; i < len; i++)
  {
    if (this->s[i] == s[j])
      j++;
    else
    {
      j = 0;
      if (this->s[i] == s[j])
        j++;
    }
    if (j == s_len)
    {
      res[k] = i - j + 1;
      k++;
      i = i - j + 1;
      j = 0;
    }
  }
  return res;
}

int* TString::StrEnt(TString & s, int & n) const
{
  if (s.len > len || s.len == 0 || s[0] == '\0')
  {
    n = 0;
    return nullptr;
  }
  int k = 0;
  int j = 0;
  for (int i = 0; i < len; i++)
  {
    if (this->s[i] == s[j])
      j++;
    else
    {
      j = 0;
      if (this->s[i] == s[j])
        j++;
    }
    if (j == s.len)
    {
      k++;
      i = i - j + 1;
      j = 0;
    }
  }
  n = k;
  if (k == 0)
    return nullptr;
  int* res = new int[k];
  k = 0;
  j = 0;
  for (int i = 0; i < len; i++)
  {
    if (this->s[i] == s[j])
      j++;
    else
    {
      j = 0;
      if (this->s[i] == s[j])
        j++;
    }
    if (j == s.len)
    {
      res[k] = i - j + 1;
      k++;
      i = i - j + 1;
      j = 0;
    }
  }
  return res;
}

char TString::MostSymb() const
{
  int count[256] = { 0 };
  int max = -1;
  char max_c = '\0';
  for (int i = 0; i < len; i++)
  {
    int cur_i = s[i] + 128;
    count[cur_i]++;
    if (count[cur_i] > max)
    {
      max = count[cur_i];
      max_c = s[i];
    }
  }
  return max_c;
}

char* TString::SymbList(int& n) const
{
  if (len == 0)
  {
    n = 0;
    return nullptr;
  }
  int k = 0;
  bool letrs[256] = { 0 };
  for (int i = 0; i < len; i++)
  {
    if (!letrs[s[i] + 128])
    {
      letrs[s[i] + 128] = true;
      k++;
    }
  }
  /*for (int i = 0; i < 256; i++)
    letrs[i] = false;*/
  std::memset(letrs, 0, sizeof(letrs));
  n = k;
  char* res = new char[k];
  k = 0;
  for (int i = 0; i < len; i++)
  {
    if (!letrs[s[i] + 128])
    {
      letrs[s[i] + 128] = true;
      res[k++] = s[i];
    }
  }
  return res;
}

int TString::SymbCountDict(char** symbs, int** count) const
{
  int letrs[256] = { 0 };
  int n = 0;
  for (int i = 0; i < len; i++)
  {
    if (!letrs[s[i] + 128])
      n++;
    letrs[s[i] + 128]++;
  }
  //delete[] *symbs;
  //delete[] *count;
  *symbs = new char[n];
  *count = new int[n];
  n = 0;
  for (int i = 0; i < 256; i++)
  {
    if (letrs[i])
    {
      (*symbs)[n] = i - 128;
      (*count)[n] = letrs[i];
      n++;
    }
  }
  return n;
}

bool TString::IsCorrectLen() const
{
  return CStrLen(s) == len;
}

bool TString::IsCorrectBuffer() const
{
  return buffer == len + 1;
}

bool TString::IsCorrectProp() const
{
  return IsCorrectLen() && IsCorrectBuffer();
}

bool TString::IsNumber() const
{
  int dots = 0;
  if (s[0] == '.' || s[len - 1] == '.')
    return false;
  for (int i = 0; i < len; i++)
  {
    if (!std::isdigit(s[i]))
    {
      if (s[i] == '.')
      {
        dots++;
        if (dots > 1)
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
  }
  return true;
}

TString& TString::operator=(const TString& s)
{
  SetString(s);
  return *this;
}

TString& TString::operator=(const char* s)
{
  SetString(s);
  return *this;
}

TString& TString::operator=(const char& s)
{
  SetString(1, s);
  return *this;
}

TString& TString::operator+=(const TString& s)
{
  ExtendBuffer(len + s.len + 1);
  for (int i = 0; i < s.len; i++)
  {
    this->s[i + len] = s.s[i];
  }
  this->s[len + s.len] = '\0';
  len += s.len;
  return *this;
}

TString& TString::operator+=(const char* s)
{
  int s_len = CStrLen(s);
  ExtendBuffer(len + s_len + 1);
  for (int i = 0; i < s_len; i++)
  {
    this->s[i + len] = s[i];
  }
  this->s[len + s_len] = '\0';
  len += s_len;
  return *this;
}

TString& TString::operator+=(const char& s)
{
  ExtendBuffer(len + 2);
  len++;
  this->s[len - 1] = s;
  this->s[len] = '\0';
  return *this;
}

char& TString::operator[](int i)
{
  if (i > len || i < 0)
    throw "Index out of array.";
  return s[i];
}

const char& TString::operator[](int i) const
{
  if (i > len || i < 0)
    throw "Index out of array.";
  return s[i];
}

void TString::SetBuffer(int n, bool force)
{
  if (n > buffer || force)
  {
    // it will destroy content anyway. Use ExtendBuffer(int n) otherwise
    Free();
    s = new char[n];
    buffer = n;
  }
}

void TString::ExtendBuffer(int n)
{
  if (n > buffer && n > len + 1)
  {
    char* tmp = new char[n];
    for (int i = 0; i < len + 1; i++)
      tmp[i] = s[i];
    Free();
    s = tmp;
    buffer = n;
  }
}

int TString::CStrLen(const char* s) const
{
  // https://www.strchr.com/optimized_strlen_function
  const char* temp = s;
  while (*s)
    s++;
  return s - temp;
}

void TString::Free()
{
  if (buffer)
    delete[] s;
  buffer = 0;
  //len = 0;
}

std::ostream& operator<<(std::ostream& os, const TString& s)
{
  os << s.s;
  return os;
}

std::istream& operator>>(std::istream& is, TString& s)
{
  const int STR_IN_BUFFER = 1024;
  char c;
  int i = 0, k = 0;
  s.len = 0;
  s.SetBuffer(STR_IN_BUFFER, true);
  while (is.get(c) && c != 10)
  {
    if (i >= STR_IN_BUFFER)
    {
      k++;
      i = 0;
      s.ExtendBuffer(STR_IN_BUFFER*(k+1));
    }
    s.s[i + STR_IN_BUFFER*k] = c;
    s.len++;
    i++;
  }
  if (i >= STR_IN_BUFFER)
  {
    k++;
    s.len = STR_IN_BUFFER*k - 1;
    s.ExtendBuffer(STR_IN_BUFFER*k + 1);
    s.len++;
    s.s[STR_IN_BUFFER*k] = '\0';
  }
  else
  {
    s.s[i + STR_IN_BUFFER*k] = '\0';
    s.len = i + STR_IN_BUFFER*k;
    s.FixBufferSize();
  }
  return is;
}

TString operator+(const TString& s1, const TString& s2)
{
  TString res;
  res.SetBuffer(s1.len + s2.len + 1);
  res.len = s1.len + s2.len;
  for (int i = 0; i < s1.len; i++)
  {
    res.s[i] = s1.s[i];
  }
  for (int i = 0; i < s2.len; i++)
  {
    res.s[i + s1.len] = s2.s[i];
  }
  res.s[s1.len + s2.len] = '\0';
  return res;
}

TString operator+(const TString& s1, const char* s2)
{
  TString res;
  int s2_len = res.CStrLen(s2);
  res.SetBuffer(s1.len + s2_len + 1);
  res.len = s1.len + s2_len;
  for (int i = 0; i < s1.len; i++)
  {
    res.s[i] = s1.s[i];
  }
  for (int i = 0; i < s2_len; i++)
  {
    res.s[i + s1.len] = s2[i];
  }
  res.s[s1.len + s2_len] = '\0';
  return res;
}

TString operator+(const char* s1, const TString& s2)
{
  TString res;
  int s1_len = res.CStrLen(s1);
  res.SetBuffer(s1_len + s2.len + 1);
  res.len = s1_len + s2.len;
  for (int i = 0; i < s1_len; i++)
  {
    res.s[i] = s1[i];
  }
  for (int i = 0; i < s2.len; i++)
  {
    res.s[i + s1_len] = s2.s[i];
  }
  res.s[s1_len + s2.len] = '\0';
  return res;
}

TString operator+(const TString& s1, const char& s2)
{
  TString res;
  res.SetBuffer(s1.len + 2);
  res.len = s1.len + 1;
  for (int i = 0; i < s1.len; i++)
    res.s[i] = s1.s[i];
  res.s[s1.len] = s2;
  res.s[res.len] = '\0';
  return res;
}

TString operator+(const char& s1, const TString& s2)
{
  TString res;
  res.SetBuffer(s2.len + 2);
  res.len = s2.len + 1;
  res.s[0] = s1;
  for (int i = 0; i < s2.len; i++)
    res.s[i + 1] = s2.s[i];
  res.s[res.len] = '\0';
  return res;
}

bool operator==(const TString& s1, const TString& s2)
{
  if (s1.len != s2.len)
    return false;
  for (int i = 0; i < s1.len; i++)
    if (s1.s[i] != s2.s[i])
      return false;
  return true;
}

bool operator==(const TString& s1, const char* s2)
{
  int s2_len = s1.CStrLen(s2);
  if (s1.len != s2_len)
    return false;
  for (int i = 0; i < s2_len; i++)
    if (s1.s[i] != s2[i])
      return false;
  return true;
}

bool operator==(const char* s1, const TString& s2)
{
  return s2 == s1;
}

bool operator==(const TString& s1, const char& s2)
{
  return (s1.len == 1) && (s1.s[0] == s2);
}

bool operator==(const char& s1, const TString& s2)
{
  return s2 == s1;
}

bool operator>(const TString& s1, const TString& s2)
{
  bool s1_len_greater = s1.len > s2.len;
  int min_len = (s1_len_greater) ? s2.len : s1.len;
  for (int i = 0; i < min_len; i++)
    if (s1.s[i] != s2.s[i])
      return s1.s[i] > s2.s[i];
  return s1_len_greater;
}

bool operator>(const TString& s1, const char* s2)
{
  int s2_len = s1.CStrLen(s2);
  bool s1_len_greater = s1.len > s2_len;
  int min_len = (s1_len_greater) ? s2_len : s1.len;
  for (int i = 0; i < min_len; i++)
    if (s1.s[i] != s2[i])
      return s1.s[i] > s2[i];
  return s1_len_greater;
}

bool operator>(const char* s1, const TString& s2)
{
  int s1_len = s2.CStrLen(s1);
  bool s1_len_greater = s1_len > s2.len;
  int min_len = (s1_len_greater) ? s2.len : s1_len;
  for (int i = 0; i < min_len; i++)
    if (s1[i] != s2.s[i])
      return s1[i] > s2.s[i];
  return s1_len_greater;
}

bool operator>(const TString& s1, const char& s2)
{
  if (s1.len && s1.s[0] != s2)
    return s1.s[0] > s2;
  return s1.len > 1;
}

bool operator>(const char& s1, const TString& s2)
{
  if (s2.len && s2.s[0] != s1)
    return s1 > s2.s[0];
  return s2.len < 1;
}

bool operator<(const TString& s1, const TString& s2)
{
  return s2 > s1;
}

bool operator<(const TString& s1, const char* s2)
{
  return s2 > s1;
}

bool operator<(const char* s1, const TString& s2)
{
  return s2 > s1;
}

bool operator<(const TString& s1, const char& s2)
{
  return s2 > s1;
}

bool operator<(const char& s1, const TString& s2)
{
  return s2 > s1;
}

bool operator>=(const TString& s1, const TString& s2)
{
  bool s1_len_greater = s1.len >= s2.len;
  int min_len = (s1_len_greater) ? s2.len : s1.len;
  for (int i = 0; i < min_len; i++)
    if (s1.s[i] != s2.s[i])
      return s1.s[i] > s2.s[i];
  return s1_len_greater;
}

bool operator>=(const TString& s1, const char* s2)
{
  int s2_len = s1.CStrLen(s2);
  bool s1_len_greater = s1.len >= s2_len;
  int min_len = (s1_len_greater) ? s2_len : s1.len;
  for (int i = 0; i < min_len; i++)
    if (s1.s[i] != s2[i])
      return s1.s[i] > s2[i];
  return s1_len_greater;
}

bool operator>=(const char* s1, const TString& s2)
{
  int s1_len = s2.CStrLen(s1);
  bool s1_len_greater = s1_len >= s2.len;
  int min_len = (s1_len_greater) ? s2.len : s1_len;
  for (int i = 0; i < min_len; i++)
    if (s1[i] != s2.s[i])
      return s1[i] > s2.s[i];
  return s1_len_greater;
}

bool operator>=(const TString& s1, const char& s2)
{
  if (s1.len && s1.s[0] != s2)
    return s1.s[0] > s2;
  return s1.len >= 1;
}

bool operator>=(const char& s1, const TString& s2)
{
  if (s2.len && s2.s[0] != s1)
    return s1 > s2.s[0];
  return s2.len <= 1;
}

bool operator<=(const TString& s1, const TString& s2)
{
  return s2 >= s1;
}

bool operator<=(const TString& s1, const char* s2)
{
  return s2 >= s1;
}

bool operator<=(const char* s1, const TString& s2)
{
  return s2 >= s1;
}

bool operator<=(const TString& s1, const char& s2)
{
  return s2 >= s1;
}

bool operator<=(const char& s1, const TString& s2)
{
  return s2 >= s1;
}


