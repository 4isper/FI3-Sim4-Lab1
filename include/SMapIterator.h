#ifndef __SMapIterator_H__
#define __SMapIterator_H__

#include "SMap.h"

template <class Key, class Data>
class TSMap;

template <class Key, class Data>
class TSMapIterator
{
protected:
  TSMap<Key, Data>* smap;
  int index;
public:
  TSMapIterator(TSMap<Key, Data>& m, int _index = 0);

  bool operator==(const TSMapIterator<Key, Data>& m);
  bool operator!=(const TSMapIterator<Key, Data>& m);
  bool operator<=(const TSMapIterator<Key, Data>& m);
  bool operator>=(const TSMapIterator<Key, Data>& m);
  bool operator<(const TSMapIterator<Key, Data>& m);
  bool operator>(const TSMapIterator<Key, Data>& m);

  TSMapIterator<Key, Data> operator++();
  TSMapIterator<Key, Data> operator--();

  TItem<Key, Data>& operator*();
};

template<class Key, class Data>
inline TSMapIterator<Key, Data>::TSMapIterator(TSMap<Key, Data>& m, int _index)
{
  smap = &m;
  index = _index;
}

template<class Key, class Data>
inline bool TSMapIterator<Key, Data>::operator==(const TSMapIterator<Key, Data>& m)
{
  return index == m.index;
}

template<class Key, class Data>
inline bool TSMapIterator<Key, Data>::operator!=(const TSMapIterator<Key, Data>& m)
{
  return index != m.index;
}

template<class Key, class Data>
inline bool TSMapIterator<Key, Data>::operator<=(const TSMapIterator<Key, Data>& m)
{
  return index <= m.index;
}

template<class Key, class Data>
inline bool TSMapIterator<Key, Data>::operator>=(const TSMapIterator<Key, Data>& m)
{
  return index >= m.index;
}

template<class Key, class Data>
inline bool TSMapIterator<Key, Data>::operator<(const TSMapIterator<Key, Data>& m)
{
  return index < m.index;
}

template<class Key, class Data>
inline bool TSMapIterator<Key, Data>::operator>(const TSMapIterator<Key, Data>& m)
{
  return index > m.index;
}

template<class Key, class Data>
inline TSMapIterator<Key, Data> TSMapIterator<Key, Data>::operator++()
{
  index++;
  if (index > smap->GetCount())
  {
    index = smap->GetCount();
  }
  return *this;
}

template<class Key, class Data>
inline TSMapIterator<Key, Data> TSMapIterator<Key, Data>::operator--()
{
  index--;
  if (index < 0)
  {
    index = 0;
  }
  return *this;
}

template<class Key, class Data>
inline TItem<Key, Data>& TSMapIterator<Key, Data>::operator*()
{
  return smap->items[index];
}

#endif