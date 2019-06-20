#pragma once

#include <iostream>
using namespace std;

/*
简单工厂模式
适用情况：
1、对象要由工厂生成，所以工厂必须存在，从而将对象生成过程隐藏起来。
2、对象数量不是太多，并且扩展要求不高。
*/

enum class WidgetType:int
{
	Base,
	Image,
	Button,
};

class Widget
{
public:
	virtual void Printf()=0;
public:
	WidgetType type;
	
};


class Image :public Widget
{
public:
	virtual void Printf() override
	{
		cout << "I am Image !" << endl;
	}
};

class Button :public Widget
{
	virtual void Printf() override
	{
		cout << "I am Button !" << endl;
	}
};

class WidgetFactory
{
public:
	Widget* createWidget(WidgetType type)
	{
		switch (type)
		{
		case WidgetType::Button:
			return new Button;
			break;
		case WidgetType::Image:
			return new Image();
			break;
		default:
			break;
		}
		return nullptr;
	}
};