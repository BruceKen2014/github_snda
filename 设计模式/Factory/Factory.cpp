// Factory.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "SimpleFactory.h"
#include "FactoryMethod.h"
#include "AbstractFactory.h"


/*
小结：
真正要用工厂模式的地方，大多还是以简单工厂模式为最实用，工厂方法模式虽然做到了扩展性强那么一点点，但是带来了大量的工厂类，实在显得臃肿。
*/
void TestSimpleFactory()
{
	//简单工厂模式
	WidgetFactory* pFactory = new WidgetFactory;
	Widget* pImage = pFactory->createWidget(WidgetType::Image);
	Widget* pBtn = pFactory->createWidget(WidgetType::Button);

	pImage->Printf();
	pBtn->Printf();
}

void TestFactoryMethod()
{
	//工厂方法模式
	CarFactory* pBwmFactory = new BMWFactory;
	CarFactory* pBenzFactory = new BenzFactory;

	Car* bmw = pBwmFactory->createCar();
	Car* benz = pBenzFactory->createCar();
	bmw->Printf();
	benz->Printf();
}

void AbstractFactory()
{
	PencilFactory* pSolidFactory = new SolidPencilFactory;
	PencilFactory* pThinFactory = new ThinPencilFactory;

	Pencil* p1 = pSolidFactory->createGreenPencil();
	Pencil* p2 = pSolidFactory->createRedPencil();
	Pencil* p3 = pThinFactory->createGreenPencil();
	Pencil* p4 = pThinFactory->createRedPencil();
	p1->Draw();
	p2->Draw();
	p3->Draw();
	p4->Draw();
}
int main()
{
	TestSimpleFactory();
	TestFactoryMethod();
	AbstractFactory();
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
