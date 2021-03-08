// function_library.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <regex>

#include "function_library.h"

using namespace std;




int main()
{
	MYString out_str;
	function_library::CensorWord(MYText("邓邓小的才平是大坏蛋"), out_str, { MYText("邓"), MYText("小"), MYText("平") });
	function_library::CensorWord(MYText("dengxiao的才ping是大坏蛋"), out_str, { MYText("deng"), MYText("xiao"), MYText("ping") });
	
	vector<pair<MYString, MYString>> FileNames;

	function_library::GetDirectoryFiles(MYText("D:\\Github\\github_snda"), FileNames,{MYText(".cpp"),MYText(".h") }, true);
	function_library::DeleteDirectoryFiles(MYText("C:\\Users\\Daying\\Desktop\\TestDelete"), {}, true);

	MYString ReplaceRet = function_library::ReplaceFileNameSuffix(MYText("你好张三.mp3"), MYText(".cpp"));
	MYString ReplaceRet2= function_library::ReplaceFileNameSuffix(MYText("你好张三.mp3"), MYText("cpp"));

	MYString PureName = function_library::GetPureFileName(MYText("D:\\Github\\github_snda\\12.obj"));
	MYString PurePath = function_library::GetPureFilePath(MYText("D:\\Github\\github_snda\\12.obj"));

	std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件