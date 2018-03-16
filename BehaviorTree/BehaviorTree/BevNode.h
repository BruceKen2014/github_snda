#pragma once
#include <vector>
#include <iostream>

using namespace std;

enum BevNodeExeRet
{
	BNER_Success,
	BNER_Fail,
	BNER_Runing
};

class Npc;
class BevNode
{
protected:
	vector<BevNode*> m_children;
	BevNode*		 m_pFahter;
	BevNode*		 m_pRunningChild;
	Npc*			 m_pNpc;
public:
	BevNode();
	void AddChild(BevNode* pNode);
	void SetRunningChild(BevNode* pNode);
	BevNode* GetRunningChild();
	virtual BevNodeExeRet Execute() = 0;
};

class BevNodeParallel :public BevNode
{
public:
	BevNodeParallel(Npc* pNpc)
	{
		m_pNpc = pNpc;
	}
public:
	virtual BevNodeExeRet Execute() override
	{
		for (auto node : m_children)
			node->Execute();
		return BevNodeExeRet::BNER_Success;
	}
};

/*ѡ��ڵ㣺ֻҪ��һ���ӽڵ����гɹ����򷵻أ���������ʣ�µ��ӽڵ㣬����ζ��ѡ��ڵ���ӽڵ��������л���Ĺ�ϵ�����ܹ�ͬʱִ�У����繤������Ϣ
�������й�����������Ϣ�����������������Ϣ����ͬһ�����ڵ�����Ļ�����ô������ڵ��������ͱ�Ȼ��Selector������������Sequence��ͬʱ�ӽڵ�Ҳ�����ȼ�
��ϵ��ǰ����ӽڵ������ں�����ӽڵ㣬���繤�������ȼ�������Ϣ����˼�����ܹ������������ܹ������ж���Ϣ*/
class BevNodeSelector : public BevNode
{
public:
	virtual BevNodeExeRet Execute() override
	{
		BevNodeExeRet Ret = BevNodeExeRet::BNER_Fail;
		if (m_pRunningChild != NULL)
			Ret = m_pRunningChild->Execute();
		else
		{
			for (auto node : m_children)
			{
				Ret = node->Execute();
				if (Ret == BNER_Success || Ret == BevNodeExeRet::BNER_Runing)
					//ֻҪ��һ����Ϊ�ǺϷ��ģ��ͷ���
					break;
			}
		}
		return Ret;
	}
};


class BevNodeSequence : public BevNode
{
public:
	virtual BevNodeExeRet Execute() override
	{
		BevNodeExeRet Ret = BevNodeExeRet::BNER_Fail;
		if (m_pRunningChild != NULL)
			Ret = m_pRunningChild->Execute();
		else
		{
			for (auto node : m_children)
			{
				Ret = node->Execute();
				if (Ret == BNER_Success)
					continue;
				break;
			}
		}
		return Ret;
	}
};

//=======================decorator node=================================
class BevNodeDecorator :public BevNode
{

};

//���ӽڵ�ȡ��,������������ڲ���condition
class BevNodeDecoratorNot:public BevNodeDecorator
{
public:
	virtual BevNodeExeRet Execute() override;
};


//=======================condition node=================================
class BevNodeCondition :public BevNode
{

};


class BevNodeConditionHealthy :public BevNodeCondition
{
public:
	virtual BevNodeExeRet Execute() override;
};


class BevNodeConditionTired :public BevNodeCondition
{
public:
	virtual BevNodeExeRet Execute() override;
};


//=======================action node=================================

class BevNodeBehavior :public BevNode
{

};

class BevNodeBehaviorRecover :public BevNodeBehavior
{
public:

	virtual BevNodeExeRet Execute() override;
};

class BevNodeBehaviorWork :public BevNodeBehavior
{
public:
	virtual BevNodeExeRet Execute() override;
};


