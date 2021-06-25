#pragma once

struct Task {
	int mId;
	Task(int id) :mId(id) {
		std::cout << "Task::Constructor" << std::endl;
	}
	~Task() {
		std::cout << "Task::Destructor" << std::endl;
	}
};
/*
创建unique_ptr有如下方法：
1、新建一个空的unique_ptr		std::unique_ptr<int> ptr1
2、用指针创建一个unique_ptr	std::unique_ptr<Task> taskPtr(new Task(23))
3、用原生指针创建unique_ptr的时候，传入一个定制的析构器 std::unique_ptr<int,decltype(CallableObject)> ptr(new int, CallableObject);

判断是否为空：
1、if (!ptr1)
2、if (ptr1 == nullptr)

赋值：
unique_ptr是独占智能指针，不可以赋值，但是可以移动
unique_ptr ptr1(ptr2); 错误！不可以拷贝！
ptr1 = ptr2; 错误！不可以赋值
unique_tr ptr1(st::move(ptr2)); 正确！可以移动

使用：
像正常指针一样使用
获取成员变量：ptr->m_a;
取对象：*ptr;
获取对象指针：Task* p = ptr.get();

释放
1、自动释放，离开生命域之后，unique_ptr自动delete指针
2、手动释放 ptr.reset();删除关联的原始指针,重置 unique_ptr 为空
3、手动释放并重新指定 ptr.reset(p) 接受一个原始指针作为参数，这样ptr删除自身指针的同时，接管p的控制权。
4、手动释放 ptr = nullptr;将独占智能指针置为nullptr，此时独占智能指针销毁原生指针
5、auto p = ptr.release()交出指针控制权，之后必须手动delete p


注意：
1、两个unique_ptr之间的传递类似于 ptr1.reset(ptr2.release()); ptr2交出控制权，ptr1释放了自身指针的同时接管了ptr2交出的指针
2、unique_ptr是独占智能指针，不可以拷贝构造、赋值，但可以通过函数进行返回，因为返回的时候实际上调用了移动构造函数。
3、没有make_shared这种函数来返回unique_ptr。
4、unique_ptr指定析构器的做法和shared_ptr不一样，
   unique_ptr的格式是unique_ptr<int, D> ptr(new int ,d)；
   shared_ptr的格式是shared_ptr<int> ptr(new int, d);
*/
void TestUniquePtr()
{
	// 空对象 unique_ptr
	std::unique_ptr<int> ptr1;

	{
		auto deleter = [](int* p) { cout << "delete " << *p << endl; delete p; };
		std::unique_ptr<int, decltype(deleter)> ptr(new int(12), deleter);
	}
	// 检查 ptr1 是否为空
	if (!ptr1)
		std::cout << "ptr1 is empty" << std::endl;

	// 检查 ptr1 是否为空
	if (ptr1 == nullptr)
		std::cout << "ptr1 is empty" << std::endl;

	// 不能通过赋值初始化unique_ptr
	// std::unique_ptr<Task> taskPtr2 = new Task(); // Compile Error

	// 通过原始指针创建 unique_ptr
	std::unique_ptr<Task> taskPtr(new Task(23));

	// 检查 taskPtr 是否为空
	if (taskPtr != nullptr)
		std::cout << "taskPtr is  not empty" << std::endl;

	// 访问 unique_ptr关联指针的成员
	std::cout << taskPtr->mId << std::endl;

	std::cout << "Reset the taskPtr" << std::endl;
	// 重置 unique_ptr 为空，将删除关联的原始指针
	taskPtr.reset();

	// 检查是否为空 / 检查有没有关联的原始指针
	if (taskPtr == nullptr)
		std::cout << "taskPtr is  empty" << std::endl;

	// 通过原始指针创建 unique_ptr
	std::unique_ptr<Task> taskPtr2(new Task(55));

	if (taskPtr2 != nullptr)
		std::cout << "taskPtr2 is  not empty" << std::endl;

	// unique_ptr 对象不能复制
	//taskPtr = taskPtr2; //compile error
	//std::unique_ptr<Task> taskPtr3 = taskPtr2;

	{
		// 转移所有权（把unique_ptr中的指针转移到另一个unique_ptr中）
		std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);
		// 转移后为空
		if (taskPtr2 == nullptr)
			std::cout << "taskPtr2 is  empty" << std::endl;
		// 转进来后非空
		if (taskPtr4 != nullptr)
			std::cout << "taskPtr4 is not empty" << std::endl;

		std::cout << taskPtr4->mId << std::endl;

		//taskPtr4 超出下面这个括号的作用于将delete其关联的指针
	}

	std::unique_ptr<Task> taskPtr5(new Task(66));

	if (taskPtr5 != nullptr)
		std::cout << "taskPtr5 is not empty" << std::endl;

	// 释放所有权
	Task * ptr = taskPtr5.release();

	if (taskPtr5 == nullptr)
		std::cout << "taskPtr5 is empty" << std::endl;

	std::cout << ptr->mId << std::endl;

	delete ptr;
}