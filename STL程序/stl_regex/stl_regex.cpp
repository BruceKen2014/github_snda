// stl_regex.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <regex>
#include <array>

using namespace std;

/*
.     任一字符，换行符除外
.+    任一字符1个或多个
.*    任一字符0个或多个
.?    任一字符0个或1个
\w    任一字符
\d    任一数字字符(实际使用的时候要用\\d，\本身需要转义一下)
\d{3} 匹配一个3位数的十进制数
[ab]  匹配"abc"集中的任一字符
[^ab] 匹配不在"abc"集中的任一字符
[a-f] 匹配不在a到f区间的任一字符
()    一对小括号表示一个子表达式
$     尾符,表示一个字符串结束

smatch.position()		查找的字符串在源串中的起始索引
smatch.prefix()			一个ssub_match对象,表示当前匹配之前的序列(如果再迭代查找过程中,则是上次查找的结果位置到当前的位置的字符串)
smatch.suffix()			一个ssub_match对象,表示当前匹配之后的序列(查找的结果位置到整个字符串的末尾)
*/

void test_regex();		//单纯地查找一个字符串
void check_filename();	//测试文件是否是指定类型的文件
void find_words();		//查找指定字符串中符合某表达式的单词
void replace_words();   //查找指定字符串,并将替换为另外格式的字符串
void test_besh_wishes();

//判断文件是否是type类型的文件,如filename=123.mp3 type=mp3
bool IsTypeFile(string filename, string type);
int main()
{
	test_besh_wishes();
	bool CheckType = IsTypeFile("new.mp3", "mp3");
	CheckType = IsTypeFile("new.cpp", "cpp");
	CheckType = IsTypeFile("new.CXX", "CXX");
	CheckType = IsTypeFile("new.c", "C");
	test_regex();
	check_filename();
	find_words();
	replace_words();
    std::cout << "Hello World!\n";
}


void test_regex()
{
	regex reg(string("[^c]*or"));
	bool Ret = regex_match(string("world"), reg);//并不完全匹配，返回false
	Ret = regex_match(string("or"), reg); //完全匹配，返回true
}
void check_filename()
{
	regex reg(string("(.+)\\.(cpp|cxx|cc|c)$"), regex_constants::icase); //忽略大小写

	std::array<string, 5>  test_file_name = {
		"hello.c",
		"test.CPP",
		"main.cxx",
		"check.cc",
		"check.h"
	};

	smatch search_result;
	
	for (auto filename : test_file_name)
	{
		bool Ret = regex_search(filename, search_result, reg);
		if (Ret)
			cout << "name:" << search_result.str(1) << " type "<< search_result.str(2) << endl;
	}
}

void test_besh_wishes()
{
	string target_str = "besh wishes for you";
	regex reg(string("[^ ]*[o]+[^ ]*"));

	for (sregex_iterator it(target_str.begin(), target_str.end(), reg), end_it; it != end_it; ++it)
	{
		cout <<  it->str() << endl;
	}
}

void find_words()
{
	string target_str = "receive receipt theif freind d23f";
	//查找*ei*这种单词,且ei前面不能有c
	regex reg(string("[^ ]*[^c]ei[^ ]*"), regex_constants::icase);

	for (sregex_iterator it(target_str.begin(), target_str.end(), reg), end_it; it != end_it; ++it)
	{
		cout << "prefix:" << it->prefix() <<" pos:"<< it->position() <<"(" << it->str() << ")"<< "suffix:"<<it->suffix() << endl;
	}
}

bool IsTypeFile(string filename, string type)
{
	regex reg(string("(.+)\\.") + type + string("$"), regex_constants::icase); //忽略大小写
	smatch search_result;


	bool Ret = regex_search(filename, search_result, reg);
	return Ret;
}

void replace_words()
{
	//把电话号码的格式替换为xxx-xxx-xxxxxxx
	regex reg_find(string("[:](\\d{3})[-.]?(\\d{3})[-](\\d{7})"));
	string target_str("Lucy:088.626-4852321 Books:3 Lily:098626-4852321 Books:9");
	string format(":$1-$2-$3");

	smatch search_result;
	bool Ret2 = regex_search(target_str, search_result, reg_find);

	string Ret = regex_replace(target_str, reg_find, format);
}