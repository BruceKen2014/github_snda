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
	//初始化string
	string str1("this is the first try string !");
	cout<<"调用语句string st1(\"this is the first try string !\");构造函数新建一个string str1\n";
	print_string("str1", str1);
	string str2(10, 'q');
	cout<<"调用语句string str2(10, 'q');构造函数新建一个string str2\n";
	print_string("str2", str2);
	string str3 = "copy instructer";
	cout<<"调用语句string str3 = \"copy instructer\";新建一个string str3\n";
	print_string("str3", str3);

	//下标访问字符
	cout<<"string支持下标访问，str1[2]返回str1字符串中第三个字符";
	cout<<str1[2]<<endl;
	cout<<"str1.at(2)作用与str[2]一样都取得"<<str1.at(2)<<endl;

	//取得char* 
	char* ch1 = (char *)str1.c_str();
	cout<<"调用语句char* ch1 = (char *)str1.c_str();取得C风格字符串ch1\n";
	print_string("ch1", ch1);
	const char* ch2 = str1.data();
	cout<<"调用语句char* ch2 = (char *)str1.data();取得C风格字符串ch2\n";
	print_string("ch2", ch2);
	cout<<"此时strlen(chr)="<<strlen(ch1)<<" strlen(ch2)="<<strlen(ch2)<<endl;

	//从char* 拷贝
	char* ch3 = new char[32];
	memset(ch3, 0, 32);
	int temp1;
	temp1 = str1.copy(ch3, str1.length());
	cout<<"调用语句temp1 = str1.copy(ch3, str1.length());进行拷贝\n";
	cout<<"实际拷贝了temp1:"<<temp1<<"个字符\n";
	print_string("ch3", ch3);

	//string大小
	cout<<"str1.length() = "<<str1.length()<<",str1.size() = "<<str1.size()<<endl;

	//重设大小，并用字符填充
	cout<<"调用语句str1.resize(50, 'g');\n";
	str1.resize(50, 'g');
	print_string("str1", str1);
	cout<<"调用语句str1.resize(25, 'g');\n";
	str1.resize(25, 'g');
	print_string("str1", str1);

	//cin 读取到string
	cout<<"调用语句getline(cin, str1);\n";
	getline(cin, str1);
	print_string("str1", str1);

	//assign赋值
	cout<<"调用语句str1.assign(\"new string ~\"); 重新给str1赋值\n";
	str1.assign("new string ~");
	print_string("str1", str1);
	cout<<"调用语句str1.assign(\"new string ~\", 6); 重新给str1赋值\n";
	str1.assign("new string ~", 6);
	print_string("str1", str1);
	cout<<"调用语句str1.assign(string(\"another new string ~\")); 重新给str1赋值\n";
	str1.assign(string("another new string ~"));
	print_string("str1", str1);
	cout<<"调用语句str1.assign(string(\"another new string ~\"), 2, 10); 重新给str1赋值\n";
	str1.assign(string("another new string ~"), 2, 10);
	print_string("str1", str1);

	//string可以相加
	cout<<"调用语句 str1 = str1 + str2"<<endl;
	str1 = str1 + str2;
	print_string("str1", str1);
	cout<<"效果等同 str1 += str2;\n";

	//append追加内容
	cout<<"调用语句str1.append(\"append char*\");进行连接"<<endl;
	str1.append("append char*");
	print_string("str1", str1);
	cout<<"调用语句str1.append(\" the second append char*\", 15);进行连接"<<endl;
	str1.append(" the second append char*", 15);
	print_string("str1", str1);
	cout<<"调用语句str1.append(string(\" the third append char*\", 3, 10);进行连接"<<endl;
	str1.append(string(" the third append char*"), 3, 10);
	print_string("str1", str1);
	cout<<"调用语句str1.append(5, 'l');进行添加"<<endl;
	str1.append(5, 'l');
	print_string("str1", str1);

	//string判断是否相等
	cout<<"str1 == str2? 结果：";
	cout<<(str1 == str2 ? "相等" : "不相等")<<endl;
	cout<<"str1.compare(str3),返回"<<str1.compare(str3)<<endl;
	cout<<"str1.compare(\"compare string\"),返回"<<str1.compare("compare string")<<endl;
	cout<<"str1.compare(\"tcompare string\"),返回"<<str1.compare("tcompare string")<<endl;
	cout<<"调用语句str1.substr(5, 10);返回str1从位置5开始，长度为10的子字符串："<<str1.substr(5, 10)<<endl;

	//swap交换string内容
	str1.swap(str2);
	cout<<"调用语句str1.swap(str2);进行字符串的交换\n";
	print_string("str1", str1);
	print_string("str2", str2);

	//查找字符
	cout<<"调用语句str1.find('d');查找字符d在str1第一次出现的位置：";
	cout<<str1.find('d')<<"\n";
	cout<<"调用语句str2.find('a');查找字符a在str2第一次出现的位置：";
	cout<<str2.find('a')<<"\n";

	//查找字符串
	cout<<"调用语句str2.find(\"aa\");查找字符串aa在str2第一次出现的位置：";
	cout<<str2.find("aa")<<"\n";
	cout<<"调用语句str2.find(string(\"qq\"));查找字符串aa在str2第一次出现的位置：";
	cout<<str2.find(string("qq"))<<"\n";

	//replace替换
	cout<<"调用语句str2.replace(2, 4,\"Bruce\");进行替换"<<endl;
	str2.replace(2, 4,"Bruce");
	print_string("str2", str2);
	cout<<"调用语句str2.replace(2, 4,\"Bruce\", 4);进行替换"<<endl;
	str2.replace(2, 5,"Bruce", 4);
	print_string("str2", str2);
	cout<<"调用语句str2.replace(2, 4, 5, 'G');进行替换"<<endl;
	str2.replace(2, 5, 5, 'G');
	print_string("str2", str2);

	//insert
	cout<<"调用语句str2.insert(2, \"server\");进行插入"<<endl;
	str2.insert(2, "server");
	print_string("str2", str2);
	cout<<"调用语句str2.insert(2, \"client\", 5);进行插入"<<endl;
	str2.insert(2, "client", 5);
	print_string("str2", str2);
	cout<<"调用语句str2.insert(2, 5, 't');进行插入"<<endl;
	str2.insert(2, 5, 't');
	print_string("str2", str2);
	cout<<"调用语句str2.erase(2, 20);进行删除"<<endl;
	
	//erase
	str2.erase(2, 20);
	print_string("str2", str2);
	

	//基础数据类型和string互相转换
	int Int1 = 100;
	string NumStr = to_string(Int1);
	Int1 = stoi(NumStr);
	return 0;
}

