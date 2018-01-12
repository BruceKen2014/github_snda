

#include "TestOperator.h"
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;
TestOperatorBase::TestOperatorBase()
{
	b = nullptr;
	cout << "base constructor" << endl;
};
TestOperatorBase::TestOperatorBase(int a) :TestOperatorBase()
{
}
TestOperatorBase::TestOperatorBase(const TestOperatorBase& b) 
{
	cout << "base copy constructor" << endl;
};



TestOperatorBase& operator <<(TestOperatorBase& t, int& a)
{
	cout << " operatorBase " << a << endl;
	return t;
}
TestOperatorChild& operator <<(TestOperatorChild& t, int& a)
{
	cout << " operatorChild " << a << endl;
	return t;
}
namespace N1
{
	class NClass
	{
	public:
		NClass(){ cout << " N1 Class " << endl; }
	};
}
namespace N2
{
	class NClass
	{
	public:
		NClass(){ cout << " N2 Class " << endl; }
	};
}
class NClass
{
public:
	NClass(){ cout << " N0 Class " << endl; }
};
using namespace N1;
using namespace N2;
void TestOperator()
{
	int a;
	TestOperatorBase base;
	TestOperatorBase b(1);
	TestOperatorChild child;
	
	base << a;
	child << a;	
	vector<int> ddda{1,6,5,3,6,32,5};
	stable_sort(ddda.begin(), ddda.end(), [](const int&a, const int&b){return a>b; });
	ddda.push_back(10);
	ddda.shrink_to_fit();
	int v1 = 10;
	auto testlambda = [v1] () -> void {if(1) cout << "V1 " << v1 << endl; return ; };
	v1 = 20;
	testlambda();

}