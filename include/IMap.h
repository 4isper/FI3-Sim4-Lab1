#ifndef __IMap_H__
#define __IMap_H__

template <class Key, class Data>
class IMap
{
public:
  virtual Data* operator[](Key* k) = 0;
  virtual Data* Find(Key* k) = 0;
  virtual const Data* operator[](Key* k) const = 0;
  virtual const Data* Find(Key* k) const = 0;
  virtual void Add(Key* k, Data* d) = 0;
  virtual void Delete(Key* k) = 0;
};

#endif