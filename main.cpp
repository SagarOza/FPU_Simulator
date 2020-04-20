#include<stdio.h>
#include<iostream>
#include"fp.h"
#include"Stack.h"

using namespace std;

struct fp_struct{
	unsigned int manti, uexp, exp, sign;
};


fp_struct add(fp f0, fp f1){

	int man0=0, man1=0, exp0=0, exp1=0, exp_diff=0, add_exp=0, add_num=0, add_up=0, exp_cnt=0, res_exp=0, add_manti=0;
	int sign_bit=0;
	fp_struct fp_add;

	fp_add.manti=0; fp_add.uexp=0; fp_add.exp=0; fp_add.sign=0;

	fp add(0, 0, 0, 0,1);

	man0=f0.get_manti();
	man1=f1.get_manti();

	exp0=f0.get_exp();
	exp1=f1.get_exp();

	man0 += 1024;
	man1 += 1024;

	if((f0.get_sign() ^ f1.get_sign())){	// Checks for either addition or substraction.
		if(exp0>exp1){
			sign_bit=f0.get_sign();
		}else if(exp0<exp1){
			sign_bit=f0.get_sign();
		}else{
			if(man0>man1){
				sign_bit=f0.get_sign();
			}else{
				sign_bit=f1.get_sign();
			}
		}
		if(f0.get_sign()==1){
			man0=~man0;
			man0=(man0&2047);
			man0+=1;
		}else if(f1.get_sign()==1){
			man1=~man1;
			man1=(man1&2047);
			man1+=1;
		}

	}else{
		sign_bit=0;
	}
		exp_diff=exp0 - exp1;

		if(exp_diff < 0){
			exp_diff= exp1 - exp0;
			man0 = (man0 << exp_diff);
			add_exp = exp1;
		}else if(exp_diff > 0){
			man1 = (man1 << exp_diff);
			add_exp = exp0;
		}else{
			add_exp=exp0;
		}
		add_num = man1 + man0;

		if(sign_bit==1){	
			add_num=~add_num;
			add_num=(add_num&(1<<(12)-1));
		}

		add_up = add_num >> 10;

		while(add_up!=0){
			add_up = add_up >> 1;
			if(add_up==0) break;
			exp_cnt++;
		}

		add_num = (add_num >> (exp_cnt))-1024;
		add_manti = add_num;
		fp_add.exp = add_exp + exp_cnt ;
		if(sign_bit==0)
			fp_add.sign = f0.get_sign() ;
		else
			fp_add.sign = sign_bit;
		fp_add.manti = add_manti ;

	return fp_add;				//	fp_add is a fp_struct that needs to be declared properly.

}

fp_struct mul(fp f1, fp f2){

	fp_struct mul_struct;
	int man1, man2, exp1, exp2, sign1, sign2;
	int mul_manti, mul_exp, mul_ubias, mul_sign, exp_cnt=0;

	exp1 = f1.get_ubias();
	exp2 = f2.get_ubias();

	man1 = f1.get_manti();
	man2 = f2.get_manti();

	man1 +=1024;
	man2 +=1024;

	sign1 = f1.get_sign();
	sign2 = f2.get_sign();

	mul_ubias = exp1 + exp2;
	mul_exp = mul_ubias + 15;
	mul_manti = man1*man2;

	while(mul_manti > ((1<<21) -1)){
		mul_manti = (mul_manti >> 1);
		exp_cnt++;
	}

	while( mul_manti >= (( 1 << 11 )-1 )){
		mul_manti = (mul_manti >> 1);
	}
	mul_manti -= 1024;
	mul_exp+=exp_cnt;
	while( mul_exp >= (( 1<<5 ) -1) ){
		mul_exp = (mul_exp >> 1);
	}

	mul_struct.manti = mul_manti;
	mul_struct.exp = mul_exp;
	mul_struct.sign = sign1^sign2;

	return mul_struct;

}

fp compute_fp(fp_struct struct_data){

	fp fP(0, 0, 0, 0, 1);

	fP.set_sign(struct_data.sign);
	fP.set_manti(struct_data.manti);
	fP.set_exp(struct_data.exp);
	fP.find_ubias();

	return fP;

}

int main(){

	int f0_sign, f0_exp, f0_manti;
	int f1_sign, f1_exp, f1_manti;

	int F0[2], F1[2];

	cout << "f0:: " << endl;
	cin >> F0[1] >> F0[0];
	cout << "f1:: " << endl;
	cin >> F1[1] >> F1[0] ;
	cout << endl;

	fp fp0(0, 0, F0[1], F0[0], 1), fp1(0, 0, F1[1], F1[0],1), fadd(0, 0, 0, 0, 1), fmul(0, 0, 0, 0, 1);

	fp_struct add_struct, mul_struct;

	add_struct=add(fp0, fp1);
	mul_struct=mul(fp0, fp1);
	fadd=compute_fp(add_struct);
	fmul=compute_fp(mul_struct);

	cout << hex << "FP0	:" << fp0.get_fp() << "	(in hex)" << endl;
	fp0.fp_burp();
	cout << endl;
	cout << hex << "FP1	:" << fp1.get_fp() << "	(in hex)" << endl;
	fp1.fp_burp();
	cout << endl;
	cout << hex << "FP_add	:" << fadd.get_fp() << "	(in hex)" << endl;
	fadd.fp_burp();
	cout << endl;
	cout << hex << "FP_mul	:" << fmul.get_fp() << "	(in hex)" << endl;
	fmul.fp_burp();
	cout << endl;

	return 0;
}
