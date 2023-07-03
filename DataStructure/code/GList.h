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
//求广义表L的深度
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

//用sub返回串s的第pos个字符起长度为len的子串
bool SubString(String& sub, String s, int pos, int len) {
	AssignString(sub,len);
	for (int i = 0; i < len ; i++) {
		sub[i] = s[pos + i-1];
	}
	return true;
}

//以ts作为被切割字符串(按第一个逗号切割)，hs返回逗号前，ts返回逗号后
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

//用字符串构造广义表 形如 （a,b,(c,a,d)） 一个元素是单字符
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

