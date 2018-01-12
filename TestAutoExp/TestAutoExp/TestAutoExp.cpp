// TestAutoExp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
using namespace std;
template<typename T>
class DVector
{
public:
	typedef T* iterator;
	typedef const T* const_interator;
protected:
	T* ptr;
	int size;
	int capacity;
	iterator begin;
	iterator end;
	const char* str;
public:
	DVector()
	{
		str = "21434";
		ptr = nullptr;
		size = 0;
		capacity = 1;
		begin = nullptr;
		end = nullptr;
		ptr = new T[capacity];
	}
	~DVector()
	{
		delete[] ptr;
	}
	void push_back(const T& value)
	{
		ptr[size++] = value;
		if (size >= capacity)
		{
			capacity *= 2;
			T* newData = new T[capacity];
			memcpy(newData, ptr, size * sizeof(T));
			delete[] ptr;
			ptr = newData;
		}
	}
};
template<typename T>
class TestMyClass :public DVector<T>
{

};
typedef DVector<int>  DVectorInt;
int main()
{
	//https://msdn.microsoft.com/en-us/library/jj620914.aspx
	TestMyClass<int> tt;
	DVectorInt array;
	array.push_back(5);
	array.push_back(6);
	array.push_back(7);
	vector<int> std_vector;
	std_vector.push_back(5);
	std_vector.push_back(6);
	std_vector.push_back(7);
    return 0;
}

