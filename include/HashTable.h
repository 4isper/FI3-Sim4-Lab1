#include "IMap.h"
#include "Item.h"

#ifndef __HashTable_H__
#define __HashTable_H__
template <class Key, class Data>
class THashTable : public IMap<Key,Data>
{
public:
	THashTable(int size_table = 10);
	THashTable(const THashTable<Key, Data>& m);
	~THashTable();
	int HashFunction(Key* k, int table_size);
	int HashFunction(Key* k, int table_size) const;
	int DoubleHashFunction(int table_size,int prev_index);
	int DoubleHashFunction(int table_size,int prev_index) const;
	void Add(Key* k, Data* d);
	Data* Find(Key* k);
	const Data* Find(Key* k) const;
	void Delete(Key* k); 
	Data* operator[](Key* k);
	const Data* operator[](Key* k) const;
	int FindInd(Key* k);
	int FindInd(Key* k) const;
protected:
	TItem<Key, Data>* items;
};

template<class Key, class Data>
inline THashTable<Key, Data>::THashTable(int size_table)
{
	if (size_table > 0)
	{
		this->size = size_table;
		this->count = 0;
		items = new TItem<Key, Data>[this->size];
		for (int i = 0; i < this->size; i++)
			items[i].SetState(2);
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
inline int THashTable<Key, Data>::HashFunction(Key* k, int table_size)
{
	int sum = 0;
	for (char ch : *k)
		sum += ch;
	return sum % table_size;
}

template<class Key, class Data>
inline int THashTable<Key, Data>::HashFunction(Key* k, int table_size) const
{
	int sum = 0;
	for (char ch : *k)
		sum += ch;
	return sum % table_size;
}

template<class Key, class Data>
inline int THashTable<Key, Data>::DoubleHashFunction(int table_size,int prev_index)
{
	int p = 1;
	return (prev_index + p) % table_size;
}

template<class Key, class Data>
inline int THashTable<Key, Data>::DoubleHashFunction(int table_size, int prev_index) const
{
	int p = 1;
	return (prev_index + p) % table_size;
}

template<class Key, class Data>
inline void THashTable<Key, Data>::Add(Key* k, Data* d)
{
	if (this -> IsFull())
		throw "Table is full!!";
	int num = -1;
	int prev_index = 0;
	int index = HashFunction(k, this ->size);
	do
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
		else if ((items[index].GetState() == 2) && (num > -1))
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
			index = DoubleHashFunction(this->size, prev_index);
		}
	} while (true);
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
	int index = HashFunction(k, this->size);
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
			index = DoubleHashFunction(this->size, prev_index);
		}
	}
	throw "Key is not found!!!";
}

template<class Key, class Data>
inline int THashTable<Key, Data>::FindInd(Key* k) const
{
	int num = -1;
	int prev_index = 0;
	int index = HashFunction(k, this->size);
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
			index = DoubleHashFunction(this->size, prev_index);
		}
	}
	throw "Key is not found!!!";
}

#endif