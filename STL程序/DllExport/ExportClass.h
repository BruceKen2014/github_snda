#pragma once

#define DLL_EXPORT _declspec(dllexport)
class DLL_EXPORT ExportClass
{
public:
	int member = 10;

	void MemberFunction();
};

extern "C" DLL_EXPORT int ReturnSum(int a, int b);