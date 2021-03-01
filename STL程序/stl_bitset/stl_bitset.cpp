// stl_bitset.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <bitset>
#include <string>


/*
bitset用来处理二进制数据非常方便,可以把它理解为一个类,其中封装维护了一个bool数组
*/
int main()
{
	
	std::bitset<16> bitset_empty;		//初始化一个空的bitset，含有16位，默认全部置为0
	std::bitset<8>  bitset_int(53);		//初始化一个bitset，传入Int
	std::bitset<8>  bitset_c_str("001100");				//初始化一个bitset，传入const char*
	std::bitset<8>  bitset_str(std::string("1110100")); //初始化一个bitset，传入string

	
	auto bit_size = bitset_int.size();	//bitset.size() bitset的位数
	bool has_1 = bitset_int.any();		//bitset.any() 检测是否有的位置为1
	bool all_1 = bitset_int.all();		//bitset.all() 检测是否全部为1
	auto _1_count = bitset_int.count(); //bitset.count() 检测位置为1的数量
	bool all_0 = bitset_int.none();		//bitset.none() 检测是否全部为0
	bitset_int.flip(3);					//bitset.flip(index) 翻转指定位
	bitset_int.flip();					//bitset.flip() 对所有位进行翻转
	bool is_true = bitset_int[7];       //bitset[pos]  判断指定pos是否为1
	bitset_int.set();					//所有位置全部置为1
	bitset_int.reset();					//所有位置全部置为0	
	bitset_int.set(6);					//把index=6的位置为1
	bitset_int[6] = 1;					//把index=6的位置为1
	bitset_int.reset(5);				//把index=5的位置为0
	bitset_int = bitset_int << 1;		//bitset左移操作
	bitset_int = bitset_int >> 2;       //bitset右移操作
	bitset_int |= std::bitset<8>(8);    //bitset或操作，类似的有或| 与 & 异或 ^
	auto bitset_value = bitset_int.to_ulong();				//bitset.to_ulong()将bitset 转换为unsigned long
	auto bitset_value2 = bitset_int.to_ullong();			//bitset.to_ullong()将bitset 转换为unsigned long long
	std::string bitset_value_str = bitset_int.to_string();	//bitset.to_string()将bitset 转换为string
    std::cout << "Hello World!\n";
}
