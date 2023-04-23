// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// ������������ �������������� ���������

#include <iostream>
#include "Formula.h"

int main(int argc, char* argv[])
{
	TFormula<double> test;
	test.SetFormula(TString("a+b*cos(c*pi)"));
	test.CreatePostfixForm();
	std::cout << "Postfix form for " << test.GetFormula() << " is " << test.GetPostfixForm() << std::endl;
	TString vars[] = { "a", "b", "c" };
	double vals[] = { 1.0, 2.2, 2.4 };
	std::cout << "Let ";
	for (size_t i = 0; i < 2; i++)
	{
		std::cout << vars[i] << " = " << vals[i] << ", ";
	}
	std::cout << vars[2] << " = " << vals[2] << ".\n";
	test.SetDefinedValues(vars, vals, 3);
	std::cout << "Then " << test.GetFormula() << " is equal to " << test.Calculate() << std::endl;
	std::cout << "The value should be " << vals[0] + vals[1] * std::cos(vals[2] * M_PI) << std::endl;
	return 0;
}