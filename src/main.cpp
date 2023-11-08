#include <iostream>
#include "example.h"
#include "string.h"
using namespace std;
int main() {
	string s = "-1+2*66*(6+(-86))+3+4";
	int a = strlen("-1+2*66*(6+(-86))+3+4");
	int i = 0;
	Lexema* ar;
	ar = new Lexema[a];
	int l = 0;
	while (i<a) {
		int un;
		char c;
		double num;
		if (( i==0 && s[0] == '-') || ((i != 0) && ((s[i] == '-') && ((s[i - 1] == '+') || (s[i - 1] == '-') || (s[i - 1] == '*') || (s[i - 1] == '/'))))) {
			int j=i+1;
			un = -1;
			while ((s[j] == '1' || s[j] == '2' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == '6' || s[j] == '7' || s[j] == '8' || s[j] == '9' || s[j] == '0') && (j<a)) {
				if (j -i- 1==0) {
					num = s[j]-'0';
				}
				else {
					num = (num * (10 * (j - i - 1)))+(s[j]-'0');
				}
				j =j+1;
			}
			num = num * un;
			ar[l]=Lexema(num);
			l = l + 1;
			i = j;
			num = 0;
		}
		else if (s[i] =='1' || s[i] ==  '2' || s[i] == '3' || s[i] == '4' || s[i] == '5' || s[i] == '6' || s[i] == '7' || s[i] == '8' || s[i] == '9' || s[i] == '0') {
			int j = i;
			int raz = 0;
			while ((s[j] == '1' || s[j] == '2' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == '6' || s[j] == '7' || s[j] == '8' || s[j] == '9' || s[j] == '0') && (j < a)) {
				if (j - i== 0) {
					num = s[j] - '0';
				}
				else {
					num = (num * (10 * (j - i-raz))) + (s[j]-'0');
					raz = raz + 1;
				}
				j = j + 1;
			}
			ar[l] = Lexema(num);
			l = l + 1;
			i = j;
		}
		else if ((s[i] == '+') || (s[i] == '-') || (s[i] == '*') || (s[i] == '/') || (s[i]=='(') || (s[i]==')')) {
			c = s[i];
			ar[l] = Lexema(c);
			l = l + 1;
			i = i + 1;
		}
	}
	for (int i = 0; i < l; i++) {
		cout << ar[i];
	}
}