#include "Polynom.h"

#include <gtest.h>

TEST(TPolynom, test1)
{
	TPolynom P, Q, Res, Must;
	size_t a1[] = { 5, 2, 5 }, a2[] = { 4, 3, 3 }, a3[] = { 3, 5, 1 }, b1[] = { 3, 2, 6 }, b2[] = { 2, 1, 8 };
	TMonom m1s[] = { TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(7.0, a3, 3)};
	TMonom m2s[] = { TMonom(4.0, b1, 3), TMonom(-6.0, b2, 3) };
	TMonom m3s[] = { TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(7.0, a3, 3), TMonom(4.0, b1, 3), TMonom(-6.0, b2, 3) };
	for (size_t i = 0; i < 3; i++)
		P += m1s[i];
	for (size_t i = 0; i < 2; i++)
		Q += m2s[i];
	for (size_t i = 0; i < 5; i++)
		Must += m3s[i];
	Res = P + Q;
	EXPECT_EQ(Must, Res);
	std::stringstream bf;
	bf << Res;
	EXPECT_EQ("3*(x_0)^5*(x_1)^2*(x_2)^5-5*(x_0)^4*(x_1)^3*(x_2)^3+7*(x_0)^3*(x_1)^5*x_2+4*(x_0)^3*(x_1)^2*(x_2)^6-6*(x_0)^2*x_1*(x_2)^8", bf.str());
}

TEST(TPolynom, test2)
{
	TPolynom P, Q, Res, Must;
	size_t a1[] = { 5, 2, 5 }, a2[] = { 4, 3, 3 }, a3[] = { 3, 5, 1 }, b1[] = { 7, 2, 6 }, b2[] = { 6, 1, 8 };
	TMonom m1s[] = { TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(7.0, a3, 3) };
	TMonom m2s[] = { TMonom(4.0, b1, 3), TMonom(-6.0, b2, 3) };
	TMonom m3s[] = { TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(7.0, a3, 3), TMonom(4.0, b1, 3), TMonom(-6.0, b2, 3) };
	for (size_t i = 0; i < 3; i++)
		P += m1s[i];
	for (size_t i = 0; i < 2; i++)
		Q += m2s[i];
	for (size_t i = 0; i < 5; i++)
		Must += m3s[i];
	Res = P + Q;
	EXPECT_EQ(Must, Res);
	std::stringstream bf;
	bf << Res;
	EXPECT_EQ("4*(x_0)^7*(x_1)^2*(x_2)^6-6*(x_0)^6*x_1*(x_2)^8+3*(x_0)^5*(x_1)^2*(x_2)^5-5*(x_0)^4*(x_1)^3*(x_2)^3+7*(x_0)^3*(x_1)^5*x_2", bf.str());
}

TEST(TPolynom, test3)
{
	TPolynom P, Q, Res, Must;
	size_t a1[] = { 5, 2, 5 }, a2[] = { 4, 3, 3 }, a3[] = { 3, 5, 1 };
	TMonom m1s[] = { TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(7.0, a3, 3) };
	TMonom m2s[] = { TMonom(4.0, a1, 3), TMonom(5.0, a2, 3) };
	TMonom m3s[] = { TMonom(7.0, a1, 3), TMonom(7.0, a3, 3) };
	for (size_t i = 0; i < 3; i++)
		P += m1s[i];
	for (size_t i = 0; i < 2; i++)
		Q += m2s[i];
	for (size_t i = 0; i < 2; i++)
		Must += m3s[i];
	Res = P + Q;
	EXPECT_EQ(Must, Res);
	std::stringstream bf;
	bf << Res;
	EXPECT_EQ("7*(x_0)^5*(x_1)^2*(x_2)^5+7*(x_0)^3*(x_1)^5*x_2", bf.str());
}

TEST(TPolynom, test4)
{
	TPolynom P, Q, Res, Must;
	size_t a1[] = { 5, 2, 5 }, a2[] = { 4, 3, 3 }, a3[] = { 7, 5, 1 }, b1[] = { 6, 2, 6 }, b2[] = { 2, 1, 8 };
	TMonom m1s[] = { TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(7.0, a3, 3) };
	TMonom m2s[] = { TMonom(4.0, b1, 3), TMonom(-6.0, b2, 3) };
	TMonom m3s[] = { TMonom(7.0, a3, 3), TMonom(4.0, b1, 3), TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(-6.0, b2, 3) };
	for (size_t i = 0; i < 3; i++)
		P += m1s[i];
	for (size_t i = 0; i < 2; i++)
		Q += m2s[i];
	for (size_t i = 0; i < 5; i++)
		Must += m3s[i];
	Res = P + Q;
	EXPECT_EQ(Must, Res);
	std::stringstream bf;
	bf << Res;
	EXPECT_EQ("7*(x_0)^7*(x_1)^5*x_2+4*(x_0)^6*(x_1)^2*(x_2)^6+3*(x_0)^5*(x_1)^2*(x_2)^5-5*(x_0)^4*(x_1)^3*(x_2)^3-6*(x_0)^2*x_1*(x_2)^8", bf.str());
}

TEST(TPolynom, test5)
{
	TPolynom P, Q, Res, Must;
	size_t a1[] = { 5, 2, 5 }, a2[] = { 4, 3, 3 }, a3[] = { 7, 5, 1 };
	TMonom m1s[] = { TMonom(3.0, a1, 3), TMonom(-5.0, a2, 3), TMonom(7.0, a3, 3) };
	TMonom m2s[] = { TMonom(-3.0, a1, 3), TMonom(5.0, a2, 3), TMonom(-7.0, a3, 3) };
	for (size_t i = 0; i < 3; i++)
		P += m1s[i];
	for (size_t i = 0; i < 3; i++)
		Q += m2s[i];
	Res = P + Q;
	EXPECT_EQ(Must, Res);
	std::stringstream bf;
	bf << Res;
	EXPECT_EQ("0", bf.str());
}
