//template<typename ElemType>
//bool MakeLNode(LNode<ElemType>*& p, ElemType e = ElemType()) { 此处使用了显示赋值的方法，把任何一个系统类型赋值为默认值（一般是0），把自定义类型按照其无参构造，构造一个类型赋值给e。如此并实现了e不管是什么类型，如果不传入参数，都有一个默认值。int a = int (3);系统类型都有类似如此的赋值方式
//	p = (LNode<ElemType>*)malloc(sizeof(LNode<ElemType>));
//	if (!p)
//		return false;
//	p->data = e;
//	p->next = NULL;
//	return true;
//}

