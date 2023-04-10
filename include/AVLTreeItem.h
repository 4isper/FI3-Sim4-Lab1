#ifndef __AVLTreeItem_H__
#define __AVLTreeItem_H__

#include "Item.h"
#include <cstdint>

template<class Key, class Data>
class TAVLTreeItem : public TItem<Key, Data>
{
protected:
  uint8_t height; // height < 1.44*log(n+2) => works for n < ~2^(254)-2 which is more than enough
  TAVLTreeItem<Key, Data>* left;
  TAVLTreeItem<Key, Data>* right;
public:
  TAVLTreeItem(Key* k = nullptr, Data* d = nullptr, uint8_t height = ~0, TAVLTreeItem<Key, Data>* left = nullptr, TAVLTreeItem<Key, Data>* right = nullptr);
  TAVLTreeItem(const TAVLTreeItem<Key, Data>& item);
  uint8_t GetHeight(void) const;
  uint8_t GetHeightRight(void) const;
  uint8_t GetHeightLeft(void) const;
  void SetHeight(uint8_t height);
  TAVLTreeItem<Key, Data>* GetLeft(void);
  const TAVLTreeItem<Key, Data>* GetLeft(void) const;
  void SetLeft(TAVLTreeItem<Key, Data>* left);
  TAVLTreeItem<Key, Data>* GetRight(void);
  const TAVLTreeItem<Key, Data>* GetRight(void) const;
  void SetRight(TAVLTreeItem<Key, Data>* right);
  bool IsNull(void) const;
  int GetBalanceFactor(void) const;
  void CalculateHeight(void);
  void FullDelete(void);
};

template <class Key, class Data>
inline TAVLTreeItem<Key, Data>::TAVLTreeItem(Key *k, Data *d, uint8_t height, TAVLTreeItem<Key, Data> *left, TAVLTreeItem<Key, Data> *right) : TItem<Key, Data>(k, d)
{
  if (height == ~0)
  {
    CalculateHeight();
  }
  else
  {
    this->height = height;
  }
  this->left = left;
  this->right = right;
}

template <class Key, class Data>
inline TAVLTreeItem<Key, Data>::TAVLTreeItem(const TAVLTreeItem<Key, Data> &item) : TAVLTreeItem<Key, Data>(item.key, item.data, item.height, nullptr, nullptr) //TItem<Key, Data>(item.key, item.data)
{
  //this->height = item.height;
  //this->left = nullptr;
  //this->right = nullptr;
}

template <class Key, class Data>
inline uint8_t TAVLTreeItem<Key, Data>::GetHeight(void) const
{
  return height;
}

template <class Key, class Data>
inline uint8_t TAVLTreeItem<Key, Data>::GetHeightRight(void) const
{
  return right != nullptr ? right->height : 0;
}

template <class Key, class Data>
inline uint8_t TAVLTreeItem<Key, Data>::GetHeightLeft(void) const
{
  return left != nullptr ? left->height : 0;
}

template <class Key, class Data>
inline void TAVLTreeItem<Key, Data>::SetHeight(uint8_t height)
{
  height = height;
}

template <class Key, class Data>
inline TAVLTreeItem<Key, Data> *TAVLTreeItem<Key, Data>::GetLeft(void)
{
  return left;
}

template <class Key, class Data>
inline const TAVLTreeItem<Key, Data> *TAVLTreeItem<Key, Data>::GetLeft(void) const
{
  return left;
}

template <class Key, class Data>
inline void TAVLTreeItem<Key, Data>::SetLeft(TAVLTreeItem<Key, Data> *left)
{
  this->left = left;
}

template <class Key, class Data>
inline TAVLTreeItem<Key, Data> *TAVLTreeItem<Key, Data>::GetRight(void)
{
  return right;
}

template <class Key, class Data>
inline const TAVLTreeItem<Key, Data> *TAVLTreeItem<Key, Data>::GetRight(void) const
{
  return right;
}

template <class Key, class Data>
inline void TAVLTreeItem<Key, Data>::SetRight(TAVLTreeItem<Key, Data> *right)
{
  this->right = right;
}

template <class Key, class Data>
inline bool TAVLTreeItem<Key, Data>::IsNull(void) const
{
  return this->GetKey() == nullptr;
  //return height == 0;
}

template <class Key, class Data>
inline int TAVLTreeItem<Key, Data>::GetBalanceFactor(void) const
{
  return static_cast<int>(GetHeightRight()) - static_cast<int>(GetHeightLeft());
}

template <class Key, class Data>
inline void TAVLTreeItem<Key, Data>::CalculateHeight(void)
{
  uint8_t hl = GetHeightLeft();
  uint8_t hr = GetHeightRight();
  SetHeight((hl > hr ? hl : hr)+1);
}

template <class Key, class Data>
inline void TAVLTreeItem<Key, Data>::FullDelete(void)
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
