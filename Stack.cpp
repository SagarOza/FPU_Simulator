/*
 * Stack.cpp
 *
 *  Created on: 24-Mar-2018
 *      Author: Sagar
 */
#include<iostream>
#include "Stack.h"

namespace std {

Stack::Stack(int s):elem{new int[s]},sz{s}
{
	// TODO Auto-generated constructor stub
	elem = new int[s];
	sz=s;
	head=-1;
	i=0;
	while((i)!=s)
		elem[i++]=0;
}

int Stack::size(){
	return sz;
}

void Stack::push(int a){

	if(!isFull()){
		elem[++head]=a;
	}else
		cout << "Stack Full!!" << endl;

}
int Stack::pop(){

	if(!isEmpty()){
		int data = elem[head--];
		return data;
	}
	else
		return -1;

}
int Stack::peek(){

		if(!isEmpty())
			return elem[head];
		else
			return -1;

}
bool Stack::isEmpty(){

	if(head!=-1)
		return false;
	else
		return true;

}
bool Stack::isFull(){

	if(head==sz)
		return true;
	else
		return false;
}


Stack::~Stack() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
