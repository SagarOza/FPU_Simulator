#include<iostream>
#include<stdio.h>
#include "fp.h"
//#include "Stack.h"

using namespace std;

int main(){

	unsigned int F[4], sel=1;
	F[0] = 11000000;
	F[1] = 10000000;
	F[2] = 00000000;
	F[3] = 00000000;
	sel  = 1;

	fp f0(F[3], F[2], F[1], F[0], sel);

	cout << hex << f0.get_fp() << endl;

	f0.set_sel(1);
	f0.set_sign(1);
	f0.set_exp(29);

	cout << hex << f0.get_fp() << endl;
//	cout << hex << f0.get_sign() << endl;

	return 0;
}
