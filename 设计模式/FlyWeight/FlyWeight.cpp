// FlyWeight.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <map>

/*
享元模式：
核心思想就是数据共用，将能共用的数据提取出来，以降低内存开销，提高性能。
以下例子中，Actor引用了Mesh，多个Actor实例可能使用的是同一个Mesh，那么这个Mesh就可以被设计成享元，MeshFactory里面存放的享元以名字为区别，只要是一个名字，就取同一份数据。
享元中分内部数据与外部数据，内部数据是不变的，比如Mesh的模型定点数据，外部数据是可能改变的，比如外部传入的Mesh Scale。
经过如此设计后，那么100个相同模型的怪物，在内存中就只有一份怪物模型数据
*/
using namespace std;
class Mesh
{
public:
	Mesh(string name) :m_name(name) {}
public:
	void SetScale(float scale) { m_fScale = scale; }
	string GetName() {return m_name;}
protected:
	//inner Data 内部数据，不变
	string m_name;

	//out Data，外部数据，可能改变
	float  m_fScale;
};

class Monster1Mesh:public Mesh
{
public:
	Monster1Mesh(string name) :Mesh(name) {}
};

class Monster2Mesh :public Mesh
{
public:
	Monster2Mesh(string name) :Mesh(name) {}
};

class Monster3Mesh :public Mesh
{
public:
	Monster3Mesh(string name) :Mesh(name) {}
};

class Actor
{
public:
	void SetMesh(Mesh* pMesh) { m_pMesh = pMesh; }
public:
	void DrawMesh()
	{
		m_pMesh->SetScale(m_fScale);
		cout << "draw mesh " << m_pMesh->GetName().c_str() << endl;
	}
protected:
	Mesh* m_pMesh;
	float m_fScale=1.0f;
};


#define MonsterName1 "monster1"
#define MonsterName2 "monster2"
#define MonsterName3 "monster3"

class MeshFactory
{
public:
	Mesh* GetMesh(string name)
	{
		map<string, Mesh*>::iterator it = Meshs.find(name);
		if (it != Meshs.end())
			return it->second;
		Mesh* pMesh = nullptr;;
		if(name == MonsterName1)
			pMesh = new Monster1Mesh(name);
		else if (name == MonsterName2)
			pMesh = new Monster2Mesh(name);
		else if (name == MonsterName3)
			pMesh = new Monster3Mesh(name);
		Meshs.insert(make_pair(name,pMesh));
		return pMesh;
	}
public:
	map<string, Mesh*> Meshs;
};
int main()
{
	MeshFactory* pFactory = new MeshFactory;
	Actor* m1 = new Actor;
	m1->SetMesh(pFactory->GetMesh(MonsterName1));
	Actor* m2 = new Actor;
	m2->SetMesh(pFactory->GetMesh(MonsterName2));
	Actor* m3 = new Actor;
	m3->SetMesh(pFactory->GetMesh(MonsterName3));

	Actor* m4 = new Actor;
	m4->SetMesh(pFactory->GetMesh(MonsterName1));
	Actor* m5 = new Actor;
	m5->SetMesh(pFactory->GetMesh(MonsterName2));
	Actor* m6 = new Actor;
	m6->SetMesh(pFactory->GetMesh(MonsterName3));

	m1->DrawMesh();
	m2->DrawMesh();
	m3->DrawMesh();
	m4->DrawMesh();
	m5->DrawMesh();
	m6->DrawMesh();


    std::cout << "Hello World!\n"; 
}
