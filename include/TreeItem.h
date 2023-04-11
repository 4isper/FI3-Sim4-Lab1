#ifndef __TreeItem_H__
#define __TreeItem_H__

#include "Item.h"

template<class Key, class Data>
class TTreeItem : public TItem<Key, Data>
{
protected:
  TTreeItem<Key, Data>* left;
  TTreeItem<Key, Data>* right;
public:
  TTreeItem(Key* k = nullptr, Data* d = nullptr, TTreeItem<Key, Data>* left = nullptr, TTreeItem<Key, Data>* right = nullptr);
  TTreeItem(const TTreeItem<Key, Data>& item);
  TTreeItem<Key, Data>* GetLeft(void);
  const TTreeItem<Key, Data>* GetLeft(void) const;
  void SetLeft(TTreeItem<Key, Data>* left);
  TTreeItem<Key, Data>* GetRight(void);
  const TTreeItem<Key, Data>* GetRight(void) const;
  void SetRight(TTreeItem<Key, Data>* right);
  bool IsNull(void) const;
  void FullDelete(void);
};

template <class Key, class Data>
inline TTreeItem<Key, Data>::TTreeItem(Key* k, Data* d, TTreeItem<Key, Data>* left, TTreeItem<Key, Data>* right) : TItem<Key, Data>(k, d)
{
  this->left = left;
  this->right = right;
}

template <class Key, class Data>
inline TTreeItem<Key, Data>::TTreeItem(const TTreeItem<Key, Data>& item) : TTreeItem<Key, Data>(item.key, item.data, nullptr, nullptr)
{
}

template <class Key, class Data>
inline TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetLeft(void)
{
  return left;
}

template <class Key, class Data>
inline const TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetLeft(void) const
{
  return left;
}

template <class Key, class Data>
inline void TTreeItem<Key, Data>::SetLeft(TTreeItem<Key, Data>* left)
{
  this->left = left;
}

template <class Key, class Data>
inline TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetRight(void)
{
  return right;
}

template <class Key, class Data>
inline const TTreeItem<Key, Data>* TTreeItem<Key, Data>::GetRight(void) const
{
  return right;
}

template <class Key, class Data>
inline void TTreeItem<Key, Data>::SetRight(TTreeItem<Key, Data>* right)
{
  this->right = right;
}

template <class Key, class Data>
inline bool TTreeItem<Key, Data>::IsNull(void) const
{
  return this->key == nullptr;
}

template <class Key, class Data>
inline void TTreeItem<Key, Data>::FullDelete(void)
{
  if (left != nullptr)
  {
    left->FullDelete();
    delete left;
  }
  if (right != nullptr)
  {
    right->FullDelete();
    delete right;
  }
}

#endif
