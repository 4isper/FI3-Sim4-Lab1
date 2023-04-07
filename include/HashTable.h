/*Status of the table row
1 - line is busy
2 - line is free
3 - line deleted
4 - row outside the table(for the insertion algorithm)
*/

#include "IMap.h"
#include "Item.h"

#ifndef __HashTable_H__
#define __HashTable_H__

template <class Key, class Data>										
class THashTableIterator;

template <class Key, class Data>
class THashTable : public IMap<Key,Data>
{
public:
	THashTable(int size_table = 10);
	THashTable(const THashTable<Key, Data>& m);
	~THashTable();
	int HashFunction(Key* k);
	int HashFunction(Key* k) const;
	int DoubleHashFunction(int prev_index);
	int DoubleHashFunction(int prev_index) const;
	void Add(Key* k, Data* d);
	Data* Find(Key* k);
	const Data* Find(Key* k) const;
	void Delete(Key* k); 
	Data* operator[](Key* k);
	const Data* operator[](Key* k) const;
	int FindInd(Key* k);
	int FindInd(Key* k) const;
	THashTableIterator<Key, Data> Begin();
	THashTableIterator<Key, Data> End();
protected:
	TItem<Key, Data>* items;
	friend class THashTableIterator<Key, Data>;
};

template<class Key, class Data>
inline THashTable<Key, Data>::THashTable(int size_table)
{
	if (size_table > 0)
	{
		this->size = size_table;
		this->count = 0;
		items = new TItem<Key, Data>[this->size + 1];
		for (int i = 0; i < this->size; i++)
			items[i].SetState(2);
		items[size].SetState(4);
	}
	else
	{
		throw "fail init";
	}
}

template<class Key, class Data>
inline THashTable<Key, Data>::THashTable(const THashTable<Key, Data>& m)
{
	this->count = m.count;
	this->size = m.size;
	items = new TItem<Key, Data>[this->size];
	for (int i = 0; i < this->size; i++)
	{
		items[i] = m.items[i];
	}
}

template<class Key, class Data>
inline THashTable<Key, Data>::~THashTable()
{
	if (items != nullptr)
	{
		delete[] items;
		items = nullptr;
	}
}

template<class Key, class Data>
inline int THashTable<Key, Data>::HashFunction(Key* k)
{
	std::hash<Key> hashFunction;
	return hashFunction(*k) % (this->size + 1);
}

template<class Key, class Data>
inline int THashTable<Key, Data>::HashFunction(Key* k) const
{
	std::hash<Key> hashFunction;
	return hashFunction(*k) % (this->size + 1);
}

template<class Key, class Data>
inline int THashTable<Key, Data>::DoubleHashFunction(int prev_index)
{
	int p = 1;
	return (prev_index + p) % (this->size + 1);
}

template<class Key, class Data>
inline int THashTable<Key, Data>::DoubleHashFunction(int prev_index) const
{
	int p = 1;
	return (prev_index + p) % (this->size + 1);
}

template<class Key, class Data>
inline void THashTable<Key, Data>::Add(Key* k, Data* d)
{
	if (this -> IsFull())
		throw "Table is full!!";
	int num = -1;
	int prev_index = 0;
	int index = HashFunction(k);
	while(true)
	{
		if ((items[index].GetState() == 1) && (*(items[index].GetKey()) == *k))
			throw "Duplication!!";
		else if ((items[index].GetState() == 3) && (num == -1))
			num = index;
		else if ((items[index].GetState() == 2) && (num == -1))
		{
			items[index].SetState(1);
			items[index].SetKey(k);
			items[index].SetData(d);
			this->count++;
			break;
		}
		else if (((items[index].GetState() == 2) || (items[index].GetState() == 4)) && (num > -1))
		{
			items[num].SetState(1);
			items[num].SetKey(k);
			items[num].SetData(d);
			this ->count++;
			break;
		}
		else
		{
			prev_index = index;
			index = DoubleHashFunction(prev_index);
		}
	}
}

template<class Key, class Data>
inline Data* THashTable<Key, Data>::Find(Key* k)
{
	int index = FindInd(k);
	return items[index].GetData();
}

template<class Key, class Data>
inline const Data* THashTable<Key, Data>::Find(Key* k) const
{
	int index = FindInd(k);
	return items[index].GetData();
}

template<class Key, class Data>
inline void THashTable<Key, Data>::Delete(Key* k)
{
	int index = FindInd(k);
	items[index].SetState(3);
	this ->count--;
}

template<class Key, class Data>
inline Data* THashTable<Key, Data>::operator[](Key* k)
{
	return Find(k);
}

template<class Key, class Data>
inline const Data* THashTable<Key, Data>::operator[](Key* k) const
{
	return Find(k);
}

template<class Key, class Data>
inline int THashTable<Key, Data>::FindInd(Key* k)
{
	int num = -1;
	int prev_index = 0;
	int index = HashFunction(k);
	for (int i = 0; i < this->size; i++)
	{
		if ((items[index].GetState() == 1) && (*(items[index].GetKey()) == *k))
		{
			num = index;
			return num;
		}
		else
		{
			prev_index = index;
			index = DoubleHashFunction(prev_index);
		}
	}
	throw "Key is not found!!!";
}

template<class Key, class Data>
inline int THashTable<Key, Data>::FindInd(Key* k) const
{
	int num = -1;
	int prev_index = 0;
	int index = HashFunction(k);
	for (int i = 0; i < this->size; i++)
	{
		if ((items[index].GetState() == 1) && (*(items[index].GetKey()) == *k))
		{
			num = index;
			return num;
		}
		else
		{
			prev_index = index;
			index = DoubleHashFunction(prev_index);
		}
	}
	throw "Key is not found!!!";
}

template<class Key, class Data>
inline THashTableIterator<Key, Data> THashTable<Key, Data>::Begin()
{
	return THashTableIterator<Key, Data>(*this);
}

template<class Key, class Data>
inline THashTableIterator<Key, Data> THashTable<Key, Data>::End()
{
	return THashTableIterator<Key, Data>(*this, this->GetCount());
}

#endif