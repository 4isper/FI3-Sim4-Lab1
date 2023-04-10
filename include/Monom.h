// ����, �����, ���� "��������� � ��������� ������"
//
//
//
// �����

#ifndef __Monom_H__
#define __Monom_H__

#include <iostream>

class TMonom
{
protected:
	double K;
	size_t* A;
	size_t N;
	size_t realN;
	//const static size_t ZeroA = 0;
	friend class TPolynom;
public:
	TMonom(double K_ = 0.0, const size_t* A_ = nullptr, size_t N_ = 0);
	TMonom(const TMonom& m);
	TMonom(TMonom&& m) noexcept;
	TMonom& operator=(const TMonom& m);
	TMonom& operator=(const double& K_);
	TMonom& operator=(TMonom&& m) noexcept;
	~TMonom();

	void SetN(size_t N_, bool clear = true);
	void SetK(double K_) noexcept;
	void SetA(const size_t* A_, size_t N_);
	void SetAM(const size_t& v, size_t i);

	TMonom operator-(void) const;

	double GetK(void) const;
	size_t GetN(void) const;
	size_t GetAM(size_t i) const;
	const size_t* GetA(void) const;
	size_t GetRealN(void) const;

	bool operator>(const TMonom& m) const noexcept;
	bool operator<(const TMonom& m) const noexcept;
	bool operator>=(const TMonom& m) const noexcept;
	bool operator<=(const TMonom& m) const noexcept;
	bool operator==(const TMonom& m) const noexcept;
	bool operator!=(const TMonom& m) const noexcept;

	bool DegreesG(const TMonom& m) const noexcept;
	bool DegreesL(const TMonom& m) const noexcept;
	bool DegreesGE(const TMonom& m) const noexcept;
	bool DegreesLE(const TMonom& m) const noexcept;
	bool DegreesE(const TMonom& m) const noexcept;
	bool DegreesNE(const TMonom& m) const noexcept;

	bool DegreesG(const size_t* A_, size_t N_) const noexcept;
	bool DegreesL(const size_t* A_, size_t N_) const noexcept;
	bool DegreesGE(const size_t* A_, size_t N_) const noexcept;
	bool DegreesLE(const size_t* A_, size_t N_) const noexcept;
	bool DegreesE(const size_t* A_, size_t N_) const noexcept;
	bool DegreesNE(const size_t* A_, size_t N_) const noexcept;

	//friend std::istream& operator>>(std::istream& istr, TMonom& m);
	friend std::ostream& operator<<(std::ostream& ostr, const TMonom& m);
};

#endif