// Singleton.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>

/*
单例模式：核心思想就是一个类在系统只能有一个实例,所以必须保证构造函数是私有的
*/

using namespace std;
class SystemSingleton
{
public:
	static SystemSingleton* getInstance()
	{
		static SystemSingleton* pInstance = new SystemSingleton;
		return pInstance;
	}
public:
	void Hello() { cout << "hello, I am SystemSingleton !" << endl; }
private:
	SystemSingleton() {}

};

class MyArray
{
public:
	MyArray() = default;
	~MyArray()
	{
		cout << "析构" << m_iCount << endl;
	}
	MyArray(int count) :m_iCount(count),m_iMax(count)
	{
		cout << "构造函数" << endl;
		pData = new int[m_iCount];
	}
	MyArray(const MyArray& OtherValue)
	{
		cout << "copy构造函数" << endl;
		if (pData != nullptr)
			delete[] pData;
		m_iCount = OtherValue.m_iCount;
		pData = new int[m_iCount];
	}
	MyArray(MyArray&& OtherValue)
	{
		cout << "move构造函数" << endl;
		m_iCount = OtherValue.m_iCount;
		pData = OtherValue.pData;
		OtherValue.m_iCount = 0;
		OtherValue.pData = nullptr;
	}

	int m_iCount= 0;
	int m_iMax = 0;
	int* pData=0;
};
int main()
{
	vector<MyArray> vec;
	vec.push_back(MyArray(5));
	MyArray d2 = MyArray(5);
	SystemSingleton::getInstance()->Hello();
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
