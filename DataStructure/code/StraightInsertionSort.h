#pragma once
#pragma once
#include"SqList.h"
//不带哨兵的顺序表
void InsertSort(SqList<int>& l) {
	for (int i = 1; i < l.length; i++) {
		if (l.data[i] < l.data[i - 1]) {
			int temp = l.data[i];
			l.data[i] = l.data[i - 1];
			int j = i - 2;
			for (; j >= 0; j--) {
				if (temp < l.data[j])
					l.data[j + 1] = l.data[j];
				else
					break;
			}
			l.data[j + 1] = temp;
		}
	}
}
////带哨兵的顺序表
//void InsertSort(SqList<int>& l) {
//	for (int i = 2; i < l.length; i++) {
//		if (l.data[i] < l.data[i - 1]) {
//			l.data[0] = l.data[i];
//			l.data[i] = l.data[i - 1];
//			int j = i - 2;
//			for (; l.data[0] < l.data[j]; j--)
//				l.data[j + 1] = l.data[j];
//			l.data[j + 1] = l.data[0];
//		}
//	}
//}
//带哨兵折半插入排序
void BinsertSort(SqList<int>s) {
	for (int i = 2; i < s.length; i++) {
		s.data[0] = s.data[i];
		int max = i - 1, min = 1;
		int mid = 0;
		while (min <= max) {
			mid = (int)((max + min) / 2);
			if (s.data[0] < s.data[mid])
				max = mid - 1;
			else
				min = mid + 1;
		}
		int j;
		for (j = i - 1; j >= max + 1; j--)
			s.data[j + 1] = s.data[j];
		s.data[j + 1] = s.data[0];
	}
}