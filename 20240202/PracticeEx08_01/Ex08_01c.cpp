#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	cout << "ŒvŽZŽ®:";
	string inputstr;
	getline(cin, inputstr);
	cout << inputstr << endl;
	if (stoi(inputstr) < 0)
	{
		cout << "ERROR: ŒvŽZ‚Å‚«‚È‚¢‰‰ŽZŽq‚ªŠÜ‚Ü‚ê‚Ä‚¢‚Ü‚·";
	}
	else
	{
		stringstream inputSstr (inputstr);
		int x, y;

		inputSstr >> x >> y;
		cout << "=" << x + y; //Œ‹‰Ê
	}
	
	
	cout << "\nƒvƒƒOƒ‰ƒ€‚ðI—¹‚µ‚Ü‚·..." << endl;

	system("pause");
	return 0;
}