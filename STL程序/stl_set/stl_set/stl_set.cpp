// stl_set.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
begin()		����set�����ĵ�һ��Ԫ�صĵ�ַ
end()		����set���������һ��Ԫ�ص�ַ
clear()		ɾ��set�����е����е�Ԫ��
empty()		�ж�set�����Ƿ�Ϊ��
max_size()	����set�������ܰ�����Ԫ��������
size()		���ص�ǰset�����е�Ԫ�ظ���
erase(it)   ɾ��������ָ��it��Ԫ��
find()      ����set��ĳ��Ԫ�س��ֵ�λ�á�����ҵ����ͷ������Ԫ�صĵ�������������Ԫ�ز����ڣ��򷵻� s.end
*/
int _tmain(int argc, _TCHAR* argv[])
{
	set<int> s0;				//��ʼ������set
	set<int> s1{1,1,2,2,3,6,23};//�б��ʼ��
	set<int> s2(s1);			//��ʼ������������
	int arry[4] = {1, 3, 7, 2};
	set<int> s3(arry, arry + 4);//��ʼ��������������
	
	
	s1.insert(s1.begin(), 10); //��ָ��iterator����Ԫ��
	s1.emplace(20);            //����Ԫ��
	set<int>::const_iterator ite = s1.find(20); //����
	int size = s1.size();      //set��С
	s1.swap(s2);               //set����

	return 0;
}

