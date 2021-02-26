// stl_vector.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>


using namespace std;


/*
��������
c.assign(beg,end)	  ��[beg; end)�����е����ݸ�ֵ��c��
c.assign(n,elem)	  ��n��elem�Ŀ�����ֵ��c�� 
c.at(idx)             ��������idx��ָ�����ݣ����idxԽ�磬�׳�out_of_range��
c.back()              �������һ�����ݣ��������������Ƿ���ڡ�
c.begin()			  ���ص������صĿ�һ�����ݡ�
c.capacity()		  �������������ݸ�����
c.clear()			  �Ƴ��������������ݡ�
c.empty()			  �ж������Ƿ�Ϊ�ա�
c.end()				  ָ��������е����һ�����ݵ�ַ��
c.erase(pos)		  ɾ��posλ�õ����ݣ�������һ�����ݵ�λ�á�
c.erase(beg,end)	  ɾ��[beg,end)��������ݣ�������һ�����ݵ�λ�á�
c.front()			  ���ص�һ�����ݡ�
get_allocator		  ʹ�ù��캯������һ��������
c.insert(pos,elem)	  ��posλ�ò���һ��elem����������������λ�á�
c.insert(pos,n,elem)  ��posλ�ò���n��elem���ݡ��޷���ֵ��
c.insert(pos,beg,end) ��posλ�ò�����[beg,end)��������ݡ��޷���ֵ��
c.insert(pos,initializer_list) ��posλ�ò���һ����ʼ���б�
c.max_size()		  ����������������ݵ�������
c.pop_back()		  ɾ�����һ�����ݡ�
c.push_back(elem)	  ��β������һ�����ݡ�
c.rbegin()			  ����һ��������еĵ�һ�����ݡ�
c.rend()			  ����һ��������е����һ�����ݵ���һ��λ�á�
c.resize(num)		  ����ָ�����еĳ��ȡ�
c.reserve()			  �����ʵ���������
c.size()			  ����������ʵ�����ݵĸ�����
c1.swap(c2)			  ��c1��c2Ԫ�ػ�����
swap(c1,c2)			  ͬ�ϲ�����
vector<Elem> c		  ����һ���յ�vector��
vector <Elem> c1(c2)  ����һ��vector��
vector <Elem> c(n)	  ����һ��vector������n�����ݣ����ݾ���ȱʡ���������
vector <Elem> c(n, elem)   ����һ������n��elem������vector��
vector <Elem> c(beg,end)   ����һ����[beg;end)�����vector��
c.~ vector <Elem>()		   �����������ݣ��ͷ��ڴ档
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
	cout<<"v1��ʼ����:";
	print_vector(v1);
	cout<<"v2��ʼ����:";
	print_vector(v2);

	cout<<"�������v2.assign(v1.begin(), v1.end())��"<<endl;
	v2.assign(v1.begin(), v1.end());  
	cout<<"v1:";
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);

	cout<<"�������v2.assign(v1.begin(),  v1.begin()+1)��"<<endl;
	v2.assign(v1.begin(), v1.begin()+1);  
	cout<<"v1:";
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);

	int& temp = v2.back();	 //back()���ص���һ������
	temp = 3;
	print_vector(v2);

	it = v1.end()- 1; 
	cout<<*it<<endl;
	it = v1.erase(it);	 //����������ã�����it����ΪҰָ��
	if(it == v1.end())
		cout<<"ɾ���������һ��Ԫ��"<<endl;
	else
		cout<<*it<<endl;
	it = v2.insert(v2.begin(), 5);
	cout<<*it<<endl;
	print_vector(v2);
	v2.insert(v2.begin()+1, 4, 88);
	print_vector(v2);
	v2.insert(v2.begin()+1, v1.begin(), v1.end());
	print_vector(v2);
	cout<<"��ǰv2.size() = "<<v2.size()<<endl;
	v2.pop_back();
	cout<<"ִ��v2.pop_back()֮��, v2.size() = "<<v2.size()<<endl;

	cout<<"����ָ��v2�ĳ���Ϊ40�����v2"<<endl;
	v2.resize(40);
	print_vector(v2);
	cout<<"����ָ��v2�ĳ���Ϊ6�����v2"<<endl;
	v2.resize(6);
	print_vector(v2);
	cout<<"����v2.resize(9, 5),���v2"<<endl;
	v2.resize(9, 5);
	print_vector(v2);

	cout<<"����v1.swap(v2)֮ǰ\nv1:";
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);

	cout<<"����v1.swap(v2)֮��\nv1:";
	v1.swap(v2);
	print_vector(v1);
	cout<<"v2:";
	print_vector(v2);



	return 0;
}

