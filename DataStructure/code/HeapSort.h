#pragma once
#include"SqList.h"
//�󶥶�   
void HeapAdjust(SqList<int>s, int begin, int end) {
	int temp = s.data[begin];//�˴�����д�� ������begin����ֵȥɸѡ��ʱ�򣬲���ÿһ��ɸѡ��Ҫ�ı��ʼbegin��λ��
	int r;					 //----��Ϊ��һֱ�ڱ�λ�á������ȷ����ͨ��17����ȷ������ֵ
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
//			int temp = s.data[begin];//����д��������ÿ��begin��ֵ��ӦԪ����һ��ɸѡ�о����������ַ�ı����ֵ
//			s.data[begin] = s.data[i];
//			s.data[i] = temp;
//			begin = i;
//		}
//	}
//}