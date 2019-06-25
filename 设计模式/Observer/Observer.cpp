// Observer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>


/*
观察者模式：Observer模式，我更倾向于叫它Notify模式
应用情形：A改变时需要通知别人，并且A不需要知道别人是些什么人，只要发出一个改变调用就行了。
在下面的例子中，当玩家的输入发生变化时，并不知道按钮会响应，也不知道哪些逻辑模块会响应，它只需要发出输入变化的通知就行了。
核心做法就是在一个纯虚积累中维持一个Observer队列，所有需要监听本类事件的类都被加入到这个队列中。
有些设计中将Object设计成纯虚的，所有add remove update函数都不实现，而下放到它的子类中实现，这是完全的机械做法，因为这部分的代码是所有子类
所通用并且以后也不会变化而且就算变化子列也可以重写的，因此完全不应该放在子类中，子类仅仅是当需要有新的被监听对象时才应该出现。
我的Dex引擎中listener eventHandler eventSender采用了类似的架构设计。

以下例子中的加强版就是让Object也继承自Observer，它便既可以发出Notify，也可以监听别人的Notify了。
*/

using namespace std;

class Observer
{
public:
	virtual void OnNotify() = 0;
};

class Btn : public Observer
{
public:
	virtual void OnNotify() override {cout << "按钮收到事件 ！" << endl;}
};

class Logic : public Observer
{
public:
	virtual void OnNotify() override { cout << "逻辑模块收到事件 ！" << endl; }
};

class Object
{

public:
	void AddObserver(class Observer* pObserver) { m_vecObservers.push_back(pObserver); }
	void RemoveObserver(class Observer* pObserver) 
	{ 
		for (vector<class Observer*>::iterator ite = m_vecObservers.begin();  ite != m_vecObservers.end(); ++ite)
			if (*ite == pObserver)
			{
				m_vecObservers.erase(ite);
				return;
			}
	}
	virtual void Notify()
	{
		for (auto v : m_vecObservers)
			v->OnNotify();
	}
protected:
	vector<class Observer*> m_vecObservers;
};

class Input : public Object
{
public:
	virtual void Notify() override
	{
		cout << "输入发生改变" << endl;
		Object::Notify();
	}
};


int main()
{
	Object* pInput = new Input;
	pInput->AddObserver(new Btn);
	pInput->AddObserver(new Logic);
	pInput->Notify();


    std::cout << "Hello World!\n"; 
}