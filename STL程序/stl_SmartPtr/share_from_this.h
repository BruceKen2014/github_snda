#pragma once




/*
enable_shared_from_this
Q：什么是enable_shared_from_this？
A：enable_shared_from_this是一个模板类，如果一个类想要在内部向外部传递自己的智能指针，则应该public继承这个模板类。

Q：为什么一个类要向外部传递自己的智能指针？
A：首先解释为什么向外部传递指针，然后解释为什么传递的是智能指针。
   在一些情况下，一个类实例生成以后，需要将自己的指针提供给外部某个模块使用（比如向一些模板将自己注册进去），这就需要向外部传递自己。
   为什么传递智能指针呢？因为向外部注册自己以后，之后的过程this指针可能已经被销毁，那么外部使用自己的模块就会出现问题，所以使用智能指针保持对自己的引用。
   等外部所有引用this的模块都取消了对this的引用之后，再自动销毁。

Q：向外部传递共享智能指针直接返回make_shared<T>(this)不就行了吗，为什么要继承enable_shared_from_this？
A：我们要知道，如果调用make_shared<T>(this)，那就意味着将原生指针的控制权又另外授权给了其他的共享指针，这在共享指针编程中是禁止的！这会导致外部的共享指针
   和自己内部构造的共享指针控制同一个原生指针，导致多次释放的问题。

Q：enable_shared_from_this的实现原理是什么？
A：enable_shared_from_this内部有一个weak_ptr变量，用于追踪shared_ptr，然后shared_from_this函数就用这个weak_ptr生成了一个强引用的共享指针shared_ptr。

Q：什么时候必须用共享指针呢？
A：我们可以看出，很多时候，不用共享指针只用原生指针也能工作，只需要记得new delete的时机就行，那么存不存在一些情况只能用共享指针而无法用原生指针呢？我认为至少有一种
情况共享指针最方便，那就是一个实例生成以后，需要被很多其他模块使用，并且其他模块取消引用的先后顺序和时机是未知的，这个时候使用共享指针就最方便，自己生成以后，把共享
指针扔给其他各个模块，等到所有模块都取消引用以后就自动释放。这种情况下用原生指针就很麻烦，其他模块使用的是原生指针，就只能置nullptr而不能释放，这就要求必须有一个单独
模块来追踪其他模块的使用，并且在它们置nullptr以后，再进行delete，其实干的也就是shared_ptr的事情。

注意：
class继承了enable_shared_from_this，那么在内部调用shared_from_this()的时候，必须保证原生指针已被shared_ptr管理，否则调用失败。原因很简单，shared_from_this是用
weak_ptr生成shared_ptr的，如果连controll block都没有，必然没有weak_ptr。
*/
shared_ptr<class TestA> other_module_ptr;

class TestA : public enable_shared_from_this<TestA>
{
public:
	TestA(int i)
	{
		cout << "Constructor" << endl;
	}
	~TestA()
	{
		cout << "DeStructor" << endl;
	}
	void Prepare()
	{
		other_module_ptr = shared_from_this();
	}

	void Print() { cout << "hello " << endl; }
};

int TestSharedFromThis()
{
	{
		//这里生成了a的实例，并且将自己注册给了其他模块，然后a的生命期就结束了，但因为内部使用shared_from_this，所以增加了自己的强引用，所以虽然
		//a的生命期已经结束，但并不会释放。
		shared_ptr<TestA> a = make_shared<TestA>(8);
		a->Prepare();
	}

	//这是使用a实例的其他模块，已然保持着对a的强引用
	if (other_module_ptr)
		other_module_ptr->Print();
	//使用完之后，减少引用计数，这里才进行了自动释放。
	other_module_ptr.reset();

	return 0;
}