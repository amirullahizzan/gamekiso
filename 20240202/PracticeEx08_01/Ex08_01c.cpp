#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	cout << "�v�Z��:";
	string inputstr;
	getline(cin, inputstr);
	cout << inputstr << endl;
	if (stoi(inputstr) < 0)
	{
		cout << "ERROR: �v�Z�ł��Ȃ����Z�q���܂܂�Ă��܂�";
	}
	else
	{
		stringstream inputSstr (inputstr);
		int x, y;

		inputSstr >> x >> y;
		cout << "=" << x + y; //����
	}
	
	
	cout << "\n�v���O�������I�����܂�..." << endl;

	system("pause");
	return 0;
}