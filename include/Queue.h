#ifndef __Queue_H__
#define __Queue_H__

#include <iostream>

template<typename T>
class TQueue
{
protected:
  T* pMem;
  int size;
  int first;
  int last;
public:
  TQueue(int _size = 1);
  TQueue(const TQueue<T>& q);
  TQueue(TQueue<T>&& q);
  ~TQueue();

  TQueue<T>& operator=(const TQueue<T>& q);
  TQueue<T>& operator=(TQueue<T>&& q);
  bool operator==(const TQueue<T>& q) const;
  bool operator!=(const TQueue<T>& q) const;

  bool isEmpty();
  bool isFull();
  void Push(T elem);
  T Pop();
  T Top();
  void rePack();
  void Free();
};

template<typename T>
inline TQueue<T>::TQueue(int _size)
{
  if (_size > 0)
  {
    size = _size;
    first = 0;
    last = 0;
    pMem = new T[size];
  }
  else
  {
    throw "fail init queue";
  }
}

template<typename T>
inline TQueue<T>::TQueue(const TQueue<T>& q)
{
  if (q.pMem == nullptr)
  {
    size = 0;
    first = 0;
    last = 0;
    pMem = nullptr;
  }
  else
  {
    size = q.size;
    first = q.first;
    last = q.last;
    pMem = new T[size];
    for (int i = 0; i < size; i++)
    {
      pMem[i] = q.pMem[i];
    }
  }
}

template<typename T>
inline TQueue<T>::TQueue(TQueue<T>&& q)
{
  size = q.size;
  first = q.first;
  last = q.last;
  pMem = q.pMem;

  q.size = 0;
  q.first = 0;
  q.last = 0;
  q.pMem = nullptr;
}

template<typename T>
inline TQueue<T>::~TQueue()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
  size = 0;
  first = 0;
  last = 0;
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(const TQueue<T>& q)
{
  if (this == &q)
  {
    return *this;
  }
  if (pMem != nullptr)
  {
    delete[] pMem;
  }
  if (q.pMem == nullptr)
  {
    pMem = nullptr;
    size = 0;
    first = 0;
    last = 0;
  }
  else
  {
    size = q.size;
    first = q.first;
    last = q.last;
    pMem = new T[size];
    for (int i = 0; i < size; i++)
    {
      pMem[i] = q.pMem[i];
    }
  }
  return *this;
}

template<typename T>
inline TQueue<T>& TQueue<T>::operator=(TQueue<T>&& q)
{
  if (this == &q)
  {
    return *this;
  }
  if (pMem != nullptr)
  {
    delete[] pMem;
  }
  pMem = q.pMem;
  size = q.size;
  first = q.first;
  last = q.last;

  q.pMem = nullptr;
  q.size = 0;
  q.first = 0;
  q.last = 0;
  return *this;
}

template<typename T>
inline bool TQueue<T>::operator==(const TQueue<T>& q) const
{
  if (size != q.size || first != q.first || last != q.last)
  {
    return false;
  }
  for (int i = 0; i < size; i++)
  {
    if (pMem[i] != q.pMem[i])
    {
      return false;
    }
  }
  return true;
}

template<typename T>
inline bool TQueue<T>::operator!=(const TQueue<T>& q) const
{
  if (size != q.size || first != q.first || last != q.last)
  {
    return true;
  }
  for (int i = 0; i < size; i++)
  {
    if (pMem[i] != q.pMem[i])
    {
      return true;
    }
  }
  return false;
}

template<typename T>
inline bool TQueue<T>::isEmpty()
{
  if (first == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
inline bool TQueue<T>::isFull()
{
  if (size == first)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
inline void TQueue<T>::Push(T elem)
{
  if (isFull())
  {
    throw "fail queue full";
  }
  pMem[first] = elem;
  first++;
}

template<typename T>
inline T TQueue<T>::Pop()
{
  if (isEmpty())
  {
    throw "fail queue empty";
  }
  return pMem[last++];
}

template<typename T>
inline T TQueue<T>::Top()
{
  if (isEmpty())
  {
    throw "fail queue empty";
  }
  return pMem[last];
}

template<typename T>
inline void TQueue<T>::rePack()
{
  if (last != 0)
  {
    for (int i = last; i < first; i++)
    {
      pMem[i - last] = pMem[i];
    }
    first = first - last;
    last = 0;
  }
  else
  {
    throw "cant repack";
  }
}

template<typename T>
inline void TQueue<T>::Free()
{
  first = 0;
  last = 0;
}

#endif