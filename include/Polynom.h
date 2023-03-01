// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// �������

#ifndef __Polynom_H__
#define __Polynom_H__

#include <iostream>
#include <cmath>
#include "Monom.h"
#include "TList.h"

class TPolynom
{
protected:
	TList<TMonom> monoms = TList<TMonom>();
	size_t maxN = 0;
public:
	TPolynom() {}
	TPolynom(const TPolynom& p);
	TPolynom& operator=(const TPolynom& p);

	size_t GetMaxN(void) const noexcept;

	void Clear(const size_t* A_, size_t N_);
	void Clear(void);
	double GetK(const size_t* A_, size_t N_) const;
	void SetK(const double& K_,const size_t* A_, size_t N_);
	void SetK(const TMonom& m);
	TMonom Get(size_t i) const;
	double Compute(const double* A_, size_t N_) const;

	TPolynom operator+(const TPolynom& p) const;
	TPolynom operator-(const TPolynom& p) const;
	TPolynom operator*(const TPolynom& p) const;

	TPolynom& operator+=(const TPolynom& p);
	TPolynom& operator-=(const TPolynom& p);
	TPolynom& operator*=(const TPolynom& p);

	TPolynom operator+(const TMonom& p) const;
	TPolynom operator-(const TMonom& p) const;
	TPolynom operator*(const TMonom& p) const;

	TPolynom& operator+=(const TMonom& p);
	TPolynom& operator-=(const TMonom& p);
	TPolynom& operator*=(const TMonom& p);

	TPolynom operator-(void) const;

	bool operator==(const TPolynom& m) const noexcept;
	bool operator!=(const TPolynom& m) const noexcept;

	//friend std::istream& operator>>(std::istream& istr, TPolynom& p);
	friend std::ostream& operator<<(std::ostream& ostr, const TPolynom& p);
};

#endif