#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout << "文字列を入力 > " << flush;
	string inputstr;
	getline(cin, inputstr);

	string inputSkip;
	cout << "スキップする文字を入力 > " << flush;
	getline(cin, inputSkip);

	string::size_type skipPos = inputstr.find(inputSkip);
	
	for(size_t i = 0; i < inputstr.size();i++)
	{
	if (skipPos != string::npos) 
	{ 
		inputstr.replace(skipPos, 1, "");
	}
	skipPos = inputstr.find(inputSkip);
	}
	
	//inputstr.insert(skipPos, "");
	//inputstr.erase(skipPos); //deletes all lines from this pos

	cout << inputstr << endl;

	system("pause");
	return 0;
}