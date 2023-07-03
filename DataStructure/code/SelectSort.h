#pragma once
#include"Sqlist.h"
void SelectSort(SqList<int>s) {
	for (int i = 0; i < s.length; i++) {
		int markForJ = i;
		for (int j = i + 1; j < s.length; j++)
			if (s.data[j] < s.data[markForJ]) 
				markForJ = j;
			
		if (i != markForJ) {
			int temp = s.data[i];
			s.data[i] = s.data[markForJ];
			s.data[markForJ] = temp;
		}
	}
}