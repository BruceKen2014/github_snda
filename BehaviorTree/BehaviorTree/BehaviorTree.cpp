// BehaviorTree.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Npc.h"






int main()
{
	Npc* pNpc = new Npc;
	while (1)
	{
		pNpc->Update();
	}
    return 0;
}

