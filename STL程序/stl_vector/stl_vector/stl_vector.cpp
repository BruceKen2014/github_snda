// stl_vector.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;


/*
��������
c.assign(beg,end)	  ��[beg; end)�����е����ݸ�ֵ��c��
c.assign(n,elem)	  ��n��elem�Ŀ�����ֵ��c�� 
c.at(idx)             ��������idx��ָ�����ݣ����idxԽ�磬�׳�out_of_range��
c.back()              �������һ�����ݣ��������������Ƿ���ڡ�
c.begin()			  ���ص������صĿ�һ�����ݡ�
c.capacity()		  �����������ܹ����ɵ����ݸ�������size��һ������
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
c.reserve(num)		  Ԥ������ָ�����������������������ʵ�ֿ���һ��������n��Ԫ�ص��ڴ棬�����ʱ��û�е���Ԫ�ع��캯����
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

	//vector��ʼ��
	vector<int> v1;//��vector
	vector<int> v2 {10, 50, 30, 40, 66, 88}; //��ʼ���б�
	vector<int> v3 = {60, 20, 90}; //��ʼ���б�
	vector<int> v4(v2);   //��������
	vector<int> v5 = v2;  //��������
	vector<int> v6(6);    //vector������6��int��Ĭ��Ϊ0
	vector<int> v7(6,8);  //vector������6��8
	vector<int> v8(v2.begin(), v2.begin() + 3);//�ñ��vector����������

	//vector���Ԫ��push_back
	v2.push_back(36);	 

	//���ң�����findȫ�ֺ���
	vector<int>::iterator ite = find(v2.begin(), v2.end(), 20);

	//�˻ض��������Ŀռ�
	v2.shrink_to_fit();

	//vector����
	sort(v2.begin(), v2.end(), [](int a, int b) -> bool { return a > b; });
	
	int size = v2.size();		  //vector��С
	int capacity = v2.capacity(); //vector������Ŀռ�
	//assign��ֵ
	v2.assign(v3.begin(), v3.end());
	v2.assign(v1.begin(), v1.begin()+1);  

	v2.back() = 3;	 //back()���ص���һ������
	v2.front() = 12;

	//ɾ��Ԫ��
	vector<int>::iterator it = v1.end()- 1;
	it = v1.erase(it);	 //����������ã�����it����ΪҰָ��
	if(it == v1.end())
		cout<<"ɾ���������һ��Ԫ��"<<endl;

	//ɾ��ָ��index��Ԫ�أ�ͨ��index���������ָ��
	v2.erase(v2.begin() + 3);

	//��ָ����iterator������Ԫ��
	it = v2.insert(v2.begin(), 5);
	v2.insert(v2.begin()+1, 4, 88);		//����4��88
	v2.insert(v2.begin()+1, v1.begin(), v1.end());

	//ɾ�������������һ��Ԫ��
	v2.pop_back();
	
	v2.resize(40);	//����ָ��v2�ĳ���Ϊ40
	v2.resize(9, 5);//����ָ��v2�ĳ���Ϊ9

	//���齻��
	v1.swap(v2);



	return 0;
}

