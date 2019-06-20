#pragma once
#include <iostream>
using namespace std;


/*
工厂方法模式
这个模式的好处就是在增加汽车时，不用修改已有工厂的内容，直接添加新的工厂即可。
即对修改关闭，对扩展开放。
*/


class Car
{
public:
	virtual void Printf() = 0;
};

class BMWCar : public Car
{
public:
	virtual void Printf() 
	{
		cout << "I am BWM" << endl;
	}
};

class BenzCar : public Car
{
public:
	virtual void Printf()
	{
		cout << "I am Benz" << endl;
	}
};


class CarFactory
{
public:
	virtual Car* createCar() = 0;
};


class BMWFactory :public CarFactory
{
public:
	virtual Car* createCar()
	{
		return new BMWCar;
	}
};

class BenzFactory :public CarFactory
{
public:
	virtual Car* createCar()
	{
		return new BenzCar;
	}
};