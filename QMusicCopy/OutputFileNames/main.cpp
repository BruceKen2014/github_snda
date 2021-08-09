

#include <iostream>
#include <string>
#include <Windows.h>
#include <corecrt_io.h>
#include <vector>
#include <map>
#include <Shlwapi.h>
#include <regex>
#include <utility>

#include "function_library.h"

#pragma comment ( lib,"function_library.lib" ) 


int main(int argc, char *argv[])
{
	LPWSTR *szArglist = NULL;
	int nArgs;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

	wstring target_path;
	if (nArgs <= 1)
	{
		cout << "！！！！未指定目标路径，寻找当前路径文件" << endl;
		wchar_t curr_dir[128];
		GetCurrentDirectoryW(128, curr_dir);
		target_path = curr_dir;

	}
	else
	{
		target_path = szArglist[1];
		cout << "目标路径 " << function_library::GetOutputString(target_path) << endl;
	}

	vector<pair<wstring, wstring>> DirectoryFiles;
	const vector<wstring> Types;
	//扫描出所有文件
	function_library::GetDirectoryFiles(target_path, DirectoryFiles, Types,false);

	//过滤出纯文件名
	vector<wstring> FileNames;
	FileNames.reserve(DirectoryFiles.size()+1);

	FileNames.push_back(TEXT("total number:") + to_wstring(DirectoryFiles.size()));
	for (auto& Pair : DirectoryFiles)
		FileNames.push_back(Pair.second);
	
	function_library::WriteStringArrayToFile(L"全部歌曲名.txt", FileNames);

	cout << "press any key to continue!\n";
	int Ret;
	cin >> Ret;
	return 0;
}