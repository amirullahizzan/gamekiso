#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "•¶Žš—ñ‚ð“ü—Í > " << flush;
	string inputstr;
	getline(cin , inputstr);
	
	for (size_t i = 0; i < inputstr.size()+2; i++)
	{
		cout << "+";
	}
	cout << "\n+" << inputstr << "+\n";
	for (size_t i = 0; i < inputstr.size()+2; i++)
	{
		cout << "+";
	}
		cout << endl;

	system("pause");
	return 0;
}