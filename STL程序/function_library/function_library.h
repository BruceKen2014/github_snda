#pragma once
#include <string>
#include <vector>

using namespace std;

#ifdef _UNICODE
typedef  wchar_t MYChar;
typedef  wstring MYString;
typedef  wregex  MYRegex;
using MYSMatch = smatch;

#define MYText(txt) L##txt
#define MyStrLen wcslen
#define MYStrChr wcschr
#define MYStrCat wcscat
#define MYAccess _waccess
#define MYSystem _wsystem
#define MYfopen  _wfopen_s
#define MYfgets  fgetws
#define MYCout  cout
#else
typedef  char MYChar;
typedef  string MYString;
typedef  regex  MYRegex;
using MYSMatch = wsmatch;

#define MYText(txt) txt
#define MyStrLen strlen
#define MYStrChr strchr
#define MYStrCat strcat
#define MYAccess _access
#define MYSystem system
#define MYfopen  fopen_s
#define MYfgets  fgets
#define MYCout  cout

#endif

class function_library
{
public:
	//判断文件是否是type类型的文件,如filename=123.mp3 type=.mp3
	static bool IsTypeFile(const MYString& filename, const MYString& type);
	/*
	判断文件是否是type类型的文件
	filename=123.mp3 
	types是类型的集合如=.mp3 .mp4
	*/
	static bool IsTypesFile(const MYString& filename, const vector<MYString>& types);

	//分割字符串
	static void SplitStr(const MYString& str, MYChar split_char, vector<MYString> &out);
	//获取能向cout输出的字符串
	static string GetOutputString(MYString str);

	/*
	替换文件的后缀名
	FileName   = "你好张三.mp3"
	TargetType = .cpp
	替换后为你好张三.cpp
	*/
	static MYString ReplaceFileNameSuffix(const MYString& FileName, const MYString& TargetType);

	//获取带路径文件名的纯文件名,如C:\\hello\\1.txt转换为1.txt
	static MYString GetPureFileName(const MYChar* FileName);
	//获取带路径文件名的纯路径名,如C:\\hello\\1.txt转换为C:\\hello
	static MYString GetPureFilePath(const MYChar* FileName);

	//读取一个文本文件，将内容以行为单位，读取到字符串数组中
	static void ReadFileToStringArray(const MYString& FileName, vector<MYString>& StringArray);
	//将字符串数组写入到一个文本文件中,默认以\r\n分割字符串
	static void WriteStringArrayToFile(const MYString& FileName, const vector<MYString>& StringArray, const MYString SplitStr=MYText("\r\n"));

	//删除一个字符串末尾的\r \n
	static void ReadStringEnd_r_n(MYChar* String);

	//该文件是否存在
	static bool IsFileExist(const MYString& FileName);

	/*
	获取指定路径下面的所有指定类型的文件
	FolderPath:绝对路径如D:\Software\KMPlayer
	FileName:文件名，first是路径，second是单独的文件名，如D:\Software\KMPlayer new.cpp
	Types：指定的文件类型，如果为空，则返回所有类型的文件
	Children:是否迭代查找
	*/
	static void GetDirectoryFiles(const MYString& FolderPath, vector<pair<MYString, MYString>>& FileName, const vector<MYString>& Types, bool Children = true);
	
	/*
	删除指定路径下面的所有指定类型的文件
	FolderPath:绝对路径如D:\Software\KMPlayer
	Types：指定的文件类型，如果为空，则删除所有类型的文件
	Children:是否迭代删除
	Folder:是否删除文件夹
	Root:是否删除根目录
	Stage:用于记录迭代层级
	*/
	static void DeleteDirectoryFiles(const MYString& FolderPath, const vector<MYString>& Types, 
		bool Children= true, bool Folder = true, bool Root=false, int Stage=1);

	/*
	过滤掉源字符串中的敏感词
	src_str源字符串，如邓小平是大坏蛋，六四杀了很多人
	censor_words敏感词，可以使单独的词如"邓小平"，也可以使组合如{邓,小,平}
	返回string如 ***是大坏蛋，六四杀了很多人 //这里的六四需要再进行一波处理
	*/
	static bool CensorWord(const MYString& src_str, MYString& out_str, const vector<MYString>& censor_words);
};