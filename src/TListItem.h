// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// ������� ������

#ifndef __TListItem_H__
#define __TListItem_H__

template<typename T>
class TListItem
{
public:
	T data;
	TListItem<T>* next = nullptr;
	TListItem<T>* prev = nullptr;
};



#endif