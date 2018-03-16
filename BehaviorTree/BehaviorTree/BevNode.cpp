

#include "Npc.h"
#include "BevNode.h"

BevNode::BevNode()
{
	m_pFahter = NULL;
	m_pRunningChild = NULL;
	m_pNpc = NULL;
}

void BevNode::AddChild(BevNode* pNode)
{
	if (pNode != NULL)
		pNode->m_pNpc = m_pNpc;
	m_children.push_back(pNode);
	pNode->m_pFahter = this;
}

void BevNode::SetRunningChild(BevNode* pNode)
{
	m_pRunningChild = pNode;
	if (m_pRunningChild != NULL)
	{
		if (m_pFahter != NULL)
			m_pFahter->SetRunningChild(this);
	}
	else
		if (m_pFahter != NULL)
			m_pFahter->SetRunningChild(NULL);
}

BevNode* BevNode::GetRunningChild()
{
	return m_pRunningChild;
}

BevNodeExeRet BevNodeBehaviorRecover::Execute()
{
	if (m_pNpc->m_iHp >= 10)
	{
		cout << "npc recover ok." << endl;
		m_pFahter->SetRunningChild(NULL);
		return BevNodeExeRet::BNER_Success;
	}
	cout << "npc is recovering hp:"<< m_pNpc->m_iHp << endl;
	if (m_pFahter->GetRunningChild() != this)
		m_pFahter->SetRunningChild(this);
	m_pNpc->m_iHp += 1;
	return BevNodeExeRet::BNER_Runing;
}

BevNodeExeRet BevNodeBehaviorWork::Execute()
{
	if (m_pNpc->m_iHp >= 5)
	{
		cout << "npc is working hp:" << m_pNpc->m_iHp << endl;
		if(m_pFahter->GetRunningChild() != this)
			m_pFahter->SetRunningChild(this);
		m_pNpc->m_iHp -= 1;
		return BevNodeExeRet::BNER_Runing;
	}
	cout << "npc energy not enough" << endl;
	m_pFahter->SetRunningChild(NULL);
	return BevNodeExeRet::BNER_Fail;
}

BevNodeExeRet BevNodeConditionHealthy::Execute()
{
	if (m_pNpc->m_iHp >= 5)
		return BevNodeExeRet::BNER_Success;
	return BevNodeExeRet::BNER_Fail;
}

BevNodeExeRet BevNodeConditionTired::Execute()
{
	if (m_pNpc->m_iHp < 5)
		return BevNodeExeRet::BNER_Success;
	return BevNodeExeRet::BNER_Fail;
}

BevNodeExeRet BevNodeDecoratorNot::Execute()
{
	BevNodeExeRet Ret = BevNodeExeRet::BNER_Success;
	if (m_children.size() != 0)
		Ret = m_children[0]->Execute();
	if (Ret == BevNodeExeRet::BNER_Success || Ret == BevNodeExeRet::BNER_Runing)
		Ret = BevNodeExeRet::BNER_Fail;
	else 
		Ret = BevNodeExeRet::BNER_Success;
	return Ret;
}
