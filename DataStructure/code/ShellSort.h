#pragma once
#include"SqList.h"
void ShellInsert(SqList<int>s,int dk) {
	for (int i = dk + 1; i < s.length; i++) {
		if (s.data[i] < s.data[i - dk]) {
			s.data[0] = s.data[i];
			int j;
			for (j = i - dk; j > 0 && s.data[0] < s.data[j]; j -= dk) 
				s.data[j+dk] = s.data[j];
			s.data[j + dk] = s.data[0];
		
		}
	}

}
void ShellSort(SqList<int>& s, int* dlta, int n) {
	for (int i = 0; i < n; i++)
		ShellInsert(s, dlta[i]);
}