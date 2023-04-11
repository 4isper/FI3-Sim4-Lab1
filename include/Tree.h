#ifndef __Tree_H__
#define __Tree_H__

#include "IMap.h"
#include "TreeItem.h"
#include "Item.h"

template<class Key, class Data>
class TTree : public IMap<Key, Data>
{
protected:
  TTreeItem<Key, Data>* root;
  void DeepCopyRecursion(const TTreeItem<Key, Data>* itemFrom, TTreeItem<Key, Data>* itemTo);
  Data* FindRecursion(TTreeItem<Key, Data>* item, Key* k);
  const Data* FindRecursion(TTreeItem<Key, Data>* item, Key* k) const;
  TTreeItem<Key, Data>* AddRecursion(TTreeItem<Key, Data>* item, Key* k, Data* d);
  TTreeItem<Key, Data>* DeleteRecursion(TTreeItem<Key, Data>* item, Key* k);
public:
  TTree(int sz = 100);
  TTree(const TTree<Key, Data>& tr);
  ~TTree();
  Data* operator[](Key* k);
  Data* Find(Key* k);
  const Data* operator[](Key* k) const;
  const Data* Find(Key* k) const;
  void Add(Key* k, Data* d);
  void Delete(Key* k);
};

template<class Key, class Data>
inline void TTree<Key, Data>::DeepCopyRecursion(const TTreeItem<Key, Data>* itemFrom, TTreeItem<Key, Data>* itemTo)
{
  if (itemFrom->GetLeft())
  {
    itemTo->SetLeft(new TTreeItem<Key, Data>(*(itemFrom->GetLeft())));
    DeepCopyRecursion(itemFrom->GetLeft(), itemTo->GetLeft());
  }
  if (itemFrom->GetRight())
  {
    itemTo->SetRight(new TTreeItem<Key, Data>(*(itemFrom->GetRight())));
    DeepCopyRecursion(itemFrom->GetRight(), itemTo->GetRight());
  }
}

template<class Key, class Data>
inline Data* TTree<Key, Data>::FindRecursion(TTreeItem<Key, Data>* item, Key* k)
{
  if (item == nullptr)
  {
    throw "key not found";
  }
  if (*k < *(item->GetKey()))
  {
    return FindRecursion(item->GetLeft(), k);
  }
  else if (*k > *(item->GetKey()))
  {
    return FindRecursion(item->GetRight(), k);
  }
  else
  {
    return item->GetData();
  }
}

template<class Key, class Data>
inline const Data* TTree<Key, Data>::FindRecursion(TTreeItem<Key, Data>* item, Key* k) const
{
  if (item == nullptr)
  {
    throw "key not found";
  }
  if (*k < *(item->GetKey()))
  {
    return FindRecursion(item->GetLeft(), k);
  }
  else if (*k > *(item->GetKey()))
  {
    return FindRecursion(item->GetRight(), k);
  }
  else
  {
    return item->GetData();
  }
}

template<class Key, class Data>
inline TTreeItem<Key, Data>* TTree<Key, Data>::AddRecursion(TTreeItem<Key, Data>* item, Key* k, Data* d)
{
  if (item == nullptr)
  {
    TTreeItem<Key, Data>* tmp = new TTreeItem<Key, Data>(k, d);
    return tmp;
  }
  if (*k < *(item->GetKey()))
  {
    item->SetLeft(AddRecursion(item->GetLeft(), k, d));
  }
  else if (*k > *(item->GetKey()))
  {
    item->SetRight(AddRecursion(item->GetRight(), k, d));
  }
  else
  {
    throw "cannot add duplicate keys";
  }
}

template<class Key, class Data>
inline TTreeItem<Key, Data>* TTree<Key, Data>::DeleteRecursion(TTreeItem<Key, Data>* item, Key* k)
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
    delete item;
    return nullptr;
  }
}

template<class Key, class Data>
inline TTree<Key, Data>::TTree(int sz)
{
  if (sz > 0)
  {
    this->size = sz;
    this->count = 0;
    root = nullptr;
  }
  else
  {
    throw "fail init";
  }
}

template<class Key, class Data>
inline TTree<Key, Data>::TTree(const TTree<Key, Data>& tr)
{
  this->size = tr.size;
  this->count = tr.count;
  if (tr.count > 0)
  {
    root = new TTreeItem<Key, Data>(*tr.root);
    DeepCopyRecursion(tr.root, this->root);
  }
  else
  {
    root = nullptr;
  }
}

template<class Key, class Data>
inline TTree<Key, Data>::~TTree()
{
  if (root != nullptr)
  {
    root->FullDelete();
    delete root;
  }
  this->count = 0;
  this->size = 0;
}

template<class Key, class Data>
inline Data* TTree<Key, Data>::operator[](Key* k)
{
  return Find(k);
}

template<class Key, class Data>
inline Data* TTree<Key, Data>::Find(Key* k)
{
  if (this->IsEmpty())
  {
    throw "key not found";
  }
  return FindRecursion(root, k);
}

template<class Key, class Data>
inline const Data* TTree<Key, Data>::operator[](Key* k) const
{
  return Find(k);
}

template<class Key, class Data>
inline const Data* TTree<Key, Data>::Find(Key* k) const
{
  if (this->IsEmpty())
  {
    throw "key not found";
  }
  return FindRecursion(root, k);
}

template<class Key, class Data>
inline void TTree<Key, Data>::Add(Key* k, Data* d)
{
  if (this->IsFull())
  {
    throw "cannot be added to the full map";
  }
  if (this->IsEmpty())
  {
    root = new TTreeItem<Key, Data>(k, d);
  }
  else
  {
    root = AddRecursion(root, k, d);
  }
  this->count++;
}

template<class Key, class Data>
inline void TTree<Key, Data>::Delete(Key* k)
{
  if (this->IsEmpty())
  {
    throw "key not found";
  }
  root = DeleteRecursion(root, k);
  this->count--;
}

#endif
