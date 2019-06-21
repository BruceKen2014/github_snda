// Command.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stack>
using namespace  std;
/*
命令模式 Command模式：
之所以命名为'命令模式'，是因为每一次请求都可以理解为一个命令，所以谓之“命令”，命令模式有如下特点
1、每一次请求就是一个命令
2、所有命令都有执行接口，所以必有一个抽象的命令子类
3、命令数量可以任意扩展，具体命令之间是同级关系，因此具体命令互不影响
4、系统执行命令后，可以保存执行记录，因此命令可被undo redo。
*/

class Command
{
public:
	virtual void Execute() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

class Command1:public Command
{
public:
	virtual void Execute() override { cout << "Command1 execute !" << endl;}
	virtual void Undo() override	{ cout << "Command1 undo !" << endl; }
	virtual void Redo() override	{ cout << "Command1 redo !" << endl; }
};

class Command2 :public Command
{
public:
	virtual void Execute() override{ cout << "Command2 execute !" << endl;}
	virtual void Undo() override   { cout << "Command2 undo !" << endl; }
	virtual void Redo() override   { cout << "Command2 redo !" << endl; }
};


class CommandMgr
{
public:
	void DoCommand(Command* command)
	{
		command->Execute();
		DoLists.push(command);
	}
	void UnDo()
	{
		if (DoLists.size() == 0)	return;
		ReDoLists.push(DoLists.top());
		DoLists.top()->Undo();
		DoLists.pop();
	}
	void ReDo()
	{
		if (ReDoLists.size() == 0)	return;
		DoLists.push(ReDoLists.top());
		ReDoLists.top()->Redo();
		ReDoLists.pop();
	}
protected:
	stack<Command*> DoLists;
	stack<Command*> ReDoLists;
};

int main()
{
	CommandMgr* pMgr = new CommandMgr;
	pMgr->DoCommand(new Command1);
	pMgr->DoCommand(new Command2);
	pMgr->UnDo();
	pMgr->UnDo();
	pMgr->ReDo();
	pMgr->ReDo();
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
