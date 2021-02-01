// stl_set.cpp : �������̨Ӧ�ó������ڵ㡣
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
	cout<<"welcome, boy!���ǲ���set�÷��ĳ���"<<endl;
	cout<<"set���ֳ�ʼ����ʽ"<<endl;
	cout<<"��һ�֣�set<int> set1"<<endl;
	set<int> set1;
	print_set("set1", set1);
	cout<<"�ڶ��֣��������� set<int> set2(set1)"<<endl;
	set<int> set2(set1);
	print_set("set2", set2);
	int arry[4] = {1, 3, 7, 2};
	set<int> set3(arry, arry + 4);
	cout<<"�����֣�����������ֵset<int> set3(arry, arry + 4)"<<endl;
	print_set("set3", set3);
	return 0;
}

