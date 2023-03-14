#ifndef __Item_H__
#define __Item_H__

template <class Key, class Data>
class TItem {
protected:
  Key* key;
  Data* data;
public:
  TItem(Key* k = nullptr, Data* d = nullptr);
  Key* GetKey();
  void SetKey(Key* k);
  Data* GetData();
  void SetData(Data* d);
  bool operator==(const TItem<Key, Data>& p);
  bool operator!=(const TItem<Key, Data>& p);
  bool operator>=(const TItem<Key, Data>& p);
  bool operator<=(const TItem<Key, Data>& p);
  bool operator>(const TItem<Key, Data>& p);
  bool operator<(const TItem<Key, Data>& p);
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
inline void TItem<Key, Data>::SetData(Data* d)
{
  data = d;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator==(const TItem<Key, Data>& p)
{
  return this->key == p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator!=(const TItem<Key, Data>& p)
{
  return this->key != p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator>=(const TItem<Key, Data>& p)
{
  return this->key >= p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator<=(const TItem<Key, Data>& p)
{
  return this->key <= p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator>(const TItem<Key, Data>& p)
{
  return this->key > p.key;
}

template<class Key, class Data>
inline bool TItem<Key, Data>::operator<(const TItem<Key, Data>& p)
{
  return this->key < p.key;
}

#endif 