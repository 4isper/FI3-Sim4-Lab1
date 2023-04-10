#include "Monom.h"

TMonom::TMonom(double K_, const size_t* A_, size_t N_)
{
	if (A_ == nullptr)
		N = 0;
	else
		N = N_;
	realN = 0;
	K = K_;
	if (N != 0)
	{
		//size_t lostZeroes = 0;
		A = new size_t[N];
		for (size_t i = 0; i < N; i++)
		{
			this->SetAM(A_[i], i);
			//A[i] = A_[i];
			//if (A[i] != 0)
			//{
			//	realN += lostZeroes + 1;
			//	lostZeroes = 0;
			//}
			//else
			//{
			//	lostZeroes++;
			//}
		}
	}
	else
		A = nullptr;
}

TMonom::TMonom(const TMonom& m)
{
	A = nullptr;
	N = 0;
	this->operator=(m);
}

TMonom::TMonom(TMonom&& m) noexcept
{
	this->operator=(m);
}

TMonom& TMonom::operator=(const TMonom& m)
{
	K = m.K;
	realN = m.realN;
	if (m.A == nullptr)
	{
		N = 0;
		return *this;
	}
	if (m.A == A)
		return *this;
	if (N != m.N)
	{
		size_t* tmp = new size_t[m.N];
		N = m.N;
		if (A != nullptr)
			delete[] A;
		A = tmp;
	}
	for (size_t i = 0; i < N; i++)
		A[i] = m.A[i];
	return *this;
}

TMonom& TMonom::operator=(const double& K_)
{
  K = K_;
  A = nullptr;
  N = 0;
  realN = 0;
	return *this;
}

TMonom& TMonom::operator=(TMonom&& m) noexcept
{
	A = nullptr;
	N = 0;
	std::swap(A, m.A);
	std::swap(K, m.K);
	std::swap(N, m.N);
	std::swap(realN, m.realN);
	return *this;
}

TMonom::~TMonom()
{
	delete[] A;
	K = double();
	N = 0;
	realN = 0;
}

void TMonom::SetN(size_t N_, bool clear)
{
	if (N_ == 0)
		throw "N_ cannot be 0";
	if (N_ != N)
	{
		//size_t* tmp = new size_t[N_];
		TMonom tmp(TMonom(0.0, new size_t[N_], N_));
		size_t i;
		if (!clear)
		{
			if (N_ > N)
			{
				for (i = 0; i < N; i++)
					//tmp[i] = A[i];
					tmp.SetAM(A[i], i);
				for (; i < N_; i++)
					//tmp[i] = 0;
					tmp.SetAM(0, i);
			}
			else
			{
				for (i = 0; i < N_; i++)
					//tmp[i] = A[i];
					tmp.SetAM(A[i], i);
			}
		}
		N = N_;
		A = tmp.A;
	}
	if (N == N_ || clear)
	{
		realN = 0;
		for (size_t i = 0; i < N_; i++)
			A[i] = 0;
	}
}

void TMonom::SetK(double K_) noexcept
{
	K = K_;
}

void TMonom::SetA(const size_t* A_, size_t N_)
{
	if (A_ != nullptr || N_ == 0)
	{
		//size_t* tmp = new size_t[N_];
		TMonom tmp(TMonom(0.0, new size_t[N_], N_));
		for (size_t i = 0; i < N_; i++)
			//tmp[i] = A_[i];
			tmp.SetAM(A[i], i);
		delete[] A;
		A = tmp.A;
		N = N_;
	}
	else
	{
		delete[] A;
		A = nullptr;
		N = 0;
		realN = 0;
	}
}

void TMonom::SetAM(const size_t& v, size_t i)
{
	if (i >= N && v > 0)
	{
		SetN(i + 1, false);
		SetAM(v, i);
	}
	if (i >= N && v == 0)
		return;
	A[i] = v;
	if (v > 0 && i >= realN)
		realN = i + 1;
	if (v == 0 && realN > 0 && i == realN - 1 )
	{
		for (size_t j = realN - 1; j > 0; j--)
		{
			if (A[j] == 0)
				realN--;
			else
				break;
		}
		if (realN == 1 && A[0] == 0)
			realN = 0;
	}
}

TMonom TMonom::operator-(void) const
{
	TMonom tmp(*this);
	tmp.K = -tmp.K;
	return tmp;
}

double TMonom::GetK(void) const
{
	return K;
}

size_t TMonom::GetN(void) const
{
	return N;
}

size_t TMonom::GetAM(size_t i) const
{
	if (i >= N)
		return 0;
	return A[i];
}

const size_t* TMonom::GetA(void) const
{
	return A;
}

size_t TMonom::GetRealN(void) const
{
	return realN;
}

bool TMonom::operator>(const TMonom& m) const noexcept
{
	if (m.A == nullptr)
		return realN != 0 || K > m.K;
	if (A == m.A)
		return K > m.K;
	if (A == nullptr)
		return K > m.K && m.realN == 0;
	size_t MaxN;
	size_t MinN;
	size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= m.N)
	{
		MaxN = N;
		MinN = m.N;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = m.N;
		MinN = N;
		AMaxN = m.A;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] < m.A[i])
			return false;
		else if (A[i] > m.A[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return AMaxNisThis;
	return K > m.K;
}

bool TMonom::operator<(const TMonom& m) const noexcept
{
	if (m.A == nullptr)
		return realN == 0 && K < m.K;
	if (A == m.A)
		return K < m.K;
	if (A == nullptr)
		return K < m.K || m.realN != 0;
	size_t MaxN;
	size_t MinN;
	size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= m.N)
	{
		MaxN = N;
		MinN = m.N;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = m.N;
		MinN = N;
		AMaxN = m.A;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] > m.A[i])
			return false;
		else if (A[i] < m.A[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return !AMaxNisThis;
	return K < m.K;
}

bool TMonom::operator>=(const TMonom& m) const noexcept
{
	if (m.A == nullptr)
		return realN != 0 || K >= m.K;
	if (A == m.A)
		return K >= m.K;
	if (A == nullptr)
		return K >= m.K && m.realN == 0;
	size_t MaxN;
	size_t MinN;
	size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= m.N)
	{
		MaxN = N;
		MinN = m.N;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = m.N;
		MinN = N;
		AMaxN = m.A;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] < m.A[i])
			return false;
		else if (A[i] > m.A[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return AMaxNisThis;
	return K >= m.K;
}

bool TMonom::operator<=(const TMonom& m) const noexcept
{
	if (m.A == nullptr)
		return realN == 0 && K <= m.K;
	if (A == m.A)
		return K <= m.K;
	if (A == nullptr)
		return K <= m.K || m.realN != 0;
	size_t MaxN;
	size_t MinN;
	size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= m.N)
	{
		MaxN = N;
		MinN = m.N;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = m.N;
		MinN = N;
		AMaxN = m.A;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] > m.A[i])
			return false;
		else if (A[i] < m.A[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return !AMaxNisThis;
	return K <= m.K;
}

bool TMonom::operator==(const TMonom& m) const noexcept
{
	if (m.A == nullptr)
		return realN == 0 && K == m.K;
	if (A == m.A)
		return K == m.K;
	if (A == nullptr)
		return K == m.K && m.realN == 0;
	size_t MaxN;
	size_t MinN;
	size_t* AMaxN;
	if (N >= m.N)
	{
		MaxN = N;
		MinN = m.N;
		AMaxN = A;
	}
	else
	{
		MaxN = m.N;
		MinN = N;
		AMaxN = m.A;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
		if (A[i] != m.A[i])
			return false;
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return false;
	return K == m.K;
}

bool TMonom::operator!=(const TMonom& m) const noexcept
{
	return !(this->operator==(m));
}

bool TMonom::DegreesG(const TMonom& m) const noexcept
{
	return DegreesG(m.A, m.N);
}

bool TMonom::DegreesL(const TMonom& m) const noexcept
{
	return DegreesL(m.A, m.N);
}

bool TMonom::DegreesGE(const TMonom& m) const noexcept
{
	return DegreesGE(m.A, m.N);
}

bool TMonom::DegreesLE(const TMonom& m) const noexcept
{
	return DegreesLE(m.A, m.N);
}

bool TMonom::DegreesE(const TMonom& m) const noexcept
{
	return DegreesE(m.A, m.N);
}

bool TMonom::DegreesNE(const TMonom& m) const noexcept
{
	return DegreesNE(m.A, m.N);
}

bool TMonom::DegreesG(const size_t* A_, size_t N_) const noexcept
{
	if (A_ == nullptr)
		return realN != 0;
	if (A == A_)
		return false;
	if (A == nullptr)
		return false;
	size_t MaxN;
	size_t MinN;
	const size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= N_)
	{
		MaxN = N;
		MinN = N_;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = N_;
		MinN = N;
		AMaxN = A_;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] < A_[i])
			return false;
		else if (A[i] > A_[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return AMaxNisThis;
	return false;
}

bool TMonom::DegreesL(const size_t* A_, size_t N_) const noexcept
{
	if (A_ == nullptr)
		return false;
	if (A == A_)
		return false;
	if (A == nullptr)
	{
		for (size_t i = 0; i < N_; i++)
			if (A_[i] != 0)
				return true;
		return false;
	}
	size_t MaxN;
	size_t MinN;
	const size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= N_)
	{
		MaxN = N;
		MinN = N_;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = N_;
		MinN = N;
		AMaxN = A_;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] > A_[i])
			return false;
		else if (A[i] < A_[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return !AMaxNisThis;
	return false;
}

bool TMonom::DegreesGE(const size_t* A_, size_t N_) const noexcept
{
	if (A_ == nullptr)
		return true;
	if (A == A_)
		return true;
	if (A == nullptr)
	{
		for (size_t i = 0; i < N_; i++)
			if (A_[i] != 0)
				return false;
		return true;
	}
	size_t MaxN;
	size_t MinN;
	const size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= N_)
	{
		MaxN = N;
		MinN = N_;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = N_;
		MinN = N;
		AMaxN = A_;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] < A_[i])
			return false;
		else if (A[i] > A_[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return AMaxNisThis;
	return true;
}

bool TMonom::DegreesLE(const size_t* A_, size_t N_) const noexcept
{
	if (A_ == nullptr)
		return realN == 0;
	if (A == A_)
		return true;
	if (A == nullptr)
		return true;
	size_t MaxN;
	size_t MinN;
	const size_t* AMaxN;
	bool AMaxNisThis;
	if (N >= N_)
	{
		MaxN = N;
		MinN = N_;
		AMaxN = A;
		AMaxNisThis = true;
	}
	else
	{
		MaxN = N_;
		MinN = N;
		AMaxN = A_;
		AMaxNisThis = false;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
	{
		if (A[i] > A_[i])
			return false;
		else if (A[i] < A_[i])
			return true;
	}
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return !AMaxNisThis;
	return true;
}

bool TMonom::DegreesE(const size_t* A_, size_t N_) const noexcept
{
	if (A_ == nullptr)
		return realN == 0;
	if (A == A_)
		return true;
	if (A == nullptr)
	{
		for (size_t i = 0; i < N_; i++)
			if (A_[i] != 0)
				return false;
		return true;
	}
	size_t MaxN;
	size_t MinN;
	const size_t* AMaxN;
	if (N >= N_)
	{
		MaxN = N;
		MinN = N_;
		AMaxN = A;
	}
	else
	{
		MaxN = N_;
		MinN = N;
		AMaxN = A_;
	}
	size_t i;
	for (i = 0; i < MinN; i++)
		if (A[i] != A_[i])
			return false;
	for (; i < MaxN; i++)
		if (AMaxN[i] != 0)
			return false;
	return true;
}

bool TMonom::DegreesNE(const size_t* A_, size_t N_) const noexcept
{
	return !(this->DegreesE(A_, N_));
}

std::ostream& operator<<(std::ostream& ostr, const TMonom& m)
{
	ostr << m.K;
	size_t i;
	for (i = 0; i < m.realN; i++)
	{
		if (m.A[i] != 0)
		{
			if (m.A[i] != 1)
				ostr << '*' << '(' << 'x' << '_' << i << ')' << '^' << m.A[i];
			else
				ostr << '*' << 'x' << '_' << i;
		}
	}
	return ostr;
}