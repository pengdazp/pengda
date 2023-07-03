#pragma once
#include"SqList.h"
//大顶堆   
void HeapAdjust(SqList<int>s, int begin, int end) {
	int temp = s.data[begin];//此处这种写法 在于用begin处的值去筛选的时候，不是每一轮筛选都要改变初始begin的位置
	int r;					 //----因为他一直在变位置。当最后确定后，通过17再来确定他的值
	for ( r = begin * 2 + 1; r <= end; r = r * 2 + 1) {
		
		if (r < end && s.data[r] < s.data[r + 1]) r++;
		if (temp >= s.data[r])
			break;
		else {
			s.data[begin] = s.data[r];
			begin = r;
		}
	}
	s.data[begin] = s.data[r];
}
void HeapSort(SqList<int>s) {
	for (int i = s.length / 2-1; i >= 0; i--) {
		HeapAdjust(s, i, s.length);
	}
	
	for (int i = s.length - 1; i > 0; i--) {
		int temp = s.data[0];
		s.data[0] = s.data[i];
		s.data[i] = temp;
		HeapAdjust(s, 0, i-1);
	}
}



//
//void HeapAdjust(SqList<int>s, int begin, int end) {
//	int rc = s.data[begin];
//	for (int i = begin * 2 ; i <= end; i = i * 2) {
//		if (i<end && s.data[i] < s.data[i + 1]) i++;
//		if (s.data[begin] >= s.data[i])
//			break;
//		else {
//			int temp = s.data[begin];//此种写法，在于每次begin初值对应元素在一轮筛选中就随其物理地址改变而赋值
//			s.data[begin] = s.data[i];
//			s.data[i] = temp;
//			begin = i;
//		}
//	}
//}