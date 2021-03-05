// stl_list.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <list>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	list<int> lst0;			//��ʼ����������
	list<int> L1(9);		//��ʼ������9��Ԫ��
	list<int> L2(7, 3);		//��ʼ������7��Ԫ�أ�ȫ��������Ϊ3
	list<int> lst3(L2);		//�ñ�������ʼ��

	L1.assign(3, 4);					//���·���ֵ������3��Ԫ�أ�ֵȫ��Ϊ4
	L1.assign(L2.begin(), L2.end());	//���·���ֵ������������м��Ԫ��

	L1.erase(L1.begin());//����ɾ��Ԫ�أ���������ĵ�����

	L1.front() = 2;		//��ȡ&����������Ԫ��
	L1.back() = 2;		//��ȡ&����������Ԫ��	
	L1.push_back(6);	//����׷��Ԫ�أ�push_back׷����β��
	L1.push_back(7);	//����׷��Ԫ�أ�push_back׷����β��
	L1.remove(2);		//����ɾ��Ԫ�أ��������ΪԪ�ص�ֵ������ƥ�����ֵ��Ԫ�ض�����ɾ��
	L1.remove_if([](int v) -> bool { return v >= 6 && v <= 7; });//����ɾ��Ԫ�أ��Զ�����ʽ/����������ƥ���Ԫ�ض�����ɾ��

	int Size = L1.size(); //��������Ԫ�ظ���
	L1.pop_front();		  //ɾ����Ԫ��
	L1.pop_back();        //ɾ��βԪ��
	L2.clear();			  //�ÿգ���ɾ������Ԫ��
	L1.reverse();		  //����ת
	
	L1.sort(greater<int>());//��������
	L2.sort();				//��������Ĭ�����򣬼�����<����

	L1.sort();L1.merge(L2);	//����ϲ��������򣬺ϲ���L2��գ�Ҫ��L1����<���򣬷��򱨴�

	L2.push_back(8);
	list<int>::iterator iterator2 = L2.begin(); 
	L2.splice(iterator2,L1);			  //�����и��ָ����λ�ò��������������������������Ϊ�գ�������iterator2ָ��δ�䣬����ָ��8
	L1.splice(L1.begin(), L2, L2.begin());//�����и��ָ��λ��������������ĵ�����ָ���ֵ��������������ֵ���г�	 	

	
	L2.insert(L2.begin(), L2.begin(), L2.end());//������룬����������ĵ�������Χ
	L2.swap(L1);//������



	L1.unique();  //ɾ�������ظ�Ԫ��

	return 0;
}

