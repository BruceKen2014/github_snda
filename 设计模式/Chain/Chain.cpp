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

int main()
{
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

