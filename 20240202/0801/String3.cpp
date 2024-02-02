#include <iostream>
#include <string>
using namespace std;

int main()
{
	string hello = "Hello!"; //using OBJECT instead of address, unlike const char*
	//string hello ("Hello!"); //using OBJECT instead of address, unlike const char*
	//converting from string to char, use stringname.c_str();

	cout << hello << endl;

	hello = "Hello";
	hello += ", world!"; //is an OPERATOR. operator += (const char* );

	cout << "「" << hello << "」を文字コードに変えると" << endl;

	//あいう
	//#include <Windows.h>
	//IsDBCSLeadByte();

	//for (size_t i = 0, i < hello.size(); i++)
	for (int i = 0, size = hello.size(); i < size; i++)
	{
		cout << (int)(unsigned char)hello[i] << ","; //Operator of operator[](int i); also returns char* probably
	}

	cout << endl
		 << "になります。" << endl;

	return 0;
}