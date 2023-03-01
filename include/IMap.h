#ifndef __IMap_H__
#define __IMap_H__

template <class Key, class Data>
class IMap
{
public:
  virtual Data& operator[](const Key& k) = 0;
  virtual Data& Find(const Key& k) = 0;
  virtual const Data& operator[](const Key& k) const = 0;
  virtual const Data& Find(const Key& k) const = 0;
  virtual void Add(const Key& k, const Data& d) = 0;
  virtual void Delete(const Key& k) = 0;
};

#endif