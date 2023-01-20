
# A Fraction class using C++

This is my first attempt at writing a utility class, which is implemented using modern C++, and the class also supports all kinds of arithmatical operations with a fraction.

Since mathematics is not my subject of speciality, I am quite sure that the algorithms I have used here can modt likely be optimized with far better ones (suggestions are welcome in this regard).

The main objective of this micro-project cum exercise is to practice developing better class designs (class design and mathematical designs should be treated as completely different aspect) with respect to this micro-project.

This is the first version of the Fraction class.


## License

[MIT](https://choosealicense.com/licenses/mit/)

Copyright (c) [2023] [Sougata]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


## Usage/Examples

Constructing a fraction:

```
//default constructor
Fraction f1;
//constructs a fraction with numerator = 0 and denominator = 1

//constructing with parameters
Fraction f2(2,5); // implies 2/5
Fraction f3(6); // implies 6/1 = 6

//constructing with initializer list
//must contain no more than 3 arguments

//if one parameter - implies an integer
Fraction f4{4}; // similar to Fraction f4(4); --> implies 4/1 = 4

//if two parameters - implies a fraction
Fraction f5{3,9}; // implies 3/9 = 1/3 (reduction is automatically done with every actions)

//if three parameters - implies a mixed fraction
Fraction f6{3,1,7}; // implies 3(1/7) = 22/7

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
Fraction f11{"-14/-21"}; // implies 2/3
//Fraction f_11{"5/--25"}; //error - will throw exception
//Fraction f_11_a{"-14/-2-1"}; //error - unknown behaviour

//copy constructing from another Fraction
Fraction f12{f5 + f8}; // 101/150
Fraction f13{0.293 + f6}; 
std::cout << std::endl << f13; // 24051/7000 = 3(3051/7000)
```
Fraction arithmatic:

```
//fraction arithmatic
Fraction f14 = Fraction{ "1/-3" } + Fraction(.33333) + Fraction{ 3,1,4 };
std::cout << std::endl << f14; // 3(1/4)

Fraction f15 = 3.19 - f14;
std::cout << std::endl << f15; // -3/50

std::cout << std::endl << (f9 / f11); // 1/2
std::cout << std::endl << (f2 * f10); // 14/45

std::cout << std::endl << (f8 -= f5); // 1/150
std::cout << std::endl << (f12 += f13); // 4(2293/21000)
```

Fraction Comparison:

```
//comparative operations
std::cout << std::endl << (f10 > f7); // 1
std::cout << std::endl << (f2 == 0.4); // 1
```

Public functions:

1. bool isProper() const noexcept : true - if the fraction is a proper fraction (numerator < denominator)
```
std::cout << std::endl << f6.isProper(); // 0
```
2. double toDecimal() const noexcept
```
std::cout << std::endl << f6.toDecimal(); // 3.14286
```
3. FractionPair toFractionPair() const noexcept
returns the numerator and denominator in pair.
```
auto frac{ f6.toFractionPair() };
std::cout << std::endl << frac.first << "\t" << frac.second;
// outputs:
// 22      7
```
4. std::string toString(bool mixedOrNot = true) const noexcept
returns a string in the form of mixed fraction notation or proper fraction notation (if argument is false)
```
std::cout << std::endl << f6.toString(); // 3(1/7)
std::cout << std::endl << f6.toString(false); // 22/7
```