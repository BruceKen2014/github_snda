// stl_queue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <deque>
#include <algorithm>
#include "Sort.h"

using namespace std;
void TestQuickSort()
{
	vector<int> TestVector{ 10,20,5,2,61,29,4,8,12,6 };
	PrintVector(TestVector);
	QuickSort(TestVector, 0, TestVector.size() - 1);
}
void TestBubbleSort()
{
	vector<int> TestVector{ 10,20,5,2,61,29,4,8,12,6 };
	PrintVector(TestVector);
	BubbleSort(TestVector);
}
void TestInsertSort()
{
	vector<int> TestVector{ 10,20,5,2,61,29,4,8,12,6 };
	PrintVector(TestVector);
	InsertSort(TestVector);
}
void TestMergeSort()
{
	vector<int> TestVector{ 10,20,5,2,61,29,4,8,12,6, 7,23,8,21,15,9};
	PrintVector(TestVector);
	MergeSort(TestVector);
}
void TestShellSort()
{
	vector<int> TestVector{ 10,20,5,2,61,29,4,8,12,6, 7,23,8,21,15,9 };
	PrintVector(TestVector);
	ShellSort(TestVector);
}
int main()
{
	TestShellSort();
	return 0;
}