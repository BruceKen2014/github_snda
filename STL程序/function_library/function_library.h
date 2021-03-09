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
	//�ж��ļ��Ƿ���type���͵��ļ�,��filename=123.mp3 type=.mp3
	static bool IsTypeFile(const MYString& filename, const MYString& type);
	/*
	�ж��ļ��Ƿ���type���͵��ļ�
	filename=123.mp3 
	types�����͵ļ�����=.mp3 .mp4
	*/
	static bool IsTypesFile(const MYString& filename, const vector<MYString>& types);

	//�ָ��ַ���
	static void SplitStr(const MYString& str, MYChar split_char, vector<MYString> &out);
	//��ȡ����cout������ַ���
	static string GetOutputString(MYString str);

	/*
	�滻�ļ��ĺ�׺��
	FileName   = "�������.mp3"
	TargetType = .cpp
	�滻��Ϊ�������.cpp
	*/
	static MYString ReplaceFileNameSuffix(const MYString& FileName, const MYString& TargetType);

	//��ȡ��·���ļ����Ĵ��ļ���,��C:\\hello\\1.txtת��Ϊ1.txt
	static MYString GetPureFileName(const MYChar* FileName);
	//��ȡ��·���ļ����Ĵ�·����,��C:\\hello\\1.txtת��ΪC:\\hello
	static MYString GetPureFilePath(const MYChar* FileName);

	//��ȡһ���ı��ļ�������������Ϊ��λ����ȡ���ַ���������
	static void ReadFileToStringArray(const MYString& FileName, vector<MYString>& StringArray);
	//���ַ�������д�뵽һ���ı��ļ���,Ĭ����\r\n�ָ��ַ���
	static void WriteStringArrayToFile(const MYString& FileName, const vector<MYString>& StringArray, const MYString SplitStr=MYText("\r\n"));

	//ɾ��һ���ַ���ĩβ��\r \n
	static void ReadStringEnd_r_n(MYChar* String);

	//���ļ��Ƿ����
	static bool IsFileExist(const MYString& FileName);

	/*
	��ȡָ��·�����������ָ�����͵��ļ�
	FolderPath:����·����D:\Software\KMPlayer
	FileName:�ļ�����first��·����second�ǵ������ļ�������D:\Software\KMPlayer new.cpp
	Types��ָ�����ļ����ͣ����Ϊ�գ��򷵻��������͵��ļ�
	Children:�Ƿ��������
	*/
	static void GetDirectoryFiles(const MYString& FolderPath, vector<pair<MYString, MYString>>& FileName, const vector<MYString>& Types, bool Children = true);
	
	/*
	ɾ��ָ��·�����������ָ�����͵��ļ�
	FolderPath:����·����D:\Software\KMPlayer
	Types��ָ�����ļ����ͣ����Ϊ�գ���ɾ���������͵��ļ�
	Children:�Ƿ����ɾ��
	Folder:�Ƿ�ɾ���ļ���
	Root:�Ƿ�ɾ����Ŀ¼
	Stage:���ڼ�¼�����㼶
	*/
	static void DeleteDirectoryFiles(const MYString& FolderPath, const vector<MYString>& Types, 
		bool Children= true, bool Folder = true, bool Root=false, int Stage=1);

	/*
	���˵�Դ�ַ����е����д�
	src_strԴ�ַ��������Сƽ�Ǵ󻵵�������ɱ�˺ܶ���
	censor_words���дʣ�����ʹ�����Ĵ���"��Сƽ"��Ҳ����ʹ�����{��,С,ƽ}
	����string�� ***�Ǵ󻵵�������ɱ�˺ܶ��� //�����������Ҫ�ٽ���һ������
	*/
	static bool CensorWord(const MYString& src_str, MYString& out_str, const vector<MYString>& censor_words);
};