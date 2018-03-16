#pragma once

class BevNodeParallel;
class Npc
{
public:
	Npc();
public:
	void Update();
public:
	BevNodeParallel* m_BevTree;
	int	     m_iHp;
};