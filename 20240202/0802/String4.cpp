#include <iostream>
#include <string>
using namespace std;

int main()
{
	while (true)
	{
		string line;

		cout << "なんか文章を入力してください > " << flush;
		//cin >> line;

		getline(cin, line);
		if (line == "quit")
		{
			break;
		}

		//this elseif program finds letter and save it
		string::size_type pos = line.rfind("。"); //finds the order of the letter from behind
		if (pos == string::npos)
		{
			line += "アルネ";
		}
		else
		{
			line.insert(pos, "アルネ");
		}

		cout << line << endl;
	}
}