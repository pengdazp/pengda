#pragma once
#define MAX_SqList_LENGTH  100
#define SqList_INCREMENT 10
#include<string>
#include<iostream>
using namespace std;

template <typename dataType>
class SqList {
public:
	dataType *data;
	int length;
	int size;
	SqList() {
	
	}
	SqList(const SqList& p) {
		this->data = new dataType[p.length];
		for (int i = p.length; i >= 0; i--) {
			this->data[i] = p.data[i];
		}
		this->length = p.length;
		this->size = p.size;
	}
};
//初始化一个线性表
template<typename dataType>
bool InitSqList(SqList<dataType>& L, dataType* d = NULL, int n = 0) {
	if (n == 0) {
		L.data = new dataType[SqList_INCREMENT];
		if (!L.data)
			return false;
		L.length = 0;
		L.size = SqList_INCREMENT;
		return true;
	}
	else {
		L.data = new dataType[n];
		if (!L.data)
			return false;
		else {
			L.data = d;
		}
		L.length = n;
		L.size = n;
		return true;
	}
}
//释放一个线性表
template<typename dataType>
bool DestroySqList(SqList<dataType>& L) {
	if (L.data) {
		delete[]L;
		return true;
	}
	return false;
}
//把线性表置空
template<typename dataType>
void ClearSqList(SqList<dataType>& L) {
	L.length = 0;
}
//判读先线性表是否为空
template<typename dataType>
bool SqListEmpty(SqList<dataType>& L) {
	if (L.length == 0)
		return true;
	return false;
}
//返回线性表的长度
template<typename dataType>
int SqListLength(SqList<dataType>& L) {
	return L.length;
}
//用e返回先信标中的第i个元素的值
template<typename dataType>
bool GetElem(SqList<dataType>& L, int i, dataType e) {
	if (i<0 || i>L.length)
		return false;
	e = L.data[i - 1];
	return false;
}

//满足线性表中第一个与e满足关系compare()的数据元素的位序。
template<typename dataType>
int LocatElem(SqList<dataType>& L, dataType e, char c) {
	switch (c) {
	case '=':
		for (int i = 0; i < L.length; i++) {
			if (L.data[i] == e)
				return i + 1;
		}
		return 0;
		break;
	case '>':
		for (int i = 0; i < L.length; i++) {
			if (L.data[i] > e)
				return i + 1;
		}
		return 0;
		break;
	case'<':
		for (int i = 0; i < L.length; i++) {
			if (L.data[i] < e)
				return i + 1;
		}
		return 0;
		break;
	}
}
//用priorE返回curE的前驱
template<typename dataType>
bool PriorElme(SqList<dataType>& L, dataType curE, dataType priorE) {
	for (int i = 0; i < L.length; i++) {
		if (curE == L.data[i]) {
			priorE = L.data[i - 1];
			return true;
		}
	}
	return false;
}
//用nextE返回curE的后驱
template<typename dataType>
bool NextElme(SqList<dataType>& L, dataType curE, dataType nextE) {
	for (int i = 0; i < L.length; i++) {
		if (curE == L.data[i]) {
			nextE = L.data[i + 1];
			return true;
		}
	}
	return false;
}
//在线性表的第i个位置之前插入新的数据元素e
template<typename dataType>
bool SqListInsert(SqList<dataType>& L, int i, dataType e) {
	if (i<0 || i>L.length+1)
		return false;
	if (L.length  > L.size) {
		dataType *newBase = (dataType*)realloc(L.data,L.size + SqList_INCREMENT);
		if (!newBase)
			return false;
		L.data = newBase;
		L.size += SqList_INCREMENT;
	}
	for (int j = L.length - 1; j >= i-1; j--) {
		L.data[j+1] = L.data[j];
	}
	L.data[i - 1] = e;
	L.length++;
	return true;
}
//删除线性表的第i个元素，并用e返回其值
template<typename dataType>
bool SqListDelete(SqList<dataType>& L, int i, dataType e) {
	if (i<0 || i>L.length)
		return false;
	e = L.data[i - 1];
	for (int j = i; j < L.length; j++) {
		L.data[i - 1] = L.data[i];
	}
	L.length--;
}
//把在线性表2中有，但是1中没有的元素，插入到1中
template<typename dataType>
bool SqListUnion(SqList<dataType>& L1, SqList<dataType>& L2) {
	for (int i = 0; i < L2.length; i++) {
		if (! LocatElem(L1,L2.data[i],'='))
			if (!SqListInsert(L1, i+1, L2.data[i]))
				return false;
	}
	return true;
}
//|有按值非递减有序排列的线性表1和2|把线性表2和线性表1合并为一个新的按值非递减排序的线性表3
template<typename dataType>
void MergeSqList(SqList<dataType>& L1, SqList<dataType>& L2, SqList<dataType>& L3) {
	InitSqList(L3);
	int index;
	for (int i = 0; i < L1.length; i++) {
		if (index = LocatElem(L3, L1.data[i], '>')) {
			SqListInsert(L3, index, L1.data[i]);
		}
		else
			SqListInsert(L3, L3.length + 1,L1.data[i]);
	}
	for (int i = 0; i < L2.length; i++) {
		if (index = LocatElem(L3, L2.data[i], '>')) {
			SqListInsert(L3, index, L2.data[i]);
		}
		else
			SqListInsert(L3, L3.length + 1, L2.data[i]);
	}
}
template<typename ElemType>
void PrintSqList(SqList<ElemType> l) {
	for (int i = 0; i < l.length; i++)
		cout << l.data[i] << endl;

}