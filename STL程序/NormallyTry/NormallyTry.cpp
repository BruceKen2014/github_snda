// NormallyTry.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <windows.h>

#include <iostream>
#include <thread>
#include <mutex>
//#include <libloaderapi.h>
#include "function_library.h"
#include "../DllExport/ExportClass.h"

#pragma comment(lib, "function_library")

using namespace function_library;
using namespace std;


template<typename T>
struct CheckArgument
{
};

template<>
struct CheckArgument<int>
{
    enum {value = true};
};


template<typename T, typename = typename enable_if<CheckArgument<T>::value>::type >
struct FArgument
{
    T value;
};
int main()
{

    FArgument<int> a;
    //FArgument<float> a;

    HINSTANCE hDll = LoadLibrary("DllExport.dll");

    if (hDll == 0)
    {
        cout << "load dll library error !" << endl;
        return 0;
    }

    //ReturnSum(11,1);
    auto DllAddFunc =(decltype(&ReturnSum)) GetProcAddress(hDll, "ReturnSum");
    if(DllAddFunc)
        DllAddFunc(10,2000);
    return 0;
}