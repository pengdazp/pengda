#pragma once
#include"LinkBiTree.h"

template <typename key>
class KeyType {
public:
	key key;

};
template<typename elemType,typename keyType>
bool SearchBST(LinkBiTree<elemType> T, KeyType<keyType> key,LinkBiTree<elemType> &p ) {
	if (!T) {
		return false;
	}
	p = T;
	if (key.key == T->data) {
		p = T;
		return true;
	}
	else if (key.key < T->data)
		return SearchBST(T->lChild, key, p);
	else
		return SearchBST(T->rChild, key, p);
}
template<typename elemType,typename keyType>
bool InsertBST(LinkBiTree<elemType>t, KeyType<keyType>e) {
	LinkBiTree<elemType> p = NULL;
	if (!SearchBST(t, e, p)) {
		LinkBiTree<elemType> s = new BiTNode<elemType>;
		s->data = e.key;
		s->lChild = s->rChild = NULL;
		if (!p)
			t = s;
		else if (e.key<p->data) {
			p->lChild = s;
		}
		else
			p->rChild = s;
		return true;
	}
	return false;
}