#pragma once
using namespace std;

template <class ElemType>
class LNode {
public:
	ElemType data;
	LNode* next;
};
template <class ElemType>
class LinkList { //��ͷ�ڵ�ĵ�����
public:
	LNode<ElemType>* head, * tail;
	int length;
};

//
// ��!�����а������Ĳ��������۷���Ϊ��1���ҵ�Ҫ�����Ľ��  2���Խ����в��� 
//������pָ���ֵΪe�Ľ��
template<typename ElemType>
bool MakeLNode(LNode<ElemType> *&p,ElemType e = ElemType ()) {
	p = (LNode<ElemType>*)malloc(sizeof(LNode<ElemType>));
	if (!p)
		return false;
	p->data = e;
	p->next = NULL;
	return true;
}
//�ͷ�P��ָ���
template<typename ElemType>
bool FreeLNode(LNode<ElemType>&p) {
	delete p;
	if (!p)
		return true;
	return false;
}
//����һ���յ���������
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

//��L������ĵ�i��Ԫ�ش���ʱ����ȡ��ֵ����ֵ��e
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
	int j = 1; //����
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

//�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
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
//�ڴ�ͷ���ĵ�����L�У�ɾ����i��Ԫ�أ�����e������ֵ
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
//������λ�򣬽�������ͷ���ĵ������Ա�
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
//����ֵ�ǵݼ����е�LA��LB�б��鲢�����б�õ��µ��б�LC,LC������˳��Ҳ�Ƿǵݼ���
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
