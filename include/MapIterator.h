#ifndef __MapIterator_H__
#define __MapIterator_H__

#include "Map.h"

template <class Key, class Data>
class TMap;

template <class Key, class Data>
class TMapIterator
{
protected:
  TMap<Key, Data>* map;
  int index;
public:
  TMapIterator(TMap<Key, Data>& m, int _index = 0);

  bool operator==(const TMapIterator<Key, Data>& m);
  bool operator!=(const TMapIterator<Key, Data>& m);
  bool operator<=(const TMapIterator<Key, Data>& m);
  bool operator>=(const TMapIterator<Key, Data>& m);
  bool operator<(const TMapIterator<Key, Data>& m);
  bool operator>(const TMapIterator<Key, Data>& m);

  TMapIterator<Key, Data> operator++();
  TMapIterator<Key, Data> operator--();

  TItem<Key, Data>& operator*();
};

template<class Key, class Data>
inline TMapIterator<Key, Data>::TMapIterator(TMap<Key, Data>& m, int _index)
{
  map = &m;
  index = _index;
}

template<class Key, class Data>
inline bool TMapIterator<Key, Data>::operator==(const TMapIterator<Key, Data>& m)
{
  return index == m.index;
}

template<class Key, class Data>
inline bool TMapIterator<Key, Data>::operator!=(const TMapIterator<Key, Data>& m)
{
  return index != m.index;
}

template<class Key, class Data>
inline bool TMapIterator<Key, Data>::operator<=(const TMapIterator<Key, Data>& m)
{
  return index <= m.index;
}

template<class Key, class Data>
inline bool TMapIterator<Key, Data>::operator>=(const TMapIterator<Key, Data>& m)
{
  return index >= m.index;
}

template<class Key, class Data>
inline bool TMapIterator<Key, Data>::operator<(const TMapIterator<Key, Data>& m)
{
  return index < m.index;
}

template<class Key, class Data>
inline bool TMapIterator<Key, Data>::operator>(const TMapIterator<Key, Data>& m)
{
  return index > m.index;
}

template<class Key, class Data>
inline TMapIterator<Key, Data> TMapIterator<Key, Data>::operator++()
{
  index++;
  if (index > map->GetCount())
  {
    index = map->GetCount();
  }
  return *this;
}

template<class Key, class Data>
inline TMapIterator<Key, Data> TMapIterator<Key, Data>::operator--()
{
  index--;
  if (index < 0)
  {
    index = 0;
  }
  return *this;
}

template<class Key, class Data>
inline TItem<Key, Data>& TMapIterator<Key, Data>::operator*()
{
  return map->items[index];
}

#endif