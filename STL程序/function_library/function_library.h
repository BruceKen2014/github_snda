#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

#define MYText(str)  L##str

template<typename T1, typename T2>
std::ostream& operator <<(std::ostream& os, const std::pair<T1, T2>& pair)
{
	os << pair.first << ":" << pair.second << " ";
	return os;
}

namespace function_library
{
	//文件相关
#pragma region file
	//判断文件是否是type类型的文件,如filename=123.mp3 type=.mp3
	bool IsTypeFile(const string& filename, const string& type);
	bool IsTypeFile(const wstring& filename, const wstring& type);
	/*
	判断文件是否是type类型的文件
	filename=123.mp3 
	types是类型的集合如=.mp3 .mp4
	*/
	bool IsTypesFile(const string& filename, const vector<string>& types);
	bool IsTypesFile(const wstring& filename, const vector<wstring>& types);
	/*
	替换文件的后缀名
	FileName   = "你好张三.mp3"
	TargetType = .cpp
	替换后为你好张三.cpp
	*/
	string   ReplaceFileNameSuffix(const string& FileName, const string& TargetType);
	wstring ReplaceFileNameSuffix(const wstring& FileName, const wstring& TargetType);

	//获取带路径文件名的纯文件名,如C:\\hello\\1.txt转换为1.txt
	string GetPureFileName(const string& FileName);
	wstring GetPureFileName(const wstring& FileName);

	//获取带路径文件名的纯路径名,如C:\\hello\\1.txt转换为C:\\hello
	string GetPureFilePath(const string& FileName);
	wstring GetPureFilePath(const wstring& FileName);

	//获取文件名的纯名称，如1.mp3返回1
	string GetFileNameNoExtension(const string& FileName);
	wstring GetFileNameNoExtension(const wstring& FileName);

	//获取文件名的后缀，如1.mp3返回.mp3
	string GetFileNameExtension(const string& FileName);
	wstring GetFileNameExtension(const wstring& FileName);

	//获取文件的大小
	int GetFileSize(const string& FileName);
	int GetFileSize(const wstring& FileName);

	//读取一个文本文件，将内容以行为单位，读取到字符串数组中
	void ReadFileToStringArray(const string& FileName, vector<string>& StringArray);
	void ReadFileToStringArray(const wstring& FileName, vector<wstring>& StringArray);

	//将字符串数组写入到一个文本文件中,默认以\r\n分割字符串
	void WriteStringArrayToFile(const string& FileName, const vector<string>& StringArray, const string SplitStr ="\r\n");
	void WriteStringArrayToFile(const wstring& FileName, const vector<wstring>& StringArray, const wstring SplitStr=L"\r\n");

	//该文件是否存在
	bool IsFileExist(const string& FileName);
	bool IsFileExist(const wstring& FileName);

	/*
	获取指定路径下面的所有指定类型的文件
	FolderPath:绝对路径如D:\Software\KMPlayer
	FileName:文件名，first是路径，second是单独的文件名，如D:\Software\KMPlayer new.cpp
	Types：指定的文件类型，如果为空，则返回所有类型的文件
	Children:是否迭代查找
	*/
	void GetDirectoryFiles(const string& FolderPath, vector<pair<string, string>>& FileNames, const vector<string>& Types, bool Children = true);
	void GetDirectoryFiles(const wstring& FolderPath, vector<pair<wstring, wstring>>& FileNames, const vector<wstring>& Types, bool Children = true);
	
	/*
	删除指定路径下面的所有指定类型的文件
	FolderPath:绝对路径如D:\Software\KMPlayer
	Types：指定的文件类型，如果为空，则删除所有类型的文件
	Children:是否迭代删除
	Folder:是否删除文件夹
	Root:是否删除根目录
	Stage:用于记录迭代层级
	*/
	void DeleteDirectoryFiles(const string& FolderPath, const vector<string>& Types, bool Children = true, bool Folder = true, bool Root = false, int Stage = 1);
	void DeleteDirectoryFiles(const wstring& FolderPath, const vector<wstring>& Types, bool Children = true, bool Folder = true, bool Root = false, int Stage = 1);

#pragma  endregion

	//字符串相关
#pragma region string
	//分割字符串
	void SplitStr(const string& str, char split_char, vector<string> &out);
	void SplitStr(const wstring& str, wchar_t split_char, vector<wstring> &out);

	//获取能向cout输出的字符串
	string GetOutputString(string str);
	string GetOutputString(wstring str);

	//删除一个字符串末尾的\r \n
	void ReadStringEnd_r_n(char* String);
	void ReadStringEnd_r_n(wchar_t* String);

	/*
	过滤掉源字符串中的敏感词
	src_str源字符串，如邓小平是大坏蛋，六四杀了很多人
	censor_words敏感词，可以使单独的词如"邓小平"，也可以使组合如{邓,小,平}
	返回string如 ***是大坏蛋，六四杀了很多人 //这里的六四需要再进行一波处理
	*/
	bool CensorWord(const string& src_str, string& out_str, const vector<string>& censor_words);
	bool CensorWord(const wstring& src_str, wstring& out_str, const vector<wstring>& censor_words);
#pragma  endregion

	//其他
#pragma region etc
	//计算一个整数二进制中的1的个数
	int  GetBinaryOneCount(int Value);
	
	//以下两个函数成对出现，调用第一个函数开始记录时间，调用第二个函数返回距离调用第一个函数经过了多少时间
	//用于计算两个函数之间的代码时间消耗,单位毫秒ms
	void  StartCountDurationTime();
	int   GetDurationTime();

	//将vector set list map中的所有元素输出到cout中,主要用来调试
	template<typename T>
	void PrintContainer(const T& vec)
	{
		for (const auto& value : vec)
			cout << value << " ";
		cout << endl;
	}
#pragma  endregion


};