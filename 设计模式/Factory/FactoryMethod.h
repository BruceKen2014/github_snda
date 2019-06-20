#pragma once
#include <iostream>
using namespace std;


/*
��������ģʽ
���ģʽ�ĺô���������������ʱ�������޸����й��������ݣ�ֱ������µĹ������ɡ�
�����޸Ĺرգ�����չ���š�
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