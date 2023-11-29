#include <iostream>
#include "example.h"
#include "string.h"
#include <stack>
#include <queue>
#include <math.h>
#include <cmath>
using namespace std;
int main() {
		string s;
		getline(cin, s);
		int a = s.size();
		int i = 0;
		Lexema* ar;
		ar = new Lexema[a + 1000];
		int l = 0;
		while (i < a) {
			int un;
			char c;
			double num;
			if ((i > 0 && s[i] == '-' && s[i - 1] == '(') || (i == 0 && s[0] == '-') || ((i != 0) && ((s[i] == '-') && ((s[i - 1] == '+') || (s[i - 1] == '-') || (s[i - 1] == '*') || (s[i - 1] == '/'))))) {
				double c = -1;
				ar[l] = Lexema(c);
				ar[l + 1] = Lexema('*');
				l = l + 2;
				i = i + 1;
			}
			else if (s[i] == '1' || s[i] == '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9' || s[i] == '0') {
				int j = i;
				int raz = 0;
				while ((s[j] == '1' || s[j] == '2' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == '6' || s[j] == '7' || s[j] == '8' || s[j] == '9' || s[j] == '0') && (j < a)) {
					if (j - i == 0) {
						num = s[j] - '0';
					}
					else {
						num = (num * (10 * (j - i - raz))) + (s[j] - '0');
						raz = raz + 1;
					}
					j = j + 1;
				}
				ar[l] = Lexema(num);
				l = l + 1;
				i = j;
			}
			else if ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/') || (s[i] == '(') || (s[i] == ')') || (s[i] == '^')) {
				c = s[i];
				ar[l] = Lexema(c);
				l = l + 1;
				i = i + 1;
			}
			else if (s[i] == 'e') {
				ar[l] = Lexema('e');
				l = l + 1;
				i = i + 1;
			}
			else if (i + 2 < a && s[i] == 's' && s[i + 1] == 'i' && s[i + 2] == 'n') {
				string c = "sin";
				ar[l] = Lexema(c);
				l = l + 1;
				i = i + 3;
			}
			else if (i + 2 < a && s[i] == 'c' && s[i + 1] == 'o' && s[i + 2] == 's') {
				string c = "cos";
				ar[l] = Lexema(c);
				l = l + 1;
				i = i + 3;
			}
			else if (i + 2 < a && s[i] == 'c' && s[i + 1] == 't' && s[i + 2] == 'g') {
				string c = "ctg";
				ar[l] = Lexema(c);
				l = l + 1;
				i = i + 3;
			}
			else if (i + 1 < a && s[i] == 't' && s[i + 1] == 'g') {
				string c = "tg";
				ar[l] = Lexema(c);
				l = l + 1;
				i = i + 2;
			}
			else if (i + 1 < a && s[i] == 'l' && s[i + 1] == 'n') {
				string c = "ln";
				ar[l] = Lexema(c);
				l = l + 1;
				i = i + 2;
			}
			else if (i + 1 < a && s[i] == 'l' && s[i + 1] == 'g') {
				string c = "lg";
				ar[l] = Lexema(c);
				l = l + 1;
				i = i + 2;
			}
			else {
				throw 'FALL';
			}
		}
		chstring(ar);
		queue<Lexema> polish_notation;
		stack<Lexema> operations;
		for (int i = 0; i < l; i++) {
			if (ar[i].gettype(ar[i]) == 1) {
				polish_notation.push(ar[i]);
			}
			if (ar[i].gettype(ar[i]) != 1) {
				if ((ar[i].gettype(ar[i]) != 6) && (ar[i].gettype(ar[i]) != 7) && (operations.size() != 0) && (operations.top().getpr(operations.top()) < ar[i].getpr(ar[i]))) {
					while ((operations.size() != 0) && (operations.top().gettype(operations.top()) != 6)) {
						polish_notation.push(operations.top());
						operations.pop();
					}
					operations.push(ar[i]);
				}
				else if (ar[i].gettype(ar[i]) == 7) {
					while (operations.top().gettype(operations.top()) != 6) {
						polish_notation.push(operations.top());
						operations.pop();
					}
					operations.pop();
				}
				else {
					operations.push(ar[i]);
				}
			}
		}
		while (operations.size() != 0) {
			polish_notation.push(operations.top());
			operations.pop();
		}
		stack<double> calc;
		while (polish_notation.size() != 0) {
			if (polish_notation.front().gettype(polish_notation.front()) == 1) {
				calc.push(polish_notation.front().getval(polish_notation.front()));
				polish_notation.pop();
			}
			else if (polish_notation.front().gettype(polish_notation.front()) != 1) {
				if (polish_notation.front().gettype(polish_notation.front()) == 9) {
					double b;
					b = calc.top();
					calc.pop();
					double c = sin(b);
					calc.push(c);
					polish_notation.pop();
				}
				else if (polish_notation.front().gettype(polish_notation.front()) == 10) {
					double b;
					b = calc.top();
					calc.pop();
					double c = cos(b);
					calc.push(c);
					polish_notation.pop();
				}
				else if (polish_notation.front().gettype(polish_notation.front()) == 11) {
					double b;
					b = calc.top();
					calc.pop();
					if (cos(b) == 0) {
						throw 'FALL';
					}
					double c = tan(b);
					calc.push(c);
					polish_notation.pop();
				}
				else if (polish_notation.front().gettype(polish_notation.front()) == 12) {
					double b;
					b = calc.top();
					calc.pop();
					if (sin(b) == 0) {
						throw 'FALL';
					}
					double c = 1 / tan(b);
					calc.push(c);
					polish_notation.pop();
				}
				else if (polish_notation.front().gettype(polish_notation.front()) == 13) {
					double b;
					b = calc.top();
					calc.pop();
					if (b <= 0) {
						throw 'FALL';
					}
					double c;
					if (b == exp(1)) {
						c = 1;
					}
					else {
						c = log(b);
					}
					calc.push(c);
					polish_notation.pop();
				}
				else if (polish_notation.front().gettype(polish_notation.front()) == 14) {
					double b;
					b = calc.top();
					calc.pop();
					if (b <= 0) {
						throw 'FALL';
					}
					double c = log10(b);
					calc.push(c);
					polish_notation.pop();
				}
				else {
					double a;
					double b;
					a = calc.top();
					calc.pop();
					b = calc.top();
					calc.pop();
					if (polish_notation.front().gettype(polish_notation.front()) == 2) {
						double c;
						c = a + b;
						calc.push(c);
					}
					if (polish_notation.front().gettype(polish_notation.front()) == 3) {
						double c;
						c = b - a;
						calc.push(c);
					}
					if (polish_notation.front().gettype(polish_notation.front()) == 4) {
						double c;
						c = a * b;
						calc.push(c);
					}
					if (polish_notation.front().gettype(polish_notation.front()) == 5) {
						double c;
						if (a == 0) {
							throw 'FALL';
						}
						c = b / a;
						calc.push(c);
					}
					if (polish_notation.front().gettype(polish_notation.front()) == 8) {
						double c;
						c = pow(b, a);
						calc.push(c);
					}
					polish_notation.pop();
				}
			}
		}
		cout << calc.top();
}