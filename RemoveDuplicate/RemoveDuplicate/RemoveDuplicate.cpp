// RemoveDuplicate.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <corecrt_io.h>

//删除目标路径下的重复文件，针对重复文件的后缀(1)(2)等进行判定

using namespace std;
char curr_dir[128];
void CheckDuplicateFiles();
int main()
{
	GetCurrentDirectory(128, curr_dir);
	CheckDuplicateFiles();

	int Ret;
	cin >> Ret;
	return 0;
}

void CheckDuplicateFiles()
{
	string Path(curr_dir);
	long hFile = 0;
	_finddata_t fileinfo;
	string p;
	hFile = _findfirst(p.assign(Path).append("\\*").c_str(), &fileinfo);
	int count = 0;
	if (hFile != -1)
	{//find
		do
		{
			if (fileinfo.attrib & _A_SUBDIR)
			{//文件夹
			}
			else
			{//文件
				int Lenth = strlen(fileinfo.name);
				while (1)
				{
					Lenth--;
					if (Lenth < 0)
						break;
					if (fileinfo.name[Lenth] == ')')
					{
						int PreIndex = Lenth - 1;
						if (PreIndex >= 0)
						{
							if (fileinfo.name[PreIndex] >= '1' && fileinfo.name[PreIndex] <= '9')
							{
								remove(fileinfo.name);
								cout << "删除重复文件" << fileinfo.name << endl;
								count++;
							}
							else
							{//防止删除Beyond - 天真的创伤 (第三版混音).ncm 这种格式的文件
								
							}
						}
						break;
					}
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	cout << "共删除" << count << "个文件"<<endl;
}
