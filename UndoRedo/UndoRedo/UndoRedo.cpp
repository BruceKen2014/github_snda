// UndoRedo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>

using namespace std;
class Operation
{
public:
	virtual void Do() = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

class OperationA : public Operation
{
public:
	virtual void Do() {};
	virtual void Undo() {};
	virtual void Redo() {};
};

class OperationB : public Operation
{
public:
	virtual void Do() {};
	virtual void Undo() {};
	virtual void Redo() {};
};

class OperationManager
{
public:
	void AddOperation(Operation* op) { m_vecDones.push_back(op); }
	void Undo()
	{
		if (m_vecDones.size() == 0)
			return;
		Operation* op = m_vecDones.back();
		op->Undo();
		m_vecRedos.push_back(op);
		m_vecDones.pop_back();
	}
	void Redo()
	{
		if (m_vecRedos.size() == 0)
			return;
		Operation* op = m_vecRedos.back();
		op->Redo();
		m_vecDones.push_back(op);
		m_vecRedos.pop_back();
	}
private:
	vector<Operation*> m_vecDones;
	vector<Operation*> m_vecRedos;

};
int main()
{
	OperationManager* mgr = new OperationManager;
	OperationA* a = new OperationA;
	OperationB* b = new OperationB;
	a->Do();
	b->Do();
	mgr->AddOperation(a);
	mgr->AddOperation(b);
	mgr->Undo();
	mgr->Undo();
	mgr->Redo();
	mgr->Redo();
    return 0;
}

