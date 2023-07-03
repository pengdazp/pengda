#pragma once
using namespace std;

template <class ElemType>
class LNode {
public:
	ElemType data;
	LNode* next;
};
template <class ElemType>
class LinkList { //带头节点的单链表
public:
	LNode<ElemType>* head, * tail;
	int length;
};

//
// 【!】所有包含结点的操作，其宏观方法为：1、找到要操作的结点  2、对结点进行操作 
//分配由p指向的值为e的结点
template<typename ElemType>
bool MakeLNode(LNode<ElemType> *&p,ElemType e = ElemType ()) {
	p = (LNode<ElemType>*)malloc(sizeof(LNode<ElemType>));
	if (!p)
		return false;
	p->data = e;
	p->next = NULL;
	return true;
}
//释放P所指结点
template<typename ElemType>
bool FreeLNode(LNode<ElemType>&p) {
	delete p;
	if (!p)
		return true;
	return false;
}
//构造一个空的线性链表
template <typename ElemType>
bool InitLinkList(LinkList<ElemType> &L) {
	LNode<ElemType> *ln;
	if (MakeLNode(ln)) {
		L.head = L.tail = ln;
		L.length = 0;
		return true;
	}
	return false; int a = int(3);
}

//当L单链表的第i个元素存在时，获取其值并赋值给e
template <typename ElemType>
bool GetLinkListElem(LinkList<ElemType>&L,int i,ElemType e) {
	/*LNode<ElemType> *p = L.head;
	while (p->next != NULL) {
		p = p->next;
		if (--i == 0) {
			e = p->data;
			return true;
		}
	}
	return false;*/
	LNode<ElemType>* p = L.head->next;
	int j = 1; //计数
	while (p && j < i) {
		p = p->next;
		j++;
	}
	if (p && j == i) {
		e = p->data;
		return true;
	}
	return false;
}

//在带头结点的单链线性表L中第i个位置之前插入元素e
template <typename ElemType>
bool InsertLinkList(LinkList<ElemType>& L, int i, ElemType e) {
	LNode<ElemType>* p = L.head->next;
	int j = 1;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p && j == i - 1) {
		LNode<ElemType>* q;
		MakeLNode(q, e);
		q->next = p->next;
		p->next = q;
		return true;
	}
	L.length++;
	return false;
}
//在带头结点的单链表L中，删除第i个元素，并由e返回其值
template <typename ElemType>
bool DeleteLinkList(LinkList<ElemType>& L, int i, ElemType &e) {
	LNode<ElemType>* p = L.head->next;
	int j = 1;
	while (p->next && j < i-1) {
		p = p->next;
		j++;
	}
	if (p->next && j == i-1 ) {
		LNode<ElemType>* q = p->next;
		e = q->data;
		p->next = p->next->next;
		delete q;
		return true;
	}
	L.length--;
	return false;
}
//按数组位序，建立带表头结点的单链线性表
template <typename ElemType>
bool CreatLinkList(LinkList<ElemType> &L, ElemType* myArray, int n) {
	LNode<ElemType>* ln;
	InitLinkList(L);
	LNode<ElemType>* p = L.head;
	for (int i = 0; i < n; i++) {
		if (MakeLNode(ln, myArray[i])) {
			p->next = ln;
			p = p->next;
		}
		else
			return false;
	}
	L.tail = p;
	L.length = n;
	return true;
}
//两按值非递减排列的LA和LB列表，归并其两列表得到新的列表LC,LC的排序顺序也是非递减。
template <typename ElemType>
bool MargeLinkList(LinkList<ElemType> &la,LinkList<ElemType> &lb,LinkList<ElemType> &lc) {
	InitLinkList(lc);
	LNode<ElemType>* a = la.head->next, * b = lb.head->next, * c = lc.head;
	while (a && b) {
		if (a->data <= b->data) {
			c->next = a;
			a = a->next;
			c = c->next;
		}
		else {
			c->next = b;
			b = b->next;
			c = c->next;
		}
	}
	a ? c->next = a : c->next = b;
	lc.length = la.length + lb.length;
	return true;
}
//
