//#include<cstdlib>
//typedef struct HTNode {
//	unsigned int weight;
//	unsigned int parent, rChild, lChild;
//}*HuffmanTree;
//typedef char** HuffmanCod;
//
//void Select(HuffmanTree &ht,int i,int n1,int n2) {
//
//}
//
////hc为哈夫曼编码数组，ht为哈夫曼树未初始化，int为哈夫曼编码数组每个元素对应的数对应的权值
//bool HuffmanCoding(HuffmanTree& ht, HuffmanCod& hc, unsigned int* w, int n) {
//	if (n <= 1)
//		return false;
//	unsigned int m = 2 * n - 1;
//	ht = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));
//	HuffmanTree p = ht + 1;
//	int i;
//	for (i = 1; i <= n; i++, p++)
//		*p = { w[i],0,0,0 };
//	for (; i <= m; i++, p++)
//		*p = { 0,0,0,0 };
//	int n1, n2;
//	for (i = n + 1; i <= m; i++) {
//		Select(ht, i - 1, n1, n2);
//		ht[n1].parent = i;
//		ht[n2].parent = i;
//		ht[i].lChild = n1;
//		ht[i].rChild = n2;
//		ht[i].weight = ht[n1].weight + ht[n2].weight;
//	}
//
//}