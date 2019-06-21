// Facade.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

/*
Facade模式（外观模式）
即把一些子系统的同一调用封装到一个类里面，只把该类的外观开放给客户
简单地说就是一种封装，外观模式就是个称呼而已。
*/
using namespace std;
class System1
{
public:
	void Check()
	{
		cout << "system 1 ok !" << endl;
	}
};

class System2
{
public:
	void Check()
	{
		cout << "system 2 ok !" << endl;
	}
};

class System3
{
public:
	void Check()
	{
		cout << "system 3 ok !" << endl;
	}
};

class Facade
{
public:
	void Check()
	{
		s1.Check();
		s2.Check();
		s3.Check();
	}
public:
	System1 s1;
	System2 s2;
	System3 s3;
};

int main()
{
	Facade f;
	f.Check();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
