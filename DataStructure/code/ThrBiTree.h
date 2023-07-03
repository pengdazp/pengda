#pragma once
typedef  enum PointerTag{ Link,Thread };

template<class TElemType>
class ThrBiNode {
public:
	PointerTag lTag,rTag;
	TElemType data;
	ThrBiNode* lChild;
	ThrBiNode* rChild;
};

template<typename ElemType>
using ThrBiTree = ThrBiNode<ElemType>*;

//用字符串创建一个线索二叉树(未线索化)
//前序遍历创造的
template<typename TElemType>
bool CreateThrBiTree(ThrBiTree<TElemType> &b) {
	char ch;
	ch = getchar();
	if (ch == ' ')
		b = NULL;
	else {
		b = (ThrBiTree<TElemType>)malloc(sizeof(ThrBiNode<TElemType>));
		if (!b)
			return false;
		b->data = ch;
		b->lTag = Link;
		b->rTag = Link;
		CreateThrBiTree(b->lChild);
		CreateThrBiTree(b->rChild);
	}
	return true;
}

template<typename TElemType>
void InThreading(ThrBiTree<TElemType> p, ThrBiTree<TElemType> &pre) {
	if (p) {
		InThreading(p->lChild,pre);
		if (!p->lChild) {
			p->lTag = Thread;
			p->lChild = pre;
		}
		if (!pre->rChild) {
			pre->rTag = Thread;
			pre->rChild = p;
		}
		pre = p;
		InThreading(p->rChild,pre);
	}

}
//中序遍历二叉树，并将其中序线索化，Thrt指向头节点。
template<typename TElemType>
bool InOderThreading(ThrBiTree<TElemType>& thrT, ThrBiTree<TElemType> t) {
	thrT = (ThrBiTree<TElemType>)malloc(sizeof(ThrBiNode<TElemType>));
	if (!thrT)
		return false;
	thrT->lTag = Link;
	thrT->rTag = Thread;
	thrT->rChild = thrT;
	if (!t)
		thrT->lChild = thrT;
	else {
		thrT->lChild = t;
		ThrBiTree<TElemType> pre = thrT;
		InThreading(t, pre);
		thrT->rChild = pre;
		pre->rTag = Thread;
		pre->rChild = thrT;
	}
	return true;
}

//T指向头节点
//中序遍历二叉线索树的非递归算法，对每个元素调用Visit函数。
template<typename TElemType>
bool InOderTraverse_Thr(ThrBiTree<TElemType>t, bool (*Visit)(TElemType)) {
	ThrBiTree<TElemType>p = t->lChild;
	while (p != t) {
		while (p->lTag == Link)
			p = p->lChild;
		if (!Visit(p->data))
			return false;
		while (p->rTag == Thread && p->rChild != t) {
			p = p->rChild;
			if (!Visit(p->data))
				return false;
		}
		p = p->rChild;
	}
}
