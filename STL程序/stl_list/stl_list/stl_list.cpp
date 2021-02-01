// stl_list.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <list>

using namespace std;

template<typename T>
void print_list(list<T> lst)
{
	for(list<T>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

template<typename T>
void oppo_print(list<T> lst)
{
	cout<<"�������:";
	for(list<T>::reverse_iterator it = lst.rbegin(); it != lst.rend(); it++)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	list<int> lst1(9);
	list<int> lst2(7, 3);
	list<int> lst3(lst2);
	cout<<"lst1:";
	print_list(lst1);
	cout<<"lst2:";
	print_list(lst2);
	cout<<"lst3:";
	print_list(lst3);

	cout<<"����lst1.assign(3,4)֮ǰ,��ӡlst1����"<<endl;
	print_list(lst1);
	cout<<"����lst1.assign(3,4)֮��,lst1:"<<endl;
	lst1.assign(3,4);
	print_list(lst1);

	cout<<"�������lst1.assign(lst2.begin(), lst2.end())֮��";
	lst1.assign(lst2.begin(), lst2.end());
	cout<<"\nlst1:";
	print_list(lst1);
	lst1.front() = 12;
	print_list(lst1);
	oppo_print(lst1);

	cout<<*(lst1.erase(lst1.begin()))<<endl;
	print_list(lst1);
	lst1.remove(2);
	cout<<"����lst1.reverse()��ת֮ǰ\nlst1:";
	lst1.push_back(6);
	lst1.push_back(9);
	print_list(lst1);
	cout<<"����lst1.reverse()��ת֮��\nlst1:";
	lst1.reverse();
	print_list(lst1);
	cout<<"����st1.sort()֮��\n";
	lst1.sort(greater<int>());
	cout<<"lst1:";
	print_list(lst1);
	cout<<"lst2:";
	print_list(lst2);
	lst1.sort();
	lst2.sort();
	cout<<"����lst1.merge(lst2)֮��"<<endl;
	lst1.merge(lst2);
	cout<<"lst1:";
	print_list(lst1);
	cout<<"lst2:";
	print_list(lst2);
	cout<<"�������lst2.splice(lst2.begin(),lst1)"<<endl;
	list<int>::iterator iterator2 = lst2.begin(); 
	lst2.splice(iterator2,lst1);  //iterator2ָ��δ�䣬��ʱ��Ȼlst2��Ԫ���ˣ���iterator2����ָ��β��
	cout<<"lst1:";
	print_list(lst1);
	cout<<"lst2:";
	print_list(lst2);
	cout<<"�������lst1.splice(lst1.begin(),lst2, lst2.begin()֮��"<<endl;
	lst1.splice(lst1.begin(),lst2, lst2.begin());	 
	cout<<"lst1:";
	print_list(lst1);
	cout<<"lst2:";
	print_list(lst2);   
	cout<<"�������lst2.insert(lst2.begin(), lst2.begin(), lst2.end())֮��"<<endl;
	lst2.insert(lst2.begin(), lst2.begin(), lst2.end());
	print_list(lst2);
	cout<<"�������print_list(lst2)֮��"<<endl;
	lst2.swap(lst1);
	cout<<"lst1:";
	print_list(lst1);
	cout<<"lst2:";
	print_list(lst2);  

	cout<<"�������lst1.unique()֮��"<<endl;
	lst1.unique();
	cout<<"lst1:";
	print_list(lst1);

	return 0;
}

