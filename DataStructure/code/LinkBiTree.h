#pragma once
#include<iostream>
#include"SqStack.h"
using namespace std;
template<typename TElemType>
class BiTNode{
public:
	BiTNode* lChild;
	BiTNode* rChild;
	TElemType data;
};

template<typename TElemType>
using LinkBiTree = BiTNode<TElemType>*;

//���ַ�������һ��������
//ǰ����������
template<typename TElemType>
bool CreateBiTree(LinkBiTree<TElemType> &b) {
	char ch;
	ch = getchar();
	if (ch == ' ')
		b = NULL;
	else {
		b = (LinkBiTree<TElemType>)malloc(sizeof(BiTNode<TElemType>));
		if (!b)
			return false;
		b->data = ch;
		CreateBiTree(b->lChild);
		CreateBiTree(b->rChild);
	}
	return true;
}

template<typename TElemType>
bool Visit(TElemType e) {
	cout << e << "  ";
	return true;
}

//�����������������ÿһ������Ԫ�ص��ú���Visit
//�ݹ��㷨
template<typename TElemType>
bool InOderTraverse_Re(LinkBiTree<TElemType>& b, bool (*Visit)(TElemType e)) {
	if (b) {
		if (InOderTraverse_Re(b->lChild,Visit) && Visit(b->data) && InOderTraverse_Re(b->rChild,Visit))
			return true;
		else
			return false;
	}
	else
		return true;
}

//�����������������ÿһ������Ԫ�ص��ú���Visit
//�ǵݹ��㷨
template<typename TElemType>
bool InOderTraverse_NRe(LinkBiTree<TElemType>& b, bool (*Visit)(TElemType e)) {
	SqStack<LinkBiTree<TElemType>> s;
	InitStack(s);
	Push(s, b);
	LinkBiTree<TElemType> p;
	while (!StackEmpty(s)) {
		while (GetTop(s, p) && p)
			Push(s, p->lChild);
		Pop(s, p);
		if (!StackEmpty(s)) {
			Pop(s, p);
			if (!Visit(p->data))
				return false;
			Push(s, p->rChild);
		}
	}
	return true;
}

//ǰ��������������ÿһ������Ԫ�ص��ú���Visit
//�ǵݹ��㷨
template<typename TElemType>
bool PreOderTraverse_NRe(LinkBiTree<TElemType>& b, bool (*Visit)(TElemType e)) {
	SqStack<LinkBiTree<TElemType>> s;
	InitStack(s);
	Push(s, b);
	LinkBiTree<TElemType> p;
	while (!StackEmpty(s)) {
		while (GetTop(s, p) && p) {
			Push(s, p->lChild);
			Visit(p->data);
		}
		Pop(s, p);
		if (!StackEmpty(s)) {
			Pop(s, p);
			Push(s, p->rChild);
		}
	}
	return true;
}

