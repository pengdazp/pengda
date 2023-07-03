#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include"String.h"
typedef enum {ATOM,LIST}ElemTag;
template<typename AtomType>
class GLNode {
public:
	ElemTag tag;
	union {
		AtomType atom;
		struct {
			GLNode* hp;
			GLNode* tp;
		}prt;
	};
public:
	GLNode() {
		
	}
};


template<typename AtomType>
using GList = GLNode<AtomType>*;
//������L�����
template<typename AtomType>
int GListDepth(GList<AtomType> &g) {
	if (!g)
		return 1;
	if (g->tag == ATOM)
		return 0;
	int max = 0;
	for (GLNode<AtomType>* p = g; p; p = p->prt.tp) {
		int temp = GListDepth(p->prt.hp);
		if (temp > max) max = temp;
	}
	return max + 1;
}

//��sub���ش�s�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
bool SubString(String& sub, String s, int pos, int len) {
	AssignString(sub,len);
	for (int i = 0; i < len ; i++) {
		sub[i] = s[pos + i-1];
	}
	return true;
}

//��ts��Ϊ���и��ַ���(����һ�������и�)��hs���ض���ǰ��ts���ض��ź�
bool Sever(String& hs, String& ts) {
	int i = 0;
	int mask = 0;
	for (i = 0; ts[i] != ','&& i<ts.length || mask; i++){
		if (ts[i] == '(')
			mask += 1;
		if (ts[i] == ')')
			mask -= 1;
	}
	if (i == ts.length) {
		SubString(hs, ts, 1, ts.length);
		delete[] ts.ch;
		ts.ch = NULL;
		ts.length = 0;
		return true;
	}
	AssignString(hs,i);

	SubString(hs, ts, 1, i);
	SubString(ts, ts, i + 2, ts.length- (i + 1));
	return true;
}

//���ַ����������� ���� ��a,b,(c,a,d)�� һ��Ԫ���ǵ��ַ�
template<typename AtomType>
bool CreateGList(GList<AtomType>& g, String s) {
	if (s.length == 1) {
		if (!(g = (GList<AtomType>)malloc(sizeof(GLNode<AtomType>))))
			return false;
		g->tag = ATOM;
		g->atom = s;
		return true;
	}
	if (StrCompare(s, "()")) {
		g = NULL;
		return true;
	}
	if (!(g = (GList<AtomType>)malloc(sizeof(GLNode<AtomType>))))
		return false;
	g->tag = LIST;

	GList<AtomType>p1 = g, p2 = g;

	String ts;
	SubString(ts, s, 2, s.length - 2);
	String hs;
	Sever(hs, ts);
	CreateGList(p1->prt.hp, hs);
	while(ts.ch){
		if (!(p2 =(GList<AtomType>)malloc(sizeof(GLNode<AtomType>))))
			return false;
		Sever(hs, ts);
		CreateGList(p2->prt.hp, hs);
		p1->prt.tp = p2;
		p2->tag = LIST;
		p1 = p2;
	}
	p2->prt.tp = NULL;
	return true;
}

