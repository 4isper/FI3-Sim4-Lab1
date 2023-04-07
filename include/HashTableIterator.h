#ifndef __HashTableIterator_H__
#define __HashTableIterator_H__

#include "HashTable.h"

template <class Key, class Data>
class THashTable;

template <class Key, class Data>
class THashTableIterator
{
protected:
	THashTable<Key, Data>* hashTable;
	int index;
public:
	THashTableIterator(THashTable<Key, Data>& m, int _index = 0);
	bool operator==(const THashTableIterator<Key, Data>& m);
	bool operator!=(const THashTableIterator<Key, Data>& m);
	bool operator<=(const THashTableIterator<Key, Data>& m);
	bool operator>=(const THashTableIterator<Key, Data>& m);
	bool operator<(const THashTableIterator<Key, Data>& m);
	bool operator>(const THashTableIterator<Key, Data>& m);

	THashTableIterator<Key, Data> operator++();
	THashTableIterator<Key, Data> operator--();

	TItem<Key, Data>& operator*();
};

template<class Key, class Data>
inline THashTableIterator<Key, Data>::THashTableIterator(THashTable<Key, Data>& m, int _index)
{
	hashTable = &m;
	index = _index;
}

template<class Key, class Data>
inline bool THashTableIterator<Key, Data>::operator==(const THashTableIterator<Key, Data>& m)
{
	return index == m.index;
}

template<class Key, class Data>
inline bool THashTableIterator<Key, Data>::operator!=(const THashTableIterator<Key, Data>& m)
{
	return index != m.index;
}

template<class Key, class Data>
inline bool THashTableIterator<Key, Data>::operator<=(const THashTableIterator<Key, Data>& m)
{
	return index <= m.index;
}

template<class Key, class Data>
inline bool THashTableIterator<Key, Data>::operator>=(const THashTableIterator<Key, Data>& m)
{
	return index >= m.index;
}

template<class Key, class Data>
inline bool THashTableIterator<Key, Data>::operator<(const THashTableIterator<Key, Data>& m)
{
	return index < m.index;
}

template<class Key, class Data>
inline bool THashTableIterator<Key, Data>::operator>(const THashTableIterator<Key, Data>& m)
{
	return index > m.index;
}

template<class Key, class Data>
inline THashTableIterator<Key, Data> THashTableIterator<Key, Data>::operator++()
{
	index++;
	if (index > hashTable->GetCount())
	{
		index = hashTable->GetCount();
	}
	return *this;
}

template<class Key, class Data>
inline THashTableIterator<Key, Data> THashTableIterator<Key, Data>::operator--()
{
	index--;
	if (index < 0)
	{
		index = 0;
	}
	return *this;
}


template<class Key, class Data>
inline TItem<Key, Data>& THashTableIterator<Key, Data>::operator*()
{
	if (hashTable->items[index].GetState() == 3)
		throw "Element deleted!!";
	return hashTable ->items[index];
}
#endif
