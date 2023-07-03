#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NO_VA_START_VALIDATION
#pragma once
#include<iostream>
#include<cstdarg>
#define MAX_ARRAY_DIM 8
using namespace std;
template<class ElemType>
class Array{
public:
	ElemType* base;
	int dim;
	int* bounds;
	int* constants;
};
template<typename ElemType>
bool InitArray(Array<ElemType>&a,int dim,...) {
	va_list ap;
	if (dim<1 || dim>MAX_ARRAY_DIM)
		return false;
	a.dim = dim;
	a.bounds = (int*)malloc(sizeof(int) * dim);
	va_start(ap,dim);
	int total = 1;
	for (int i = 0; i < dim; i++) {
		a.bounds[i] = va_arg(ap,int);
		if (a.bounds[i] < 0)
			return false;
		total *= a.bounds[i];
	}
	va_end(ap);
	a.base = (ElemType*)malloc(sizeof(ElemType) * total);
	if (!a.base)
		return false;
	a.constants = (int*)malloc(sizeof(int) * dim);
	a.constants[dim - 1] = 1;
	//���ַ������У�����for�Ǵ�0��ʼ��n-2���г�ʼ��������һ�����ĳ�ʼ������Ҫ��һ������ֵ��������Ҫ�ȳ�ʼ��dim-1  Ȼ���dim-2��0���г�ʼ��
	//for (int i = 0; i < dim - 1; i++)
	//	a.constants[i] = a.constants[i + 1] * a.bounds[i + 1];
	for (int i = dim - 2; i >= 0; i--)
		a.constants[i] = a.constants[i + 1] * a.bounds[i + 1];
	return true;
}

template<typename ElemType>
bool DestroyArray(Array<ElemType>& a) {
	if(a.base)free(a.base);
	free(a.bounds);
	free(a.constants);
	a.dim = 0;
	return true;
}
//��apָʾ�ĸ��±�ֵ�Ϸ�����Ҫ�����Ԫ����A����Ե�ַoff
template<typename ElemeType>
bool Locate(Array<ElemeType>& a, va_list ap, int& off) {
	off = 0;
	for (int i = 0; i < a.dim; i++) {
		int ind = va_arg(ap, int);
		if (ind<0 || ind>a.bounds[i])
			return false;
		off += a.constants[i] * ind;
	}
	return true;
}
//A��nά���飬eΪԪ�ر����������n���±�ֵ�������±겻���磬��e��ֵΪ��ָ����A��Ԫ��ֵ
template<typename ElemeType>
bool Value(Array<ElemeType>& a, ElemeType& e, ...) {
	va_list ap;
	va_start(ap, e);
	int off = 0;
	if (!Locate(a, ap, off))
		return false;
	e = *(a.base + off);
	return true;
}
//��Ԫ��e��ֵ��nά����A��n���±��Ӧ��Ԫ�ظ�ֵ
template<typename ElemeType>
bool Assign(Array<ElemeType>& a, ElemeType e, ...) {
	va_list ap;
	int off = 0;
	va_start(ap, e);
	if (!Locate(a, ap, off))
		return false;
	*(a.base + off) = e;
	return true;
}