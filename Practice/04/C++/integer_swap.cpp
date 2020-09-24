#include <iostream>

using namespace std;

int main() {
    int a;
    int b;

    cout << "Введите два целых числа, разделённых пробелом или новой строкой." << endl;
    cin >> a >> b;

    a = a - b;
    b = b + a;
    a = b - a;

    cout << "Значение a = " << a << endl;
    cout << "Значение b = " << b << endl;

	int temp;
	temp = a;
	a = b;
	b = temp;

    cout << "Значение a = " << a << endl;
    cout << "Значение b = " << b << endl;
}
