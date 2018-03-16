
#include "BevNode.h"
#include "Npc.h"


Npc::Npc()
{
	m_iHp = 0;
	m_BevTree = new BevNodeParallel(this);

	BevNodeSelector* workORrevoer = new BevNodeSelector;
	m_BevTree->AddChild(workORrevoer);

	BevNodeSequence* work = new BevNodeSequence;
	BevNodeSequence* recover = new BevNodeSequence;
	workORrevoer->AddChild(work);
	workORrevoer->AddChild(recover);

	work->AddChild(new BevNodeConditionHealthy);
	work->AddChild(new BevNodeBehaviorWork);

	BevNodeDecoratorNot* notHealth = new BevNodeDecoratorNot;
	recover->AddChild(notHealth);
	recover->AddChild(new BevNodeBehaviorRecover);


	notHealth->AddChild(new BevNodeConditionHealthy);
	

}

void Npc::Update()
{
	if (m_BevTree != NULL)
		m_BevTree->Execute();
}

