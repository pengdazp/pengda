//#pragma once
//#include<iostream>
//using namespace std;
//
//class Human {
//public:
//	int (*p)();
//	int high;
//	bool Visit_High() {
//		cout << high << endl;
//		return true;
//	}
//	bool Add_High() {
//		high++;
//		cout << high << endl;
//		return true;
//	}
//};
//int a() {
//	cout << "a" << endl;
//	return 34;
//}
//int main() {
//	bool (Human:: * visit)() = &Human::Visit_High; //����ָ����ĳ�Ա������ָ��
//	Human h;
//	h.high = 178;
//	//ͨ�� . �ҵ���ĺ���ָ���Ա����Ϊ�丳ֵ��ͨ�������Ա���ú��� 
//	h.p = a;
//	h.p();
//	//h.(*p)(); //�ڵ�ź�Ӧ���ǳ�Ա��������ʹ��(*p)()�����ȶԺ���ָ��������ڵ��õķ�������
//	(h.*visit)();//ͨ�����Ա������ָ��visit����h���ʵ����Ӧ��visit��ָ������Ա������Ŀǰֻ����ôһ��д����
//	bool (Human:: * visit2)() = visit;
//	(h.*visit2)();
//	//h.visit();  ����
//	//h.(*visit)();  ����
//	system("pause");
//	return 0;
//}