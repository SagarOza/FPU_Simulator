#include<stdio.h>
#include<iostream>
#include "fp.h"
#include "Stack.h"

using namespace std;

struct fp_struct{
	unsigned int manti, uexp, exp, typ, sign;
};

fp_struct add(fp f0, fp f1, int p_typ){

	int man0, man1, b_man0, b_man1, exp0, exp1, exp_diff, add_exp;
       	int cnt_1=0, cnt_0=0, cnt_b=0, add_num, add_dw, add_up, b_add_up, add_manti;
	Stack s_buf(80);
	fp_struct add_struct;

	man0 = f0.get_manti();
	man1 = f1.get_manti();

	exp0 = f0.get_exp();
	exp1 = f1.get_exp();

	exp_diff = exp0 - exp1;

	man0 += 1024;
	man1 += 1024;
	
	if(exp_diff < 0){
		
		exp_diff = exp1 - exp0;
		man1 = (man1 << exp_diff);
		add_exp = exp0;

	}else if(exp_diff > 0){
		
		add_exp = exp1;
		man0 = (man0 << exp_diff);

	}else{
		add_exp = exp1 ;
	}

	add_num = man1 + man0;
	add_dw = (add_num & 1023);
	add_up = ((add_num - add_dw) >> 10);
	b_add_up = add_up;

	if(exp_diff!=0 || man0!=man1){
	while(1){
		if(b_add_up==0){
			exp_diff=cnt_b-1;
			break;
		}
		b_add_up/=2;
		cnt_b++;
	}
	}
	add_manti = add_num & ( (1 << (9 + cnt_b)) - 1);
	add_exp += exp_diff;

	add_struct.manti = add_manti;
	add_struct.uexp = add_exp;
	add_struct.sign = f0.get_sign();
	add_struct.typ = p_typ;
	
	return add_struct;
}

fp compute_fp(fp_struct fdata){
	unsigned int F[4];

	F[3]=00000000;
	F[2]=00000000;
	F[1]=00000000;
	F[0]=00000000;

	fp f0(F[3], F[2], F[1], F[0], fdata.typ);

	f0.set_sign(fdata.sign);
	f0.set_exp(fdata.uexp);
	f0.set_manti(fdata.manti);
	f0.find_ubias();	
	return f0;
}

fp_struct mul(fp f1, fp f2, int typ){

	
	fp_struct mul_struct;
	int man1, man2, exp1, exp2, sign1, sign2;
	int mul_manti, mul_uexp, mul_exp, mul_sign;

	exp1 = f1.get_ubias();
	exp2 = f2.get_ubias();

	man1 = f1.get_manti();
	man2 = f2.get_manti();

	man1 += 1024;
	man2 += 1024;

	sign1 = f1.get_sign();
	sign2 = f2.get_sign();

	mul_uexp = exp1 + exp2;
	mul_exp = mul_uexp + 15;
	mul_manti = man1*man2;

	while( mul_manti >= ((1 << 11) - 1) ){
		mul_manti = (mul_manti >> 1);
	}
	mul_manti -= 1024;
	mul_manti = (mul_manti >> 1);
	while( mul_exp >= ((1 << 5) - 1) ){
		mul_exp = (mul_exp >> 1);
	}

	cout << hex << mul_manti << " " << dec << mul_exp << endl;

	mul_struct.manti = mul_manti;
	mul_struct.uexp = mul_exp;
	if( sign1 > 0 || sign2 > 0){
		mul_struct.sign = sign1 ^ sign2;
	} else {
		mul_struct.sign = 0;
	}
	mul_struct.typ = typ;

	return mul_struct;
}

int main(){

        int fp1[4], fp0[4], bin_data, p_typ;
	fp_struct ans_struct, mul_struct_ans;

        cout << "Precision Type: ";
        cin >> p_typ;
        cin >> fp0[1] >> fp0[0];
        cin >> fp1[1] >> fp1[0];

        fp0[3]=11000000; fp0[2]=10000000;
        fp1[3]=0; fp1[2]=0;

        fp f_0( fp0[3], fp0[2], fp0[1], fp0[0], p_typ);
        fp f_1( fp1[3], fp1[2], fp1[1], fp1[0], p_typ);
	fp f_2( 0, 0, 0, 0, p_typ);
	fp f_3( 0, 0, 0, 0, p_typ);

	ans_struct = add(f_0, f_1, p_typ);
	f_2=compute_fp(ans_struct);
	
	mul_struct_ans = mul(f_0, f_1, p_typ);
	f_3=compute_fp(mul_struct_ans);

	cout << ans_struct.uexp << " " << hex << ans_struct.manti << endl;
        f_0.fp_burp();
        cout << endl;
        f_1.fp_burp();
	cout << endl;
	cout << "Addition:" << endl;
	cout << "---------" << endl;
	f_2.fp_burp();
	cout << endl;
	cout << "Multiplication:" << endl;
	cout << "---------------" << endl;
	f_3.fp_burp();

        return 0;
}

