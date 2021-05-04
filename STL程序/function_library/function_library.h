#pragma once
#include <string>
#include <vector>

using namespace std;

#ifdef _UNICODE
#define MYText(txt) L##txt
#else


#endif

class function_library
{
public:
	//�ļ����
#pragma region file
	//�ж��ļ��Ƿ���type���͵��ļ�,��filename=123.mp3 type=.mp3
	static bool IsTypeFile(const string& filename, const string& type);
	static bool IsTypeFile(const wstring& filename, const wstring& type);
	/*
	�ж��ļ��Ƿ���type���͵��ļ�
	filename=123.mp3 
	types�����͵ļ�����=.mp3 .mp4
	*/
	static bool IsTypesFile(const string& filename, const vector<string>& types);
	static bool IsTypesFile(const wstring& filename, const vector<wstring>& types);
	/*
	�滻�ļ��ĺ�׺��
	FileName   = "�������.mp3"
	TargetType = .cpp
	�滻��Ϊ�������.cpp
	*/
	static string   ReplaceFileNameSuffix(const string& FileName, const string& TargetType);
	static wstring ReplaceFileNameSuffix(const wstring& FileName, const wstring& TargetType);

	//��ȡ��·���ļ����Ĵ��ļ���,��C:\\hello\\1.txtת��Ϊ1.txt
	static string GetPureFileName(const string& FileName);
	static wstring GetPureFileName(const wstring& FileName);

	//��ȡ��·���ļ����Ĵ�·����,��C:\\hello\\1.txtת��ΪC:\\hello
	static string GetPureFilePath(const string& FileName);
	static wstring GetPureFilePath(const wstring& FileName);

	//��ȡ�ļ����Ĵ����ƣ���1.mp3����1
	static string GetFileNameNoExtension(const string& FileName);
	static wstring GetFileNameNoExtension(const wstring& FileName);

	//��ȡ�ļ����ĺ�׺����1.mp3����.mp3
	static string GetFileNameExtension(const string& FileName);
	static wstring GetFileNameExtension(const wstring& FileName);

	//��ȡ�ļ��Ĵ�С
	static int GetFileSize(const string& FileName);
	static int GetFileSize(const wstring& FileName);

	//��ȡһ���ı��ļ�������������Ϊ��λ����ȡ���ַ���������
	static void ReadFileToStringArray(const string& FileName, vector<string>& StringArray);
	static void ReadFileToStringArray(const wstring& FileName, vector<wstring>& StringArray);

	//���ַ�������д�뵽һ���ı��ļ���,Ĭ����\r\n�ָ��ַ���
	static void WriteStringArrayToFile(const string& FileName, const vector<string>& StringArray, const string SplitStr ="\r\n");
	static void WriteStringArrayToFile(const wstring& FileName, const vector<wstring>& StringArray, const wstring SplitStr=MYText("\r\n"));

	//���ļ��Ƿ����
	static bool IsFileExist(const string& FileName);
	static bool IsFileExist(const wstring& FileName);

	/*
	��ȡָ��·�����������ָ�����͵��ļ�
	FolderPath:����·����D:\Software\KMPlayer
	FileName:�ļ�����first��·����second�ǵ������ļ�������D:\Software\KMPlayer new.cpp
	Types��ָ�����ļ����ͣ����Ϊ�գ��򷵻��������͵��ļ�
	Children:�Ƿ��������
	*/
	static void GetDirectoryFiles(const string& FolderPath, vector<pair<string, string>>& FileNames, const vector<string>& Types, bool Children = true);
	static void GetDirectoryFiles(const wstring& FolderPath, vector<pair<wstring, wstring>>& FileNames, const vector<wstring>& Types, bool Children = true);
	
	/*
	ɾ��ָ��·�����������ָ�����͵��ļ�
	FolderPath:����·����D:\Software\KMPlayer
	Types��ָ�����ļ����ͣ����Ϊ�գ���ɾ���������͵��ļ�
	Children:�Ƿ����ɾ��
	Folder:�Ƿ�ɾ���ļ���
	Root:�Ƿ�ɾ����Ŀ¼
	Stage:���ڼ�¼�����㼶
	*/
	static void DeleteDirectoryFiles(const string& FolderPath, const vector<string>& Types, bool Children = true, bool Folder = true, bool Root = false, int Stage = 1);
	static void DeleteDirectoryFiles(const wstring& FolderPath, const vector<wstring>& Types, bool Children = true, bool Folder = true, bool Root = false, int Stage = 1);

#pragma  endregion

	//�ָ��ַ���
	static void SplitStr(const string& str, char split_char, vector<string> &out);
	static void SplitStr(const wstring& str, wchar_t split_char, vector<wstring> &out);

	//��ȡ����cout������ַ���
	static string GetOutputString(string str);
	static string GetOutputString(wstring str);

	//ɾ��һ���ַ���ĩβ��\r \n
	static void ReadStringEnd_r_n(char* String);
	static void ReadStringEnd_r_n(wchar_t* String);

	//����һ�������������е�1�ĸ���
	static int  GetBinaryOneCount(int Value);

	/*
	���˵�Դ�ַ����е����д�
	src_strԴ�ַ��������Сƽ�Ǵ󻵵�������ɱ�˺ܶ���
	censor_words���дʣ�����ʹ�����Ĵ���"��Сƽ"��Ҳ����ʹ�����{��,С,ƽ}
	����string�� ***�Ǵ󻵵�������ɱ�˺ܶ��� //�����������Ҫ�ٽ���һ������
	*/
	static bool CensorWord(const string& src_str, string& out_str, const vector<string>& censor_words);
	static bool CensorWord(const wstring& src_str, wstring& out_str, const vector<wstring>& censor_words);
};