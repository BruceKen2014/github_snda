// function_library.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <regex>

#include "function_library.h"
#include "DexExpression.h"

using namespace std;




int main()
{

	function_library::Debug_PrintMiddleExpression("AddHp(10+100*3,500+199+GetPlayerLocationZ())");
	
	function_library::Debug_PrintBackExpression("AddHp(10+100*3,500+199+GetPlayerLocationZ())");

	DECLARE_COMMAND_TEST;

	function_library::ExcuteExpression("Say(\"hello world!\")");
	function_library::ExcuteExpression("SetHp(2.0*3 + GetHp())");

	wstring out_str;
	function_library::CensorWord(MYText("邓邓小的才平是大坏蛋"), out_str, { MYText("邓"), MYText("小"), MYText("平") });
	function_library::CensorWord(MYText("dengxiao的才ping是大坏蛋"), out_str, { MYText("deng"), MYText("xiao"), MYText("ping") });
	
	vector<pair<wstring, wstring>> FileNames;

	function_library::GetDirectoryFiles(MYText("G:\\下载歌曲"), FileNames,{}, false);
	function_library::DeleteDirectoryFiles(MYText("C:\\Users\\Daying\\Desktop\\TestDelete"), {}, true);

	wstring ReplaceRet = function_library::ReplaceFileNameSuffix(MYText("你好张三.mp3"), MYText(".cpp"));
	wstring ReplaceRet2= function_library::ReplaceFileNameSuffix(MYText("你好张三.mp3"), MYText("cpp"));

	wstring PureName = function_library::GetPureFileName(MYText("D:\\Github\\github_snda\\12.obj"));
	wstring PurePath = function_library::GetPureFilePath(MYText("D:\\Github\\github_snda\\12.obj"));

	vector<wstring>  TextContent;
	function_library::ReadFileToStringArray(MYText("FileName.txt"), TextContent);

	vector<wstring> WriteContent;//{MYText("dddd"), MYText("中国队") };
	WriteContent.push_back(MYText("中国乒乓球一队"));
	WriteContent.push_back(MYText("dd中的dd"));
	function_library::WriteStringArrayToFile(MYText("输出文件.txt"), WriteContent);

	vector<wstring> vecFileNames;
	vector<pair<wstring, wstring>> DirectoryFiles;
	const vector<wstring> Types;
	//扫描出所有文件
	function_library::GetDirectoryFiles(L"G:\\下载歌曲", DirectoryFiles, Types, false);

	for (auto& Pair : DirectoryFiles)
		vecFileNames.push_back(Pair.second);
	function_library::WriteStringArrayToFile(MYText("歌曲名.txt"), vecFileNames);

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