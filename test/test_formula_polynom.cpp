#include "Polynom.h"
#include "Formula.h"

#include <gtest.h>

TEST(TFormula, poly_test1)
{
    TFormula<TPolynom> test;
    test.SetFormula("a+b*c");
    TPolynom a;
    TPolynom b;
    TPolynom c;
    TString str[] = {"a", "b", "c"};

    size_t m1a[] = {0};
    size_t m2a[] = {1};
    size_t m3a[] = {2};

    TMonom a1(2.0, m1a, 1);
    TMonom a2(1.0, m2a, 1);
    TMonom a3(1.0, m3a, 1);
    a += a1;
    a += a2;
    a += a3;

    TMonom b1(2.0, m1a, 1);
    TMonom b2(1.0, m2a, 1);
    b += b1;
    b += b2;

    TMonom c1(1.0, m1a, 1);
    TMonom c2(3.0, m2a, 1);
    c += c1;
    c += c2;

    test.SetDefinedValue(&(str[0]), &a);
    test.SetDefinedValue(&(str[1]), &b);
    test.SetDefinedValue(&(str[2]), &c);
    EXPECT_EQ(a+b*c, test.Calculate());
}
