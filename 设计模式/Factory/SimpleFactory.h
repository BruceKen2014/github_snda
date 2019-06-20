#pragma once

#include <iostream>
using namespace std;

/*
�򵥹���ģʽ
���������
1������Ҫ�ɹ������ɣ����Թ���������ڣ��Ӷ����������ɹ�������������
2��������������̫�࣬������չҪ�󲻸ߡ�
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