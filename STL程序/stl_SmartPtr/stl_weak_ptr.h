#pragma once

/*
创建weak_ptr有如下方法
1、新建一个空的弱智能指针			weak_ptr<int> ptr;		
2、用共享智能指针初始化			weak_ptr<int> ptr(sha_ptr);
1、用别的弱智能指针初始化			weak_ptr<int> ptr(other_weak_ptr);

释放
因为只是弱指针，所以并不是真正释放了内存，只是放弃了自己对原生指针的引用，除此之外，并不改变任何事
1、 ptr = nullptr;
2、 ptr.reset();

获取原生指针的强引用数量
ptr.use_count();

判断原生指针是否还有效
1、ptr.expired(); 如果use_count()==0,返回true，否则返回false
2、ptr.lock(); 获取shared_ptr，判断这个shared_ptr是否有效

使用原生指针
必须调用lock函数，获取shared_ptr，然后使用这个shared_ptr操作
shared_ptr<int> sp = ptr0.lock();
if(sp)
  do someting...

注意：
1、当weak_ptr指向的obj被销毁后，lock将无法获得有效的shared_ptr
2、如果weak_ptr成功获得了shared_ptr，那么shared_tr的引用将会+1，这个shared_ptr销毁后计数再-1
*/
void TestWeakPtr()
{
	weak_ptr<int> ptr0;				//新建一个空的可以指向int的弱智能指针
	shared_ptr<int> sha_ptr = make_shared<int>(3);
	weak_ptr<int> weak_ptr1(sha_ptr);	//新建一个指向共享智能指针的弱智能指针
	weak_ptr<int> weak_ptr2(weak_ptr1);		//用别的共享智能指针初始化
	shared_ptr<int> sha_ptr2(weak_ptr2);
	{
		if (shared_ptr<int> sp = weak_ptr2.lock())
		{
			cout << *sp << endl;
		}
	}
	sha_ptr2.reset();
	sha_ptr.reset();
	weak_ptr1.reset();
	weak_ptr2.reset();
	int i = 0;
	int j = 0;
}