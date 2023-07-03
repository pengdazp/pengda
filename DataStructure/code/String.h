#pragma once
class String {
public:
	char* ch;
	int length;
	char& operator[](int i) {
		return ch[i];
	}
	String& operator=(String &s) {
		if (this->ch!= NULL && (unsigned long long)this->ch != 0xcdcdcdcdcdcdcdcd)
			delete[] this->ch;
		this->ch = new char[s.length];
		this->length = s.length;
		for (int i = s.length; i-1 >= 0; i--)
			this->ch[i-1] = s.ch[i-1];
		return *this;
	}
	String& operator=(const char* s) {
		int i = 0;
		for (; s[i] != '\0'; i++);
		if (this->ch)
			delete[] this->ch;
		this->ch = new char[i];
		for (; i-1 > 0; i--)
			this->ch[i-1] = s[i-1];
		this->length = i;
		return *this;
	}
	String(const char* s) {
		int i = 0;
		for (; s[i] != '\0'; i++);
		this->ch = new char[i];
		this->length = i;
		for (; i - 1 >= 0; i--)
			this->ch[i - 1] = s[i - 1];
	}
	String(int n) {
		this->ch = new char[n];
		this->length = n;
	}
	String(const String& s) { //拷贝构造函数
		this->ch = new char[s.length];
		this->length = s.length;
		for (int i = s.length; i - 1 >= 0; i--)
			this->ch[i - 1] = s.ch[i - 1];
	}
	String() {
		this->ch = NULL;
		this->length = 0;
	}
	~String() {
		if (this->ch)
			delete[] ch;
	}
};
//比较两个字符串，相同返回true不同返回false;
bool StrCompare(String s1,String s2) {
	if (s1.length != s2.length)
		return false;
	int len = s1.length;
	while (len+1) {
		if (s1.ch[len - 1] == s2.ch[len - 1]) {
			len--;
			continue;
		}
		else
			return false;
	}
	return true;
}
//通过一个字符数组('\0'结束)注册一个字符串
bool AssignString(String &s,char*c,int n) {
	s.ch = new char[n];
	for (; n != 0; n--)
		s.ch[n-1] = c[n-1];
	s.length = n;
	return true;
}
//为字符串申请长度为n的字符长度
bool AssignString(String& s, int n) {
	s.ch = new char[n];
	s.length = n;
	return true;
}
