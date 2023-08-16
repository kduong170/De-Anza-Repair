/* 
DeleteStack.h
	Written by Henri Wood
*/

#ifndef DeleteStack_h
#define DeleteStack_h

#include "SmartPhone.h"

class DeleteStack {

	struct stackNode {
		SmartPhone value;
		stackNode* next;
	};

	stackNode* top;
	int length;

public:
	DeleteStack() {
		top = NULL;
		length = 0;
	}
	~DeleteStack();

	void push(SmartPhone item);
	SmartPhone pop();
	void clearStack();

	bool isEmpty() { return length == 0; }
	int getLength() { return length; }

};

DeleteStack::~DeleteStack() {
	stackNode* deleteNode;

	if (length > 0) {
		while (top) {
			deleteNode = top;
			top = top->next;
			delete deleteNode;
		}
		delete top;
	}
}

void DeleteStack::push(SmartPhone item) {
	stackNode* newNode = new stackNode;
	newNode->value = item;
	newNode->next = top;
	top = newNode;
	length++;
}

SmartPhone DeleteStack::pop() {
	SmartPhone returnPhone;
	stackNode* deleteNode;

	returnPhone = top->value;
	deleteNode = top;
	top = top->next;
	delete deleteNode;
	length--;

	return returnPhone;
}

void DeleteStack::clearStack() {
	stackNode* deleteNode;
	if (length > 0) {
		while (top) {
			deleteNode = top;
			top = top->next;
			delete deleteNode;
		}
		length = 0;
	}
}


#endif