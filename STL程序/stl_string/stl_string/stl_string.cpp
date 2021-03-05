// stl_string.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<string>

using namespace std;

/*
	string str = to_string(int);	//将基础数据类型转换为string
	int = stoi(string);				//将string转换为基础数据类型
*/

#define TRAN(str)  #str
   

int _tmain(int argc, _TCHAR* argv[])
{
	//初始化string
	string str1("this is the first try string !");
	string str2(10, 'q');
	string str3 = "copy instructer";
	const char* c_str = "const char* ";
	string str4(c_str, 3);	 //c_str的前3个字符赋值给str4
	string str5(str3, 2);	 //将str3从第2个index开始的字符串赋值给str5
	string str6(str3, 2, 5); //将str3从第2个index开始的5个字符串赋值给str6


	//下标访问字符
	auto c1 = str1[2];
	auto c2 = str1.at(2);

	//取得char* 
	char* ch1 = (char *)str1.c_str();
	const char* ch2 = str1.data();

	//从str1中至多复制n个字符到字符指针ch3指向的空间中
	char* ch3 = new char[32];
	memset(ch3, 0, 32);
	int temp1;
	temp1 = str1.copy(ch3, str1.length());

	//string大小
	int length = str1.length();
	int size = str1.size();

	//重设大小，多出的空间用字符填充，这个函数不会冲掉原来的内容，只要resize的大小小于原来的空间，才会对多余的字符进行丢弃
	str1.resize(50, 'g');
	str1.resize(10, 'g');

	//cin 读取到string
	getline(cin, str1);

	//assign重新赋值，注意是重新赋值，而不是追加
	str1.assign("new string ~");
	str1.assign("new string ~", 6); //复制6个字符
	str1.assign(string("another new string ~"));
	str1.assign(string("another new string ~"), 2, 10); //从参数的第2个位置开始，赋值10个字符

	//string可以相加
	str1 = str1 + str2;

	//append追加内容
	str1.append("append char*");
	str1.append(" the second append char*", 15);
	str1.append(string(" the third append char*"), 3, 10);
	str1.append(5, 'l');

	//string判断是否相等
	bool equal  = str1 == str2;
	bool equal2 = str1.compare(str3)==0;
	bool equal3 = str1.compare(2, 3, str3) == 0;		  //将str1的第2个位置开始的3个字符与str3比较
	bool equal4 = str1.compare(2, 3, str3, 1, 4) == 0;//将str1的第2个位置开始的3个字符与str3的第1个位置开始的4个字符比较

	//子字符串，从位置5开始，长度为10的子字符串
	string sub_str = str1.substr(5, 10);

	//swap交换string内容
	str1.swap(str2);

	//查找字符第一次出现的位置
	auto c_index = str1.find('d');
	if (c_index != str1.npos)
	{//找到
	}
	//查找字符最后一次(倒数第一次)出现的位置
	c_index = str1.rfind('d');
	if (c_index != str1.npos)
	{//找到
	}

	//查找字符串第一次出现的位置
	auto str_index = str2.find("aa");
	if (str_index != str1.npos)
	{//找到
	}
	//查找字符串最后一次(倒数第一次)出现的位置
	str_index = str2.rfind("aa");
	if (str_index != str1.npos)
	{//找到
	}

	
	auto index = str1.find_first_of(str2,2); //在str1中查找str2集合中任何一个字符第一次出现的index,第2个参数可以选，表示从第几个index开始查起
	index = str1.find_last_of(str2);		 //在str1中查找str2集合中任何一个字符最后一次出现的index
	index = str1.find_first_not_of(str2,2);  //在str1中查找非str2集合中的字符第一次出现的index,第2个参数可以选，表示从倒数第几个index开始查起
	index = str1.find_last_not_of(str2);     //在str1中查找非str2集合中的字符最后一次出现的index

	//replace替换
	str2.replace(2, 4,"Bruce");    //将str第2个字符开始的4个字符替换为Bruce
	str2.replace(2, 5,"Bruce", 4); //将str第2个字符开始的5个字符替换为Bruce的前4个字符
	str2.replace(2, 5, 5, 'G');    //将str第2个字符开始的5个字符替换为5个G字符

	//insert
	str2.insert(2, "server");    //第2个index插入字符串
	str2.insert(2, "client", 5); //第2个index插入字符串中的前5个字符，
	str2.insert(2, 5, 't');		 //第2个index插入5个字符
	
	//erase
	str2.erase(2, 20); //删除从第2个字符开始的20个字符，如果20不传，则删除2之后的所有

	//基础数据类型和string互相转换
	int Int1 = 100;
	string NumStr = to_string(Int1);
	Int1 = stoi(NumStr);
	return 0;
}

