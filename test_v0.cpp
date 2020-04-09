#include<iostream>
#include<stdio.h>
#include<bitset>
#include "Stack.h"

using namespace std;

class fp{
	private:

		unsigned int sign, fpoint, exp, manti, ubias;
		
	public:
		fp(int, int, int, int, int);

		//	Defining all the Getters
		int get_fp(){
			return fpoint;
		}

		int get_sign(){
			return sign;
		}

		int get_exp(){
			return exp;
		}

		int get_manti(){
			return manti;
		}

		int get_ubias(){
			return ubias;
		}

		void fp_burp(){
			cout << "sign	:" << sign << endl;
			cout << "exp	:" << exp << endl;
			cout << "ubias	:" << ubias << endl;
			cout << "manti	:" << hex << manti << endl;
		}
		virtual ~fp();
};

fp::fp(int i3e_fp_3, int i3e_fp_2, int i3e_fp_1, int i3e_fp_0, int p_sel){
	
	int buf, new_buf, bit_c, cnt;
	Stack s0(80), s1(80), s2(80), s3(80);

	buf=0;
	cnt=0;

	if( p_sel==0 ){
		bit_c==4;
	}else if( p_sel==1 ){
		bit_c=16;
	}else if( p_sel==2 ){
		bit_c=32;
	}else if( p_sel==3 ){
		bit_c=64;
	}else{
		cout << "Enter proper selection" << endl;
	}

	while(cnt !=8){
		s3.push( i3e_fp_3%10 );
		i3e_fp_3/=10;

		s2.push( i3e_fp_2%10 );
		i3e_fp_2/=10;

		s1.push( i3e_fp_1%10 );
		i3e_fp_1/=10;
		
		s0.push( i3e_fp_0%10 );
		i3e_fp_0/=10;
	
		cnt++;
	}

	//	Appending bits in s3
	while( !s3.isEmpty() ){
		new_buf=s3.pop();	
		cout << new_buf;
		buf = new_buf | (buf << 1);

	}
	
	cout << " ";
	//	Appending bits in s2
	while( !s2.isEmpty() ){
		new_buf=s2.pop();	
		cout << new_buf;
		buf = new_buf | (buf << 1);
	}
	
	cout << " ";
	//	Appending bits in s1
	while( !s1.isEmpty() ){
		new_buf=s1.pop();
		cout << new_buf;
		buf = new_buf | (buf << 1);
	}
	
	cout << " ";
	//	Appending bits in s0
	while( !s0.isEmpty() ){
		new_buf=s0.pop();
		cout << new_buf;
		buf = new_buf | (buf << 1);
	}

	cout << endl;

	fpoint = buf;
	sign = ( ( fpoint & ( 1 << (bit_c - 1) ) ) >> bit_c - 1 );
	exp = (fpoint & ((2047 >> 3*(3-p_sel)) << (bit_c - (6 + 3*(p_sel - 1))))) >> (bit_c - (6 + 3*(p_sel-1)));
	manti = (fpoint & 1023);
	ubias = exp - (2047 >> (3*(3-p_sel)+1));

}

fp::~fp(){
}

int main(){

	int fp1[4], fp0[4], bin_data, p_typ;

	cout << "Precision Type: ";
	cin >> p_typ;
	cin >> fp0[1] >> fp0[0];
	cin >> fp1[1] >> fp1[0];

	fp0[3]=11000000; fp0[2]=10000000;
	fp1[3]=00000000; fp1[2]=00000000;

	fp f_0( fp0[3], fp0[2], fp0[1], fp0[0], p_typ);
	fp f_1( fp1[3], fp1[2], fp1[1], fp1[0], p_typ);
	
	f_0.fp_burp();
	cout << endl;
	f_1.fp_burp();

	return 0;
}
