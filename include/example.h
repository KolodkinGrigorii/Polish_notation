#include <iostream>
#include <string>
using namespace std;
class Lexema {
private:
	int type;//1-число, 2-плюс, 3-бинарный минус, 4-умножение, 5-деление, 6-лс, 7-пс
	int pr;
	double val;
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
		if (s == 'e') {
			type = 1;
			pr = 9999;
			val = exp(1);
		}
		if (s == '(') {
			type = 6;
			pr = 99;
		}
		else if (s == ')') {
			type = 7;
			pr = 99;
		}
		else if (s == '+') {
			type = 2;
			pr = 4;
		}
		else if (s == '-') {
			type = 3;
			pr = 3;
		}
		else if (s == '*') {
			type = 4;
			pr = 2;
		}
		else if (s == '/') {
			type = 5;
			pr = 2;
		}
		else if (s == '^') {
			type = 8;
			pr = 1;
		}
	}
	Lexema(string s) {
		if (s == "sin") {
			type = 9;
			pr = 0;
		}
		if (s == "cos") {
			type = 10;
			pr = 0;
		}
		if (s == "tg") {
			type = 11;
			pr = 0;
		}
		if (s == "ctg") {
			type = 12;
			pr = 0;
		}
		if (s == "ln") {
			type = 13;
			pr = 0;
		}
		if (s == "lg") {
			type = 14;
			pr = 0;
		}
	}
	Lexema& Lexema::operator=(const Lexema& v)
	{
		type = v.type;
		pr = v.pr;
		val = v.val;
		return *this;
	}
	int gettype(Lexema c) {
		return c.type;
	}
	double getval(Lexema c) {
		return c.val;
	}
	int getpr(Lexema c) {
		return c.pr;
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
		else if (v.type == 8) {
			cout << "^";
		}
		else if (v.type == 9) {
			cout << "sin";
		}
		else if (v.type == 10) {
			cout << "cos";
		}
		else if (v.type == 11) {
			cout << "tg";
		}
		else if (v.type == 12) {
			cout << "ctg";
		}
		else if (v.type == 13) {
			cout << "ln";
		}
		else if (v.type == 14) {
			cout << "lg";
		}
		return out;
	}
};
int getSt(Lexema c) {
	if (c.gettype(c)==2 || c.gettype(c) == 3 || c.gettype(c) == 4 || c.gettype(c) == 5 || c.gettype(c)==8) {
		return 3;
	}
	else if (c.gettype(c) == 6){
		return 4;
	}
	else if (c.gettype(c) == 7) {
		return 5;
	}
	else if (c.gettype(c) == 9 || c.gettype(c) == 10 || c.gettype(c) == 11 || c.gettype(c) == 12 || c.gettype(c) == 13 || c.gettype(c) == 14) {
		return 2;
	}
	else{
		return 1;
	}
}
void chstring(Lexema* ar, int c) {
	int scounter = 0;
	int a = c;
	int i = 0;
	int CurrentStatus;//0-start,1-number,2-un_op,3-bin_op,4-lefts,5-rights,6-end
	while (i < a) {
		if (i == 0 && (getSt(ar[i]) == 1 || getSt(ar[i])==2)) {
			CurrentStatus = getSt(ar[i]);
		}
		else if (i == 0 && getSt(ar[i]) == 4) {
			scounter++;
			CurrentStatus = 4;
		}
		else if (i == 0) {
			throw 'FALL';
		}
		else if (i!=0) {
			if (CurrentStatus == 1) {
				if (CurrentStatus == 1 && ((getSt(ar[i]) == 1) || (getSt(ar[i]) == 4))) {
					throw 'FALL';
				}
				else if (CurrentStatus == 1 && getSt(ar[i]) == 5) {
					scounter--;
					CurrentStatus = 5;
				}
				else if (CurrentStatus == 1 && (getSt(ar[i]) == 3 || getSt(ar[i])==2)) {
					CurrentStatus = getSt(ar[i]);
				}
			}
			else if (CurrentStatus == 3) {
				if (CurrentStatus == 3 && ((getSt(ar[i]) == 3 || getSt(ar[i]) == 5) || i == a)) {
					throw 'FALL';
				}
				else if (CurrentStatus == 3 && getSt(ar[i]) == 4) {
					scounter++;
					CurrentStatus = 4;
				}
				else if (CurrentStatus == 3) {
					CurrentStatus = getSt(ar[i]);
				}
			}
			else if (CurrentStatus == 4) {
				if (CurrentStatus == 4 && ((getSt(ar[i]) == 3 || getSt(ar[i]) == 5) || i == a)) {
					throw 'FALL';
				}
				else if (CurrentStatus == 4 && getSt(ar[i]) == 4) {
					scounter++;
					CurrentStatus = 4;
				}
				else if (CurrentStatus == 4) {
					CurrentStatus = getSt(ar[i]);
				}
			}
			else if (CurrentStatus == 5) {
				if (CurrentStatus == 5 && ((getSt(ar[i]) == 4 || getSt(ar[i]) == 1))) {
					throw 'FALL';
				}
				else if (CurrentStatus == 5 && getSt(ar[i]) == 5) {
					scounter--;
					CurrentStatus = 5;
				}
				else if (CurrentStatus == 5 && getSt(ar[i])==3) {
					CurrentStatus = getSt(ar[i]);
				}
				else {
					throw 'FALL';
				}
			}
			else if (CurrentStatus == 2) {
				if (getSt(ar[i]) == 4) {
					scounter++;
					CurrentStatus = 4;
				}
				else {
					throw 'FALL';
				}
			}
		}
		if (i == a - 1) {
			if (scounter != 0) {
				throw 'FALL';
			}
		}
		i++;
	}
}
