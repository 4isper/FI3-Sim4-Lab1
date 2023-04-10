#ifndef __STack_H__
#define __STack_H__

template<typename T>
class TStack
{
protected:
  T* pMem;
  int size;
  int first;
public:
  TStack(int _size = 1);
  TStack(const TStack<T>& st);
  TStack(TStack<T>&& st);
  ~TStack();

  TStack<T>& operator=(const TStack<T>& st);
  TStack<T>& operator=(TStack<T>&& st);
  bool operator==(const TStack<T>& st) const;
  bool operator!=(const TStack<T>& st) const;

  bool isEmpty();
  bool isFull();
  void Push(T elem);
  T Pop();
  T Top();
};

template<typename T>
inline TStack<T>::TStack(int _size)
{
  if (_size > 0)
  {
    size = _size;
    first = 0;
    pMem = new T[size];
  }
  else
  {
    throw "fail init stack";
  }
}

template<typename T>
inline TStack<T>::TStack(const TStack<T>& st)
{
  if (st.pMem == nullptr)
  {
    pMem = nullptr;
    size = 0;
    first = 0;
  }
  else
  {
    size = st.size;
    first = st.first;
    pMem = new T[size];
    for (int i = 0; i < size; i++)
    {
      pMem[i] = st.pMem[i];
    }
  }
}

template<typename T>
inline TStack<T>::TStack(TStack<T>&& st)
{
  size = st.size;
  first = st.first;
  pMem = st.pMem;

  st.size = 0;
  st.first = 0;
  st.pMem = nullptr;
}

template<typename T>
inline TStack<T>::~TStack()
{
  if (pMem != nullptr)
  {
    delete[] pMem;
    pMem = nullptr;
  }
  size = 0;
  first = 0;
}

template<typename T>
inline TStack<T>& TStack<T>::operator=(const TStack<T>& st)
{
  if (this == &st)
  {
    return *this;
  }
  if (pMem != nullptr)
  {
    delete[] pMem;
  }
  if (st.pMem == nullptr)
  {
    pMem = nullptr;
    size = 0;
    first = 0;
  }
  else
  {
    size = st.size;
    first = st.first;
    pMem = new T[size];
    for (int i = 0; i < size; i++)
    {
      pMem[i] = st.pMem[i];
    }
  }
  return *this;
}

template<typename T>
inline TStack<T>& TStack<T>::operator=(TStack<T>&& st)
{
  if (this == &st)
  {
    return *this;
  }
  if (pMem != nullptr)
  {
    delete[] pMem;
  }
  pMem = st.pMem;
  size = st.size;
  first = st.first;

  st.pMem = nullptr;
  st.size = 0;
  st.first = 0;
  return *this;
}

template<typename T>
inline bool TStack<T>::operator==(const TStack<T>& st) const
{
  if (size != st.size || first != st.first)
  {
    return false;
  }
  for (int i = 0; i < size; i++)
  {
    if (pMem[i] != st.pMem[i])
    {
      return false;
    }
  }
  return true;
}

template<typename T>
inline bool TStack<T>::operator!=(const TStack<T>& st) const
{
  if (size != st.size || first != st.first)
  {
    return true;
  }
  for (int i = 0; i < size; i++)
  {
    if (pMem[i] != st.pMem[i])
    {
      return true;
    }
  }
  return false;
}

template<typename T>
inline bool TStack<T>::isEmpty()
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
inline bool TStack<T>::isFull()
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
inline void TStack<T>::Push(T elem)
{
  if (isFull())
  {
    throw "fail stack full";
  }
  pMem[first] = elem;
  first++;
}

template<typename T>
inline T TStack<T>::Pop()
{
  if (isEmpty())
  {
    throw "fail stack empty";
  }
  //return pMem[first - 1];
  first--;
  return pMem[first];
}

template<typename T>
inline T TStack<T>::Top()
{
  if (isEmpty())
  {
    throw "fail stack empty";
  }
  return pMem[first - 1];
}

#endif