// Proxy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>

/*
代理模式：又称委托模式
如果一个类在某些情况下，无法亲自出面，或者别人代替出现表现更好，那么就可以考虑使用代替模式。
比如代理服务器，其中的逻辑调用都使用真实服务器的逻辑，但网络速率却有着更优异的表现。
以下例子中，代练是一种典型的代理模式，代练玩家执行逻辑时调用的都是客户的逻辑，只不过这个执行过程由代练执行而已。
*/

using namespace std;
class Player
{
public:
	Player(string name) :m_name(name) {}
public:
	virtual void Login() = 0;

protected:
	string m_name;
};

class Zhangsan :public Player
{
public:
	Zhangsan(string name) :Player(name) {}
public:
	virtual void Login() override  { cout << "正常玩家 " << m_name.c_str() << "登录了" << endl; }

};

class PlayerProxy :public Player
{
public:
	PlayerProxy(Player* p) :Player(""),m_pClient(p) {}
public:
	virtual void Login() override
	{
		cout << " 嘘————" << endl;
		m_pClient->Login();
	}
protected:
	Player* m_pClient;
};
int main()
{
	Player* Zs = new Zhangsan("张三");
	Player* proxy = new PlayerProxy(Zs);
	proxy->Login();
    std::cout << "Hello World!\n"; 
}

