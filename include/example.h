#include <iostream>
#include <string>
using namespace std;
enum Type{number, un_op, bin_op, lefts, rights, add, sub, mul, dvs, deg, sns, csn, ln, lg, tg, ctg};
class Lexema {
private:
	Type type;//1-число, 2-плюс, 3-бинарный минус, 4-умножение, 5-деление, 6-лс, 7-пс
	int pr;
	double val;
public:
	Lexema() {
		type = number;
		pr = 9999;
		val = 0;
	}
	Lexema(double s) {
		type = number;
		pr = 9999;
		val = s;
	}
	Lexema(char s) {
		if (s == 'e') {
			type = number;
			pr = 9999;
			val = exp(1);
		}
		if (s == '(') {
			type = lefts;
			pr = 99;
		}
		else if (s == ')') {
			type = rights;
			pr = 99;
		}
		else if (s == '+') {
			type = add;
			pr = 4;
		}
		else if (s == '-') {
			type = sub;
			pr = 3;
		}
		else if (s == '*') {
			type = mul;
			pr = 2;
		}
		else if (s == '/') {
			type = dvs;
			pr = 2;
		}
		else if (s == '^') {
			type = deg;
			pr = 1;
		}
	}
	Lexema(string s) {
		if (s == "sin") {
			type = sns;
			pr = 0;
		}
		if (s == "cos") {
			type = csn;
			pr = 0;
		}
		if (s == "tg") {
			type = tg;
			pr = 0;
		}
		if (s == "ctg") {
			type = ctg;
			pr = 0;
		}
		if (s == "ln") {
			type = ln;
			pr = 0;
		}
		if (s == "lg") {
			type = lg;
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
	Type gettype(Lexema c) {
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
Type getSt(Lexema c) {
	if (c.gettype(c) == add || c.gettype(c) == sub || c.gettype(c) == mul || c.gettype(c) == dvs || c.gettype(c) == deg) {
		return bin_op;
	}
	else if (c.gettype(c) == sns || c.gettype(c) == csn || c.gettype(c) == tg || c.gettype(c) == ctg || c.gettype(c) == lg || c.gettype(c) == ln) {
		return un_op;
	}
	else if (c.gettype(c) == lefts) {
		return lefts;
	}
	else if (c.gettype(c) == rights) {
		return rights;
	}
	else {
		return number;
	}
}
void chstring(Lexema* ar, int c) {
	int scounter = 0;
	int a = c;
	int i = 0;
	Type CurrentStatus;//0-start,1-number,2-un_op,3-bin_op,4-lefts,5-rights,6-end
	while (i < a) {
		if (i == 0 && getSt(ar[i]) == un_op && i == a - 1) {
			throw 'FALL';
		}
		else if (i == 0 && (getSt(ar[i]) == number || getSt(ar[i])==un_op)) {
			CurrentStatus = getSt(ar[i]);
		}
		else if (i == 0 && getSt(ar[i]) == lefts) {
			scounter++;
			CurrentStatus = lefts;
		}
		else if (i == 0) {
			throw 'FALL';
		}
		else if (i!=0) {
			if (CurrentStatus == number) {
				if ((getSt(ar[i]) == number) || (getSt(ar[i]) == lefts)) {
					throw 'FALL';
				}
				else if (getSt(ar[i]) == rights) {
					scounter--;
					CurrentStatus = rights;
				}
				else if (getSt(ar[i]) == bin_op || getSt(ar[i])==un_op) {
					CurrentStatus = getSt(ar[i]);
				}
			}
			else if (CurrentStatus == bin_op) {
				if (getSt(ar[i]) == bin_op || getSt(ar[i]) == rights) {
					throw 'FALL';
				}
				else if (getSt(ar[i]) == lefts) {
					scounter++;
					CurrentStatus = lefts;
				}
				else if (CurrentStatus == bin_op) {
					CurrentStatus = getSt(ar[i]);
				}
			}
			else if (CurrentStatus == lefts) {
				if ((getSt(ar[i]) == bin_op || getSt(ar[i]) == rights)) {
					throw 'FALL';
				}
				else if (getSt(ar[i]) == lefts) {
					scounter++;
					CurrentStatus = lefts;
				}
				else if (CurrentStatus == lefts) {
					CurrentStatus = getSt(ar[i]);
				}
			}
			else if (CurrentStatus == rights) {
				if (getSt(ar[i]) == lefts || getSt(ar[i]) == number) {
					throw 'FALL';
				}
				else if (getSt(ar[i]) == rights) {
					scounter--;
					CurrentStatus = rights;
				}
				else if (getSt(ar[i])==bin_op) {
					CurrentStatus = getSt(ar[i]);
				}
				else {
					throw 'FALL';
				}
			}
			else if (CurrentStatus == un_op) {
				if (getSt(ar[i]) == lefts) {
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
