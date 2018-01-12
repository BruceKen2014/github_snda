

#pragma once

#include <iostream>
using namespace std;
class TestOperatorBase
{
public:
	void * b;
	TestOperatorBase();
	TestOperatorBase(int a);
	TestOperatorBase(const TestOperatorBase& b);
};
class TestOperatorChild :public TestOperatorBase{};

void TestOperator();