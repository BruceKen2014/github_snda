// std_initializer_list.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <initializer_list>
#include <vector>

//initializer_list本身比较简单，初始化的时候用一对大括号包起来，用的时候用begin\end 或者auto都可以
//std中vector、list等都已经添加了对initializer_list的支持

using namespace std;

int Sum(std::initializer_list<int> Args)
{
	int Ret = 0;
	for (auto &param : Args)
	{
		Ret += param;
	}
	std::cout << "Sum:" << Ret << endl;
	return Ret;
}

int main()
{
	initializer_list<int> S1{ 1, 2, 3};

	Sum(S1);

	int NewInt = 5;
	Sum({ 1, 2, 3,4,NewInt});
    std::cout << "Hello World!\n";
}

