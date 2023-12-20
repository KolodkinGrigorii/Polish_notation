#include <iostream>
#include <string>
using namespace std;
enum Type{number, un_op, bin_op, lefts, rights, add, sub, mul, dvs, deg, sns, csn, ln, lg, tg, ctg};
class Lexema {
private:
	Type type;
	int pr;
	double val;
	Type st;
public:
	Lexema() {
		type = number;
		val = 0;
		st = number;
	}
	Lexema(double s) {
		type = number;
		val = s;
		st = number;
	}
	Lexema(char s) {
		if (s == 'e') {
			type = number;
			val = exp(1);
			st = number;
		}
		if (s == '(') {
			type = lefts;
			pr = 99;
			st = lefts;
		}
		else if (s == ')') {
			type = rights;
			pr = 99;
			st = rights;
		}
		else if (s == '+') {
			type = add;
			pr = 4;
			st = bin_op;
		}
		else if (s == '-') {
			type = sub;
			pr = 3;
			st = bin_op;
		}
		else if (s == '*') {
			type = mul;
			pr = 2;
			st = bin_op;
		}
		else if (s == '/') {
			type = dvs;
			pr = 2;
			st = bin_op;
		}
		else if (s == '^') {
			type = deg;
			pr = 1;
			st = bin_op;
		}
	}
	Lexema(string s) {
		if (s == "sin") {
			type = sns;
			pr = 0;
			st = un_op;
		}
		if (s == "cos") {
			type = csn;
			pr = 0;
			st = un_op;
		}
		if (s == "tg") {
			type = tg;
			pr = 0;
			st = un_op;
		}
		if (s == "ctg") {
			type = ctg;
			pr = 0;
			st = un_op;
		}
		if (s == "ln") {
			type = ln;
			pr = 0;
			st = un_op;
		}
		if (s == "lg") {
			type = lg;
			pr = 0;
			st = un_op;
		}
	}
	Lexema& Lexema::operator=(const Lexema& v)
	{
		type = v.type;
		pr = v.pr;
		val = v.val;
		return *this;
	}
	Type gettype(Lexema c) {
		return c.type;
	}
	double getval(Lexema c) {
		return c.val;
	}
	int getpr(Lexema c) {
		return c.pr;
	}
	Type getSt() {
		return st;
	}
	friend std::ostream& operator<<(std::ostream& out, const Lexema& v)
	{
		if (v.type==1) {
			cout << v.val;
		}
		else if (v.type == add) {
			cout << "+";
		}
		else if (v.type == sub) {
			cout << "-";
		}
		else if (v.type == mul) {
			cout << "*";
		}
		else if (v.type == dvs) {
			cout << "/";
		}
		else if (v.type == lefts) {
			cout << "(";
		}
		else if (v.type == rights) {
			cout << ")";
		}
		else if (v.type == deg) {
			cout << "^";
		}
		else if (v.type == sns) {
			cout << "sin";
		}
		else if (v.type == csn) {
			cout << "cos";
		}
		else if (v.type == tg) {
			cout << "tg";
		}
		else if (v.type == ctg) {
			cout << "ctg";
		}
		else if (v.type == ln) {
			cout << "ln";
		}
		else if (v.type == lg) {
			cout << "lg";
		}
		return out;
	}
};

void chstring(Lexema* ar, int c) {
	int scounter = 0;
	int a = c;
	int i = 0;
	Type CurrentStatus;
	while (i < a) {
		if (i == 0 && ar[i].getSt() == un_op && i == a - 1) {
			throw 'FALL';
		}
		else if (i == 0 && (ar[i].getSt() == number || ar[i].getSt()==un_op)) {
			CurrentStatus = ar[i].getSt();
		}
		else if (i == 0 && ar[i].getSt() == lefts) {
			scounter++;
			CurrentStatus = lefts;
		}
		else if (i == 0) {
			throw 'FALL';
		}
		else if (i!=0) {
			if (CurrentStatus == number) {
				if ((ar[i].getSt() == number) && (ar[i].getSt() == lefts)) {
					throw 'FALL';
				}
				else if (ar[i].getSt() == rights) {
					scounter--;
					CurrentStatus = rights;
				}
				else if (ar[i].getSt() == bin_op || ar[i].getSt()==un_op) {
					CurrentStatus = ar[i].getSt();
				}
			}
			else if (CurrentStatus == bin_op) {
				if (ar[i].getSt() == bin_op || ar[i].getSt() == rights) {
					throw 'FALL';
				}
				else if (ar[i].getSt() == lefts) {
					scounter++;
					CurrentStatus = lefts;
				}
				else if (CurrentStatus == bin_op) {
					CurrentStatus = ar[i].getSt();
				}
			}
			else if (CurrentStatus == lefts) {
				if ((ar[i].getSt() == bin_op || ar[i].getSt() == rights)) {
					throw 'FALL';
				}
				else if (ar[i].getSt() == lefts) {
					scounter++;
					CurrentStatus = lefts;
				}
				else if (CurrentStatus == lefts) {
					CurrentStatus = ar[i].getSt();
				}
			}
			else if (CurrentStatus == rights) {
				if (ar[i].getSt() == lefts || ar[i].getSt() == number) {
					throw 'FALL';
				}
				else if (ar[i].getSt() == rights) {
					scounter--;
					CurrentStatus = rights;
				}
				else if (ar[i].getSt()==bin_op) {
					CurrentStatus = ar[i].getSt();
				}
				else {
					throw 'FALL';
				}
			}
			else if (CurrentStatus == un_op) {
				if (ar[i].getSt() == lefts) {
					scounter++;
					CurrentStatus = lefts;
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
			if (CurrentStatus == bin_op || CurrentStatus == lefts) {
				throw 'FALL';
			}
		}
		i++;
	}
}
