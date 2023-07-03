#pragma once
#include"SqList.h"
void Merge(SqList<int>s1, SqList<int>& s2, int i, int m, int n) {
	int j,k;
	for ( k = i, j = m + 1; i <= m && j <= n; k++) {
		if (s1.data[i] < s1.data[j]) {
			s2.data[k] = s1.data[i];
			i++;
		}
		else {
			s2.data[k] = s1.data[j];
			j++;
		}
	}
	if (i <= m) 
		for (; i <= m; i++) 
			s2.data[k] = s1.data[i];
	if (j <= n)
		for (; i <= n; i++)
			s2.data[k] = s1.data[j];
	
}
void MSort(SqList<int>s1, SqList<int>&s2, int s, int t) {
	if (s == t)
		s2.data[s] = s1.data[s];
	else {
		int m = (s + t) / 2;
		MSort(s1, s2, s, m);
		MSort(s2, s2, m+1, t);
		Merge(s2, s2, s, m, t);
	}
}
void MergeSort(SqList<int> &s) {
	MSort(s, s, 0, s.length - 1);
	
}