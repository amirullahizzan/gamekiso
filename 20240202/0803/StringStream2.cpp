#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	stringstream sstr("1 2"); //put the next string after empty space and can convert them to other types.
	int x, y;
	//float x, y;
	//if (sstr.fail()) returns bool of the failed insertion
	sstr >> x >> y;
	cout << x << " + " << y << " = " << (x + y) << endl;
}