// WyyToMyFolder.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <corecrt_io.h>
#include <vector>
#include <Shlwapi.h>

using namespace std;

#ifdef _UNICODE
typedef  wchar_t MYChar;
typedef  wstring MYString;
#define MYText(txt) L##txt
#define MyStrLen wcslen
#define MYStrChr wcschr
#define MYStrCat wcscat
#define MYAccess _waccess
#define MYSystem _wsystem
#define MYCout  cout
#else
typedef  char MYChar;
typedef  string MYString;
#define MYText(txt) txt
#define MyStrLen strlen
#define MYStrChr strchr
#define MYStrCat strcat
#define MYAccess _access
#define MYSystem system
#define MYCout  cout
#endif

/*将网易云下载目录中的文件转换并拷贝到目标文件夹，分以下几步进行
1、扫描网易云下面的所有NCM文件，检测非NCM文件名列表是否包含，如果包含，则意味同名的mp3(或wma)文件已经存在了，否则导出mp3文件
2、将当前目录下面需要拷贝的文件(mp3,wma,ogg等等)拷贝到目标文件夹下去。
*/	

MYChar curr_dir[128];

//判断filename的后缀类型是否是Type
bool IsTypeFile(const MYChar* filename, const MYChar* Type);
//判断filename是否是需要拷贝的音乐文件
bool IsMusicTypeFile(const MYChar* filename);
//判断文件名是否是重复文件名针对重复文件的后缀(1)(2)等进行判定
bool IsDuplicateFile(const MYChar* filename);
//获取NCM文件对应的MP3文件名
MYString GetNCM_MP3Name(const MYChar* FileName);
//获取带路径文件名的纯文件名,如C://1.txt转换为1.txt
MYString GetPureFileName(const MYChar* FileName);
//删除重复文件
void RemoveDuplicateFiles();
//将NCM文件转换为MP3文件
void ConverNCMFile();
//将音乐文件拷贝到目标路径去
void CopyMusicFile();
//分割字符串
void SplitStr(MYString str, MYChar split_char, vector<MYString> &out);

string GetOutputString(MYString str);

//该文件是否存在
bool IsFileExist(const MYChar* FileName)
{
	return MYAccess(FileName, 0) == 0;
}	
MYChar DownloadPath[128];
MYChar TargetPath[128];
vector<MYString> MusicFileType;
int main()
{
	GetCurrentDirectory(128, curr_dir);
	MYString InitPath(curr_dir);
	InitPath.append(MYText("\\setting.ini"));
	GetPrivateProfileString(MYText("setting"), MYText("DowloadPath"), MYText(""), DownloadPath, 128, InitPath.c_str());
	GetPrivateProfileString(MYText("setting"), MYText("TargetPath"), MYText(""), TargetPath, 128, InitPath.c_str());

	MYChar CopyType[128];
	memset(CopyType, 0 , 128);
	GetPrivateProfileString(MYText("setting"), MYText("CopyType"), MYText(""), CopyType, 128, InitPath.c_str());
	SplitStr(CopyType, ',', MusicFileType);

	RemoveDuplicateFiles();
	ConverNCMFile();
	CopyMusicFile();



	int Ret = 1;
	cin >> Ret;
    std::MYCout << "Hello World!\n"; 
}

bool IsTypeFile(const MYChar* filename, const MYChar* Type)
{
	int TypeLenth = MyStrLen(Type);
	const MYChar* TypePoint = &Type[TypeLenth - 1];
	const MYChar* FileNamePoint = &filename[MyStrLen(filename) - 1];

	int CompareCount = 0;
	while(CompareCount < TypeLenth)
	{
		if (*TypePoint == *FileNamePoint)
		{
			--TypePoint;
			--FileNamePoint;
			CompareCount++;
			continue;
		}
		else
			return false;
	}
	return true;
}

bool IsMusicTypeFile(const MYChar* filename)
{
	for (auto Type : MusicFileType)
	{
		if (IsTypeFile(filename, Type.c_str()))
			return true;
	}
	return false;
}
MYString GetNCM_MP3Name(const MYChar* FileName)
{
	MYChar TempFile[128];
	memset(TempFile, 0 , 128);
	int index = 0;
	while (1)
	{
		if (FileName[index] == '.' && FileName[index + 1] == 'n' && FileName[index + 2] == 'c')
			break;
		TempFile[index] = FileName[index];
		index++;
		TempFile[index] = 0;
	}
	MYStrCat(TempFile, MYText(".mp3"));

	return TempFile;
}

void RemoveDuplicateFiles()
{
	MYCout << "开始删除重复文件" << endl;
	HANDLE hFile = 0;
	MYString p;
	WIN32_FIND_DATA wfd; //数据结构;
	hFile = FindFirstFile(p.assign(DownloadPath).append(MYText("\\*")).c_str(), &wfd);
	int count = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
			}
			else
			{//文件
				MYString TargetName = DownloadPath;
				TargetName = TargetName.append(MYText("\\")).append(wfd.cFileName);

				if(IsDuplicateFile(TargetName.c_str()))
				{
					DeleteFile(TargetName.c_str());
					MYCout << "删除重复文件" << GetOutputString(TargetName).c_str() << endl;
					count++;
				}
			}
		} while (FindNextFile(hFile, &wfd));
	}
	MYCout << "共删除" << count << "个文件" << endl;
}

void ConverNCMFile()
{
	MYCout << "开始mp3转换" << endl;
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	MYString p;
	hFile = FindFirstFile(p.assign(DownloadPath).append(MYText("\\*")).c_str(), &wfd);
	int ConvertCount = 0;
	vector<MYString> ConverTargetName;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
			}
			else
			{//文件
				MYString TargetName = DownloadPath;
				TargetName = TargetName.append(MYText("\\")).append(wfd.cFileName);
				if (IsTypeFile(wfd.cFileName, MYText("ncm")))
				{//ncm文件
					//检测对应的mp3文件是否存在
					MYString mp3Name = MYString(DownloadPath).append(MYText("\\")).append(GetNCM_MP3Name(wfd.cFileName));
					if (IsFileExist(mp3Name.c_str()))
					{//mp3文件已经存在，不转换
						MYCout << GetOutputString(mp3Name).c_str() << "已存在，不对ncm进行转换" << endl;
					}
					else
					{//mp3文件不存在，加入NCM转换队列
						ConverTargetName.push_back(TargetName);
					}
				}

			}
		} while (FindNextFile(hFile, &wfd));
	}
	for (auto FileName : ConverTargetName)
	{
		MYString command;
		command.append(MYText("ncmDump.exe \"")).append(FileName).append(MYText("\""));

		MYSystem(command.c_str());
		MYString name = GetNCM_MP3Name(FileName.c_str());
		MYCout << GetOutputString(name).c_str() << "转换成功" << endl;
	}
	MYCout << "共转换ncm文件" << ConverTargetName.size() << "个" << endl;
}

void CopyMusicFile()
{
	MYCout << "开始音乐文件的拷贝" << endl;
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	MYString p;
	hFile = FindFirstFile(p.assign(DownloadPath).append(MYText("\\*")).c_str(), &wfd);
	int count = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
			}
			else
			{//文件
				int Lenth = MyStrLen(wfd.cFileName);
				if (IsMusicTypeFile(wfd.cFileName))
				{
					MYString TargetName = TargetPath;
					TargetName = TargetName.append(MYText("\\")).append(wfd.cFileName);
					MYString SrcName = DownloadPath;
					SrcName = SrcName.append(MYText("\\")).append(wfd.cFileName);
					if (!IsFileExist(TargetName.c_str()))
					{
						MYCout << GetOutputString(TargetName).c_str() << "不存在，开始拷贝" <<endl;
						if (CopyFile(SrcName.c_str(), TargetName.c_str(), true))
						{
							MYCout << "    拷贝文件" << GetOutputString(TargetName).c_str() << endl;
							count++;
						}
						else
						{
							MYCout << "    拷贝失败：" << GetOutputString(TargetName).c_str() << endl;
						}
					}

				}
			}
		} while (FindNextFile(hFile, &wfd));
	}
	MYCout << "本次拷贝了" << count << "个文件"<<endl;
}

void SplitStr(MYString str, MYChar split_char, vector<MYString> &out)
{
	MYChar* pt = (MYChar*)str.c_str();
	MYChar* begin = pt;
	MYChar* end = MYStrChr(pt, split_char);
	while (end != NULL)
	{
		MYString temp;
		temp.insert(0, begin, end - begin);
		out.push_back(temp);
		begin = end + 1;
		end = MYStrChr(begin, split_char);
	}
	if (end == NULL && begin != NULL)
	{
		MYString temp;
		temp.insert(0, begin, pt + str.size() - begin);
		out.push_back(temp);
	}
}

MYString GetPureFileName(const MYChar* FileName)
{
	MYString Temp(FileName);
	int index = Temp.find_last_of('\\');
	MYString substr = Temp.substr(index+1);
	return substr;
}

bool IsDuplicateFile(const MYChar* filename)
{
	int Lenth = MyStrLen(filename);
	while (1)
	{
		Lenth--;
		if (Lenth < 0)
			break;
		if (filename[Lenth] == ')')
		{
			int PreIndex = Lenth - 1;
			if (PreIndex >= 0)
			{
				if (filename[PreIndex] >= '1' && filename[PreIndex] <= '9')
				{
					return true;
				}
				else
				{//防止删除Beyond - 天真的创伤 (第三版混音).ncm 这种格式的文件
					return false;
				}
			}
			break;
		}
	}
	return false;
}

string GetOutputString(MYString str)
{
#ifdef _UNICODE
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, str.c_str(), -1, NULL, 0, NULL, FALSE);

	char psText[128];
	memset(psText,0, 128);
	WideCharToMultiByte(CP_OEMCP, NULL, str.c_str(), -1, psText, dwNum, NULL, FALSE);
	return string(psText);
#else
	return str;
#endif
}