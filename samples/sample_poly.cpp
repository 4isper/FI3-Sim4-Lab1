// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// ������������ ���������

#include <iostream>
#include "Polynom.h"

int main()
{
	TPolynom p;
	size_t m1a[] = {1, 0, 1};
	TMonom m1(2.2, m1a, 3);
	m1a[2]++;
	TMonom m2(5.0, m1a, 3);
	m1a[2]--;
	m1a[0]++;
	TMonom m3(-12.5, m1a, 3);
	m1a[0] = 3;
	m1a[1] = 3;
	m1a[2] = 3;
	TMonom m4(-1.5, m1a, 3);
	m1a[0] = 1;
	m1a[1] = 0;
	m1a[2] = 0;
	TMonom m5(-2.0, m1a, 3);
	double m2a[] = { 1.0, 1.0, 1.0 };
	p = p + m1;
	p = p + m2;
	p = p + m3;
	p = p + m4;
	p = p + m5;
	std::cout << p << std::endl;
	std::cout << p.Compute(m2a, 3) << std::endl;
	return 0;
}