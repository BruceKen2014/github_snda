// BehaviorTree.cpp : 定义控制台应用程序的入口点。
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

