#pragma once
#define INIT_STACK_SIZE 100
#define STACKINCREMENT 10
#include<iostream>
using namespace std;

template<class SElemType>
class SqStack {
public:
	SElemType* base;
	SElemType* top;
	int stackSize;
};
class Human {
public:
	int (*p)();
	int high;
	bool Visit_High() {
		cout << high << endl;
		return true;
	}
};
template<typename SElemType>
bool InitStack(SqStack<SElemType>& s) {
	s.base = (SElemType*)malloc(sizeof(SElemType) * INIT_STACK_SIZE);
	if (!s.base)
		return false;
	s.top = s.base;
	s.stackSize = INIT_STACK_SIZE;
	return true;
}
template<typename SElemType>
bool DestroyStack(SqStack<SElemType>&s) {
	if (!s.base)
		return false;
	delete[]s.base;
	s.top = NULL;
	return true;
}
template<typename SElemType>
bool ClearStack(SqStack<SElemType>& s) {
	s.top = s.base;
	s.stackSize = 0;
	return true;
}
template<typename SElemType>
bool StackEmpty(SqStack<SElemType>&s) {
	if (s.base == s.top)
		return true;
	return false;
}
template<typename SElemType>
int StackLength(SqStack<SElemType>& s) {
	return s.stackSize;
}
template<typename SElemType>
bool GetTop(SqStack<SElemType>&s,SElemType &e) {
	if (s.top == s.base)
		return false;
	e = *(s.top-1);
	return true;
}
template<typename SElemType>
bool Push(SqStack<SElemType>& s, SElemType& e) {
	if (s.top - s.base + 1 > s.stackSize) {
		s.base = (SElemType*)realloc(s.base, sizeof(SElemType) * (s.stackSize + STACKINCREMENT)); //【!】注意带sizeof
		s.top = s.base + s.stackSize + STACKINCREMENT;
		s.stackSize += STACKINCREMENT;
	}
	*s.top++ = e;
	return true;
}
template<typename SElemType>
bool Pop(SqStack<SElemType>& s, SElemType& e) {
	if (s.base == s.top)
		return false;
	e = *(--s.top);
	return true;
}


template<typename SElemType>
bool StackTraverse(SqStack<SElemType>& s, bool(SElemType::*visit)()) {
	SElemType* p = s.top;
	//--p;
	//(*p).high = 34;   注意一定要加括号  不然*p.high  就是* (p.high)
	do {
		if (!(*--p.*visit)())
			return false;
	} while (p != s.base);
	
	return true;
}