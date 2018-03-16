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

/*选择节点：只要有一个子节点运行成功，则返回，不再运行剩下的子节点，这意味着选择节点的子节点往往具有互斥的关系，不能够同时执行，比如工作和休息
不能运行工作又运行休息，所以如果工作和休息是在同一个父节点下面的话，那么这个父节点的组合类型必然是Selector，而不可能是Sequence，同时子节点也有优先级
关系，前面的子节点优先于后面的子节点，比如工作的优先级高于休息，意思就是能工作则工作，不能工作再判断休息*/
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
					//只要有一个行为是合法的，就返回
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

//对子节点取反,理论上最好用于操作condition
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


