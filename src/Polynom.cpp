#include "Polynom.h"

TPolynom::TPolynom(const TPolynom& p)
{
	//monoms = p.monoms;
	//maxN = p.maxN;
	this->operator=(p);
}

TPolynom& TPolynom::operator=(const TPolynom& p)
{
	maxN = p.maxN;
	monoms = p.monoms;
	return *this;
}

size_t TPolynom::GetMaxN(void) const noexcept
{
	return maxN;
}

void TPolynom::Clear(const size_t* A_, size_t N_)
{
	size_t sz = monoms.GetCount();
	if (A_ != nullptr && N_ != 0)
	{
		for (size_t i = 0; i < sz; i++)
		{
			TMonom& m = monoms.Get(i);
			bool equal = m.DegreesE(A_, N_);
			if (equal)
			{
				size_t realN = m.realN;
				monoms.Pop(i);
				sz--;
				if (realN == maxN)
				{
					size_t tmp = 0;
					for (size_t j = 0; j < sz; i++)
					{
						size_t rn = monoms.Get(j).realN;
						if (rn > tmp)
							tmp = rn;
						if (tmp == maxN)
							break;
					}
					maxN = tmp;
				}
			}
			if (equal || m.DegreesL(A_, N_))
				break;
		}
	}
	else
	{
		if (monoms.GetEnd().DegreesE(nullptr, 0))
		{
			size_t realN = monoms.GetEnd().realN;
			monoms.PopEnd();
			if (realN == maxN)
			{
				size_t tmp = 0;
				for (size_t i = 0; i < sz; i++)
				{
					size_t rn = monoms.Get(i).realN;
					if (rn > tmp)
						tmp = rn;
					if (tmp == maxN)
						break;
					maxN = tmp;
				}
			}
		}
	}
}

void TPolynom::Clear(void)
{
	monoms.Clear();
	maxN = 0;
}

double TPolynom::GetK(const size_t* A_, size_t N_) const
{
	size_t i, sz = monoms.GetCount();
	for (i = 0; i < sz; i++)
	{
		const TMonom& m = monoms.Get(i);
		bool equal = m.DegreesE(A_, N_);
		if (equal)
		{
			return m.K;
		}
		if (equal || m.DegreesG(A_, N_))
			break;
	}
	return 0.0;
}

void TPolynom::SetK(const double& K_, const size_t* A_, size_t N_)
{
	size_t i, sz = monoms.GetCount();
	bool found = false;
	for (i = 0; i < sz; i++)
	{
		TMonom& m = monoms.Get(i);
		bool equal = m.DegreesE(A_, N_);
		if (equal)
		{
			m.K = K_;
			found = true;
		}
		if (equal || m.DegreesG(A_, N_))
			break;
	}
	if (!found)
	{
		this->operator+=(TMonom(K_, A_, N_));
	}
}

void TPolynom::SetK(const TMonom& m)
{
	this->SetK(m.K, m.A, m.N);
}

TMonom TPolynom::Get(size_t i) const
{
	return monoms.Get(i);
}

double TPolynom::Compute(const double* A_, size_t N_) const
{
	if (N_ < maxN)
		throw "Not enough arguments to compute.";
	double res = 0.0;
	size_t sz = monoms.GetCount();
	for (size_t i = 0; i < sz; i++)
	{
		const TMonom& m = monoms.Get(i);
		double tmp = m.K;
		for (size_t j = 0; j < m.realN; j++)
			if (m.A[j] != 0)
				tmp *= std::pow(A_[j], m.A[j]);
		res += tmp;
	}
	return res;
}

TPolynom TPolynom::operator+(const TPolynom& p) const
{
	TPolynom tmp(*this);
	return tmp += p;
}

TPolynom TPolynom::operator-(const TPolynom& p) const
{
	TPolynom tmp(*this);
	return tmp -= p;
}

TPolynom TPolynom::operator*(const TPolynom& p) const
{
	TPolynom tmp(*this);
	return tmp *= p;
}

TPolynom& TPolynom::operator+=(const TPolynom& p)
{
	size_t sz = p.monoms.GetCount();
	for (size_t i = 0; i < sz; i++)
		*this += p.monoms.Get(i);
	return *this;
}

TPolynom& TPolynom::operator-=(const TPolynom& p)
{
	size_t sz = p.monoms.GetCount();
	for (size_t i = 0; i < sz; i++)
		*this -= p.monoms.Get(i);
	return *this;
}

TPolynom& TPolynom::operator*=(const TPolynom& p)
{
	size_t sz = p.monoms.GetCount();
	for (size_t i = 0; i < sz; i++)
		this->operator+=((*this) * p.monoms.Get(i));
	return *this;
}

TPolynom TPolynom::operator+(const TMonom& p) const
{
	TPolynom tmp(*this);
	return tmp += p;
}

TPolynom TPolynom::operator-(const TMonom& p) const
{
	TPolynom tmp(*this);
	return tmp -= p;
}

TPolynom TPolynom::operator*(const TMonom& p) const
{
	TPolynom tmp(*this);
	return tmp *= p;
}

TPolynom& TPolynom::operator+=(const TMonom& p)
{
	size_t i, sz = monoms.GetCount();
	if (sz != 0)
	{
		TMonom prev = monoms.GetStart();
		for (i = 0; i < sz; i++)
		{
			const TMonom& cur = monoms.Get(i);
			if (cur.DegreesGE(p))
				prev = cur;
			else
				break;
		}
		if (prev.DegreesE(p))
		{
			TMonom& tmp = monoms.Get(i - 1);
			if (tmp.K == (-p.K))
				Clear(tmp.A, tmp.N);
			else
				tmp.K += p.K;
		}
		else
			monoms.Push(p, i);
	}
	else
	{
		monoms.PushStart(p);
	}
	if (maxN <= p.realN)
		maxN = p.realN;
	return *this;
}

TPolynom& TPolynom::operator-=(const TMonom& p)
{
	TMonom tmp(-p);
	return this->operator+=(tmp);
}

TPolynom& TPolynom::operator*=(const TMonom& p)
{
	size_t sz = monoms.GetCount();
	for (size_t i = 0; i < sz; i++)
	{
		TMonom& m = monoms.Get(i);
		m.K *= p.K;
		if (m.N < p.realN)
			m.SetN(p.realN, false);
		for (size_t j = 0; j < p.realN; j++)
			m.A[j] += p.A[j];
		if (m.realN < p.realN)
			m.realN = p.realN;
	}
	return *this;
}

TPolynom TPolynom::operator-(void) const
{
	TPolynom tmp(*this);
	size_t sz = tmp.monoms.GetCount();
	for (size_t i = 0; i < sz; i++)
	{
		TMonom& m = tmp.monoms.Get(i);
		m = -m;
	}
	return tmp;
}

bool TPolynom::operator==(const TPolynom& m) const noexcept
{
	size_t sz = monoms.GetCount();
	if (sz != m.monoms.GetCount())
		return false;
	for (size_t i = 0; i < sz; i++)
		if (monoms.Get(i) != m.monoms.Get(i))
			return false;
	return true;
}

bool TPolynom::operator!=(const TPolynom& m) const noexcept
{
	return !(this->operator==(m));
}

std::ostream& operator<<(std::ostream& ostr, const TPolynom& p)
{
	size_t sz = p.monoms.GetCount();
	bool all_zeroes = true;
	if (sz != 0)
	{
		ostr << p.monoms.GetStart();
		for (size_t i = 1; i < sz; i++)
		{
			const TMonom& m = p.monoms.Get(i);
			if (m.GetK() != 0.0)
			{
				if (m.GetK() >= 0.0)
					ostr << '+';
				ostr << m;
				all_zeroes = false;
			}
		}
	}
	if (all_zeroes)
		ostr << 0;
	return ostr;
}