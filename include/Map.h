#ifndef __Map_H__
#define __Map_H__

#include "IMap.h"
#include "Item.h"
#include <iostream>

template <class Key, class Data>
class TMapIterator;

template <class Key, class Data>
class TMap : public IMap<Key, Data>
{
protected:
  TItem<Key, Data>* items;
  int FindInd(Key* k);
  friend class TMapIterator<Key, Data>;
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

  TMapIterator<Key, Data> Begin();
  TMapIterator<Key, Data> End();

  friend std::ostream& operator<<(std::ostream& ostr, const TMap& m)
  {
    for (int i = 0; i < m.count - 1; i++)
    {
      ostr << *(m.items[i].GetKey()) << " - " << *(m.items[i].GetData()) << ", ";
    }
    ostr << *(m.items[m.count - 1].GetKey()) << " - " << *(m.items[m.count - 1].GetData());
    return ostr;
  }
};

template<class Key, class Data>
inline int TMap<Key, Data>::FindInd(Key* k)
{
  for (int i = 0; i < this->count; i++)
  {
    if (*(items[i].GetKey()) == *k)
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
    this->size = sz;
    this->count = 0;
    items = new TItem<Key, Data>[this->size];
  }
  else
  {
    throw "fail init";
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::TMap(const TMap<Key, Data>& m)
{
  this->count = m.count;
  this->size = m.size;
  items = new TItem<Key, Data>[this->size];
  for (int i = 0; i < this->size; i++)
  {
    items[i] = m.items[i];
  }
}

template<class Key, class Data>
inline TMap<Key, Data>::~TMap()
{
  if (items != nullptr)
  {
    delete[] items;
    items = nullptr;
  }
}

template<class Key, class Data>
inline Data* TMap<Key, Data>::operator[](Key* k)
{
  return Find(k);
}

template<class Key, class Data>
inline Data* TMap<Key, Data>::Find(Key* k)
{
  for (int i = 0; i < this->count; i++)
  {
    if (*(items[i].GetKey()) == *k)
    {
      return items[i].GetData();
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline const Data* TMap<Key, Data>::operator[](Key* k) const
{
  return Find(k);
}

template<class Key, class Data>
inline const Data* TMap<Key, Data>::Find(Key* k) const
{
  for (int i = 0; i < this->count; i++)
  {
    if (*(items[i].GetKey()) == *k)
    {
      return items[i].GetData();
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline void TMap<Key, Data>::Add(Key* k, Data* d)
{
  if (this->IsFull())
  {
    throw "cannot be added to the full map";
  }
  for (int i = 0; i < this->count; i++)
  {
    if (*(items[i].GetKey()) == *k)
    {
      throw "cannot add duplicate keys";
    }
  }
  items[this->count].SetKey(k);
  items[this->count].SetData(d);
  this->count++;
}

template<class Key, class Data>
inline void TMap<Key, Data>::Delete(Key* k)
{
  int ind = FindInd(k);
  items[ind] = items[this->count - 1];
  items[this->count - 1] = nullptr;
  count--;
}

template<class Key, class Data>
inline TMapIterator<Key, Data> TMap<Key, Data>::Begin()
{
  return TMapIterator<Key, Data>(*this);
}

template<class Key, class Data>
inline TMapIterator<Key, Data> TMap<Key, Data>::End()
{
  return TMapIterator<Key, Data>(*this, this->GetCount());
}

#endif