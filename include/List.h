// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// �������� ������

// TODO: add list iterator

#ifndef __List_H__
#define __List_H__

#include <iostream>
#include "ListItem.h"

template <typename T>
class TList
{
protected:
	size_t count;
	TListItem<T>* start;
	TListItem<T>* end;

	//TListItem<T>* cur_item;
	//size_t cur_item_i;

	TListItem<T>* GetListItem(size_t i) const;
public:
	TList();
	TList(const TList<T>& l);
	TList& operator=(const TList<T>& l);
	~TList();

	bool IsEmpty() const noexcept;

	void PushStart(const T& data);
	void PushEnd(const T& data);
	void Push(const T& data, size_t i);

	T& GetStart(void);
	T& GetEnd(void);
	T& Get(size_t i);

	const T& GetStart(void) const;
	const T& GetEnd(void) const;
	const T& Get(size_t i) const;

	void PopStart();
	void PopEnd();
	void Pop(size_t i);

	void Clear();

	size_t GetCount(void) const noexcept;

	bool operator==(const TList& l) const noexcept;
	bool operator!=(const TList& l) const noexcept;

	//friend std::istream& operator>>(std::istream& istr, TList& l);
	friend std::ostream& operator<<(std::ostream& ostr, const TList& l)
	{
		TListItem<T>* tmp = l.start;
		for (size_t i = 0; i < l.count - 1; i++)
		{
			ostr << tmp->data << '\t';
			tmp = tmp->next;
		}
		ostr << l.end->data;
		return ostr;
	}
};

template<typename T>
inline TListItem<T>* TList<T>::GetListItem(size_t i) const
{
	if (IsEmpty())
		return nullptr;
	i = (i < count) ? i : i % count;
	TListItem<T>* tmp;
	//size_t k;
	//if (i >= cur_item_i && cur_item != nullptr)
	//{
	//	tmp = cur_item;
	//	k = cur_item_i;
	//}
	//else
	//{
	//	tmp = start;
	//	k = 0;
	//}
	//for (; k < i; k++)
	//	tmp = tmp->next;
	//cur_item_i = i;
	//cur_item = tmp;
	tmp = start;
	for (size_t k = 0; k < i; k++)
		tmp = tmp->next;
	return tmp;
}

template<typename T>
inline TList<T>::TList()
{
	count = 0;
	Clear();
}

template<typename T>
inline TList<T>::TList(const TList<T>& l)
{
	count = 0;
	Clear();
	this->operator=(l);
	//if (l.count != 0)
	//{
	//	start = new TListItem<T>;
	//	start->data = l.start->data;
	//	start->next = l.start->next;
	//	start->prev = l.start->prev;
	//	TListItem<T>* i = l.start->next;
	//	TListItem<T>* j = start;
	//	TListItem<T>* tmp;
	//	while (i != l.start)
	//	{
	//		tmp = new TListItem<T>;
	//		tmp->data = i->data;
	//		tmp->next = i->next;
	//		tmp->prev = i->prev;
	//		j->next = tmp;
	//		j->next->prev = j;
	//		if (i == l.cur_item)
	//			cur_item = tmp;
	//		j = j->next;
	//		i = i->next;
	//	}
	//	end = j;
	//	start->prev = j;
	//	count = l.count;
	//	cur_item_i = l.cur_item_i;
	//	if (l.cur_item == nullptr)
	//		cur_item = nullptr;
	//}
	//else
	//{
	//	count = 0;
	//	Clear();
	//}
}

template<typename T>
inline TList<T>& TList<T>::operator=(const TList<T>& l)
{
	if (start == l.start || end == l.end)
		return *this;
	Clear();
	//if (l.count != 0)
	//{
	//	start = new TListItem<T>;
	//	start->data = l.start->data;
	//	start->next = l.start->next;
	//	start->prev = l.start->prev;
	//	TListItem<T>* i = l.start->next;
	//	TListItem<T>* j = start;
	//	TListItem<T>* tmp;
	//	while (i != l.start)
	//	{
	//		tmp = new TListItem<T>;
	//		tmp->data = i->data;
	//		tmp->next = i->next;
	//		tmp->prev = i->prev;
	//		j->next = tmp;
	//		j->next->prev = j;
	//		//if (i == l.cur_item)
	//		//	cur_item = tmp;
	//		j = j->next;
	//		i = i->next;
	//	}
	//	end = j;
	//	start->prev = j;
	//	count = l.count;
	//	//cur_item_i = l.cur_item_i;
	//	//if (l.cur_item == nullptr)
	//	//	cur_item = nullptr;
	//}
	if (l.count != 0)
	{
		TListItem<T>* tmp = l.start;
		for (size_t i = 0; i < l.count; i++)
		{
			this->PushEnd(tmp->data);
			tmp = tmp->next;
		}
	}
	return *this;
}

template<typename T>
inline TList<T>::~TList()
{
	this->Clear();
}

template<typename T>
inline bool TList<T>::IsEmpty() const noexcept
{
	return count == 0;
}

template<typename T>
inline void TList<T>::PushStart(const T& data)
{
	TListItem<T>* tmp = new TListItem<T>;
	tmp->data = data;
	if (IsEmpty())
	{
		start = tmp;
		end = tmp;
	}
	tmp->next = start;
	tmp->prev = end;
	start->prev = tmp;
	end->next = tmp;
	start = tmp;
	count++;
	//cur_item_i++;
}

template<typename T>
inline void TList<T>::PushEnd(const T& data)
{
	TListItem<T>* tmp = new TListItem<T>;
	tmp->data = data;
	if (IsEmpty())
	{
		start = tmp;
		end = tmp;
	}
	tmp->next = start;
	tmp->prev = end;
	end->next = tmp;
	start->prev = tmp;
	end = tmp;
	count++;
}

template<typename T>
inline void TList<T>::Push(const T& data, size_t i)
{
	if (i > count)
		throw std::out_of_range("Push: index is out of range");
	if (i == 0)
		PushStart(data);
	else if (i == count)
		PushEnd(data);
	else
	{
		TListItem<T>* tmp1 = new TListItem<T>;
		tmp1->data = data;
		TListItem<T>* tmp2 = GetListItem(i);
		tmp1->next = tmp2;
		tmp1->prev = tmp2->prev;
		tmp2->prev->next = tmp1;
		tmp2->prev = tmp1;
		//cur_item_i++;
		count++;
	}
}

template<typename T>
inline T& TList<T>::GetStart(void)
{
	if (IsEmpty())
		throw std::out_of_range("List is empty");
	return start->data;
}

template<typename T>
inline T& TList<T>::GetEnd(void)
{
	if (IsEmpty())
		throw std::out_of_range("List is empty");
	return end->data;
}

template<typename T>
inline T& TList<T>::Get(size_t i)
{
	if (IsEmpty())
		throw std::out_of_range("List is empty");
	return GetListItem(i)->data;
}

template<typename T>
inline const T& TList<T>::GetStart(void) const
{
	if (IsEmpty())
		throw std::out_of_range("List is empty");
	return start->data;
}

template<typename T>
inline const T& TList<T>::GetEnd(void) const
{
	if (IsEmpty())
		throw std::out_of_range("List is empty");
	return end->data;
}

template<typename T>
inline const T& TList<T>::Get(size_t i) const
{
	if (IsEmpty())
		throw std::out_of_range("List is empty");
	//i = (i < count) ? i : i % count;
	//if (i == 0)
	//	return GetStart();
	//if (i == count - 1)
	//	return GetEnd();
	//TListItem<T>* tmp = start;
	//for (size_t k = 0; k < i; k++)
	//	tmp = tmp->next;
	//return tmp->data;
	return GetListItem(i)->data;
}

template<typename T>
inline void TList<T>::PopStart()
{
	if (count != 0)
	{
		if (count != 1)
		{
			TListItem<T>* tmp = start;
			start = tmp->next;
			end->next = start;
			start->prev = end;
			delete tmp;
			count--;
		}
		else
			Clear();
	}
	else
		throw std::out_of_range("Can't pop, list is empty.");
}

template<typename T>
inline void TList<T>::PopEnd()
{
	if (count != 0)
	{
		if (count != 1)
		{
			TListItem<T>* tmp = end;
			end = tmp->prev;
			start->prev = end;
			end->next = start;
			delete tmp;
			count--;
		}
		else
			Clear();
	}
	else
		throw std::out_of_range("Can't pop, list is empty.");
}

template<typename T>
inline void TList<T>::Pop(size_t i)
{
	if (count != 0)
	{
		if (i >= count)
			throw std::out_of_range("Pop: index is out of range.");
		if (i == 0)
			PopStart();
		else if (i == count - 1)
			PopEnd();
		else
		{
			TListItem<T>* tmp = GetListItem(i);
			//TListItem<T>* tmp_prev = cur_item;
			TListItem<T>* tmp_prev = tmp->prev;
			tmp_prev = tmp->prev;
			//cur_item_i--;
			tmp_prev->next = tmp->next;
			tmp->next->prev = tmp_prev;
			delete tmp;
			count--;
		}
	}
	else
		throw std::out_of_range("Can't pop, list is empty.");
}

template<typename T>
inline void TList<T>::Clear()
{
	if (count != 0)
	{
		TListItem<T>* tmp = start;
		while (tmp != end)
		{
			tmp = tmp->next;
			delete tmp->prev;
		}
		delete end;
		count = 0;
	}
	start = nullptr;
	end = nullptr;
	//cur_item = nullptr;
	//cur_item_i = 0;
}

template<typename T>
inline size_t TList<T>::GetCount() const noexcept
{
	return count;
}

template<typename T>
inline bool TList<T>::operator==(const TList& l) const noexcept
{
	if (IsEmpty() && l.IsEmpty())
		return true;
	if (count != l.count)
		return false;
	TListItem<T>* i = start;
	TListItem<T>* j = l.start;
	while (i != end)
	{
		if (i->data != j->data)
			return false;
		i = i->next;
		j = j->next;
	}
	return (end->data == l.end->data);
}

template<typename T>
inline bool TList<T>::operator!=(const TList& l) const noexcept
{
	return !(this->operator==(l));
}

#endif