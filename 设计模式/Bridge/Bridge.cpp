// Bridge.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>


/*Bridge模式：桥梁模式，又称桥接模式
该模式的核心思想是将类设计中的通用部分提取称为基类的成员变量，然后类有自己的继承体系，变量有自己的继承体系，两个体系通过基类的成员变量连接在一起
以下例子中，Actor有一套Actor继承体系，Mesh有一套Mesh继承体系，Actor和Mesh通过Actor中的m_pMesh变量连接在一起，两方发生改变时互不影响。
如果不采用Bridge模式，那么可能是如下的继承关系
Actor->MeshActor->StaticMeshActor->Stone
				->SkeletalMeshActor->Monster
								   ->Player
这样的继承体系看起来就比较复杂，且扩展困难，在我之前的Dex引擎中，sceneObject采用的就是这种设计，以后需要改正过来。

*/

using namespace std;
class Mesh
{
public:
	virtual void Show() = 0;
};

class StaticMesh:public Mesh
{
public:
	virtual void Show() { cout << "static mesh !" << endl; }
};

class SkeletalMesh :public Mesh
{
public:
	virtual void Show() { cout << "skeletal mesh !" << endl; }
};

class Actor
{
public:
	virtual void Info() { m_pMesh->Show(); }
public:
	void SetMesh(Mesh* pMesh) { m_pMesh = pMesh; };
protected:
	Mesh* m_pMesh;
};

class Monster:public Actor
{

};

class Player :public Actor
{

};

int main()
{
	Mesh* pMesh1 = new StaticMesh;
	Mesh* pMesh2 = new SkeletalMesh;

	Actor* pActor1 = new Monster;
	Actor* pActor2 = new Player;


	pActor1->SetMesh(pMesh1);
	pActor2->SetMesh(pMesh2);

	pActor1->Info();
	pActor2->Info();

    std::cout << "Hello World!\n"; 
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
