// WyyToMyFolder.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <corecrt_io.h>
#include <vector>
#include <Shlwapi.h>
#include <regex>
#include <utility>

#include "function_library.h"


using namespace std;

/*
1、扫描QQ音乐下载文件夹里面的文件，判读名字是否在我们的库里面能够找到，如果能够找到，说明音乐文件已存在，跳过，如果找不到，进行第2步
2、判断是否是普通未加密的文件，如果是，则直接拷贝到我们的库中，否则是加密文件，进入第3步
3、把加密的音乐文件拷贝到一个中间路径
至此本程序的工作结束


用解密工具对这个中间路径里面的加密文件进行解密，解密后的源文件会出现在windows当前用户的下载目录下

下一程序的工作
1、扫描指定的下载目录，判断是不是音乐文件（这个windows下载路径中有很多别的文件），如果是，判断文件在库中有没有，如果有则跳过，否则进入第2步
2、将音乐文件拷贝到库中，删除中间目录的临时文件

*/

//判断filename是否是需要拷贝的音乐文件
bool IsMusicTypeFile(const MYChar* filename);
//判断filename是否是QQ音乐的加密文件
bool IsMusicCompressTypeFile(const MYChar* filename);
//判断filename是否在过滤列表中
bool IsFilterFile(const MYString& filename);



//替换文件的后缀名
MYString ReplaceFileNameSuffix(const MYChar* FileName, const MYChar* TargetType);

//获取带路径文件名的纯文件名,如C://1.txt转换为1.txt
MYString GetPureFileName(const MYChar* FileName);

//扫描QQDownload下面的所有音乐文件，包括普通文件和加密文件
void ScanAllMusicFile(const MYString& FolderName);
//第一次的文件拷贝
void CopyMusicFile();
//第二次的文件拷贝
void CopyMusicFileSecond();
//删除临时目录中的加密文件
void RemoveTempFile(const MYString& FolderName);

//分割字符串
void SplitStr(MYString str, MYChar split_char, vector<MYString> &out);
string GetOutputString(MYString str);

//该文件是否存在
bool IsFileExist(const MYChar* FileName)
{
	return MYAccess(FileName, 0) == 0;
}
MYChar curr_dir[128];
MYChar QQDownloadPath[128];		//QQ音乐的下载路径
MYChar UserDownloadPath[128];   //windows用户的下载路径
MYChar TargetPath[128];         //歌曲库路径
MYChar TempPath[128];           //中间中转的临时路径


//第一个string是路径，第二个string是名字
vector<pair<MYString, MYString> > AllMusicFile;
vector<MYString> MusicFileType;
vector<MYString> QQMusicCompressType;
vector<pair<MYString, MYString>> CopyTempTargetName;
vector<MYString> FilterFileNames;
int main()
{
	GetCurrentDirectory(128, curr_dir);
	MYString InitPath(curr_dir);
	InitPath.append(MYText("\\setting.ini"));

	//QQ音乐下载路径
	GetPrivateProfileString(MYText("setting"), MYText("QQDowloadPath"), MYText(""), QQDownloadPath, 128, InitPath.c_str());
	//windows用户的下载路径
	GetPrivateProfileString(MYText("setting"), MYText("UserDowloadPath"), MYText(""), UserDownloadPath, 128, InitPath.c_str());
	//库路径
	GetPrivateProfileString(MYText("setting"), MYText("TargetPath"), MYText(""), TargetPath, 128, InitPath.c_str());
	//加密文件中转路径
	GetPrivateProfileString(MYText("setting"), MYText("TempPath"), MYText(""), TempPath, 128, InitPath.c_str());

	//拷贝的音乐文件类型
	MYChar Temp[128];
	memset(Temp, 0, 128);
	GetPrivateProfileString(MYText("setting"), MYText("CopyType"), MYText(""), Temp, 128, InitPath.c_str());
	SplitStr(Temp, ',', MusicFileType);

	//QQ音乐的加密文件类型
	memset(Temp, 0, 128);
	GetPrivateProfileString(MYText("setting"), MYText("QQMusicCompressType"), MYText(""), Temp, 128, InitPath.c_str());
	SplitStr(Temp, ',', QQMusicCompressType);

	//读取过滤文件
	function_library::ReadFileToStringArray(MYText("过滤文件.txt"), FilterFileNames);

	//扫描QQ音乐的下载路径里面所有的音乐文件
	MYCout << "扫描QQ音乐下载路径中的文件..." << endl;
	ScanAllMusicFile(QQDownloadPath);

	//进行第一次的音乐拷贝
	CopyMusicFile();

	int Ret = 1;
	if (CopyTempTargetName.size() != 0)
	{//有需要解密的文件
		cout << "请进行解密操作，解密成功后随便输入一个字符，然后回车触发文件拷贝..............." << endl;
		cin >> Ret;
		
		//解密完成，扫描是否有解密失败的文件，如果有，则将失败的文件名记录到过滤文件中
		//这个目的是，防止以后每次都扫描非法文件进行解密

		//解密过程完成后，在此输入一次，触发第二次的文件拷贝
		CopyMusicFileSecond();

		//将解密失败的文件名加入到过滤列表中
		function_library::WriteStringArrayToFile(MYText("过滤文件.txt"), FilterFileNames);

		MYCout << "开始删除中间文件" << endl;

		//二次拷贝以后，删除中间目录的文件
		RemoveTempFile(TempPath);
		//删除UserDownloadPath中生成的临时音乐文件
		RemoveTempFile(UserDownloadPath);
	}
	else
	{
		std::MYCout << "没有需要解密的文件" << endl;
	}
	for (auto filterName : FilterFileNames)
		std::MYCout << "过滤文件有：" << GetOutputString(filterName) << endl;
	std::MYCout << "press any key to continue!\n";
	cin >> Ret;
	
}

bool IsMusicTypeFile(const MYChar* filename)
{
	for (auto Type : MusicFileType)
	{
		if (function_library::IsTypeFile(filename, MYText(".") + Type))
			return true;
	}
	return false;
}
bool IsMusicCompressTypeFile(const MYChar* filename)
{
	for (auto Type : QQMusicCompressType)
	{
		if (function_library::IsTypeFile(filename, Type))
			return true;
	}
	return false;
}

bool IsFilterFile(const MYString& filename)
{
	for (auto filtername : FilterFileNames)
	{
		if (filtername == filename)
			return true;
	}
	return false;

}
MYString ReplaceFileNameSuffix(const MYChar* FileName, const MYChar* TargetType)
{
	wregex reg_find(MYString(MYText("(.*)\\.(.*)$")));
	MYString target_str(FileName);


	MYString format(MYText("$1"));
	format.append(MYText(".")).append(TargetType);

	wsmatch search_result;
	MYString Ret = regex_replace(target_str, reg_find, format);

	return Ret;
}


void ScanAllMusicFile(const MYString& FolderName)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	MYString p;
	hFile = FindFirstFile(p.assign(FolderName).append(MYText("\\*")).c_str(), &wfd);
	int count = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
				MYString TempFolderName = wfd.cFileName;
				if(TempFolderName.find(MYChar('.')) == TempFolderName.npos)
					ScanAllMusicFile(FolderName + MYText("\\") + wfd.cFileName);
			}
			else
			{//文件
				if (IsMusicTypeFile(wfd.cFileName) || IsMusicCompressTypeFile(wfd.cFileName))
					if (!IsFilterFile(wfd.cFileName))
						AllMusicFile.push_back(pair<MYString, MYString>(FolderName, MYString(wfd.cFileName)));
					else
						int iit = 0;
			}
		} while (FindNextFile(hFile, &wfd));
	}
}

void CopyMusicFile()
{
	MYCout << "开始QQ音乐文件的拷贝" << endl;

	int count = 0;
	for (auto pair : AllMusicFile)
	{
		if (IsMusicTypeFile(pair.second.c_str()))
		{
			MYString TargetName = TargetPath;
			TargetName = TargetName.append(MYText("\\")).append(pair.second.c_str());
			if (!IsFileExist(TargetName.c_str()))
			{
				MYString SrcName = pair.first;
				SrcName = SrcName.append(MYText("\\")).append(pair.second.c_str());

				MYCout << GetOutputString(TargetName).c_str() << "不存在，开始拷贝" << endl;
				if (CopyFile(SrcName.c_str(), TargetName.c_str(), true))
				{
					MYCout << "    拷贝文件" << GetOutputString(TargetName).c_str() << endl;
					count++;
				}
				else
					MYCout << "    拷贝失败：" << GetOutputString(TargetName).c_str() << endl;
			}

		}
		else if (IsMusicCompressTypeFile(pair.second.c_str()))
		{
			bool TargetExist = false;;
			//检测对应的目标音乐文件是否存在
			for (auto type : MusicFileType)
			{
				MYString TargetName = MYString(TargetPath).append(MYText("\\")).append(ReplaceFileNameSuffix(pair.second.c_str(), type.c_str()));
				if (IsFileExist(TargetName.c_str()))
				{//文件已经存在，不转换
					MYCout << GetOutputString(TargetName).c_str() << "已存在，不进行转换" << endl;
					TargetExist = true;
					break;
				}
			}
			if (!TargetExist)
			{//最终音乐文件不存在，拷贝到中间目录
				CopyTempTargetName.push_back(pair);
			}
		}
	}

	//将加密文件拷贝到中间目录中
	for (auto pair : CopyTempTargetName)
	{
		MYString TargetName = TempPath;
		TargetName = TargetName.append(MYText("\\")).append(pair.second);

		MYString SrcName = pair.first;
		SrcName = SrcName.append(MYText("\\")).append(pair.second);
		if (CopyFile(SrcName.c_str(), TargetName.c_str(), true))
			MYCout << "			拷贝临时文件成功" << GetOutputString(TargetName).c_str() << endl;
		else
			MYCout << "			拷贝临时文件失败：" << GetOutputString(TargetName).c_str() << endl;
	}
	MYCout << "本次拷贝直接音乐文件" << count << "个" << endl;
	MYCout << "本次拷贝加密音乐文件" << CopyTempTargetName.size() << "个" << endl;
}

void CopyMusicFileSecond()
{
	MYCout << "开始解密后的音乐文件的拷贝" << endl;
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	MYString p;
	hFile = FindFirstFile(p.assign(UserDownloadPath).append(MYText("\\*")).c_str(), &wfd);
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
					MYString SrcName = UserDownloadPath;
					SrcName = SrcName.append(MYText("\\")).append(wfd.cFileName);
					if (!IsFileExist(TargetName.c_str()))
					{
						MYCout << GetOutputString(TargetName).c_str() << "不存在，开始拷贝" << endl;
						if (CopyFile(SrcName.c_str(), TargetName.c_str(), true))
						{
							MYCout << "    拷贝文件" << GetOutputString(TargetName).c_str() << endl;
							count++;
						}
						else
							MYCout << "    拷贝失败：" << GetOutputString(TargetName).c_str() << endl;
					}
				}
			}
		} while (FindNextFile(hFile, &wfd));
	}
	MYCout << "加密文件有" << CopyTempTargetName.size() << "个" << endl;
	MYCout << "解密后拷贝音乐文件" << count << "个" << endl;


	//检测加密文件的最终生成文件，如果没找到，说明生成失败,加入到过滤列表中
	for (auto pair : CopyTempTargetName)
	{
		bool TargetExist = false;;
		//检测对应的目标音乐文件是否存在
		for (auto type : MusicFileType)
		{
			MYString TargetName = MYString(TargetPath).append(MYText("\\")).append(ReplaceFileNameSuffix(pair.second.c_str(), type.c_str()));
			if (IsFileExist(TargetName.c_str()))
			{//文件存在
				TargetExist = true;
				break;
			}
		}
		if (!TargetExist)
		{//最终音乐文件不存在，加入到过滤列表
			MYCout << "    解密失败：" << GetOutputString(pair.second).c_str() <<" 加入到过滤列表中"<< endl;
			FilterFileNames.push_back(pair.second);
		}
	}
}
void RemoveTempFile(const MYString& FolderName)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	MYString p;
	hFile = FindFirstFile(p.assign(FolderName).append(MYText("\\*")).c_str(), &wfd);
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
				if (IsMusicTypeFile(wfd.cFileName) || IsMusicCompressTypeFile(wfd.cFileName))
				{
					MYString RemoveFileName = FolderName;
					RemoveFileName = RemoveFileName.append(MYText("\\")).append(wfd.cFileName);
					DeleteFile(RemoveFileName.c_str());
					MYCout << "		删除临时文件" << GetOutputString(FolderName).c_str() <<":" << GetOutputString(wfd.cFileName).c_str() << endl;
				}

			}
		} while (FindNextFile(hFile, &wfd));
	}
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
	MYString substr = Temp.substr(index + 1);
	return substr;
}

string GetOutputString(MYString str)
{
#ifdef _UNICODE
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, str.c_str(), -1, NULL, 0, NULL, FALSE);

	char* psText = new char[str.length() *2 ];
	memset(psText, 0, str.length() * 2);
	WideCharToMultiByte(CP_OEMCP, NULL, str.c_str(), -1, psText, dwNum, NULL, FALSE);

	string Ret(psText);
	delete[] psText;
	return Ret;
#else
	return str;
#endif
}