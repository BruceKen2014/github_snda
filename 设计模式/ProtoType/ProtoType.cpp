// ProtoType.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>



/*
原型模式：
该模式本质就是对一个类添加克隆函数，使得可以从这个函数复制出一个一模一样的对象。
主要用于在游戏运行期间创建出一个和某对象一模一样的对象。
*/
using namespace std;
class Button
{
public:
	virtual Button* Clone() = 0 ;
	virtual void Info() { cout << name.c_str() << endl; }
protected:
	string name;
};

class ImageButton: public Button
{
public:
	ImageButton() { name = "ImageButton"; }
public:
	virtual Button* Clone()
	{
		ImageButton* pRet = new ImageButton;
		pRet->name = name;
		return pRet;
	}
};

class CheckButton : public Button
{
public:
	CheckButton() { name = "CheckButton"; }
public:
	virtual Button* Clone()
	{
		CheckButton* pRet = new CheckButton;
		pRet->name = name;
		return pRet;
	}
};
int main()
{
	Button* pBtn = new ImageButton;

	Button* pNewBtn = pBtn->Clone();
	pNewBtn->Info();
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
