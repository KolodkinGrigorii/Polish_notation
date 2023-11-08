#include <iostream>
#include <string>
using namespace std;
class Lexema {
private:
	int type;//1-число, 2-плюс, 3-бинарный минус, 4-умножение, 5-деление, 6-лс, 7-пс
	int pr;
	int val;
public:
	Lexema() {
		type = 0;
		pr = 9999;
		val = 0;
	}
	Lexema(double s) {
		type = 1;
		pr = 9999;
		val = s;
	}
	Lexema(char s) {
		if (s == '(') {
			type = 6;
			pr = 0;
		}
		else if (s == ')') {
			type = 7;
			pr = 0;
		}
		else if (s == '+') {
			type = 2;
			pr = 2;
		}
		else if (s == '-') {
			type = 3;
			pr = 2;
		}
		else if (s == '*') {
			type = 4;
			pr = 1;
		}
		else if (s == '/') {
			type = 5;
			pr = 1;
		}
	}
	Lexema& Lexema::operator=(const Lexema& v)
	{
		type = v.type;
		pr = v.pr;
		val = v.val;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, const Lexema& v)
	{
		if (v.type==1) {
			cout << v.val;
		}
		else if (v.type == 2) {
			cout << "+";
		}
		else if (v.type == 3) {
			cout << "-";
		}
		else if (v.type == 4) {
			cout << "*";
		}
		else if (v.type == 5) {
			cout << "/";
		}
		else if (v.type == 6) {
			cout << "(";
		}
		else if (v.type == 7) {
			cout << ")";
		}
		return out;
	}
};
