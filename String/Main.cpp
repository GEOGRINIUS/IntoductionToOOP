#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------------------------------------\n"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////			Class declaration (Объявление класса)									//////

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Указатель на строку в динамической памяти
public:
	int get_size()const;
	const char* get_str()const;
	char* get_str();
	//				Costructors:
	explicit String(int size = 80);
	String(const char str[]);
	String(const String& other);
	String(String&& other);
	~String();

	//			  Operators:
	String& operator=(const String& other);
	String& operator=(String&& other);

	char operator[](int i)const;
	char& operator[](int i);

	//				Methods:
	void print()const;
};

int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
//				Costructors:
String::String(int size) :size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {};
	cout << "DefConstructor:\t" << this << endl;
}
String::String(const char str[]) :String(strlen(str) + 1)		/*size(strlen(str) + 1), str(new char[size] {})*/
{
	for (int i = 0; str[i]; i++)this->str[i] = str[i];
	cout << "Constructor:\t" << this << endl;
}
String::String(const String& other) :String(other.str)
{
	cout << "CopyConstructor:\t" << this << endl;
}
String::String(String&& other)
{
	//String&& - r-value reference
	//Shallow copy - Поверхностное копирование:
	this->size = other.size;
	this->str = other.str;
	//Обязательно нужно обнулить копируемый объект:
	other.size = 0;
	other.str = nullptr;	//nullptr - это указатель на '0' (Указатель в никуда).
	//nullptr - это физический '0' (Нулевая ячейка памяти).
//Это предотвращает удаление динамической памяти деструктором.
	cout << "MoveConstructor:" << this << endl;
}
String::~String()
{
	delete[] str;
	cout << "Desctructor:\t" << this << endl;
}

//			  Operators:
String& String::operator=(const String& other)
{
	if (this == &other)return *this;
	delete[] this->str;
	//Deep copy:
	this->size = other.size;
	this->str = new char[size] {};
	for (int i = 0; i < size; i++)this->str[i] = other.str[i];
	cout << "CopyAssigment:\t" << this << endl;
	return *this;
}
String& String::operator=(String&& other)
{
	if (this == &other)return *this;
	delete[] this->str;

	this->size = other.size;
	this->str = other.str;

	other.size = 0;
	other.str = nullptr;

	cout << "MoveAssignment:\t" << endl;
	return *this;
}

char String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}

////////////////			Class declaration end (Конец Объявление класса)									//////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////			Class defenition (Определение класса)									//////

//				Methods:
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	//Сложение строк - конкатенация строк:
	String result(left.get_size() + right.get_size() - 1);
	const double PI = 3.14;
	for (int i = 0; i < left.get_size(); i++)
		result[i] = left[i];
		//result.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

////////////////			Class deferetion end (Конец Определение класса)									//////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define BASE_CHECK
#define OPERATORS_CHECK
//#define CALLING_CONSTRUCTORS

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	String str(12);	//Conversion from 'int' to 'String'
	str.print();

	String str1 = "hello";
	//str1.print();
	cout << str1 << endl;

	String str2 = str1;
	cout << str2 << endl;

	String str3;
	str3 = str2;		//CopyAssigment
	cout << str3 << endl;
#endif //BASE_CHECK

#ifdef OPERATORS_CHECK
	String str1 = "hello";
	String str2 = "world";
	cout << delimiter << endl;
	//String str3 = str1 + str2;	//MoveConstructor
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
#endif //OPERATORS_CHECK

#ifdef CALLING_CONSTRUCTORS
	String str1;		   //Default constructor
	str1.print();

	String str2(5);		   //Single-argument constructor ints (explicit)
	str2.print();

	String str3 = "hello"; //Single-argument consructor 'char'
	str3.print();

	String str4();		   //NOT default constructor
	//str4.print();		   
	//Для того чтобы явно вызвать конструктор по умолчанию, можно использовать {} следующим обрпзом:
	String str5{}; // Явный вызов конструктора по умолчанию.
	str5.print();
	//НО, с фигурными скобками нужно быть ОЧЕНЬ ОСТОРОЖНЫМ
	//Фигурные скобки как правило используются в контейнирах.

	String str6{ 7 };	   //Так же как 'str2' вызывает коструктор с одним параметрам типа 'int'
	str6.print();

	String str7{ "World" };//Так же как и 'str3' вызывает конструктор с одним параметром типа 'const char*'
	String str8{ "World" };//Так же как и 'str3' вызывает конструктор с одним параметром типа 'const char*'

	String str9 = str3;	   //CopyConstructor
	String str10(str9);	   //CopyConstructor
	String str11{ str9 };  //CopyConstructor
	str11.print();

	String str12 = str3 + str7; //MoveConstructor
	str12.print();

	String str13(str3 + str7);  //MoveConstructor
	str13.print();

	String str14{ str3 + str7 };//MoveConstructor
	str14.print();
#endif //CALLING_CONSTRUCTORS

}