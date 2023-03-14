#ifndef __SMap_H__
#define __SMap_H__

#include "IMap.h"
#include "Item.h"
#include <iostream>

template <class Key, class Data>
class TSMap : public IMap<Key, Data>
{
protected:
  TItem<Key, Data>* items;
  int size;
  int count;
public:
  TSMap(int sz = 100);
  TSMap(const TSMap<Key, Data>& m);
  ~TSMap();
  Data* operator[](Key* k);
  Data* Find(Key* k);
  const Data* operator[](Key* k) const;
  const Data* Find(Key* k) const;
  void Add(Key* k, Data* d);
  void Delete(Key* k);
  bool IsEmpty();
  bool IsFull();

  friend std::ostream& operator<<(std::ostream& ostr, const TSMap& m)
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
inline TSMap<Key, Data>::TSMap(int sz)
{
  if (sz > 0)
  {
    size = sz;
    count = 0;
    items = new TItem<Key, Data>[size];
  }
  else
  {
    throw "fail init";
  }
}

template<class Key, class Data>
inline TSMap<Key, Data>::TSMap(const TSMap<Key, Data>& m)
{
  count = m.count;
  size = m.size;
  items = new TItem<Key, Data>[size];
  for (int i = 0; i < count; i++)
  {
    items[i] = m.items[i];
  }
}

template<class Key, class Data>
inline TSMap<Key, Data>::~TSMap()
{
  if (items != nullptr)
  {
    delete[] items;
    items = nullptr;
  }
}

template<class Key, class Data>
inline Data* TSMap<Key, Data>::operator[](Key* k)
{
  int start = 0, end = count, mid = (start + end) / 2;

  while (start != end)
  {
    if (*(items[mid].GetKey()) == *k)
    {
      return items[mid].GetData();
    }
    else
    {
      if (*(items[mid].GetKey()) < *k)
      {
        start = (end - start) % 2 ? mid + 1 : mid;
      }
      else
      {
        end = mid;
      }
      mid = (start + end) / 2;
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline Data* TSMap<Key, Data>::Find(Key* k)
{
  int start = 0, end = count, mid = (start + end) / 2;

  while (start != end)
  {
    if (*(items[mid].GetKey()) == *k)
    {
      return items[mid].GetData();
    }
    else
    {
      if (*(items[mid].GetKey()) < *k)
      {
        start = (end - start) % 2 ? mid + 1 : mid;
      }
      else
      {
        end = mid;
      }
      mid = (start + end) / 2;
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline const Data* TSMap<Key, Data>::operator[](Key* k) const
{
  int start = 0, end = count, mid = (start + end) / 2;

  while (start != end)
  {
    if (*(items[mid].GetKey()) == *k)
    {
      return items[mid].GetData();
    }
    else
    {
      if (*(items[mid].GetKey()) < *k)
      {
        start = (end - start) % 2 ? mid + 1 : mid;
      }
      else
      {
        end = mid;
      }
      mid = (start + end) / 2;
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline const Data* TSMap<Key, Data>::Find(Key* k) const
{
  int start = 0, end = count, mid = (start + end) / 2;

  while (start != end)
  {
    if (*(items[mid].GetKey()) == *k)
    {
      return items[mid].GetData();
    }
    else
    {
      if (*(items[mid].GetKey()) < *k)
      {
        start = (end - start) % 2 ? mid + 1 : mid;
      }
      else
      {
        end = mid;
      }
      mid = (start + end) / 2;
    }
  }
  throw "key not found";
}

template<class Key, class Data>
inline void TSMap<Key, Data>::Add(Key* k, Data* d)
{
  int start = 0, end = count, mid = (start + end) / 2;

  if (size == count)
  {
    throw "cannot be added to the full map";
  }

  while (start != end)
  {
    if (*(items[mid].GetKey()) == *k)
    {
      throw "cannot add duplicate keys";
    }
    else
    {
      if (*(items[mid].GetKey()) < *k)
      {
        start = (end - start) % 2 ? mid + 1 : mid;
      }
      else
      {
        end = mid;
      }
      mid = (start + end) / 2;
    }
  }

  for (int i = count; i > mid; i--)
  {
    items[i] = items[i - 1];
  }
  items[mid].SetKey(k);
  items[mid].SetData(d);
  count++;
}

template<class Key, class Data>
inline void TSMap<Key, Data>::Delete(Key* k)
{
  int start = 0, end = count, mid = (start + end) / 2;
  bool f = false;

  while (start != end)
  {
    if (*(items[mid].GetKey()) == *k)
    {
      for (int i = mid; i < count - 1; i++)
      {
        items[i] = items[i + 1];
      }

      items[count - 1].SetKey(nullptr);
      items[count - 1].SetData(nullptr);
      count--;
      f = true;
      break;
    }
    else
    {
      if (*(items[mid].GetKey()) < *k)
      {
        start = (end - start) % 2 ? mid + 1 : mid;;
      }
      else
      {
        end = mid;
      }
      mid = (start + end) / 2;
    }
  }
  if (!f)
  {
    throw "key not found";
  }
}

template<class Key, class Data>
inline bool TSMap<Key, Data>::IsEmpty()
{
  return count == 0;
}

template<class Key, class Data>
inline bool TSMap<Key, Data>::IsFull()
{
  return count == size;
}

#endif