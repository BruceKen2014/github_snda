// Builder.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>


/*
建造者模式：
1、建造者模式的核心意义在于“建造”二字，建造多个部分，并且建造过程可被封装，而且易扩展，所以才谓之“建造”
2、建造者与建造者之间是平级关系，因此看起来与策略模式十分像，策略之间也是平级关系，并且可被替换，所不同的是，在建造者模式中，强调了“各个部分可被切割处理”，
   建造者返回的是一个产品，而策略者则和产品无关。我觉得策略模式才是最简单纯粹能体现继承、多态的设计模式。
3、建造者返回一个产品，这又和工厂模式类似，但建造者强调了对产品进行“切割处理”，而工厂模式则处理整体层面，比如汽车经销商（理解为汽车工厂）可以返回奥迪、宝马，但不涉及汽车的零部件，
   而具体的汽车建造者，则会“切割处理”汽车的不同部分如引擎、商标等等，将二者结合，就比较完美了，实际上，在大型项目中，都是将多种设计模式杂糅在一起的。
*/
//游戏套装
class Suit
{
public:
	int WeaponId; //武器道具ID
	int HelmetId; //头盔道具ID
	int RingId;   //戒指道具ID
};

class SuitBuilder
{
public:
	virtual void CreateWeapon() = 0;
	virtual void CreateHelmet() = 0;
	virtual void CreateRing() = 0;
	Suit getSuit() { return s; }
public:
	Suit  s;
};

//制作黄金套装
class SuitBuilderGold:public SuitBuilder
{
public:
	virtual void CreateWeapon() override { s.WeaponId = 1; }
	virtual void CreateHelmet() override { s.HelmetId = 2; }
	virtual void CreateRing()  override { s.RingId = 3; }
};

//制作战神套装
class SuitBuilderFigher :public SuitBuilder
{
public:
	virtual void CreateWeapon() override { s.WeaponId = 11; }
	virtual void CreateHelmet() override { s.HelmetId = 21; }
	virtual void CreateRing()  override { s.RingId = 31; }
};

class SuitGeter
{
public:
	Suit getSuit()
	{
		pBuilder->CreateWeapon();
		pBuilder->CreateHelmet();
		pBuilder->CreateRing();
		return pBuilder->s;
	}
public:
	void SetBuilder(SuitBuilder* Builder) { pBuilder = Builder; }
protected:
	SuitBuilder* pBuilder;
};
int main()
{
	SuitGeter* pGet = new SuitGeter;
	SuitBuilder* builder1 = new SuitBuilderGold;
	SuitBuilder* builder2 = new SuitBuilderFigher;
	pGet->SetBuilder(builder1);
	Suit s1 = pGet->getSuit();
	pGet->SetBuilder(builder2);
	Suit s2 = pGet->getSuit();
	return 0;
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
