// stl_vector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>


using namespace std;


/*
基本函数
c.assign(beg,end)	  将[beg; end)区间中的数据赋值给c。
c.assign(n,elem)	  将n个elem的拷贝赋值给c。 
c.at(idx)             传回索引idx所指的数据，如果idx越界，抛出out_of_range。
c.back()              传回最后一个数据，不检查这个数据是否存在。
c.begin()			  传回迭代器重的可一个数据。
c.capacity()		  返回容器中数据个数。
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
c.reserve()			  保留适当的容量。
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
	vector<int> v1;
	vector<int> v2;
	vector<int>::iterator it;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v2 = v1;

	v2.push_back(50);
	v2.push_back(70);
	v2.push_back(80);
	v2.push_back(90);
	cout<<"v1初始数据:";
	print_vector(v1);
	cout<<"v2初始数据:";
	print_vector(v2);

	cout<<"调用语句v2.assign(v1.begin(), v1.end())后"<<endl;
	v2.assign(v1.begin(), v1.end());  
	cout<<"v1:";
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);

	cout<<"调用语句v2.assign(v1.begin(),  v1.begin()+1)后"<<endl;
	v2.assign(v1.begin(), v1.begin()+1);  
	cout<<"v1:";
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);

	int& temp = v2.back();	 //back()返回的是一个引用
	temp = 3;
	print_vector(v2);

	it = v1.end()- 1; 
	cout<<*it<<endl;
	it = v1.erase(it);	 //该语句必须调用，否则it会沦为野指针
	if(it == v1.end())
		cout<<"删除的是最后一个元素"<<endl;
	else
		cout<<*it<<endl;
	it = v2.insert(v2.begin(), 5);
	cout<<*it<<endl;
	print_vector(v2);
	v2.insert(v2.begin()+1, 4, 88);
	print_vector(v2);
	v2.insert(v2.begin()+1, v1.begin(), v1.end());
	print_vector(v2);
	cout<<"当前v2.size() = "<<v2.size()<<endl;
	v2.pop_back();
	cout<<"执行v2.pop_back()之后, v2.size() = "<<v2.size()<<endl;

	cout<<"重新指定v2的长度为40，输出v2"<<endl;
	v2.resize(40);
	print_vector(v2);
	cout<<"重新指定v2的长度为6，输出v2"<<endl;
	v2.resize(6);
	print_vector(v2);
	cout<<"调用v2.resize(9, 5),输出v2"<<endl;
	v2.resize(9, 5);
	print_vector(v2);

	cout<<"调用v1.swap(v2)之前\nv1:";
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);

	cout<<"调用v1.swap(v2)之后\nv1:";
	v1.swap(v2);
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);



	return 0;
}

