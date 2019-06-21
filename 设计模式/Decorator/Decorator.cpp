// Decorator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
/*
装饰模式
在归纳装饰模式概念之前，先考虑如下情况
一个人从娘胎里出来，后天学会了功夫，后来又学会了开车，那么在当初创造这个人的时候是不知道人后天会功夫和会开车的，那么如何将功夫和开车技能添加到人身上呢？
我们的做法是添加一种发展了的人，这个发展了的人可以有各种发展方向，可以发展功夫，也可以发展开车，这个发展了的人自己属于人，但也维护一个出生了的人，这样一来
如果一个出生后的人，想要扩展各种技能，我们就可以添加各种发展了的人，这样就实现了“不知道胎儿会什么技能但后天可以随时学习各种技能”的需求。

以上情景归纳后就是装饰模式：现有原始Object，Object未来可能有各种发展，但现在还不提供或者不知道，我们就可以添加一个DecorateObject derived from Object，
DecorateObject其中有一个Object变量，DecorateObject对Object进行处理以进行装饰
Q：DecorateObject为什么要继承自Object，它只负责装饰Object啊？没必要一定是Object吧？
A：因为Object被DecorateA装饰后，还可以被任何其他Decorator装饰，所以DecorateObject自己必须也是一个Object，才能被传给其他Decorator

Q：同样都是对类进行功能扩展，装饰模式和组件编程有何不同？
A：组件编程的前提是在Object被创造的时候，就对Component有系统性的了解，所以可将Component队列加到Object中，而装饰模式中，Object在被创造时对未来是未知的，未来要对Object进行扩展，
   在不修改Object本身的情况下，就只能进行额外的装饰。比如说，也许你知道婴儿未来会学习功夫和开车，所以将功夫和开车作为Component，但是婴儿未来大有可为，不可能将未来一切都作为Component，十年后一种新兴技术
   或者新兴心态出现，这个人要去学习或者改变或者适应，这个时候是无法回娘胎重造的，就只能采取装饰模式，将新技能作为一种装饰，装饰到人的身上，人就适应新的时代了。继承子类可以满足需求，但是如果适应十次，就必须继承
   十次，如果是装饰的话，只需要对同一个人装饰十次就行了。
   对于类的扩展功能来说，能够进行组件编程，最好进行组件编程，组件编程不合适或者满足不了的话，就只能采取装饰模式或者继承模式了。

Q：装饰模式的有什么缺点？
A：最大的缺点就是每装饰一次，都会产生一个新的实例，要命的是这些实例都是相关的，也就是说人进化十次，那么在内存中就有10个实例存在（虽然最后使用的时候只用一个）。

*/

//人
class Human
{
public:
	virtual void Info() = 0;
};

//男人
class Man: public Human
{
	virtual void Info() { cout << "男人" << endl; }
};

//女人
class Woman :public Human
{
	virtual void Info() { cout << "女人" << endl; }
};

//能够进化发展的人
class DecoraterHuman : public Human
{
public:
	DecoraterHuman(Human* pHuman) :m_pHuman(pHuman) {}
	virtual void Info() = 0;
protected:
	Human* m_pHuman;
};

//在进化发展过程中学会了功夫的人
class KongfuHuman :public DecoraterHuman
{
public:
	KongfuHuman(Human* pHuman) :DecoraterHuman(pHuman) {}
	virtual void Info() 
	{
		m_pHuman->Info();
		cout << "学会了功夫" << endl; 
	}
};

//在进化发展过程中学会了开车的人
class DriverHuman :public DecoraterHuman
{
public:
	DriverHuman(Human* pHuman) :DecoraterHuman(pHuman) {}
	virtual void Info()
	{
		m_pHuman->Info();
		cout << "学会了开车" << endl;
	}
};



int main()
{
	//男人
	Human* pMan = new Man;
	Human* pKongfuMan = new KongfuHuman(pMan);//男人学习了功夫
	Human* pDirverMan = new DriverHuman(pKongfuMan); //学了功夫的男人，又学习了开车
	pDirverMan->Info();

	//女人
	Human* pWoman = new Woman;
	Human* pKongfuWoman = new KongfuHuman(pWoman);//女人学习了功夫
	Human* pDirverWoman = new DriverHuman(pKongfuWoman); //学习功夫的女人，又学习了开车
	pDirverWoman->Info();

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
