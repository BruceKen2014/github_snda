// stl_set.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
begin()		返回set容器的第一个元素的地址
end()		返回set容器的最后一个元素地址
clear()		删除set容器中的所有的元素
empty()		判断set容器是否为空
max_size()	返回set容器可能包含的元素最大个数
size()		返回当前set容器中的元素个数
erase(it)   删除迭代器指针it处元素
find()      查找set中某个元素出现的位置。如果找到，就返回这个元素的迭代器，如果这个元素不存在，则返回 s.end
*/
int _tmain(int argc, _TCHAR* argv[])
{
	set<int> s0;				//初始化，空set
	set<int> s1{1,1,2,2,3,6,23};//列表初始化
	set<int> s2(s1);			//初始化，拷贝构造
	int arry[4] = {1, 3, 7, 2};
	set<int> s3(arry, arry + 4);//初始化，迭代器构造
	
	
	s1.insert(s1.begin(), 10); //在指定iterator插入元素
	s1.emplace(20);            //插入元素
	set<int>::const_iterator ite = s1.find(20); //查找
	int size = s1.size();      //set大小
	s1.swap(s2);               //set交换

	return 0;
}

