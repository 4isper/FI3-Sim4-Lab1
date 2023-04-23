#include "Formula.h"
#include "MyString.h"

#include <gtest.h>

TEST(TFormula, correction_test_simple)
{
	TFormula<double> f;
	f.SetFormula("1+2");
	ASSERT_NO_THROW(f.CheckFormula(true));
	f.SetFormula("1+2*(3-2)-4");
	ASSERT_NO_THROW(f.CheckFormula(true));
	f.SetFormula("(((1+23)*1-22)+5)*2-(7");
	ASSERT_ANY_THROW(f.CheckFormula(true));
	f.SetFormula("1+2/(3-3)");
	ASSERT_NO_THROW(f.CheckFormula(true));
	f.SetFormula("1++1");
	ASSERT_ANY_THROW(f.CheckFormula(true));
}

TEST(TFormula, correction_test_advanced)
{
	TFormula<double> f;
	f.SetFormula("1+2+3+sin");
	ASSERT_ANY_THROW(f.CheckFormula(true));
	f.SetFormula("1+2+3+si");
	ASSERT_NO_THROW(f.CheckFormula(true));
	f.SetFormula("1+2+sin+3");
	ASSERT_ANY_THROW(f.CheckFormula(true));
	f.SetFormula("1+2+sin(2)+3");
	ASSERT_NO_THROW(f.CheckFormula(true));
	f.SetFormula("1+2+3+a(2)+3");
	ASSERT_ANY_THROW(f.CheckFormula(true));
	f.SetFormula("1+2+(sin(2+3))+13");
	ASSERT_NO_THROW(f.CheckFormula(true));

	f.SetFormula("1.0+2.0+sin(3.0)");
	ASSERT_NO_THROW(f.CheckFormula(true));
	f.SetFormula("1.0f+2.0+sin(3.0)");
	ASSERT_ANY_THROW(f.CheckFormula(true));
	f.SetFormula("1..0+2.0+sin(3.0)");
	ASSERT_ANY_THROW(f.CheckFormula(true));
	f.SetFormula("1.0+2.0+sin(3.0)+.");
	ASSERT_ANY_THROW(f.CheckFormula(true));
	f.SetFormula("1+2+sin#+13");
	ASSERT_ANY_THROW(f.CheckFormula(true));
}

TEST(TFormula, postfix_form_test_without_functions)
{
	TFormula<double> f;
	f.SetFormula("(a+b*c)*(c/d-e)");
	EXPECT_EQ("a b c * + c d / e - *", f.GetPostfixForm());

	f.SetFormula("-a+b*(-a+c)");
	EXPECT_EQ("a ~ b a ~ c + * +", f.GetPostfixForm());

	f.SetFormula("a+b*(-a+c)");
	EXPECT_EQ("a b a ~ c + * +", f.GetPostfixForm());

	f.SetFormula("-(a+b)+c*d");
	EXPECT_EQ("a b + ~ c d * +", f.GetPostfixForm());
}

TEST(TFormula, postfix_form_test_with_functions)
{
	TFormula<double> f;
	f.SetFormula("(a+b*sin(c+a))*(c/d-log(e))");
	EXPECT_EQ("a b c a + sin * + c d / e log - *", f.GetPostfixForm());

	f.SetFormula("a+b+sin(cos(c+log(11+d) - tan(aa+22)))");
	EXPECT_EQ("a b + c 11 d + log + aa 22 + tan - cos sin +", f.GetPostfixForm());

	f.SetFormula("-a+b+sin(cos(c+log(11+d) - tan(aa+22)))");
	EXPECT_EQ("a ~ b + c 11 d + log + aa 22 + tan - cos sin +", f.GetPostfixForm());
}

TEST(TFormula, calculation_without_functions)
{
	TFormula<double> f;
	f.SetFormula("1+1");
	EXPECT_EQ(1.0 + 1.0, f.Calculate());

	f.SetFormula("(((1+23)*1-22)+5)*2-7");
	EXPECT_EQ("1 23 + 1 * 22 - 5 + 2 * 7 -", f.GetPostfixForm());
	EXPECT_EQ(((((1.0 + 23.0) * 1.0 - 22.0) + 5.0) * 2.0 - 7.0), (f.Calculate()));

	f.SetFormula("-2^5");
	EXPECT_EQ(-std::pow(2.0, 5.0), f.Calculate());
}

TEST(TFormula, calculation_with_functions)
{
	TFormula<double> f;
	f.SetFormula("log(pi)+tan(33)");
	EXPECT_EQ(std::log(M_PI) + std::tan(33.0), f.Calculate());
}

TEST(TFormula, calculation_with_vars)
{
	TFormula<double> f;
	f.SetFormula("a1+b_*cc");
	TString vars[] = { "a1", "b_", "cc" };
	double vals[] = { 1.0, 2.2, 2.4 };
	f.SetDefinedValues(vars, vals, 3);
	EXPECT_EQ(1.0 + 2.2 * 2.4, f.Calculate());
}

TEST(TFormula, cannot_divide_by_zero)
{
	TFormula<double> f;
	f.SetFormula("1+2/(3-3)");
	ASSERT_NO_THROW(f.CreatePostfixForm());
	ASSERT_ANY_THROW(f.Calculate());
}

TEST(TFormula, can_copy_formula)
{
	TFormula<double> f;
	f.SetFormula("a1+b_*cc");
	TString vars[] = { "a1", "b_", "cc" };
	double vals[] = { 1.0, 2.2, 2.4 };
	f.SetDefinedValues(vars, vals, 3);
	EXPECT_EQ(1.0 + 2.2 * 2.4, f.Calculate());
	TFormula<double> f2(f);
	TFormula<double> f3 = f;

	EXPECT_EQ(f.GetFormula(), f2.GetFormula());
	EXPECT_EQ(f.GetFormula(), f3.GetFormula());

	EXPECT_EQ(f.GetPostfixForm(), f2.GetPostfixForm());
	EXPECT_EQ(f.GetPostfixForm(), f3.GetPostfixForm());

	EXPECT_EQ(1.0 + 2.2 * 2.4, f2.Calculate());
	EXPECT_EQ(1.0 + 2.2 * 2.4, f3.Calculate());
}

TEST(TFormula, cant_copy_self)
{
	TFormula<double> f;
	f.SetFormula("a1+b_*cc");
	TString vars[] = { "a1", "b_", "cc" };
	double vals[] = { 1.0, 2.2, 2.4 };
	f.SetDefinedValues(vars, vals, 3);

	EXPECT_NO_THROW(f = f);
}

TEST(TFormula, can_select_table)
{
	TFormula<double> f;
	f.SetFormula("a1+b_*cc");
	TString vars[] = { "a1", "b_", "cc" };
	double vals[] = { 1.0, 2.2, 2.4 };
	f.SetDefinedValues(vars, vals, 3);
	for (size_t i = 0; i < FORMULA_TABLES_ARRAY_SIZE; i++)
	{
		f.SelectTable(i);
		EXPECT_EQ(1.0 + 2.2 * 2.4, f.Calculate());
	}
}

TEST(TFormula, cant_select_table_out_of_range)
{
	TFormula<double> f;
	f.SetFormula("a1+b_*cc");
	TString vars[] = { "a1", "b_", "cc" };
	double vals[] = { 1.0, 2.2, 2.4 };
	f.SetDefinedValues(vars, vals, 3);
	EXPECT_ANY_THROW(f.SelectTable(FORMULA_TABLES_ARRAY_SIZE+1));
}
