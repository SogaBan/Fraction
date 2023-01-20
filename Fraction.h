#pragma once

#include <iostream>

class Fraction
{
public:
	using BigNum = long long int;
	using FractionPair = std::pair<BigNum, BigNum>;

private:
	//member variables
	BigNum m_numerator, m_denominator;

private:
	//member functions
	BigNum gcd(BigNum _n, BigNum _d) const noexcept;
	void reduce();
	void adjustSigns();

	//few utility functions required for conversion
	//from text to fraction
	void textToFraction(const std::string& inp);
	bool isInputValid(const std::string& inp) const noexcept;
	bool checkPresenceOfSlash(const std::string& inp) const;
	bool checkPresenceOfSign(const std::string& inp) const;
	std::string extractNumerator(const std::string& inp) const;
	std::string extractDenominator(const std::string& inp) const;


	//a bunch of utility functons required for conversion
	//from double value to fraction
	FractionPair decToFrac(const double& _d) const noexcept;
	std::string doubleToString(const double& _d) const noexcept;
	BigNum stringToBigNum(const std::string& st) const noexcept;
	void removeTrailingZeroes(std::string& val) const noexcept;
	bool isRepeating(const std::string& st) const noexcept;

public:
	//constructors
	explicit Fraction() : m_numerator{ 0 }, m_denominator{ 1 } {}
	explicit Fraction(BigNum _num, BigNum _den);
	Fraction(const std::string& input);
	explicit Fraction(const double& _dec);
	Fraction(const Fraction& _frac);
	Fraction(Fraction&& _frac) noexcept;
	Fraction(const std::initializer_list<BigNum>& params);
	~Fraction() = default;

	//overloaded operators
	Fraction& operator=(const Fraction& rhs);
	Fraction& operator=(Fraction&& rhs) noexcept;
	Fraction& operator=(const double& _d);

	bool operator==(const Fraction& rhs);
	bool operator==(const double& rhs);
	bool operator!=(const Fraction& rhs);
	bool operator!=(const double& rhs);

	bool operator>(const Fraction& rhs);
	bool operator>(const double& rhs);

	bool operator<(const Fraction& rhs);
	bool operator<(const double& rhs);

	bool operator>=(const Fraction& rhs);
	bool operator>=(const double& rhs);

	bool operator<=(const Fraction& rhs);
	bool operator<=(const double& rhs);

	Fraction& operator+=(const Fraction& rhs);
	Fraction& operator+=(const double& _d);
	Fraction& operator+=(const int& _bn);

	Fraction& operator-=(const Fraction& rhs);
	Fraction& operator-=(const double& _d);
	Fraction& operator-=(const int& _bn);

	Fraction& operator*=(const Fraction& rhs);
	Fraction& operator*=(const double& _d);
	Fraction& operator*=(const int& _bn);

	Fraction& operator/=(const Fraction& rhs);
	Fraction& operator/=(const double& _d);
	Fraction& operator/=(const int& _bn);

	//friend functions
	friend std::ostream& operator<<(std::ostream& os, const Fraction& frac);

	//friend functions for addition (+)
	friend Fraction operator+(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator+(const Fraction& lhs, const BigNum& rhs);
	friend Fraction operator+(const BigNum& lhs, const Fraction& rhs);
	friend Fraction operator+(const Fraction& lhs, const double& rhs);
	friend Fraction operator+(const double& lhs, const Fraction& rhs);

	//friend functions for substraction (-)
	friend Fraction operator-(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator-(const Fraction& lhs, const BigNum& rhs);
	friend Fraction operator-(const BigNum& lhs, const Fraction& rhs);
	friend Fraction operator-(const Fraction& lhs, const double& rhs);
	friend Fraction operator-(const double& lhs, const Fraction& rhs);

	//friend functions for multiplication (*)
	friend Fraction operator*(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator*(const Fraction& lhs, const BigNum& rhs);
	friend Fraction operator*(const BigNum& lhs, const Fraction& rhs);
	friend Fraction operator*(const Fraction& lhs, const double& rhs);
	friend Fraction operator*(const double& lhs, const Fraction& rhs);

	//friend functions for division (/)
	friend Fraction operator/(const Fraction& lhs, const Fraction& rhs);
	friend Fraction operator/(const Fraction& lhs, const BigNum& rhs);
	friend Fraction operator/(const BigNum& lhs, const Fraction& rhs);
	friend Fraction operator/(const Fraction& lhs, const double& rhs);
	friend Fraction operator/(const double& lhs, const Fraction& rhs);

public:
	//member functions
	bool isProper() const noexcept;
	double toDecimal() const noexcept;
	FractionPair toFractionPair() const noexcept;
	std::string toString(bool mixedNotation = false) const noexcept;
};
