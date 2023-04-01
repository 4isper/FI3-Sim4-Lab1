#ifndef __Item_H__
#define __Item_H__

#include <iostream>

template <class Key, class Data>
class TItem {
protected:
  Key* key;
  Data* data;
  int state;
public:
  TItem(Key* k = nullptr, Data* d = nullptr);
  Key* GetKey();
  int GetState();
  void SetState(int st);
  const Key* GetKey() const;
  void SetKey(Key* k);
  Data* GetData();
  const Data* GetData() const;
  void SetData(Data* d);
  bool operator==(const TItem<Key, Data>& p) const;
  bool operator!=(const TItem<Key, Data>& p) const;
  bool operator>=(const TItem<Key, Data>& p) const;
  bool operator<=(const TItem<Key, Data>& p) const;
  bool operator>(const TItem<Key, Data>& p) const;
  bool operator<(const TItem<Key, Data>& p) const;

  friend std::ostream& operator<<(std::ostream& ostr, const TItem<Key, Data>& item)
  {
    ostr << *(item.key) << " - " << *(item.data);
    return ostr;
  }
};

template<class Key, class Data>
inline TItem<Key, Data>::TItem(Key* k, Data* d)
{
  key = k;
  data = d;
}

template<class Key, class Data>
inline Key* TItem<Key, Data>::GetKey()
{
  return key;
}

template<class Key, class Data>
inline int TItem<Key, Data>::GetState()
{
    return state;
}

template<class Key, class Data>
inline void TItem<Key, Data>::SetState(int st)
{
    state = st;
}

template<class Key, class Data>
inline const Key* TItem<Key, Data>::GetKey() const
{
  return key;
}

template<class Key, class Data>
inline void TItem<Key, Data>::SetKey(Key* k)
{
  key = k;
}

template<class Key, class Data>
inline Data* TItem<Key, Data>::GetData()
{
  return data;
}

template<class Key, class Data>
inline const Data* TItem<Key, Data>::GetData() const
{
  return data;
}

template<class Key, class Data>
inline void TItem<Key, Data>::SetData(Data* d)
{
  data = d;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator==(const TItem<Key, Data>& p) const
{
  return this->key == p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator!=(const TItem<Key, Data>& p) const
{
  return this->key != p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator>=(const TItem<Key, Data>& p) const
{
  return this->key >= p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator<=(const TItem<Key, Data>& p) const
{
  return this->key <= p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator>(const TItem<Key, Data>& p) const
{
  return this->key > p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator<(const TItem<Key, Data>& p) const
{
  return this->key < p.key;
}

#endif 