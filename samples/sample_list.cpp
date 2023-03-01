// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// ������������ ������

#include <iostream>
#include "TList.h"

int main()
{
	TList<size_t> l;
	l.PushStart(2);
	l.PushEnd(4);
	l.Push(3, 1);
	std::cout << l << std::endl;
	l.PushEnd(6);
	l.PushStart(99);
	l.Pop(1);
	std::cout << l << std::endl;
	l.PushEnd(77);
	std::cout << l << std::endl;
	std::cout << "Start is " << l.GetStart() << std::endl;
	std::cout << "End is " << l.GetEnd() << std::endl;
	std::cout << "Center element is " << l.Get(l.GetCount() / 2) << std::endl;
	std::cout << "List is empty: " << l.IsEmpty() << std::endl;
	l.Clear();
	std::cout << "List is empty after clear: " << l.IsEmpty() << std::endl;
	return 0;
}