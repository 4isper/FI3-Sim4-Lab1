#ifndef __IMap_H__
#define __IMap_H__

template <class Key, class Data>
class IMap
{
protected:
  int size;
  int count;
public:
  virtual int GetCount() const;
  virtual Data* operator[](Key* k) = 0;
  virtual Data* Find(Key* k) = 0;
  virtual const Data* operator[](Key* k) const = 0;
  virtual const Data* Find(Key* k) const = 0;
  virtual void Add(Key* k, Data* d) = 0;
  virtual void Delete(Key* k) = 0;
  virtual bool IsEmpty() const;
  virtual bool IsFull() const;
};

template<class Key, class Data>
inline int IMap<Key, Data>::GetCount() const
{
  return count;
}

template<class Key, class Data>
inline bool IMap<Key, Data>::IsEmpty() const
{
  return count == 0;
}

template<class Key, class Data>
inline bool IMap<Key, Data>::IsFull() const
{
  return count == size;
}

#endif