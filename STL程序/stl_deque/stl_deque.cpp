// stl_queue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <deque>
#include <algorithm>

//双端队列
using namespace std;
int main()
{
	deque<int> q1;
	deque<int> q2{1, 20, 3, 6};
	deque<int> q3(q2);

	q1 = q2;

	//重新赋值，设置为6个8
	q1.assign(6, 8);
	
	//deque size
	int size = q1.size();
	

	//下标取值
	auto value = q1.at(0);
	auto value2 = q1[1];

	//首尾尾引用
	q1.back() = 5;
	q1.front() = 9;

	//清空deque
	q1.clear();

	//在iterator处插入元素
	q1.insert(q1.begin()+1, 7);

	//删除ite处的iterator，传回下一个数据的位置。
	auto ite = q1.erase(q1.begin());

	//头部插入,尾部插入
	q1.push_front(88);
	q1.push_back(66);

	//弹出首尾元素
	q1.pop_front();
	q1.pop_back();

	//首尾emplace
	q1.emplace_front(3);
	q1.emplace_back(4);

	//指定iterator处emplace
	q1.emplace(q1.begin()+2,3);

	//交换元素
	q1.swap(q2);

	//排序，默认按照<排序，元素需要支持<操作，也可以传入lambda表达式
	sort(q2.begin(), q2.end());
	sort(q2.begin(), q2.end(), [](int a, int b) -> bool {return a > b; });

	//查找，元素需要支持==操作，也可以传入lambda表达式
	find(q2.begin(), q2.end(), 8);
	find(q2.begin(), q2.end(), 8);

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
