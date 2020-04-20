#include<iostream>
#include<stdio.h>
#include<bitset>
#include "Stack.h"
#include "fp.h"

namespace std{

fp::fp(int i3e_fp_3, int i3e_fp_2, int i3e_fp_1, int i3e_fp_0, int p_sel){
	
	int buf, new_buf, bit_c, cnt;
	Stack s0(80), s1(80), s2(80), s3(80);

	buf=0;
	cnt=0;
	sel=p_sel;

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

	while( !s3.isEmpty() ){
		new_buf=s3.pop();	
		buf = new_buf | (buf << 1);

	}
	
	while( !s2.isEmpty() ){
		new_buf=s2.pop();	
		buf = new_buf | (buf << 1);
	}
	
	while( !s1.isEmpty() ){
		new_buf=s1.pop();
		buf = new_buf | (buf << 1);
	}
	
	while( !s0.isEmpty() ){
		new_buf=s0.pop();
		buf = new_buf | (buf << 1);
	}

	fpoint = buf;
	sign = ( ( fpoint & ( 1 << (bit_c - 1) ) ) >> bit_c - 1 );
	exp = (fpoint & ((2047 >> 3*(3-p_sel)) << (bit_c - (6 + 3*(p_sel - 1))))) >> (bit_c - (6 + 3*(p_sel-1)));
	manti = (fpoint & 1023);
	find_ubias();
//	ubias = exp - (2047 >> (3*(3-p_sel)+1));

}

int fp::get_fp(){
	return fpoint;
}

int fp::get_sign(){
	return sign;
}

int fp::get_exp(){
	return exp;
}

int fp::get_manti(){
	return manti;
}

int fp::get_ubias(){
	return ubias;
}

void fp::fp_burp(){
	cout << "sign	:" << dec << sign << endl;
	cout << "exp	:" << dec << exp << endl;
	cout << "manti	:" << hex << manti << endl;
	cout << "ubias	:" << dec <<ubias << endl;
}

void fp::set_sign(unsigned int s){
	sign = s;
	if(sel == 1){
		fpoint = fpoint & ((1 << 15)-1);
		fpoint = fpoint | (sign << 15);
	}else if(sel == 2){
		fpoint = fpoint & ((1 << 31)-1);
		fpoint = fpoint | (sign << 31);
	}
}
void fp::set_exp(unsigned int e){
	exp = e;
	if(sel == 1){
		fpoint = fpoint & ((1 << 10) - 1 );
		fpoint = fpoint | ((exp & 31) << 10);
	}else if(sel == 2){
		fpoint = fpoint & ((1 << 23) - 1 );
		fpoint = fpoint | ((exp & 255) << 23);
	}
	set_sign(sign);
}
void fp::set_manti(unsigned int m){
	manti = m;
	if(sel == 1){
		fpoint = fpoint & (63 << 10);
		fpoint = fpoint | (manti & ((1 << 10) - 1));
	}else if(sel == 2){
		fpoint = fpoint & (511 << 23);
		fpoint = fpoint | (manti & ((1 << 23) - 1));
	}
}
void fp::set_sel(unsigned int p_s){
	if(p_s<0 || p_s>3){
		cout << "Incorrect Data!!" << endl;
	}else{
		sel = p_s;
	}
}
void fp::find_ubias(){
	ubias = exp - (2047 >> (3*(3-sel)+1));
}

fp::~fp(){
}

}
