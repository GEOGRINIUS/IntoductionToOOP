#include<iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"

//Тут был кот Барсик

using std::cin;
using std::cout;
using std::endl;

class Point
{
	double x;
	double y;
public:
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}
	//		Constructors:
	/*Point()
	{
		x = y = 0; //Записываем в переменные члены класса значения по умолчанию.
		cout << "DefaultConstructor:\t" << this << endl;
	}*/
	//Point(double x)
	//{
	//	this->x = x;
	//	this->y = 0;
	//	cout << "SingleArgConstructor:\t" << this << endl;
	//}
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t\t" << this << endl;
	}
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstrcutor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t\t" << this << endl;
	}
	//		   Operators:
	const Point& operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "Left:\t" << this << endl;
		cout << "Right:\t" << &other << endl;
		cout << "CopyAssigment:\t\t" << this << endl;
		return *this; 
	}
	//			 Methods:
	double distance(const Point& other)const
	{
		//other.x *= 100;
		//other.y *= 100;
		//this->x *= 100;
		//this->y *= 100;
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance * x_distance + y_distance * y_distance); //Square Root
		return distance;
	}
	void print()const
	{
		cout << "X = " << x << ",\tY = " << y << endl;
	}
};

double distance(const Point& A, const Point& B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	double distance = sqrt(x_distance * x_distance + y_distance * y_distance);
	return distance;
}

Point operator+(const Point& left, const Point& right)
{
	Point result;
	result.set_x(left.get_x() + right.get_x());
	result.set_y(left.get_y() + right.get_y());
	return result;
}

//#define STRUCT_POINT
//#define DISTANCE_CHECK
//#define FOR_COUNTER_LIFETIME
//#define CONSTRUCTORS_CHECK
//#define ASSIGNMENT_CHECK
#define OPERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef STRUCT_POINT
	cout << "Hellop OOP" << endl;
	int a;
	Point A;
	A.x = 2;
	A.y = 3;
	cout << A.x << "\t" << A.y << endl;

	Point* pA = &A;
	cout << pA->x << "\t" << pA->y << endl;
#endif // STRUCT_POINT

#ifdef DISTANCE_CHECK
	Point A;
	A.set_x(2);
	A.set_y(3);
	cout << A.get_x() << "\t" << A.get_y() << endl;

	Point B;
	B.set_x(7);
	B.set_y(8);
	cout << B.get_x() << "\t" << B.get_y() << endl;

	cout << delimiter << endl;
	cout << "Расстояние от точки 'A' до точки 'B': " << A.distance(B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние от точки 'B' до точки 'A': " << B.distance(A) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'A' и 'B': " << distance(A, B) << endl;
	cout << delimiter << endl;
	cout << "Расстояние между точками 'B' и 'A': " << distance(B, A) << endl;
	cout << delimiter << endl;
#endif //DISTANCE_CHECK

#ifdef FOR_COUNTER_LIFETIME
	for (int i = 0; i < 10; i++)
	{
		cout << i << "\t";
	}
	//Если бы перменная 'i' была объектом, то по завершений всех интераций для её был бы вызван destructor,
	//Поскльку время жизни переменной 'i' завершается по завершении всех интераций цикла 'for'.
	cout << endl;
#endif //FOR_COUNTER_LIFETIME

#ifdef CONSTRUCTORS_CHECK
	Point A;		//Default constructor
	A.print();

	Point B = 5;   //Single-argument constructor (Конструктор с одним параметром)
	B.print();

	Point C(2, 3);//Конструктор с параметрами
	C.print();

	Point D = C;  //CopyConstructor
	D.print();

	Point E;
	E = D;		  //CopyAssignment
	E.print();

#endif // CONSTRUCTORS_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << tab << b << tab << c << endl;

	Point A, B, C;
	cout << delimiter << endl;
	// A,B,C = Point(2, 3);
	A = B = C = Point(2, 3);
	//Point(2, 3); - это явный вызов конструктора. 
	//Этот конструктор создает временный безымянный объект
	//Который существует только в пределах одного выражения
	//и удаляется из памяти по завершении выражения
	//Point(2, 3).print();
	cout << delimiter << endl;
	A.print();
	B.print();
	C.print();
	cout << sizeof(Point) << endl;
#endif // ASSIGNMENT_CHECK

#ifdef OPERATORS_CHECK

	int a = 2;
	int b = 3;
	int c = a + b;

	Point A(2, 3);
	Point B(7, 8);
	Point C = A + B;
	C.print();

#endif //OPERATORS_CHECK



}