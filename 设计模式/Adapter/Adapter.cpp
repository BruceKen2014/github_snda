// Adapter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

/*
适配器模式：
使用情形：目前已有系统A，我们使用系统A进行一些行为处理，但现有外来系统B，系统B也处理了一些问题，但我们使用的是A，想把原来的行为替换成B的行为
这个时候就要使用适配器模式，核心思想就是添加一个转接头，对当前使用的目标和要转接的目标进行对接。
以下面几个类为例：
Q：为什么不把OtherSystem直接加到Target中，然后在Info中调用，反而要继承出一个类呢？
A：Target是一个给定的系统，无法对它进行更改，所以只能继承。

另一种衍生出来的适配器模式
使用情形如下：有系统A，有一些功能，现在需要另外一些功能，这些功能能够用A原来的功能实现，但不能修改A（或者不适合以A的身份去做），
			于是添加系统B，但B用了A，使用的A的相关功能，进行一些封装后，开放给外界使用。
			这种情况，也可以称为适配器模式。STL中stack利用deque来实现，就是适配器模式，所以stack被称为适配器而不是容器。
*/
using namespace std;
class Target
{
public:
	virtual void Info(){cout << "Target Info" << endl;}
};

class OtherSystem
{
public:
	virtual void MyInfo() { cout << "Other System Info" << endl; }
};

class Adapter : public Target
{
public:
	Adapter(OtherSystem* pSys) :m_pSys(pSys) {}
public:
	virtual void Info() { m_pSys->MyInfo(); }
protected:
	OtherSystem* m_pSys;
};

int main()
{
	OtherSystem* pSys = new OtherSystem;
	Target* pTarget = new Adapter(pSys);
	pTarget->Info();
    std::cout << "Hello World!\n"; 
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
