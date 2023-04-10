// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// ������� ������

#ifndef __ListItem_H__
#define __ListItem_H__

template<typename T>
class TListItem
{
public:
	T data;
	TListItem<T>* next = nullptr;
	TListItem<T>* prev = nullptr;
};



#endif