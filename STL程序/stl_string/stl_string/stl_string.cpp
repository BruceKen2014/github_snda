// stl_string.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include<string>

using namespace std;


#define TRAN(str)  #str
   
template<typename T>
void print_string(char* ch, const T& str)
{
	cout<<ch<<":"<<str<<endl;
}
template<typename T>
void print_string_no_name(const char* ch, const T& str)
{
	cout<<str<<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	string str1("this is the first try string !");
	cout<<"�������string st1(\"this is the first try string !\");���캯���½�һ��string str1\n";
	print_string("str1", str1);
	string str2(10, 'q');
	cout<<"�������string str2(10, 'q');���캯���½�һ��string str2\n";
	print_string("str2", str2);
	string str3 = "copy instructer";
	cout<<"�������string str3 = \"copy instructer\";�½�һ��string str3\n";
	print_string("str3", str3);
	cout<<"string֧���±���ʣ�str1[2]����str1�ַ����е������ַ�";
	cout<<str1[2]<<endl;
	cout<<"str1.at(2)������str[2]һ����ȡ��"<<str1.at(2)<<endl;
	char* ch1 = (char *)str1.c_str();
	cout<<"�������char* ch1 = (char *)str1.c_str();ȡ��C����ַ���ch1\n";
	print_string("ch1", ch1);
	const char* ch2 = str1.data();
	cout<<"�������char* ch2 = (char *)str1.data();ȡ��C����ַ���ch2\n";
	print_string("ch2", ch2);
	cout<<"��ʱstrlen(chr)="<<strlen(ch1)<<" strlen(ch2)="<<strlen(ch2)<<endl;
	char* ch3 = new char[32];
	memset(ch3, 0, 32);
	int temp1;
	temp1 = str1.copy(ch3, str1.length());
	cout<<"�������temp1 = str1.copy(ch3, str1.length());���п���\n";
	cout<<"ʵ�ʿ�����temp1:"<<temp1<<"���ַ�\n";
	print_string("ch3", ch3);
	cout<<"str1.length() = "<<str1.length()<<",str1.size() = "<<str1.size()<<endl;
	cout<<"�������str1.resize(50, 'g');\n";
	str1.resize(50, 'g');
	print_string("str1", str1);
	cout<<"�������str1.resize(25, 'g');\n";
	str1.resize(25, 'g');
	print_string("str1", str1);
	cout<<"�������getline(cin, str1);\n";
	getline(cin, str1);
	print_string("str1", str1);
	cout<<"�������str1.assign(\"new string ~\"); ���¸�str1��ֵ\n";
	str1.assign("new string ~");
	print_string("str1", str1);
	cout<<"�������str1.assign(\"new string ~\", 6); ���¸�str1��ֵ\n";
	str1.assign("new string ~", 6);
	print_string("str1", str1);
	cout<<"�������str1.assign(string(\"another new string ~\")); ���¸�str1��ֵ\n";
	str1.assign(string("another new string ~"));
	print_string("str1", str1);
	cout<<"�������str1.assign(string(\"another new string ~\"), 2, 10); ���¸�str1��ֵ\n";
	str1.assign(string("another new string ~"), 2, 10);
	print_string("str1", str1);
	cout<<"������� str1 = str1 + str2"<<endl;
	str1 = str1 + str2;
	print_string("str1", str1);
	cout<<"Ч����ͬ str1 += str2;\n";
	cout<<"�������str1.append(\"append char*\");��������"<<endl;
	str1.append("append char*");
	print_string("str1", str1);
	cout<<"�������str1.append(\" the second append char*\", 15);��������"<<endl;
	str1.append(" the second append char*", 15);
	print_string("str1", str1);
	cout<<"�������str1.append(string(\" the third append char*\", 3, 10);��������"<<endl;
	str1.append(string(" the third append char*"), 3, 10);
	print_string("str1", str1);
	cout<<"�������str1.append(5, 'l');�������"<<endl;
	str1.append(5, 'l');
	print_string("str1", str1);
	cout<<"str1 == str2? �����";
	cout<<(str1 == str2 ? "���" : "�����")<<endl;
	cout<<"str1.compare(str3),����"<<str1.compare(str3)<<endl;
	cout<<"str1.compare(\"compare string\"),����"<<str1.compare("compare string")<<endl;
	cout<<"str1.compare(\"tcompare string\"),����"<<str1.compare("tcompare string")<<endl;
	cout<<"�������str1.substr(5, 10);����str1��λ��5��ʼ������Ϊ10�����ַ�����"<<str1.substr(5, 10)<<endl;
	str1.swap(str2);
	cout<<"�������str1.swap(str2);�����ַ����Ľ���\n";
	print_string("str1", str1);
	print_string("str2", str2);
	cout<<"�������str1.find('d');�����ַ�d��str1��һ�γ��ֵ�λ�ã�";
	cout<<str1.find('d')<<"\n";
	cout<<"�������str2.find('a');�����ַ�a��str2��һ�γ��ֵ�λ�ã�";
	cout<<str2.find('a')<<"\n";
	cout<<"�������str2.find(\"aa\");�����ַ���aa��str2��һ�γ��ֵ�λ�ã�";
	cout<<str2.find("aa")<<"\n";
	cout<<"�������str2.find(string(\"qq\"));�����ַ���aa��str2��һ�γ��ֵ�λ�ã�";
	cout<<str2.find(string("qq"))<<"\n";
	cout<<"�������str2.replace(2, 4,\"Bruce\");�����滻"<<endl;
	str2.replace(2, 4,"Bruce");
	print_string("str2", str2);
	cout<<"�������str2.replace(2, 4,\"Bruce\", 4);�����滻"<<endl;
	str2.replace(2, 5,"Bruce", 4);
	print_string("str2", str2);
	cout<<"�������str2.replace(2, 4, 5, 'G');�����滻"<<endl;
	str2.replace(2, 5, 5, 'G');
	print_string("str2", str2);
	cout<<"�������str2.insert(2, \"server\");���в���"<<endl;
	str2.insert(2, "server");
	print_string("str2", str2);
	cout<<"�������str2.insert(2, \"client\", 5);���в���"<<endl;
	str2.insert(2, "client", 5);
	print_string("str2", str2);
	cout<<"�������str2.insert(2, 5, 't');���в���"<<endl;
	str2.insert(2, 5, 't');
	print_string("str2", str2);
	cout<<"�������str2.erase(2, 20);����ɾ��"<<endl;
	str2.erase(2, 20);
	print_string("str2", str2);
	//strlen()
	return 0;
}

