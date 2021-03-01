// std_tuple.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <tuple>

/*
tuple本质上就是一个简单灵活的结构体
*/

using MyTupleType = std::tuple<int, float, bool>;
int main()
{
	//定义一个空的tuple
	MyTupleType Tuple;

	//定义一个tuple并赋值
	MyTupleType Tuple2{1, 30.f, true};

	//定义一个tuple并赋值
	auto Tuple3 = std::make_tuple(2, 15.0f, false);

	//定义一个tuple,利用std::tie，注意tie必须传递变量，因为tie的方式全部是引用
	int IValue0 = 1;
	float FValue0 = 8.8f;
	auto Tuple4 = std::tie(IValue0, FValue0);
	IValue0 = 3;


	//获取tuple中的某个值，可以用过std::tuple_element获取该变量类型，当然用auto更方便
	std::tuple_element<0, MyTupleType>::type value = std::get<0>(Tuple2);

	//获取tuple中的变量个数
	int TupleSize = std::tuple_size<MyTupleType>::value;

	int IValue = 0;
	float fValue = 0.0f;
	bool BValue = false;
	//更方便的获取tuple数据的方式，不需要的索引填充ignore
	std::tie(IValue, fValue, std::ignore) = Tuple2;

	//tuple中的变量有引用类型
	int RefValue = 0;
	auto RefTuple = std::make_tuple(std::ref(RefValue), true, 33.0f);
	RefValue = 10;
	std::get<0>(RefTuple) = 99;

	//tuple可以通过拼接构造新的tuple
	auto TupleTuple = std::tuple_cat(Tuple2, RefTuple);

    std::cout << "Hello World!\n";
}