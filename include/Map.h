#ifndef __Map_H__
#define __Map_H__

#include "IMap.h"
#include <iostream>

template <class Key, class Data>
class TMap : public IMap<Key, Data>
{
protected:
  Key** keys;
  Data** items;
  int count;
  int size;
  int FindInd(Key* k);
public:
  TMap(int sz = 100);
  TMap(const TMap<Key, Data>& m);
  ~TMap();
  Data* operator[](Key* k);
  Data* Find(Key* k);
  const Data* operator[](Key* k) const;
  const Data* Find(Key* k) const;
  void Add(Key* k, Data* d);
  void Delete(Key* k);
  bool IsEmpty();
  bool IsFull();

  friend std::ostream& operator<<(std::ostream& ostr, const TMap& m)
  {
    for (int i = 0; i < m.count - 1; i++)
    {
      ostr << *(m.keys[i]) << " - " << *(m.items[i]) << ", ";
    }
    ostr << *(m.keys[m.count - 1]) << " - " << *(m.items[m.count - 1]);
    return ostr;
  }
};

template<class Key, class Data>
inline int TMap<Key, Data>::FindInd(Key* k)
{
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *k)
    {
      return i;
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline TMap<Key, Data>::TMap(int sz)
{
  if (sz > 0)
  {
    size = sz;
    count = 0;
    keys = new Key * [size];
    items = new Data * [size];
    for (int i = 0; i < size; i++)
    {
      keys[i] = nullptr;
      items[i] = nullptr;
    }
  }
  else
  {
    throw "fail init";
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::TMap(const TMap<Key, Data>& m)
{
  count = m.count;
  size = m.size;
  keys = new Key * [size];
  items = new Data * [size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = m.keys[i];
    items[i] = m.items[i];
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::~TMap()
{
  if (keys != nullptr)
  {
    delete[] keys;
    keys = nullptr;
  }
  if (items != nullptr)
  {
    delete[] items;
    items = nullptr;
  }
}

template<class Key, class Data>
inline Data* TMap<Key, Data>::operator[](Key* k)
{
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *k)
    {
      return items[i];
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline Data* TMap<Key, Data>::Find(Key* k)
{
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *k)
    {
      return items[i];
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline const Data* TMap<Key, Data>::operator[](Key* k) const
{
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *k)
    {
      return items[i];
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline const Data* TMap<Key, Data>::Find(Key* k) const
{
  for (int i = 0; i < count; i++)
  {
    if (*(keys[i]) == *k)
    {
      return items[i];
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline void TMap<Key, Data>::Add(Key* k, Data* d)
{
  if (size == count)
  {
    throw "cannot be added to the full map";
  }
  for (int i = 0; i < count; i++)
  {
    if (*keys[i] == *k)
    {
      throw "cannot add duplicate keys";
    }
  }
  keys[count] = k;
  items[count] = d;
  count++;
}

template<class Key, class Data>
inline void TMap<Key, Data>::Delete(Key* k)
{
  int ind = FindInd(k);
  for (int i = ind; i < count - 1; i++)
  {
    keys[i] = keys[i + 1];
    items[i] = items[i + 1];
  }
  keys[count - 1] = nullptr;
  items[count - 1] = nullptr;
  count--;
}

template<class Key, class Data>
inline bool TMap<Key, Data>::IsEmpty()
{
  return count == 0;
}

template<class Key, class Data>
inline bool TMap<Key, Data>::IsFull()
{
  return count == size;
}

#endif