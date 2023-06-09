#include <iostream>
using namespace std;

int main()
{

    for (;;)
    {
        int a, b;

        cout << "1 番目の値を入力してくださ > " << flush;
        cin >> a;

        cout << "2 番目の値を入力してくださ > " << flush;
        cin >> b;

        if (b == 0)
        {
            cout << "0　では割れません！" << endl;
            break;
        }

        cout << a << " / " << b << " = "
             << a / b << " … " << a % b << endl;

        cout << "プログラムは終了しました。" << endl;
    }

}

