#pragma once
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
