#include <iostream>
#include <string>
using namespace std;

int main()
{
	while (true)
	{
		string line;

		cout << "�Ȃ񂩕��͂���͂��Ă������� > " << flush;
		//cin >> line;

		getline(cin, line);
		if (line == "quit")
		{
			break;
		}

		//this elseif program finds letter and save it
		string::size_type pos = line.rfind("�B"); //finds the order of the letter from behind
		if (pos == string::npos)
		{
			line += "�A���l";
		}
		else
		{
			line.insert(pos, "�A���l");
		}

		cout << line << endl;
	}
}