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
//	bool (Human:: * visit)() = &Human::Visit_High; //声明指向类的成员函数的指针
//	Human h;
//	h.high = 178;
//	//通过 . 找到类的函数指针成员，并为其赋值后，通过这个成员调用函数 
//	h.p = a;
//	h.p();
//	//h.(*p)(); //在点号后应该是成员名，所以使用(*p)()这种先对函数指针解引用在调用的方法不行
//	(h.*visit)();//通过类成员函数的指针visit调用h这个实例对应的visit所指向的类成员函数，目前只有这么一种写法。
//	bool (Human:: * visit2)() = visit;
//	(h.*visit2)();
//	//h.visit();  不行
//	//h.(*visit)();  不行
//	system("pause");
//	return 0;
//}