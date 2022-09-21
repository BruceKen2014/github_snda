// stl_vector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


/*
基本函数
c.assign(beg,end)	  将[beg; end)区间中的数据赋值给c。
c.assign(n,elem)	  将n个elem的拷贝赋值给c。 
c.at(idx)             传回索引idx所指的数据，如果idx越界，抛出out_of_range。
c.back()              传回最后一个数据，不检查这个数据是否存在。
c.begin()			  传回迭代器重的可一个数据。
c.capacity()		  返回容器中能够容纳的数据个数（和size不一样）。
c.clear()			  移除容器中所有数据。
c.empty()			  判断容器是否为空。
c.end()				  指向迭代器中的最后一个数据地址。
c.erase(pos)		  删除pos位置的数据，传回下一个数据的位置。
c.erase(beg,end)	  删除[beg,end)区间的数据，传回下一个数据的位置。
c.front()			  传回第一个数据。
get_allocator		  使用构造函数返回一个拷贝。
c.insert(pos,elem)	  在pos位置插入一个elem拷贝，传回新数据位置。
c.insert(pos,n,elem)  在pos位置插入n个elem数据。无返回值。
c.insert(pos,beg,end) 在pos位置插入在[beg,end)区间的数据。无返回值。
c.insert(pos,initializer_list) 在pos位置插入一个初始化列表
c.max_size()		  返回容器中最大数据的数量。
c.pop_back()		  删除最后一个数据。
c.push_back(elem)	  在尾部加入一个数据。
c.rbegin()			  传回一个逆向队列的第一个数据。
c.rend()			  传回一个逆向队列的最后一个数据的下一个位置。
c.resize(num)		  重新指定队列的长度。
c.reserve(num)		  预先申请指定个数的容量。这个函数会实现开辟一块连续的n个元素的内存，但这个时候并没有调用元素构造函数。
c.size()			  返回容器中实际数据的个数。
c1.swap(c2)			  将c1和c2元素互换。
swap(c1,c2)			  同上操作。
vector<Elem> c		  创建一个空的vector。
vector <Elem> c1(c2)  复制一个vector。
vector <Elem> c(n)	  创建一个vector，含有n个数据，数据均已缺省构造产生。
vector <Elem> c(n, elem)   创建一个含有n个elem拷贝的vector。
vector <Elem> c(beg,end)   创建一个以[beg;end)区间的vector。
c.~ vector <Elem>()		   销毁所有数据，释放内存。
*/
template<typename T>
void print_vector(vector<T> &vec)
{
	for(size_t i = 0; i < vec.size(); i++)
		cout<<vec[i]<<" ";
	cout<<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{

	//vector初始化
	vector<int> v1;//空vector
	vector<int> v2 {10, 50, 30, 40, 66, 88}; //初始化列表
	vector<int> v3 = {60, 20, 90}; //初始化列表
	vector<int> v4(v2);   //拷贝构造
	vector<int> v5 = v2;  //拷贝构造
	vector<int> v6(6);    //vector包含了6个int。默认为0
	vector<int> v7(6,8);  //vector包含了6个8
	vector<int> v8(v2.begin(), v2.begin() + 3);//用别的vector迭代器构造

	//vector添加元素push_back
	v2.push_back(36);	 

	//查找，调用find全局函数
	vector<int>::iterator ite = find(v2.begin(), v2.end(), 20);

	//退回多余的申请的空间
	v2.shrink_to_fit();

	//vector排序
	sort(v2.begin(), v2.end(), [](int a, int b) -> bool { return a > b; });
	
	int size = v2.size();		  //vector大小
	int capacity = v2.capacity(); //vector已申请的空间
	//assign赋值
	v2.assign(v3.begin(), v3.end());
	v2.assign(v1.begin(), v1.begin()+1);  

	v2.back() = 3;	 //back()返回的是一个引用
	v2.front() = 12;

	//删除元素
	vector<int>::iterator it = v1.end()- 1;
	it = v1.erase(it);	 //该语句必须调用，否则it会沦为野指针
	if(it == v1.end())
		cout<<"删除的是最后一个元素"<<endl;

	//删除指定index的元素，通过index构造迭代器指针
	v2.erase(v2.begin() + 3);

	//在指定的iterator处插入元素
	it = v2.insert(v2.begin(), 5);
	v2.insert(v2.begin()+1, 4, 88);		//插入4个88
	v2.insert(v2.begin()+1, v1.begin(), v1.end());

	//删除（弹出）最后一个元素
	v2.pop_back();
	
	v2.resize(40);	//重新指定v2的长度为40
	v2.resize(9, 5);//重新指定v2的长度为9

	//数组交换
	v1.swap(v2);



	return 0;
}

