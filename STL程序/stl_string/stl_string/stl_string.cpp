// stl_string.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<string>

using namespace std;

/*
	string str = to_string(int);	//��������������ת��Ϊstring
	int = stoi(string);				//��stringת��Ϊ������������
*/

#define TRAN(str)  #str
   

int _tmain(int argc, _TCHAR* argv[])
{
	//��ʼ��string
	string str1("this is the first try string !");
	string str2(10, 'q');
	string str3 = "copy instructer";

	//�±�����ַ�
	auto c1 = str1[2];
	auto c2 = str1.at(2);

	//ȡ��char* 
	char* ch1 = (char *)str1.c_str();
	const char* ch2 = str1.data();

	//��str1�����ิ��n���ַ����ַ�ָ��ch3ָ��Ŀռ���
	char* ch3 = new char[32];
	memset(ch3, 0, 32);
	int temp1;
	temp1 = str1.copy(ch3, str1.length());

	//string��С
	int length = str1.length();
	int size = str1.size();

	//�����С������Ŀռ����ַ���䣬�������������ԭ�������ݣ�ֻҪresize�Ĵ�СС��ԭ���Ŀռ䣬�Ż�Զ�����ַ����ж���
	str1.resize(50, 'g');
	str1.resize(10, 'g');

	//cin ��ȡ��string
	getline(cin, str1);

	//assign���¸�ֵ��ע�������¸��ƣ�������׷��
	str1.assign("new string ~");
	str1.assign("new string ~", 6); //����6���ַ�
	str1.assign(string("another new string ~"));
	str1.assign(string("another new string ~"), 2, 10); //�Ӳ����ĵ�2��λ�ÿ�ʼ����ֵ10���ַ�

	//string�������
	str1 = str1 + str2;

	//append׷������
	str1.append("append char*");
	str1.append(" the second append char*", 15);
	str1.append(string(" the third append char*"), 3, 10);
	str1.append(5, 'l');

	//string�ж��Ƿ����
	bool equal = str1 == str2;
	bool equal2 = str1.compare(str3)==0;
	
	//���ַ�������λ��5��ʼ������Ϊ10�����ַ���
	string sub_str = str1.substr(5, 10);

	//swap����string����
	str1.swap(str2);

	//�����ַ�
	auto c_index = str1.find('d');
	if (c_index != str1.npos)
	{
		//�ҵ�
	}

	//�����ַ���
	auto str_index = str2.find("aa");
	if (str_index != str1.npos)
	{
		//�ҵ�
	}

	//replace�滻
	str2.replace(2, 4,"Bruce");
	str2.replace(2, 5,"Bruce", 4);
	str2.replace(2, 5, 5, 'G');

	//insert
	str2.insert(2, "server");    //��2��index�����ַ���
	str2.insert(2, "client", 5); //��2��index�����ַ����е�ǰ5���ַ���
	str2.insert(2, 5, 't');		 //��2��index����5���ַ�
	
	//erase
	str2.erase(2, 20); //��2��indexɾ��20���ַ�

	//�����������ͺ�string����ת��
	int Int1 = 100;
	string NumStr = to_string(Int1);
	Int1 = stoi(NumStr);
	return 0;
}

