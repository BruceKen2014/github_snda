#pragma once

#include <iostream>
using namespace std;
/*
抽象工厂模式
抽象工厂模式和工厂方法模式有点类似，都是对工厂进行抽象，不同的是工厂方法模式里一个工厂只能造一个产品，而抽象工厂里面一个工厂可以造一类产品
*/



class Pencil
{
public:
	virtual void Draw() = 0;
};


//粗铅笔产品族
class SolidPencil: public Pencil
{
};

class GreenSolidPencil :public SolidPencil
{
public:
	virtual void Draw() override
	{
		cout << "green solid pencil !" <<endl;
	}
};
class RedSolidPencil :public SolidPencil
{
public:
	virtual void Draw() override
	{
		cout << "red solid pencil !" << endl;
	}
};



//细铅笔产品族
class ThinPencil : public Pencil
{

};

class GreenThinPencil :public ThinPencil
{
public:
	virtual void Draw() override
	{
		cout << "green thin pencil !" << endl;
	}
};
class RedThinPencil :public ThinPencil
{
public:
	virtual void Draw() override
	{
		cout << "red thin pencil !" << endl;
	}
};


class PencilFactory
{
public:
	virtual Pencil* createRedPencil() = 0;
	virtual Pencil* createGreenPencil() = 0;
};

class SolidPencilFactory: public PencilFactory
{
public:
	virtual Pencil* createRedPencil() 
	{
		return new GreenSolidPencil;
	}
	virtual Pencil* createGreenPencil()
	{
		return new RedSolidPencil;
	}
};

class ThinPencilFactory : public PencilFactory
{
public:
	virtual Pencil* createRedPencil()
	{
		return new GreenThinPencil;
	}
	virtual Pencil* createGreenPencil()
	{
		return new RedThinPencil;
	}
};