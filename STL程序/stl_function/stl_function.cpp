// stl_function.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <functional>
#include <map>
#include <string>
using namespace std;
int Sum(int a, int b)
{
	return a + b;
}
class FunctorMinus
{
public:
	int operator()(int a, int b)
	{
		return a - b;
	}
	static int Exp(int a, int b)
	{
		return pow(a, b);
	}
};

class ModeClass
{
public:
	int Mod(int a, int b) { return a % b; };
};
class OrClass
{
public:
	int Or(int a, int b) { return a | b; };
	void Print(){}
};

int main()
{
	map<string, function<int(int, int)>> FunctionMap;
	//function存储普通的全局函数
	FunctionMap["+"] = Sum;

	//function存储仿函数
	FunctionMap["-"] = FunctorMinus();

	//function存储未命名lambda
	FunctionMap["*"] = [](int a, int b)->int {return a * b; };

	//function存储命名lambda
	auto Divide = [](int a, int b)->int {return a / b; };
	FunctionMap["/"] = Divide;

	//function存储类静态成员函数
	FunctionMap["^"] = &FunctorMinus::Exp;

	//function存储类成员函数
	ModeClass MC;
	FunctionMap["%"] = std::bind(&ModeClass::Mod, MC, placeholders::_1, placeholders::_2);

	//function存储类成员函数
	OrClass Orc;
	auto mf= mem_fn(&OrClass::Print);
	mf(&Orc);

	cout << FunctionMap["+"](10, 3) << endl;
	cout << FunctionMap["-"](10, 3) << endl;
	cout << FunctionMap["*"](10, 3) << endl;
	cout << FunctionMap["/"](10, 3) << endl;
	cout << FunctionMap["^"](10, 3) << endl;
	cout << FunctionMap["%"](10, 3) << endl;
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
