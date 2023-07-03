//#include<iostream>
////要给一个模板类取别名  用typedef 不行，要用using
//template<typename AtomType>
//class A {
//public:
//	AtomType a;
//};
////下面这种方法不行
////template<typename AtomType>
////typedef A<AtomType>* Atom1;  //typedef A<AtomType> Atom2;
//template<typename AtomType>
//using  Atom1 = A<AtomType>*;
//template<typename AtomType>
//using  Atom2 = A<AtomType>;
