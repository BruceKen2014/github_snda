#pragma once

struct SharedPtrCls {
	int mId;
	SharedPtrCls(int id) :mId(id) {
		std::cout << "SharedPtrCls::Constructor" << std::endl;
	}
	~SharedPtrCls() {
		std::cout << "SharedPtrCls::Destructor" << std::endl;
	}
};
struct SharedPtrClsDerived:public SharedPtrCls
{
	SharedPtrClsDerived(int id) :SharedPtrCls(id)
	{
		std::cout << "SharedPtrClsDerived::Constructor" << std::endl;
	}
	~SharedPtrClsDerived() {
		std::cout << "SharedPtrClsDerived::Destructor" << std::endl;
	}
};
/*
创建shared_ptr有如下方法：
1、新建一个空的shared_ptr		std::shared_ptr<SharedPtrCls> ptr1
2、用原生指针创建一shared_ptr	std::shared_ptr<SharedPtrCls> ptr2(new SharedPtrCls(2)); 
3、make_shared构造，推荐！	std::shared_ptr<SharedPtrCls> ptr3 = make_shared<SharedPtrCls>(6);
4、通过shared_ptr拷贝构造		std::shared_ptr<SharedPtrCls> ptr4 = ptr2; //与ptr4(ptr2)等效
5、接管unique_ptr指针        std::shared_ptr<SharedPtrCls> ptr5(std::move(u_ptr)); //接管之后，u_ptr交出了指针控制权，相当于ptr5(u_ptr.release())
7、通过weak_ptr构造			std::shared_ptr<int> ptr(weak_ptr);//构造之后，weak_ptr指向的obj强引用计数+1
6、接受原生指针，指定特殊销毁器std::shared_ptr<int> ptr(new int, CallableObject);
由此可见shared_ptr构造函数既可以接受原生指针，也可以接受共享智能指针。
	接受原生指针，则接管的是原生指针的控制权，接管共享智能指针，则增加了目标共享指针的引用计数

判断是否为空：
1、if (!ptr1)
2、if (ptr1 == nullptr)

获取引用计数
ptr.use_count();

判断当前是否是唯一引用,如果use_count()==1,则返回true
ptr.unique();

赋值：
ptr1 = ptr2;  ptr1原来的引用计数-1，ptr2的引用计数+1
ptr.reset(raw_ptr);原来的引用计数-1，ptr重新指向新的原生指针raw_ptr

使用：
像正常指针一样使用
获取成员变量：ptr->m_a;
取对象：*ptr;
获取对象指针：SharedPtrCls* p = ptr.get();

释放
1、自动释放，离开生命域之后，shared_ptr引用计数-1，为0后delete指针
2、手动释放 ptr.reset();强制让引用计数-1

注意：
1、用原生指针构造共享智能指针的构造函数是explicit的，所以必须用shared_ptr<int> p(new int)这种格式，而不能用shared_ptr p = new int这种格式！
2、使用ptr.get()获取原生指针后，不应该删除这个原生指针，并且不能用这个原生指针去初始化别的智能指针。
3、如果要管理的原生指针不能用析构函数销毁，那么可以传入特殊的销毁器，以负责销毁目标指针。
4、controll block管理了strong reference和weak reference，虽然强引用计数为0后，目标指针被释放，但只要弱引用还在，controll block就依然存在
   只有弱引用也为0之后，controll block本身才会释放。so remember, weak_ptr can cause memory leak too !
5、shared_ptr父类向子类的转换Cast，全部有智能指针版本，
   dynamic_pointer_cast、static_pointer_cast、const_pointer_cast、reinterpret_point_cast(C++17带来的转换)。
   它们的区别如同dynamic_cast、static_cast的区别。
*/

class O 
{
public:
	O() { cout << "O constructor" << endl; }
	~O() { cout << "O Destructor" << endl; }
};

class A
{
public:
	A() { cout << "A constructor" << endl; }
	~A() { cout << "A Destructor" << endl; }
public:
	O o;
};
void TestMakeSharedRef()
{
	{
		shared_ptr<A> sha_a = make_shared<A>();
		shared_ptr<A> sha_b = sha_a;
		weak_ptr<A> w_ptr = sha_a;
		sha_a.reset();
		int i = 0;
	}
	{
		A* a = new A;
		shared_ptr<A> sha_a(a);
		shared_ptr<A> sha_b = sha_a;
		weak_ptr<A> w_ptr = sha_a;
		sha_a.reset();
		int i = 0;
	}
}
void TestSharedPtr()
{
	TestMakeSharedRef();

	shared_ptr<SharedPtrCls> sha_ptr;								  //一个空的、可以管理SharedPtrCls的共享智能指针
	shared_ptr<SharedPtrCls> sha_ptr2(new SharedPtrCls(2));			  //用原生指针创建一个shared_ptr
	shared_ptr<SharedPtrCls> sha_ptr3 = make_shared<SharedPtrCls>(6); //make_shared创建，括号里的参数就是SharedPtrCls构造函数的参数
	shared_ptr<SharedPtrCls> sha_ptr4 = sha_ptr2;					  //拷贝赋值
	shared_ptr<SharedPtrCls> sha_ptr5 = sha_ptr2;

	unique_ptr<SharedPtrCls> u_ptr(new SharedPtrCls(7));
	shared_ptr<SharedPtrCls> sha_ptr6(u_ptr.release());						   //接管unique_ptr的指针

	{
		//传入定制删除器
		auto destructor = [](int* p) { delete p; cout << "special destructor " << endl; };
		shared_ptr<int> temp_sha_ptr(new int, destructor);
	}
	shared_ptr<SharedPtrClsDerived> sha_ptr_derived(new SharedPtrClsDerived(2));
	shared_ptr<SharedPtrCls> sha_ptr_base = sha_ptr_derived;
	shared_ptr<SharedPtrClsDerived> sha_ptr_derived2 = static_pointer_cast<SharedPtrClsDerived>(sha_ptr_base);

	if (sha_ptr6)
		cout << "sha_ptr6 is valid" << endl;
	if (u_ptr)
		cout << "u_ptr is valid" << endl;

	//判断共享指针只能是否有效
	if (sha_ptr)
		cout << "sha_ptr is not nullptr" << endl;
	if(sha_ptr2 != nullptr)
		cout << "sha_ptr2 is not nullptr" << endl;

	cout << "sha_ptr2 use_count:" << sha_ptr2.use_count() << endl;
	cout << "sha_ptr2 is unique:" << sha_ptr2.unique() << endl;
	cout << "sha_ptr3 is unique:" << sha_ptr3.unique() << endl;

	cout << "sha_ptr2 use_count:" << sha_ptr2.use_count() << endl;
	sha_ptr5 = sha_ptr3; //ptr5原来的引用计数-1，ptr3的引用计数+1
	cout << "sha_ptr2 use_count:" << sha_ptr2.use_count() << endl;

	SharedPtrCls* raw_ptr = sha_ptr2.get();  //获取原生指针
	sha_ptr4.reset();		//引用计数-1
	sha_ptr4 = sha_ptr2;
	sha_ptr4.reset(new SharedPtrCls(23));
	

}