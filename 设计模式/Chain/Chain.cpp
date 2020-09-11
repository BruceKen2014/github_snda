// Chain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>


/*
责任链模式：Chain of Responsibility
本质就是构造一条链条，让请求在这条链条中传递，链条上每个环节都有机会处理请求
*/
using namespace std;
class GuildMember
{
public:
	virtual bool CheckBorrowMoney(int money) = 0;
	void SetSuccessor(GuildMember* pNext) { m_pNext = pNext; }
protected:
	GuildMember* m_pNext;
};
class TeamLeader:public GuildMember
{
public:
	virtual bool CheckBorrowMoney(int money)
	{
		if (money < 100)
		{
			cout << "组长可以处理" << money << "块钱的借出" << endl;
			return true;
		}
		cout << "组长处理不了" << money << "块钱的借出" << endl;
		if (m_pNext != nullptr)
			return m_pNext->CheckBorrowMoney(money);
		return false;
	}
};

class GuildLeader :public GuildMember
{
public:
	virtual bool CheckBorrowMoney(int money)
	{
		if (money < 1000)
		{
			cout << "会长可以处理" << money << "块钱的借出" << endl;
			return true;
		}
		cout << "会长处理不了" << money << "块钱的借出" << endl;
		if (m_pNext != nullptr)
			return m_pNext->CheckBorrowMoney(money);
		return false;
	}
};


class GuildLeaderChief :public GuildMember
{
public:
	virtual bool CheckBorrowMoney(int money)
	{
		if (money < 10000)
		{
			cout << "盟主可以处理" << money << "块钱的借出" << endl;
			return true;
		}
		cout << "盟主处理不了" << money << "块钱的借出" << endl;
		if (m_pNext != nullptr)
			return m_pNext->CheckBorrowMoney(money);
		return false;
	}
};



struct stEvent{

};
class CEventHandler;
class DexObject;
class CDelegate
{
public:
	CDelegate() {};
	virtual ~CDelegate() {};
};
class CDelegateG :public CDelegate
{//挂接全局函数
public:
	typedef void(*EventCallBack)(DexObject*, stEvent);
private:
	EventCallBack m_fun;
public:
	CDelegateG() {};
	CDelegateG(EventCallBack fun) {};
	virtual ~CDelegateG() {};

};
class CDelegateM :public CDelegate
{//挂接成员函数
public:
	typedef void  (CEventHandler::*EventCallBack)(CEventHandler* sys, DexObject*, stEvent);
private:
	CEventHandler* m_gameSys; //处理事件的系统
	EventCallBack  m_fun;	  //系统内函数  

public:
	CDelegateM() {};
	CDelegateM(CEventHandler* sys, EventCallBack fun) {
		m_gameSys = sys;
		m_fun = fun;
	};
	virtual ~CDelegateM() {};
};


void TInit2()
{
	int* i1 = new int[1024];
	int* i2 = new int[1024];
	int* i3 = new int[1024];
	int* i4 = new int[1024];
	int* i5 = new int[1024];


	CDelegate* g2 = new CDelegateG();
	CDelegate* g3 = new CDelegateG();
	CDelegate* g4 = new CDelegateG();
	CDelegate* g5 = new CDelegateG();
	CDelegate* g6 = new CDelegateG();


	CDelegate* e2 = new CDelegateM();
	CDelegate* e3 = new CDelegateM();
	CDelegate* e4 = new CDelegateM();
	CDelegate* e5 = new CDelegateM();
	CDelegate* e6 = new CDelegateM();


	CDelegate* l2 = new CDelegateM(nullptr, nullptr);
	CDelegate* l3 = new CDelegateM(nullptr, nullptr);
	CDelegate* l4 = new CDelegateM(nullptr, nullptr);
	CDelegate* l5 = new CDelegateM(nullptr, nullptr);
	CDelegate* l6 = new CDelegateM(nullptr, nullptr);
}
int main()
{
	TInit2();
	GuildMember* pTeamLeader = new TeamLeader;
	GuildMember* pGuilderLeader = new GuildLeader;
	GuildMember* pChif = new GuildLeaderChief;
	pTeamLeader->SetSuccessor(pGuilderLeader);
	pGuilderLeader->SetSuccessor(pChif);

	pTeamLeader->CheckBorrowMoney(50);
	pTeamLeader->CheckBorrowMoney(500);
	pTeamLeader->CheckBorrowMoney(5000);
	pTeamLeader->CheckBorrowMoney(500000);
    std::cout << "Hello World!\n"; 
}

