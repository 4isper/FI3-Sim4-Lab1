#ifndef __AVLTree_H__
#define __AVLTree_H__

#include "IMap.h"
#include "AVLTreeItem.h"
#include "Item.h"
#include <iostream>
#include <string>
#include <functional>

template<class Key, class Data>
class TAVLTree : public IMap<Key, Data>
{
protected:
  TAVLTreeItem<Key, Data>* root;
  TAVLTreeItem<Key, Data>* RotateRight(TAVLTreeItem<Key, Data>* item);
  TAVLTreeItem<Key, Data>* RotateLeft(TAVLTreeItem<Key, Data>* item);
  TAVLTreeItem<Key, Data>* Balance(TAVLTreeItem<Key, Data>* item);
  TAVLTreeItem<Key, Data>* AddRecursion(TAVLTreeItem<Key, Data>* item, Key* k, Data* d);
  TAVLTreeItem<Key, Data>* FindMostLeft(TAVLTreeItem<Key, Data>* item);
  TAVLTreeItem<Key, Data>* GetMinTree(TAVLTreeItem<Key, Data>* item);
  TAVLTreeItem<Key, Data>* DeleteRecursion(TAVLTreeItem<Key, Data>* item, Key* k);
  Data* FindRecursion(TAVLTreeItem<Key, Data>* item, Key* k);
  const Data* FindRecursion(TAVLTreeItem<Key, Data>* item, Key* k) const;
  void PrintItemRecursion(std::ostream& ostr, TAVLTreeItem<Key, Data>* item) const;
  void DrawTreeRecursion(const std::string& prefix, TAVLTreeItem<Key, Data>* item, bool isLeft) const;
  void DeepCopyRecursion(const TAVLTreeItem<Key, Data>* itemFrom, TAVLTreeItem<Key, Data>* itemTo);
  bool IsTreeBalancedRecursion(TAVLTreeItem<Key, Data>* item) const;
  void ForEachKeyRecursion(TAVLTreeItem<Key, Data>* item, std::function<void(Key*, Data*)> func);
public:
  TAVLTree(int sz = 100);
  TAVLTree(const TAVLTree<Key, Data>& m);
  ~TAVLTree();
  Data* operator[](Key* k);
  Data* Find(Key* k);
  const Data* operator[](Key* k) const;
  const Data* Find(Key* k) const;
  void Add(Key* k, Data* d);
  void Delete(Key* k);
  void DrawTree(void) const;
  void ForEachKey(std::function<void(Key*, Data*)> func);
  friend std::ostream& operator<<(std::ostream& ostr, const TAVLTree& m)
  {
    if (!m.IsEmpty())
    {
      ostr << *(m.root->GetKey()) << " - " << *(m.root->GetData());
      m.PrintItemRecursion(ostr, m.root->GetLeft());
      m.PrintItemRecursion(ostr, m.root->GetRight());
    }
    else
    {
      ostr << "NULL";
    }
    return ostr;
  }
public:
  bool IsTreeBalanced(void) const;
};

template<class Key, class Data>
class TAVLTreeItertor
{
protected:
  TAVLTree<Key, Data>* tree;
  TItem<Key, Data>* arr;
  int i;
public:
  TAVLTreeItertor<Key, Data>(TAVLTree<Key, Data>* tree);
  ~TAVLTreeItertor<Key, Data>();
};

template<class Key, class Data>
inline TAVLTreeItem<Key, Data>* TAVLTree<Key, Data>::RotateRight(TAVLTreeItem<Key, Data>* item)
{
  TAVLTreeItem<Key, Data>* tmp = item->GetLeft();
  item->SetLeft(tmp->GetRight());
  tmp->SetRight(item);
  item->CalculateHeight();
  tmp->CalculateHeight();
  return tmp;
}

template<class Key, class Data>
inline TAVLTreeItem<Key, Data>* TAVLTree<Key, Data>::RotateLeft(TAVLTreeItem<Key, Data>* item)
{
  TAVLTreeItem<Key, Data>* tmp = item->GetRight();
  item->SetRight(tmp->GetLeft());
  tmp->SetLeft(item);
  item->CalculateHeight();
  tmp->CalculateHeight();
  return tmp;
}

template<class Key, class Data>
inline TAVLTreeItem<Key, Data>* TAVLTree<Key, Data>::Balance(TAVLTreeItem<Key, Data>* item)
{
  item->CalculateHeight();
  if (item->GetBalanceFactor() == 2)
  {
    if (item->GetRight()->GetBalanceFactor() < 0)
    {
      item->SetRight(this->RotateRight(item->GetRight()));
    }
    return this->RotateLeft(item);
  }
  if (item->GetBalanceFactor() == -2)
  {
    if (item->GetLeft()->GetBalanceFactor() > 0)
    {
      item->SetLeft(this->RotateLeft(item->GetLeft()));
    }
    return this->RotateRight(item);
  }
  return item;
}

template<class Key, class Data>
inline TAVLTreeItem<Key, Data>* TAVLTree<Key, Data>::AddRecursion(TAVLTreeItem<Key, Data>* item, Key* k, Data* d)
{
  if (item == nullptr)
  {
    TAVLTreeItem<Key, Data>* tmp = new TAVLTreeItem<Key, Data>(k, d, 1);
    return tmp;
  }
  if (*k < *(item->GetKey()))
  {
    item->SetLeft(this->AddRecursion(item->GetLeft(), k, d));
  }
  else if (*k > *(item->GetKey()))
  {
    item->SetRight(this->AddRecursion(item->GetRight(), k, d));
  }
  else
  {
    throw "cannot add duplicate keys";
  }
  return this->Balance(item);
}

template<class Key, class Data>
inline TAVLTreeItem<Key, Data>* TAVLTree<Key, Data>::FindMostLeft(TAVLTreeItem<Key, Data>* item)
{
  return !(item->GetLeft() == nullptr) ? FindMostLeft(item->GetLeft()) : item;
}

template<class Key, class Data>
inline TAVLTreeItem<Key, Data>* TAVLTree<Key, Data>::GetMinTree(TAVLTreeItem<Key, Data>* item)
{
  if (item->GetLeft() == nullptr)
  {
    return item->GetRight();
  }
  item->SetLeft(GetMinTree(item->GetLeft()));
  return this->Balance(item);
}

template<class Key, class Data>
inline TAVLTreeItem<Key, Data>* TAVLTree<Key, Data>::DeleteRecursion(TAVLTreeItem<Key, Data>* item, Key* k)
{
  if (item == nullptr)
  {
    throw "key not found";
  }
  if (*k < *(item->GetKey()))
  {
    item->SetLeft(DeleteRecursion(item->GetLeft(), k));
  }
  else if (*k > *(item->GetKey()))
  {
    item->SetRight(DeleteRecursion(item->GetRight(), k));
  }
  else
  {
    TAVLTreeItem<Key, Data>* l = item->GetLeft();
    TAVLTreeItem<Key, Data>* r = item->GetRight();
    delete item;
    if (r == nullptr)
    {
      return l;
    }
    TAVLTreeItem<Key, Data>* min = this->FindMostLeft(r);
    min->SetRight(GetMinTree(r));
    min->SetLeft(l);
    return this->Balance(min);
  }
  return this->Balance(item);
}

template<class Key, class Data>
inline Data* TAVLTree<Key, Data>::FindRecursion(TAVLTreeItem<Key, Data>* item, Key* k)
{
  if (item == nullptr)
  {
    throw "key not found";
  }
  if (*k < *(item->GetKey()))
  {
    return this->FindRecursion(item->GetLeft(), k);
  }
  else if (*k > *(item->GetKey()))
  {
    return this->FindRecursion(item->GetRight(), k);
  }
  else
  {
    return item->GetData();
  }
}

template<class Key, class Data>
inline const Data* TAVLTree<Key, Data>::FindRecursion(TAVLTreeItem<Key, Data>* item, Key* k) const
{
  if (item == nullptr)
  {
    throw "key not found";
  }
  if (*k < *(item->GetKey()))
  {
    return this->FindRecursion(item->GetLeft(), k);
  }
  else if (*k > *(item->GetKey()))
  {
    return this->FindRecursion(item->GetRight(), k);
  }
  else
  {
    return item->GetData();
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::PrintItemRecursion(std::ostream& ostr, TAVLTreeItem<Key, Data>* item) const
{
  if (item != nullptr)
  {
    ostr << ", " << *(item->GetKey()) << " - " << *(item->GetData());
    PrintItemRecursion(ostr, item->GetLeft());
    PrintItemRecursion(ostr, item->GetRight());
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::DrawTreeRecursion(const std::string& prefix, TAVLTreeItem<Key, Data>* item, bool isLeft) const
{ 
  if (item != nullptr)
  {
    std::cout << prefix;
    std::cout << (isLeft ? "├──" : "└──" );
    std::cout << *(item->GetKey()) << std::endl;

    DrawTreeRecursion( prefix + (isLeft ? "│   " : "    "), item->GetLeft(), true);
    DrawTreeRecursion( prefix + (isLeft ? "│   " : "    "), item->GetRight(), false);
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::DeepCopyRecursion(const TAVLTreeItem<Key, Data>* itemFrom, TAVLTreeItem<Key, Data>* itemTo)
{
  if (itemFrom->GetLeft())
  {
    itemTo->SetLeft(new TAVLTreeItem<Key, Data>(*(itemFrom->GetLeft())));
    DeepCopyRecursion(itemFrom->GetLeft(), itemTo->GetLeft());
  }
  if (itemFrom->GetRight())
  {
    itemTo->SetRight(new TAVLTreeItem<Key, Data>(*(itemFrom->GetRight())));
    DeepCopyRecursion(itemFrom->GetRight(), itemTo->GetRight());
  }
}

template<class Key, class Data>
inline bool TAVLTree<Key, Data>::IsTreeBalancedRecursion(TAVLTreeItem<Key, Data>* item) const
{
  if (item != nullptr)
  {
    int factor = item->GetBalanceFactor();
    if (factor >= -1 && factor <= 1)
    {
      return IsTreeBalancedRecursion(item->GetRight()) && IsTreeBalancedRecursion(item->GetLeft());
    }
    else
    {
      std::cout << *(item->GetKey()) << " factor " << factor << std::endl;
      return false;
    }
  }
  else
  {
    return true;
  }
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::ForEachKeyRecursion(TAVLTreeItem<Key, Data>* item, std::function<void(Key*, Data*)> func)
{
  if (item)
  {
    func(item->GetKey(), item->GetData());
    ForEachKeyRecursion(item->GetLeft(), func);
    ForEachKeyRecursion(item->GetRight(), func);
  }
}





template<class Key, class Data>
inline TAVLTree<Key, Data>::TAVLTree(int sz)
{
  if (sz > 0)
  {
    this->size = sz;
    this->count = 0;
    this->root = nullptr;
  }
  else
  {
    throw "fail init";
  }
}

template<class Key, class Data>
inline TAVLTree<Key, Data>::TAVLTree(const TAVLTree<Key, Data>& m)
{
  this->size = m.size;
  this->count = m.count;
  if (m.count > 0)
  {
    this->root = new TAVLTreeItem<Key, Data>(*m.root);
    DeepCopyRecursion(m.root, this->root);
  }
  else
  {
    this->root = nullptr;
  }
}

template<class Key, class Data>
inline TAVLTree<Key, Data>::~TAVLTree()
{
  if (this->root != nullptr)
  {
    this->root->FullDelete();
    delete this->root;
  }
  this->count = 0;
  this->size = 0;
}

template<class Key, class Data>
inline Data* TAVLTree<Key, Data>::operator[](Key* k)
{
  return this->Find(k);
}

template<class Key, class Data>
inline const Data* TAVLTree<Key, Data>::operator[](Key* k) const
{
  return this->Find(k);
}


template<class Key, class Data>
inline Data* TAVLTree<Key, Data>::Find(Key* k)
{
  if (this->IsEmpty())
  {
    throw "key not found";
  }
  return this->FindRecursion(this->root, k);
}

template<class Key, class Data>
inline const Data* TAVLTree<Key, Data>::Find(Key* k) const
{
  if (this->IsEmpty())
  {
    throw "key not found";
  }
  return this->FindRecursion(this->root, k);
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::Add(Key* k, Data* d)
{
  if (this->IsFull())
  {
    throw "cannot be added to the full map";
  }
  if (this->IsEmpty())
  {
    this->root = new TAVLTreeItem<Key, Data>(k, d, 1);
  }
  else
  {
    this->root = this->AddRecursion(this->root, k, d);
  }
  this->count++;
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::Delete(Key* k)
{
  if (this->IsEmpty())
  {
    throw "key not found";
  }
  this->root = this->DeleteRecursion(this->root, k);
  this->count--;
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::DrawTree(void) const
{
  // https://stackoverflow.com/a/51730733
  DrawTreeRecursion("", root, false);
}

template<class Key, class Data>
inline void TAVLTree<Key, Data>::ForEachKey(std::function<void(Key*, Data*)> func)
{
  ForEachKeyRecursion(root, func);
}


template<class Key, class Data>
inline bool TAVLTree<Key, Data>::IsTreeBalanced(void) const
{
  return IsTreeBalancedRecursion(root);
}

#endif