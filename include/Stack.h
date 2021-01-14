/*
 * Stack.h
 *
 *  Created on: 24-Mar-2018
 *      Author: Sagar
 */

#ifndef STACK_H_
#define STACK_H_

namespace std{

class Stack{
	int sz,i,head;
	int* elem;

public:
	Stack(int s);

//	int& operator[](int i){return elem[i];}

	void push(int a);
	int pop();
	int peek();
	int size();
	bool isFull();
	bool isEmpty();

	virtual ~Stack();
};

}/* namespace std */

#endif /* STACK_H_ */
