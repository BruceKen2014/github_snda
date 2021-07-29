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
����unique_ptr�����·�����
1���½�һ���յ�unique_ptr		std::unique_ptr<int> ptr1
2����ָ�봴��һ��unique_ptr	std::unique_ptr<Task> taskPtr(new Task(23))
3���ñ��unique_ptr����		std::unique_ptr<int> ptr1(std::move(unique_ptr2)); //����������move���ӹ�����unique_ptr�Ĺ���Ȩ
4����ԭ��ָ�봴��unique_ptr��ʱ�򣬴���һ�����Ƶ������� std::unique_ptr<int,decltype(CallableObject)> ptr(new int, CallableObject);

�ж��Ƿ�Ϊ�գ�
1��if (!ptr1)
2��if (ptr1 == nullptr)

��ֵ��
unique_ptr�Ƕ�ռ����ָ�룬�����Ը�ֵ�����ǿ����ƶ�
unique_ptr ptr1(ptr2); ���󣡲����Կ�����
ptr1 = ptr2; ���󣡲����Ը�ֵ
unique_tr ptr1(st::move(ptr2)); ��ȷ�������ƶ�

ʹ�ã�
������ָ��һ��ʹ��
��ȡ��Ա������ptr->m_a;
ȡ����*ptr;
��ȡ����ָ�룺Task* p = ptr.get();

�ͷ�
1���Զ��ͷţ��뿪������֮��unique_ptr�Զ�deleteָ��
2���ֶ��ͷ� ptr.reset();ɾ��������ԭʼָ��,���� unique_ptr Ϊ��
3���ֶ��ͷŲ�����ָ�� ptr.reset(p) ����һ��ԭʼָ����Ϊ����������ptrɾ������ָ���ͬʱ���ӹ�p�Ŀ���Ȩ��
4���ֶ��ͷ� ptr = nullptr;����ռ����ָ����Ϊnullptr����ʱ��ռ����ָ������ԭ��ָ��
5��auto p = ptr.release()����ָ�����Ȩ��֮������ֶ�delete p


ע�⣺
1������unique_ptr֮��Ĵ��������� ptr1.reset(ptr2.release()); ptr2��������Ȩ��ptr1�ͷ�������ָ���ͬʱ�ӹ���ptr2������ָ��
2��unique_ptr�Ƕ�ռ����ָ�룬�����Կ������졢��ֵ��������ͨ���������з��أ���Ϊ���ص�ʱ��ʵ���ϵ������ƶ����캯����
3��C++14�ṩ��make_unique���ֺ���������unique_ptr,��C++11û�С�
4����Ϊunique_ptr��Ȼ��֧�ֿ����͸�ֵ�����Լ̳���ϵ�е�ת���Ͳ���֧�֣�����class B:public A, unique_ptr<B> b = a;//a is unique_ptr<A>, error!
   ���Ҫʹ������ת����ֻ��ͨ��.get()������ȡԭ��ָ�룬Ȼ����ԭ��ָ�����ת����
5����Ϊunique_ptr��֧�ֿ��������Ժ������������unique_ptr����ô�ⲿ����ʱֻ��ͨ��std::move������Ȩ�ƶ�����Ӧ������ע�⡣һ��������std::move(a)����a���Ѿ�ʧȥ������ָ��Ŀ���Ȩ�ˡ�
   ������ǲ�ϣ���ƶ�����Ӧ��ʹ�����ò���������ֵ������
6��unique_ptrָ����������������shared_ptr��һ����
   unique_ptr�ĸ�ʽ��unique_ptr<int, D> ptr(new int ,d)��C++20�У�����ֱ��ʹ��unique_ptr<int, D> ptr(new int)��ʡ����d
   shared_ptr�ĸ�ʽ��shared_ptr<int> ptr(new int, d);
   
*/

//ʹ�����ô��ݺ�������
void process(unique_ptr<Task>& ptr)
{
}
void TestUniquePtr()
{
	{
		//���ݶ���ɾ����
		auto deleter = [](int* p) { cout << "delete " << *p << endl; delete p; };
		std::unique_ptr<int, decltype(deleter)> ptr(new int(12), deleter);
	}

	{
		unique_ptr<Task> ptr0 = make_unique<Task>(12);
		process(ptr0);
		int tt = 0;
	}

	// �ն��� unique_ptr
	std::unique_ptr<int> ptr1;
	// ��� ptr1 �Ƿ�Ϊ��
	if (!ptr1)
		std::cout << "ptr1 is empty" << std::endl;

	// ��� ptr1 �Ƿ�Ϊ��
	if (ptr1 == nullptr)
		std::cout << "ptr1 is empty" << std::endl;

	// ����ͨ����ֵ��ʼ��unique_ptr
	// std::unique_ptr<Task> taskPtr2 = new Task(); // Compile Error

	// ͨ��ԭʼָ�봴�� unique_ptr
	std::unique_ptr<Task> taskPtr(new Task(23));

	// ��� taskPtr �Ƿ�Ϊ��
	if (taskPtr != nullptr)
		std::cout << "taskPtr is  not empty" << std::endl;

	// ���� unique_ptr����ָ��ĳ�Ա
	std::cout << taskPtr->mId << std::endl;

	std::cout << "Reset the taskPtr" << std::endl;
	// ���� unique_ptr Ϊ�գ���ɾ��������ԭʼָ��
	taskPtr.reset();

	// ����Ƿ�Ϊ�� / �����û�й�����ԭʼָ��
	if (taskPtr == nullptr)
		std::cout << "taskPtr is  empty" << std::endl;

	// ͨ��ԭʼָ�봴�� unique_ptr
	std::unique_ptr<Task> taskPtr2(new Task(55));

	if (taskPtr2 != nullptr)
		std::cout << "taskPtr2 is  not empty" << std::endl;

	// unique_ptr �����ܸ���
	//taskPtr = taskPtr2; //compile error
	//std::unique_ptr<Task> taskPtr3 = taskPtr2;

	{
		// ת������Ȩ����unique_ptr�е�ָ��ת�Ƶ���һ��unique_ptr�У�
		std::unique_ptr<Task> taskPtr4 = std::move(taskPtr2);
		// ת�ƺ�Ϊ��
		if (taskPtr2 == nullptr)
			std::cout << "taskPtr2 is  empty" << std::endl;
		// ת������ǿ�
		if (taskPtr4 != nullptr)
			std::cout << "taskPtr4 is not empty" << std::endl;

		std::cout << taskPtr4->mId << std::endl;

		//taskPtr4 ��������������ŵ������ڽ�delete�������ָ��
	}

	std::unique_ptr<Task> taskPtr5(new Task(66));

	if (taskPtr5 != nullptr)
		std::cout << "taskPtr5 is not empty" << std::endl;

	// �ͷ�����Ȩ
	Task * ptr = taskPtr5.release();

	if (taskPtr5 == nullptr)
		std::cout << "taskPtr5 is empty" << std::endl;

	std::cout << ptr->mId << std::endl;

	delete ptr;
}