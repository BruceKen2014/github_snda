#pragma once

#include <iostream>
using namespace std;
/*
���󹤳�ģʽ
���󹤳�ģʽ�͹�������ģʽ�е����ƣ����ǶԹ������г��󣬲�ͬ���ǹ�������ģʽ��һ������ֻ����һ����Ʒ�������󹤳�����һ������������һ���Ʒ
*/



class Pencil
{
public:
	virtual void Draw() = 0;
};


//��Ǧ�ʲ�Ʒ��
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



//ϸǦ�ʲ�Ʒ��
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