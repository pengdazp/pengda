//#include<iostream>
//using namespace std;
//class x {
//	double a;
//	int* c;
//};
//class a {
//public:
//	int b;
//	double c;
//	char* d;
//	x e;
//	a() {
//		cout << "默认构造函数" << endl;
//		this->c = 34;
//	}
//};
//int main() {
//	a a1;
//	a* b1 = (a*)malloc(sizeof(a));
//	a* b2 = new a;//当自定义类有手动添加的默认构造函数后，new会把构造函数中没有涉及的成员变量初始值递归都赋值为零，而malloc只是申请空间
//	system("pause");
//	return 0;
//}