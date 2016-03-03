#pragma once
#include<cstdlib>
#include <cstdio>
#include <iostream>
#include <cassert>

// helper function to determine GCD

int gcd(int num, int den)
{
	int remainder;
	while (den != 0)
	{
		remainder = num % den;
		num = den;
		den = remainder;
	}
	return num;
}


class Number {
public:
	Number();
	Number(int i);
	Number(int x, int y);
	
	virtual Number * clone();
	Number(const Number &copy) : letter(copy.letter->clone()) {}; 
	
	virtual Number & operator= (const Number &rhs); 

	virtual ~Number(){ // destructor
		delete letter;
		letter = 0;
	};
	
	virtual void display() const{
		letter->display();
	};

	virtual Number * operator+(const Number &otherNumber){
		letter = letter->operator+(otherNumber);
		return this;
	};

	virtual bool operator==(const Number &otherNumber){
		return letter->operator==(otherNumber);
	};

	Number * letter;
};

Number * Number::clone(){
	Number * r = new Number();
	if (letter){
		r->letter = letter->clone();
	}
	else{
		r->letter = 0;
	};
	return r;
};

Number & Number::operator= (const Number &rhs){
	if (this != &rhs){
		delete letter;
		letter = 0;
		letter = rhs.letter->clone();
	};
	return *this;
}; 


class Integer;
class Fraction;

class Fraction : public Number {
public:
	Fraction(int x, int y);
	Number * operator+(const Fraction & rhs);
	Number * operator+(const Integer & rhs);
	Number * operator+(const Number & rhs);

	bool operator==(const Fraction & rhs);
	bool operator==(const Integer & rhs);
	bool operator==(const Number & rhs);
	
	void display() const{
		std::cout << "(" << numerator << "/" << denominator << ")" << std::endl;
	};

//private:
	int numerator;
	int denominator;
};


class Integer : public Number {
public:
	
	Integer(int i) : the_integer(i) {
		std::cout << "Integer:: creating Integer" << std::endl;
	};

	Integer * clone(){
		Integer * r = new Integer(the_integer);
		return r;
	};

	void display() const{
		std::cout << the_integer << std::endl;
	};

	Number * operator+(const Number & rhs){
		std::cout << "Integer:: add some number." << std::endl;
		const Number * the_letter = 0;
		if (rhs.letter){ // peel off redundant layer of abstraction
			the_letter = rhs.letter;
		}
		else{
			the_letter = &rhs;
		};
		
		const Integer * int_rhs = dynamic_cast<const Integer *>(the_letter);
		if (int_rhs){
			the_integer += int_rhs->the_integer;
			return this;
		};

		Fraction *r = new Fraction(the_integer, 1);
		r->operator+(rhs);

		return r;
	};

	bool operator==(const Number & rhs){
		std::cout << "Integer:: is equal to some number." << std::endl;
		const Number * the_letter = 0;
		if (rhs.letter){ 
			the_letter = rhs.letter;
		}
		else{
			the_letter = &rhs;
		};

		const Integer * int_rhs = dynamic_cast<const Integer *>(the_letter);
		if (int_rhs){
			return (the_integer == int_rhs->the_integer);
		};

		const Fraction * fraction_rhs = dynamic_cast<const Fraction *>(the_letter);
		if (fraction_rhs){
			return ((float)the_integer == ((float)fraction_rhs->numerator / (float)fraction_rhs->denominator));
		};

		return false;

	};


	int getInteger(){
		return the_integer;
	}

	//private:
	int the_integer;
};


Fraction::Fraction(int x, int y) :
numerator(x), denominator(y) {
	std::cout << "Fraction:: creating Fraction." << std::endl;
};

Number * Fraction::operator+(const Fraction & rhs){
	std::cout << "Fraction:: add to Fraction." << std::endl;

	int n = numerator*rhs.denominator + rhs.numerator*denominator;
	int d = denominator*rhs.denominator;
	return new Fraction(n / gcd(n, d), d / gcd(n, d));

}

Number *Fraction::operator+(const Number & rhs){
	std::cout << "Fraction:: add some Number." << std::endl;
	const Number * the_letter = 0;
	if (rhs.letter){ 
		the_letter = rhs.letter;
	}
	else{
		the_letter = &rhs;
	};

	const Fraction * fraction_rhs = dynamic_cast<const Fraction *>(the_letter);
	if (fraction_rhs){
		int n = numerator*fraction_rhs->denominator + fraction_rhs->numerator*denominator;
		int d = denominator*fraction_rhs->denominator;
		return new Fraction(n / gcd(n, d), d / gcd(n, d));
	};

	const Integer * integer_rhs = dynamic_cast<const Integer *>(the_letter);
	if (integer_rhs){
		int n = numerator * 1 + integer_rhs->the_integer*denominator;
		int d = denominator;
		return new Fraction(n / gcd(n, d), d / gcd(n, d));;
	};
	
	// unexpected outcome
	assert(0);
}

bool Fraction::operator==(const Fraction & rhs){
	std::cout << "Fraction:: compare to Fraction." << std::endl;

	float lhsValue = (float)numerator / (float)denominator; 
	float rhsValue = (float)rhs.numerator / (float)rhs.denominator;
	
	return lhsValue==rhsValue;
}

bool Fraction::operator==(const Integer & rhs){
	std::cout << "Fraction:: compare to Integer." << std::endl;

	return ((numerator / denominator) == (rhs.the_integer));
}


bool Fraction::operator==(const Number & rhs){
	std::cout << "Fraction:: add some Number." << std::endl;
	const Number * the_letter = 0;
	if (rhs.letter){
		the_letter = rhs.letter;
	}
	else{
		the_letter = &rhs;
	};

	const Fraction * fraction_rhs = dynamic_cast<const Fraction *>(the_letter);
	if (fraction_rhs){
		float lhsValue = (float)numerator / (float)denominator;
		float rhsValue = (float)fraction_rhs->numerator / (float)fraction_rhs->denominator;

		return lhsValue == rhsValue;
	};

	const Integer * integer_rhs = dynamic_cast<const Integer *>(the_letter);
	if (integer_rhs){
		return ((numerator / denominator) == (integer_rhs->the_integer));
	};

	// unexpected outcome
	assert(0);
}


Number::Number() : letter(0) {
	
};
Number::Number(int i) : letter(0) {
	
	letter = new Integer(i);
};
Number::Number(int x, int y) : letter(0) {
	
	letter = new Fraction(x, y);
};


void test_Number(){
	std::cout << "testing ..." << std::endl;
	Number a(2);
	Integer d(2);
	Fraction b(4,5);
	Number c(3,5);

	std::cout << (a == d) <<std::endl;

	Number *e = b + c;
	e->display();
}