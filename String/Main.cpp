#include"String.h"

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