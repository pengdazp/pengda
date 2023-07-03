#pragma once
#include"SqList.h"
int Partition(SqList<int>& l, int low, int high) {
	l.data[0] = l.data[low];
	while (low < high) {
		while (low < high && l.data[high] >= l.data[0])
			high--;
		l.data[low] = l.data[high];
		while (low < high && l.data[low] <= l.data[0])
			low++;
		l.data[high] = l.data[low];
	}
	l.data[low] = l.data[0];
	return low;
}

void QSort(SqList<int>& l, int low, int high) {
	if (low < high) {
		int pivotkey = Partition(l, low, high);
		QSort(l, low, pivotkey - 1);
		QSort(l, pivotkey + 1, high);
	}
}