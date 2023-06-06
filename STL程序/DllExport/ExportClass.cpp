

#include "ExportClass.h"
#include <iostream>
using std::cout;
using std::endl;
int ReturnSum(int a, int b)
{
	std::cout << "this is dll function, version 2" << std::endl;
	return a + b;
}

void ExportClass::MemberFunction()
{
	cout << " this is class member function" << endl;
}
