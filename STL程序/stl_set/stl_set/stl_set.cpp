// stl_set.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

template<typename T>
void print_set(const char* name, set<T> sset)
{
	cout<<name<<":"<<endl;
	for(set<T>::iterator it = sset.begin(); it != sset.end(); it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"welcome, boy!这是测试set用法的程序"<<endl;
	cout<<"set四种初始化方式"<<endl;
	cout<<"第一种：set<int> set1"<<endl;
	set<int> set1;
	print_set("set1", set1);
	cout<<"第二种：拷贝构造 set<int> set2(set1)"<<endl;
	set<int> set2(set1);
	print_set("set2", set2);
	int arry[4] = {1, 3, 7, 2};
	set<int> set3(arry, arry + 4);
	cout<<"第三种：迭代器赋初值set<int> set3(arry, arry + 4)"<<endl;
	print_set("set3", set3);
	return 0;
}

