// stl_list.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	list<int> lst0;			//初始化，空链表
	list<int> L1(9);		//初始化，有9个元素
	list<int> L2(7, 3);		//初始化，有7个元素，全部用设置为3
	list<int> lst3(L2);		//用别的链表初始化

	L1.assign(3, 4);					//重新分配值，包含3个元素，值全设为4
	L1.assign(L2.begin(), L2.end());	//重新分配值，链表迭代器中间的元素

	L1.erase(L1.begin());//链表删除元素，传入参数的迭代器

	L1.front() = 2;		//获取&设置链表首元素
	L1.back() = 2;		//获取&设置链表首元素	
	L1.push_back(6);	//链表追加元素，push_back追加在尾部
	L1.push_back(7);	//链表追加元素，push_back追加在尾部
	L1.remove(2);		//链表删除元素，传入参数为元素的值，所有匹配这个值的元素都将被删除
	L1.remove_if([](int v) -> bool { return v >= 6 && v <= 7; });//链表删除元素，自定义表达式/函数，所有匹配的元素都将被删除

	int Size = L1.size(); //返回链表元素个数
	L1.pop_front();		  //删除首元素
	L1.pop_back();        //删除尾元素
	L2.clear();			  //置空，即删除所有元素
	L1.reverse();		  //链表翻转
	
	L1.sort(greater<int>());//链表排序
	L2.sort();				//链表排序，默认升序，即按照<排序

	L1.sort();L1.merge(L2);	//链表合并，并排序，合并后L2清空，要求L1必须<有序，否则报错

	L2.push_back(8);
	list<int>::iterator iterator2 = L2.begin(); 
	L2.splice(iterator2,L1);			  //链表切割，在指定的位置插入其他链表，插入后其他链表置为空，操作后iterator2指向并未变，还是指的8
	L1.splice(L1.begin(), L2, L2.begin());//链表切割，在指定位置切入其他链表的迭代器指向的值，其他链表的这个值被切除	 	

	
	L2.insert(L2.begin(), L2.begin(), L2.end());//链表插入，用其他链表的迭代器范围
	L2.swap(L1);//链表交换



	L1.unique();  //删除相邻重复元素

	return 0;
}

