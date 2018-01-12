// STLAllocator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <assert.h>
#include "TestSmartPointer.h"
#include "TestOperator.h"
#include <wtypes.h>
#include <wchar.h>
#include <forward_list>
#include <Psapi.h>
using namespace std;
namespace DexSpace
{
#define Dex_DeclareClass(Object, _Super)						\
public:												\
	virtual std::string getInstanceType() const { return #Object; } \
	virtual std::string getInstanceSuperType()const { return #_Super; } \
	static std::string  getClassType()   { return #Object; }\
	static std::string  getClassSuperType()   { return #_Super; }\
protected:\
	typedef _Super Super;
	class classT
	{
		Dex_DeclareClass(classT, classT)
	public:
		static int m_sStaticMem;
	protected:
		int m_member;
	public:
		void Print()
		{
			cout << "this is test class" << endl;
		}
		void Print2()
		{
			cout << "out member " << m_member << endl;
		}
		template<typename T>
		void PrintT(T value)
		{
			cout << "PrintT member " << value << endl;
		}
	};
	template <typename T>
	class my_allocator:public std::allocator<T>
	{
	public:
		typedef		T				value_type;
		typedef const value_type*	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&   const_reference;
		typedef	std::size_t			size_type;
		typedef std::ptrdiff_t		difference_type;
	};

}

using namespace DexSpace;
typedef  float float32;
struct stLoadingTask 
{
public:
	void DoTask();
};
class DexLoadingManager
{
protected:
	bool m_bLoadingCompleted;
	bool m_bBeginLoading;
	float32 m_fProgress;
	std::list<stLoadingTask> m_listTasks;
public:
	DexLoadingManager()
	{
		m_bBeginLoading = false;
		m_bLoadingCompleted = false;
		m_fProgress = 0.0f;
	}
public:
	void BeginLoading()
	{
		m_bBeginLoading = true;
		m_bLoadingCompleted = false;
	}
	bool LoadingComplete()
	{
		return m_bLoadingCompleted;
	}
	void Loading()
	{
		//remember time
		stLoadingTask task = m_listTasks.front();
		m_listTasks.pop_front(); 
		task.DoTask();
		//update progress
	}
	void AddTask(const stLoadingTask& task)
	{
		m_listTasks.push_back(task);
	}
};
class testMoveConstructor
{
public:
	testMoveConstructor()
	{
		cout << "default constructor" << endl;
		m = -1;
	}
	testMoveConstructor(int i) :testMoveConstructor()
	{
		m = i;
	}
	void Init()
	{
		if (p == nullptr)
			p = new int[10];
	}
	testMoveConstructor(const testMoveConstructor& t) = delete;
// 	{
// 		m = t.m;
// 		Init();
// 		if (t.p != nullptr)
// 			memcpy(p, t.p, 10 * sizeof(int));
// 		cout << "copy constructor" << endl;
// 	}
	testMoveConstructor(testMoveConstructor&& t)
	{
		m = t.m;
		p = t.p;
		t.p = nullptr;
		cout << "move constructor" << endl;
	}
	testMoveConstructor& operator = (const testMoveConstructor& t) = delete;
// 	{
// 		cout << "= operator" << endl;
// 		return *this;
// 	}
	int m = 0;
	int* p = nullptr;
};
void testMoveConstructorFun(testMoveConstructor&& t)
{
	vector<testMoveConstructor> vec;
	vec.push_back(testMoveConstructor());
}
#include <functional>
int add(int f1, int f2)
{
	return 0;
}
class RefClass;
class TestFunction
{
public:
	void Test(RefClass& cls)
	{}
	int operator()(int t1, int t2)
	{
		return 1;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	function<int(int, int)> func;
	func = add;
	TestFunction functor;
	functor.Test(RefClass());
	func = functor;
	int* aary = new int[] {1,4,56,43};
	vector<testMoveConstructor>  tttv;
	tttv.emplace_back(1);
	tttv.emplace_back(2);
	forward_list<int> forwardList2;
	list<int>		  listInt2;
	listInt2.size();
	forwardList2.push_front(2);
	size_t sz = std::distance(forwardList2.begin(), forwardList2.end());

	class tempVectorClass
	{
	public:
		std::vector<char> m_vectt;
	};
	
	tempVectorClass classVector;
	std::vector<char> vectt;
	std::string       strsize;
	std::map<int, int>  mapSize;
	strsize = "dfdfdfdf";
	classVector.m_vectt = { 1, 2, 3, 4, 7, 8, 9 };


	TestOperator();

	classT* pClass = new classT;
	my_allocator<int> tt;
	pClass->Print();
	//pClass->Print2();
	pClass->PrintT(2);
	pClass->PrintT(11.01f);

	map<int, list<int>> testMap;
	list<int>& listInt = testMap[0];
	listInt.push_back(0);
	listInt.push_back(2);
	listInt.push_back(4);
	listInt.push_back(5);
	listInt.push_back(3);
	for (auto i : listInt)
	{
		if (i == 4)
		{
			int tt = 0;
		}
	}

	TestTexture t; 
	CPointRef<TestTexture> smartPointer(&t);
	vector<int> vec{2,3};
	decltype(vec.size()) tt33;
	int&& ref = 2;
	int testref = ref;
	return 0;
}

