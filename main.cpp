#include "Fraction.h"

using namespace std;

void fraction()
{
	Fraction f1 = Fraction{ "1/-3" } + Fraction(.33333) + Fraction{ 3,1,4 };
	std::cout << f1;
	Fraction f2(2, -9);
	std::cout << endl << f2.toString() << "\t" << f2.toDecimal();

	//cout << endl << (Fraction("1/-3") == Fraction(0.333));

	cout << endl << Fraction("-14/-2-1").toString(false);
}

void forReadMe()
{
	//default constructor
	Fraction f1;
	//constructs a fraction with numerator = 0 and denominator = 1

	//constructing with parameters
	Fraction f2(2, 5); // implies 2/5
	Fraction f3(6); // implies 6/1 = 6
	std::cout << "\nf3 = " << f3 << std::endl;

	//constructing with initializer list
	//must contain no more than 3 arguments

	//if one parameter - implies an integer
	Fraction f4{ 4 }; // similar to Fraction f4(4); --> implies 4/1 = 4

	//if two parameters - implies a fraction
	Fraction f5{ 3,9 }; // implies 3/9 = 1/3 (reduction is automatically done with every actions)

	//if three parameters - implies a mixed fraction
	Fraction f6{ 3,1,7 }; // implies 3(1/7) = 22/7

	//constructing fraction from decimal
	//please note that the precision is upto 6 digits following decimal point
	Fraction f7(0.5); // implies 1/2
	Fraction f8(0.34); // implies 34/100 = 17/50
	Fraction f_8(3.14785); // implies 3(2957/20000) = 62957/20000

	//if the digits following the decimal is same,
	//this will be considered as recurring digits
	Fraction f9(0.333); // implies 1/3
	Fraction f10(0.77777); // implies 7/9

	//constructing fraction from text
	//as of date, no decimals allowed
	Fraction f11{ "-14/-21" }; // implies 2/3
	//Fraction f_11{"5/--25"}; //error - will throw exception
	//Fraction f_11_a{"-14/-2-1"}; //error - unknown behaviour

	//copy constructing from another Fraction
	Fraction f12{ f5 + f8 };
	cout << f12;
	Fraction f13{ 0.293 + f6 };
	cout << endl << f13;

	Fraction f14 = Fraction{ "1/-3" } + Fraction(.33333) + Fraction{ 3,1,4 };
	cout << endl << f14;

	Fraction f15 = 3.19 - f14;
	std::cout << std::endl << f15;

	std::cout << "\nf3 = " << f3;
	Fraction f16 = f3 - (Fraction::BigNum)6;
	std::cout << std::endl << "f16 = " << f16;

	std::cout << std::endl << (f9 / f11);
	std::cout << std::endl << (f2 * f10);

	std::cout << std::endl << (f8 -= f5);
	std::cout << std::endl << (f12 += f13);

	std::cout << std::endl << (f10 > f7);
	std::cout << std::endl << (f2 == 0.4);
	std::cout << std::endl << "Fraction(1,3) == 0.3333 : " << (Fraction(1, 3) == 0.3333);

	std::cout << std::endl << f6.isProper();
	std::cout << std::endl << f6.toDecimal();

	auto frac{ f6.toFractionPair() };
	std::cout << std::endl << frac.first << "\t" << frac.second;

	std::cout << std::endl << f6.toString();
	std::cout << std::endl << f6.toString(false);

	std::cout << std::endl << (f2 / 0.34);
}

int main()
{
	//fraction();
	forReadMe();
}