// WeakPtr.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>

using namespace std;

//模仿UE4中的FWeakObjectPtr写一个最简单的弱指针

class ObjectArray;
ObjectArray* gObjectArray = nullptr;
class Object
{
public:
	Object();
	~Object();
public:
	int Index=0;
};

class ObjectArray
{
public:
	void AddObject(Object* obj)
	{
		if (obj == nullptr)
			return;
		obj->Index = ++Count;
		ObjMap.insert({obj->Index, obj});
	}
	void RemoveObject(Object* obj)
	{
		if (obj == nullptr)
			return;
		ObjMap.erase(obj->Index);
	}
	Object* GetObject(int index)
	{
		auto Ret = ObjMap.find(index);
		if (Ret != ObjMap.end())
			return Ret->second;
		return nullptr;
	}
public:
	int Count = 0;
	map<int, Object*> ObjMap;
};

Object::Object()
{
	gObjectArray->AddObject(this);
}
Object::~Object()
{
	gObjectArray->RemoveObject(this);
}


template<typename T>
class FWeakObjectPtr
{
public:
	FWeakObjectPtr() = default;
	FWeakObjectPtr(T* obj)
	{
		Index = obj->Index;
	}

	T* Get()
	{
		T* Ret = gObjectArray->GetObject(Index);
		return Ret;
	}

public:
	void operator =(const Object* obj)
	{
		Index = obj->Index;
	}
public:
	int Index=0;
};
int main()
{
	gObjectArray = new ObjectArray;

	FWeakObjectPtr<Object> TestWeak;

	//Object生成的时候与全局的Objects绑定
	Object* myObject = new Object;

	//WeakPtr记录下Index
	TestWeak = myObject;

	//拿指针的时候用Index去全局查找
	Object* GetObj = TestWeak.Get();

	//本Object被删除的时候，已被从全局中移除
	delete myObject;

	//再用index去全局查找的时候，已经查找不到了
	Object* GetObj2 = TestWeak.Get();


    std::cout << "Hello World!\n";
}