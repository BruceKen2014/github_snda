// std_array.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <array>

using namespace std;

/*
基本函数
array.fill(value) 将数组里的数据全部重置为value
array.size()      返回数组大小
array.front()     返回数组首元素
array.back()      返回数组尾元素
array.begin()     返回数组正向遍历首元素的迭代器
array.end()       返回数组正向遍历尾元素的迭代器
array.rbegin()     返回数组反向遍历首元素的迭代器
array.rend()       返回数组反向遍历尾元素的迭代器
array.swap(array2)和别的数组交换元素
array.data()      获取数组里的元素指针

初始化主要有两种方式
array<int, 10> testArray;   这种方式，数组里的元素都是空的
array<int, 10> testArray2{3,2,10}; 这种方式用初始化列表里的值去填充数组
*/

//以下3个函数是3种遍历array的方式
void printArray1(const array<int, 10>& Array)
{
	for (auto ite = Array.begin(); ite != Array.end(); ++ite)
	{
		cout << *ite << " " ;
	}
	cout << endl;
}

void printArray2(const array<int, 10>& Array)
{
	for (auto Data: Array)
	{
		cout << Data << " ";
	}
	cout << endl;
}

void printArray3(const array<int, 10>& Array)
{
	for (decltype(Array.size()) i = 0; i < Array.size(); ++i)
	{
		cout << Array[i]<< " ";
	}
	cout << endl;
}


int main()
{
	array<int, 10> testArray;

	//将数组里的数据全部重置为9
	testArray.fill(9);

	//获取某个索引的值
	int Data1 = testArray[8];

	//获取数组的首元素 尾元素
	Data1 = testArray.front();
	Data1 = testArray.back();

	printArray1(testArray);

	testArray.fill(8);
	printArray2(testArray);

	//获取数组大小
	auto ArraySize = testArray.size();

	array<int, 10> testArray2{3,2,10};

	//array交换
	testArray2.swap(testArray);
	printArray3(testArray2);

	//获取数组的数据指针
	int* ArrayPointer = testArray2.data();

    std::cout << "Hello World!\n";
}
