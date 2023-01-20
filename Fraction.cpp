#include "Fraction.h"
#include <sstream>
#include <string>
#include <vector>
#include <utility>

Fraction::BigNum Fraction::gcd(BigNum _n, BigNum _d) const noexcept
{
	if (_d == 0)
		return _n;

	return gcd(_d, _n % _d);
}

void Fraction::reduce()
{
	auto _gcd{ abs(gcd(m_numerator, m_denominator)) };
	m_numerator /= _gcd;
	m_denominator /= _gcd;
	adjustSigns();
}

std::string Fraction::doubleToString(const double& _d) const noexcept
{
	std::ostringstream oss;
	oss << _d;
	return oss.str();
}

Fraction::BigNum Fraction::stringToBigNum(const std::string& st) const noexcept
{
	std::istringstream iss{ st };
	BigNum bn{};
	iss >> bn;
	return static_cast<BigNum>(bn);
}

void Fraction::removeTrailingZeroes(std::string& val) const noexcept
{
	val = val.substr(0, val.find_last_not_of('0') + 1);
}

bool Fraction::isRepeating(const std::string& st) const noexcept
{
	return (st.find_first_not_of(st.at(0)) == std::string::npos);
}

Fraction::FractionPair Fraction::decToFrac(const double& _d) const noexcept
{
	auto dbInput{ doubleToString(_d) };
	if (dbInput.find('.') == std::string::npos)
	{
		auto retVal{ std::make_pair(stringToBigNum(dbInput), static_cast<BigNum>(1)) };
		return retVal;
	}
	else
	{
		auto wholePart{ dbInput.substr(0, dbInput.find('.')) };
		auto fracPart{ dbInput.substr(dbInput.find('.') + 1) };

		BigNum _t_den{};
		if (isRepeating(fracPart) && fracPart.length() > 3)
		{
			_t_den = stringToBigNum(std::string(fracPart.length(), '9'));
		}
		else
		{
			_t_den = static_cast<BigNum>(pow(10, fracPart.length()));
		}

		auto _w_{ stringToBigNum(wholePart) };
		auto _n_{ stringToBigNum(fracPart) };
		_n_ = (_t_den * _w_ + _n_);
		auto retVal{ std::make_pair(_n_, _t_den) };
		return retVal;
	}
}

void Fraction::adjustSigns()
{
	if (m_denominator < 0)
	{
		if (m_numerator != 0)
		{
			m_denominator = -(m_denominator);
			m_numerator = -(m_numerator);
		}
	}
}

Fraction::Fraction(BigNum _num, BigNum _den)
	: m_numerator{ _num },
	m_denominator{ _den != 0 ? _den : throw std::invalid_argument("Denominator cannot be zero.")}
{
	reduce();
}

Fraction::Fraction(const std::string& input) : m_numerator{ 0 }, m_denominator{ 1 }
{
	textToFraction(input);
}

Fraction::Fraction(const std::initializer_list<BigNum>& params)
{
	/////////////////////////////////////////////////////////////////////////
	//the first three parameters of the initializer list will be considered
	//if one parameter - implies an integer
	//if two parameters - implies a fraction
	//if three parameters - imples a mixed fraction
	////////////////////////////////////////////////////////////////////////

	if (params.size() > 3)
		throw std::invalid_argument("Mixed fraction has three components only.");

	std::vector<BigNum> entries{ params };
	if (entries.size() == 1)
	{
		m_numerator = static_cast<BigNum>(entries.at(0));
		m_denominator = static_cast<BigNum>(1);
	}
	else if (entries.size() == 2)
	{
		if (entries.at(1) != 0)
		{
			m_numerator = static_cast<BigNum>(entries.at(0));
			m_denominator = static_cast<BigNum>(entries.at(1));
			reduce();
		}
		else
			throw std::invalid_argument("Denominator cannot be zero.");
	}
	else
	{
		if(entries.at(2) != 0)
		{
			m_numerator = static_cast<BigNum>(entries.at(0))
				* static_cast<BigNum>(entries.at(2))
				+ static_cast<BigNum>(entries.at(1));
			m_denominator = static_cast<BigNum>(entries.at(2));
			reduce();
		}
		else
			throw std::invalid_argument("Denominator cannot be zero.");
	}
}

Fraction::Fraction(const double& _dec) : m_numerator{ 0 }, m_denominator{ 1 }
{
	if (_dec != 0)
	{
		auto derived{ decToFrac(_dec) };
		m_numerator = derived.first;
		m_denominator = derived.second;
		reduce();
	}
}

Fraction::Fraction(const Fraction& _frac)
	: m_numerator{ _frac.m_numerator }, m_denominator{ _frac.m_denominator }
{
}

Fraction::Fraction(Fraction&& _frac) noexcept
	: m_numerator{ std::move(_frac.m_numerator) },
	m_denominator{ std::move(_frac.m_denominator) }
{
	reduce();
}

Fraction& Fraction::operator=(const Fraction& rhs)
{
	m_numerator = rhs.m_numerator;
	m_denominator = rhs.m_denominator;
	
	return *this;
}

Fraction& Fraction::operator=(Fraction&& rhs) noexcept
{
	m_numerator = std::move(rhs.m_numerator);
	m_denominator = std::move(rhs.m_denominator);
	reduce();

	return *this;
}

Fraction& Fraction::operator=(const double& _d)
{
	auto derived{ decToFrac(_d) };
	m_numerator = derived.first;
	m_denominator = derived.second;
	return *this;
}

bool Fraction::operator==(const Fraction& rhs)
{
	auto determinate{ (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator) };
	return (determinate == 0);
}

bool Fraction::operator==(const double& rhs)
{
	auto derived{ decToFrac(rhs) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	auto determinate{ (m_numerator * frac_den) - (frac_num * m_denominator) };
	return (determinate == 0);
};

bool Fraction::operator!=(const Fraction& rhs)
{
	auto determinate{ (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator) };
	return (determinate != 0);
}

bool Fraction::operator!=(const double& rhs)
{
	auto derived{ decToFrac(rhs) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	auto determinate{ (m_numerator * frac_den) - (frac_num * m_denominator) };
	return (determinate != 0);
}

bool Fraction::operator>(const Fraction& rhs)
{
	auto determinate{ (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator) };
	return (determinate > 0);
}

bool Fraction::operator>(const double& rhs)
{
	auto derived{ decToFrac(rhs) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	auto determinate{ (m_numerator * frac_den) - (frac_num * m_denominator) };
	return (determinate > 0);
}

bool Fraction::operator<(const Fraction& rhs)
{
	auto determinate{ (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator) };
	return (determinate < 0);
}

bool Fraction::operator<(const double& rhs)
{
	auto derived{ decToFrac(rhs) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	auto determinate{ (m_numerator * frac_den) - (frac_num * m_denominator) };
	return (determinate < 0);
}

bool Fraction::operator>=(const Fraction& rhs)
{
	auto determinate{ (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator) };
	return (determinate >= 0);
}

bool Fraction::operator>=(const double& rhs)
{
	auto derived{ decToFrac(rhs) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	auto determinate{ (m_numerator * frac_den) - (frac_num * m_denominator) };
	return (determinate >= 0);
}

bool Fraction::operator<=(const Fraction& rhs)
{
	auto determinate{ (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator) };
	return (determinate <= 0);
}

bool Fraction::operator<=(const double& rhs)
{
	auto derived{ decToFrac(rhs) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	auto determinate{ (m_numerator * frac_den) - (frac_num * m_denominator) };
	return (determinate <= 0);
}

Fraction& Fraction::operator+=(const Fraction& rhs)
{
	m_numerator = (m_numerator * rhs.m_denominator) + (rhs.m_numerator * m_denominator);
	m_denominator *= rhs.m_denominator;
	reduce();
	return *this;
}

Fraction& Fraction::operator+=(const double& _d)
{
	auto derived{ decToFrac(_d) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	m_numerator = (m_numerator * frac_den) + (frac_num * m_denominator);
	m_denominator *= frac_den;
	reduce();
	return *this;
}

Fraction& Fraction::operator+=(const int& _bn)
{
	m_numerator += (m_denominator * _bn);
	reduce();
	return *this;
}

Fraction& Fraction::operator-=(const Fraction& rhs)
{
	m_numerator = (m_numerator * rhs.m_denominator) - (rhs.m_numerator * m_denominator);
	m_denominator *= rhs.m_denominator;
	reduce();
	return *this;
}

Fraction& Fraction::operator-=(const double& _d)
{
	auto derived{ decToFrac(_d) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	m_numerator = (m_numerator * frac_den) - (frac_num * m_denominator);
	m_denominator *= frac_den;
	reduce();
	return *this;
}

Fraction& Fraction::operator-=(const int& _bn)
{
	m_numerator -= (m_denominator * _bn);
	reduce();
	return *this;
}

Fraction& Fraction::operator*=(const Fraction& rhs)
{
	m_numerator *= rhs.m_numerator;
	m_denominator *= rhs.m_denominator;
	reduce();
	return *this;
}

Fraction& Fraction::operator*=(const double& _d)
{
	auto derived{ decToFrac(_d) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	m_numerator *= frac_num;
	m_denominator *= frac_den;
	reduce();
	return *this;
}

Fraction& Fraction::operator*=(const int& _bn)
{
	m_numerator *= _bn;
	reduce();
	return *this;
}

Fraction& Fraction::operator/=(const Fraction& rhs)
{
	m_numerator *= rhs.m_denominator;
	m_denominator *= rhs.m_numerator;

	if (m_denominator == 0)
		throw std::invalid_argument("Resulting denominator is zero. Fraction is undefined");

	reduce();
	return *this;
}

Fraction& Fraction::operator/=(const double& _d)
{
	auto derived{ decToFrac(_d) };
	auto frac_num{ derived.first };
	auto frac_den{ derived.second };

	m_numerator *= frac_den;
	m_denominator *= frac_num;
	reduce();
	return *this;
}

Fraction& Fraction::operator/=(const int& _bn)
{
	m_denominator *= _bn;
	reduce();
	return *this;
}

bool Fraction::isProper() const noexcept
{
	return (abs(m_numerator) < abs(m_denominator));
}

double Fraction::toDecimal() const noexcept
{
	double result{ static_cast<double>(m_numerator) / static_cast<double>(m_denominator) };
	return result;
}

Fraction::FractionPair Fraction::toFractionPair() const noexcept
{
	FractionPair _pair_{ std::make_pair(m_numerator, m_denominator) };
	return _pair_;
}

std::string Fraction::toString(bool mixedNotation) const noexcept
{
	std::ostringstream oss;
	if (!mixedNotation)
	{
		oss << m_numerator
			<< '/'
			<< m_denominator;
		return oss.str();
	}
	else
	{
		if (m_numerator > m_denominator)
		{
			oss << (m_numerator / m_denominator)
				<< "("
				<< (m_numerator % m_denominator)
				<< "/"
				<< m_denominator
				<< ")";
			return oss.str();
		}
		else
		{
			oss << m_numerator
				<< '/'
				<< m_denominator;
			return oss.str();
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Fraction& frac)
{
	switch (frac.m_denominator)
	{
	case 0:
		os << "undefined\n";
		break;
	case 1:
		os << frac.m_numerator << "\n";
		break;
	default:
		os << frac.toString(true);
		break;
	}
	return os;
}

//friend functions for addition (+)

Fraction operator+(const Fraction& lhs, const Fraction& rhs)
{
	Fraction::BigNum frNum{ (lhs.m_numerator * rhs.m_denominator) + (rhs.m_numerator * lhs.m_denominator) };
	Fraction::BigNum frDen{ lhs.m_denominator * rhs.m_denominator };
	return Fraction{ frNum,frDen };
}

Fraction operator+(const Fraction& lhs, const Fraction::BigNum& rhs)
{
	return (lhs + Fraction(rhs, 1));
}

Fraction operator+(const Fraction::BigNum& lhs, const Fraction& rhs)
{
	return (Fraction(lhs, 1) + rhs);
}

Fraction operator+(const Fraction& lhs, const double& rhs)
{
	return (lhs + Fraction(rhs));
}

Fraction operator+(const double& lhs, const Fraction& rhs)
{
	return (Fraction(lhs) + rhs);
}

//friend functions for substraction (-)

Fraction operator-(const Fraction& lhs, const Fraction& rhs)
{
	auto frNum{ (lhs.m_numerator * rhs.m_denominator) - (rhs.m_numerator * lhs.m_denominator) };
	auto frDen{ lhs.m_denominator * rhs.m_denominator };
	return Fraction{ frNum,frDen };
}

Fraction operator-(const Fraction& lhs, const Fraction::BigNum& rhs)
{
	return (lhs - Fraction(rhs, 1));
}

Fraction operator-(const Fraction::BigNum& lhs, const Fraction& rhs)
{
	return (Fraction(lhs, 1) - rhs);
}

Fraction operator-(const Fraction& lhs, const double& rhs)
{
	return (lhs - Fraction(rhs));
}

Fraction operator-(const double& lhs, const Fraction& rhs)
{
	return (Fraction(lhs) - rhs);
}

//friend functions for multiplication (*)

Fraction operator*(const Fraction& lhs, const Fraction& rhs)
{
	auto frNum{ lhs.m_numerator * rhs.m_numerator };
	auto frDen{ lhs.m_denominator * rhs.m_denominator };
	return Fraction{ frNum,frDen };
}

Fraction operator*(const Fraction& lhs, const Fraction::BigNum& rhs)
{
	return Fraction{ lhs.m_numerator * rhs, lhs.m_denominator };
}

Fraction operator*(const Fraction::BigNum& lhs, const Fraction& rhs)
{
	return Fraction{ lhs * rhs.m_numerator, rhs.m_denominator };
}

Fraction operator*(const Fraction& lhs, const double& rhs)
{
	return (lhs * Fraction(rhs));
}

Fraction operator*(const double& lhs, const Fraction& rhs)
{
	return (Fraction(lhs) * rhs);
}

//friend functions for division (/)

Fraction operator/(const Fraction& lhs, const Fraction& rhs)
{
	auto frNum{ lhs.m_numerator * rhs.m_denominator };
	auto frDen{ lhs.m_denominator * rhs.m_numerator };
	return Fraction{ frNum,frDen };
}

Fraction operator/(const Fraction& lhs, const Fraction::BigNum& rhs)
{
	auto frNum{ lhs.m_numerator };
	auto frDen{ lhs.m_denominator * rhs };
	return Fraction{ frNum,frDen };
}

Fraction operator/(const Fraction::BigNum& lhs, const Fraction& rhs)
{
	auto frNum{ lhs * rhs.m_denominator };
	auto frDen{ rhs.m_numerator };
	return Fraction{ frNum,frDen };
}

Fraction operator/(const Fraction& lhs, const double& rhs)
{
	return (lhs / Fraction(rhs));
}

Fraction operator/(const double& lhs, const Fraction& rhs)
{
	return (Fraction(lhs) / rhs);
}

void Fraction::textToFraction(const std::string& inp)
{
	if (isInputValid(inp))
	{
		if (checkPresenceOfSign(inp) && checkPresenceOfSlash(inp))
		{
			auto numTxt{ extractNumerator(inp) };
			auto denTxt{ extractDenominator(inp) };

			m_numerator = stringToBigNum(numTxt);
			m_denominator = stringToBigNum(denTxt);
			reduce();
		}
	}
}

bool Fraction::isInputValid(const std::string& inp) const noexcept
{
	return (inp.find_first_not_of("-/0123456789") == std::string::npos);
}

bool Fraction::checkPresenceOfSlash(const std::string& inp) const
{
	if (inp.find_first_of('/') == std::string::npos)
		throw std::invalid_argument("Constructor contains no denominator.");
	else
	{
		auto firstPos{ inp.find_first_of('/') };
		auto remText{ inp.substr(firstPos + 1) };
		if (remText.find_first_of('/') == std::string::npos)
			return true;
		else
			return false;
	}
}

bool Fraction::checkPresenceOfSign(const std::string& inp) const
{
	std::vector<size_t> positionHolder;
	for (int i = 0; i < inp.length(); ++i)
	{
		if (inp.at(i) == '-')
			positionHolder.push_back(i);
	}
	if (positionHolder.size() > 2)
		return false;
	else if (positionHolder.size() == 0 || positionHolder.size() == 1)
		return true;
	else
	{
		for (auto i = 0; i < positionHolder.size() - 1; ++i)
		{
			if (positionHolder.at(i) == positionHolder.at(i + 1))
				throw std::invalid_argument("Sign error in constructor");
		}
	}
}

std::string Fraction::extractNumerator(const std::string& inp) const
{
	auto numeratorText{ inp.substr(0, inp.find('/')) };
	//check validity
	if (numeratorText.find_first_not_of("-1234567890") == std::string::npos)
		return numeratorText;
	else
		throw std::invalid_argument("error in constructor argument.");
}

std::string Fraction::extractDenominator(const std::string& inp) const
{
	auto denominatorText{ inp.substr(inp.find('/') + 1) };
	//check validity
	if (denominatorText.find_first_not_of("-1234567890") == std::string::npos)
		return denominatorText;
	else
		throw std::invalid_argument("error in constructor argument.");
}
