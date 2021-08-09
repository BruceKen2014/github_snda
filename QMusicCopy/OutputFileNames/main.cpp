

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
		cout << "��������δָ��Ŀ��·����Ѱ�ҵ�ǰ·���ļ�" << endl;
		wchar_t curr_dir[128];
		GetCurrentDirectoryW(128, curr_dir);
		target_path = curr_dir;

	}
	else
	{
		target_path = szArglist[1];
		cout << "Ŀ��·�� " << function_library::GetOutputString(target_path) << endl;
	}

	vector<pair<wstring, wstring>> DirectoryFiles;
	const vector<wstring> Types;
	//ɨ��������ļ�
	function_library::GetDirectoryFiles(target_path, DirectoryFiles, Types,false);

	//���˳����ļ���
	vector<wstring> FileNames;
	FileNames.reserve(DirectoryFiles.size()+1);

	FileNames.push_back(TEXT("total number:") + to_wstring(DirectoryFiles.size()));
	for (auto& Pair : DirectoryFiles)
		FileNames.push_back(Pair.second);
	
	function_library::WriteStringArrayToFile(L"ȫ��������.txt", FileNames);

	cout << "press any key to continue!\n";
	int Ret;
	cin >> Ret;
	return 0;
}