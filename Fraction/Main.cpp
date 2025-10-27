#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"

class Fraction;
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(const Fraction& left, const Fraction& right);
Fraction operator+(const Fraction& left, const Fraction& right);
Fraction operator-(const Fraction& left, const Fraction& right);

class Fraction
{
	int integer;		//целая часть
	int numerator;		//числитель
	int denominator;	//знаменатель
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numenator(int numenator)
	{
		this->numerator = numenator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}

	//				Constructors:
	Fraction()
	{
		integer = 0;
		numerator = 0;
		denominator = 1;
		cout << "DefaultConstructor:" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "SingleArgumentConstructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		set_numenator(numerator);
		set_denominator(denominator);
		cout << "constructor:\t\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		set_integer(integer);
		set_numenator(numerator);
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		//Здесь можно не применять set-методы, а записывать значения напрямую в переменные,
		//потому что все значение прошли фильтрацию данных при создании объекта 'other'.
		cout << "CopyConstructor:" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//			Operators:
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}
	Fraction operator*=(const Fraction& other)
	{
		return *this = *this*other;
	}
	Fraction operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	Fraction operator+=(const Fraction& other)
	{
		return *this = *this + other;
	}
	Fraction operator-=(const Fraction& other)
	{
		return *this = *this - other;
	}

	//			 Increment/Decrement:
	Fraction& operator++()
	{
		this->integer++;
		return *this;
	}
	Fraction& operator++(int)
	{
		//Постфиксные ++/-- всегда принимают один параметр типа 'int',
		//Это позволяет на уровне перегрузки функций отличать их
		//от префиксных ++/--;
		Fraction old = *this;	//old - это локальный объект 
		this->integer++;
		return old;
	}
	Fraction operator--()
	{
		this->integer--;
		return *this;
	}
	Fraction& operator--(int)
	{
		Fraction old = *this;
		this->integer--;
		return old;
	}

	//				Methods:
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		std::swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		int more, less, rest = 0;
		if (numerator > denominator)more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //GCD - Greatest Common Divisor (Наибольший общий делитель)
		numerator /= GCD;
		denominator /= GCD;
		return *this;
	}
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer) cout << "(";
			cout << numerator << "/" << denominator;
			if (integer) cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};
Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();

	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();

	//Fraction result
	//(
	//	left.get_numerator() * right.get_numerator(),
	//	left.get_denominator() * right.get_denominator()
	//);
	//result.to_proper();
	//return result;

	//Fraction result;
	//result.set_numenator(left.get_numerator() * right.get_numerator());
	//result.set_denominator(left.get_denominator() * right.get_denominator());
	//return result;
}
Fraction operator/(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}
Fraction operator+(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}
Fraction operator-(const Fraction& left, const Fraction& right)
{
	return left * right.inverted();
}

//			Comparison operators:
bool operator==(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return left.get_numerator() * right.get_denominator() == right.get_numerator() * left.get_denominator();
}
bool operator!=(const Fraction& left, const Fraction& right)
{
	return !(left == right);
}
bool operator>(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_proper();
	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator();
}
bool operator<(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_proper();
	return
		left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator>=(const Fraction& left, const Fraction& right)
{
	return !(left > right);
	//return left > right || left == right;
}
bool operator<=(const Fraction& left, const Fraction& right)
{
	return !(left < right);
	/*return left < right || left == right;*/
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_numerator())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}

//#define CONSTRUCTORS_CHECK
//#define ARITCHMETICAL_OPERATORS_CHECK
//#define COMPOUND_ASSIGMENTS_CHECK
//#define INCREMENTO_DECREMENTO

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	A.print();

	Fraction B = 5;
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();

	Fraction F;
	F = E;
	F.print();
#endif //CONSTRUCTORS_CHECK

#ifdef ARITCHMETICAL_OPERATORS_CHECK
	Fraction A(2, 3, 4);
	A.print();

	Fraction B(3, 4, 5);
	B.print();

	A.to_improper();
	A.print();
	A.to_proper();
	A.print();
	cout << delimiter << endl;
	Fraction C = A - B;
	cout << delimiter << endl;
	C.print();
#endif //ARITCHMETICAL_OPERATORS_CHECK

#ifdef COMPOUND_ASSIGMENTS_CHECK
	Fraction A(2, 3, 4);
	Fraction B(3, 4, 5);
	A *= B;
	A.print();

	A -= B;
	A.print();
#endif // COMPOUND_ASSIGMENTS_CHECK

#ifdef INCREMENTO_DECREMENTO
	for (double i = .5; i < 10; i++)
	{
		cout << i << tab;
	}
	cout << endl;

	for (Fraction i(1, 2); i.get_integer() < 10; i++)
	{
		i.print();
	}

	Fraction A(1, 2);
	Fraction B = A++;
	B.print();
#endif //INCREMENTO_DECREMENTO

	//cout << (2 == 2) << endl;
	cout << (Fraction(1, 3) <= Fraction(5, 11)) << endl;

	Fraction A(2, 3, 4);
	cout << A << endl;

	//Fraction A;
	//cout << "Введите простую дробь: "; cin >> A;
	//cout << A << endl;

}