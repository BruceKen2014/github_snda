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
	//�ļ����
#pragma region file
	//�ж��ļ��Ƿ���type���͵��ļ�,��filename=123.mp3 type=.mp3
	bool IsTypeFile(const string& filename, const string& type);
	bool IsTypeFile(const wstring& filename, const wstring& type);
	/*
	�ж��ļ��Ƿ���type���͵��ļ�
	filename=123.mp3 
	types�����͵ļ�����=.mp3 .mp4
	*/
	bool IsTypesFile(const string& filename, const vector<string>& types);
	bool IsTypesFile(const wstring& filename, const vector<wstring>& types);
	/*
	�滻�ļ��ĺ�׺��
	FileName   = "�������.mp3"
	TargetType = .cpp
	�滻��Ϊ�������.cpp
	*/
	string   ReplaceFileNameSuffix(const string& FileName, const string& TargetType);
	wstring ReplaceFileNameSuffix(const wstring& FileName, const wstring& TargetType);

	//��ȡ��·���ļ����Ĵ��ļ���,��C:\\hello\\1.txtת��Ϊ1.txt
	string GetPureFileName(const string& FileName);
	wstring GetPureFileName(const wstring& FileName);

	//��ȡ��·���ļ����Ĵ�·����,��C:\\hello\\1.txtת��ΪC:\\hello
	string GetPureFilePath(const string& FileName);
	wstring GetPureFilePath(const wstring& FileName);

	//��ȡ�ļ����Ĵ����ƣ���1.mp3����1
	string GetFileNameNoExtension(const string& FileName);
	wstring GetFileNameNoExtension(const wstring& FileName);

	//��ȡ�ļ����ĺ�׺����1.mp3����.mp3
	string GetFileNameExtension(const string& FileName);
	wstring GetFileNameExtension(const wstring& FileName);

	//��ȡ�ļ��Ĵ�С
	int GetFileSize(const string& FileName);
	int GetFileSize(const wstring& FileName);

	//��ȡһ���ı��ļ�������������Ϊ��λ����ȡ���ַ���������
	void ReadFileToStringArray(const string& FileName, vector<string>& StringArray);
	void ReadFileToStringArray(const wstring& FileName, vector<wstring>& StringArray);

	//���ַ�������д�뵽һ���ı��ļ���,Ĭ����\r\n�ָ��ַ���
	void WriteStringArrayToFile(const string& FileName, const vector<string>& StringArray, const string SplitStr ="\r\n");
	void WriteStringArrayToFile(const wstring& FileName, const vector<wstring>& StringArray, const wstring SplitStr=L"\r\n");

	//���ļ��Ƿ����
	bool IsFileExist(const string& FileName);
	bool IsFileExist(const wstring& FileName);

	/*
	��ȡָ��·�����������ָ�����͵��ļ�
	FolderPath:����·����D:\Software\KMPlayer
	FileName:�ļ�����first��·����second�ǵ������ļ�������D:\Software\KMPlayer new.cpp
	Types��ָ�����ļ����ͣ����Ϊ�գ��򷵻��������͵��ļ�
	Children:�Ƿ��������
	*/
	void GetDirectoryFiles(const string& FolderPath, vector<pair<string, string>>& FileNames, const vector<string>& Types, bool Children = true);
	void GetDirectoryFiles(const wstring& FolderPath, vector<pair<wstring, wstring>>& FileNames, const vector<wstring>& Types, bool Children = true);
	
	/*
	ɾ��ָ��·�����������ָ�����͵��ļ�
	FolderPath:����·����D:\Software\KMPlayer
	Types��ָ�����ļ����ͣ����Ϊ�գ���ɾ���������͵��ļ�
	Children:�Ƿ����ɾ��
	Folder:�Ƿ�ɾ���ļ���
	Root:�Ƿ�ɾ����Ŀ¼
	Stage:���ڼ�¼�����㼶
	*/
	void DeleteDirectoryFiles(const string& FolderPath, const vector<string>& Types, bool Children = true, bool Folder = true, bool Root = false, int Stage = 1);
	void DeleteDirectoryFiles(const wstring& FolderPath, const vector<wstring>& Types, bool Children = true, bool Folder = true, bool Root = false, int Stage = 1);

#pragma  endregion

	//�ַ������
#pragma region string
	//�ָ��ַ���
	void SplitStr(const string& str, char split_char, vector<string> &out);
	void SplitStr(const wstring& str, wchar_t split_char, vector<wstring> &out);

	//��ȡ����cout������ַ���
	string GetOutputString(string str);
	string GetOutputString(wstring str);

	//ɾ��һ���ַ���ĩβ��\r \n
	void ReadStringEnd_r_n(char* String);
	void ReadStringEnd_r_n(wchar_t* String);

	/*
	���˵�Դ�ַ����е����д�
	src_strԴ�ַ��������Сƽ�Ǵ󻵵�������ɱ�˺ܶ���
	censor_words���дʣ�����ʹ�����Ĵ���"��Сƽ"��Ҳ����ʹ�����{��,С,ƽ}
	����string�� ***�Ǵ󻵵�������ɱ�˺ܶ��� //�����������Ҫ�ٽ���һ������
	*/
	bool CensorWord(const string& src_str, string& out_str, const vector<string>& censor_words);
	bool CensorWord(const wstring& src_str, wstring& out_str, const vector<wstring>& censor_words);
#pragma  endregion

	//����
#pragma region etc
	//����һ�������������е�1�ĸ���
	int  GetBinaryOneCount(int Value);
	
	//�������������ɶԳ��֣����õ�һ��������ʼ��¼ʱ�䣬���õڶ����������ؾ�����õ�һ�����������˶���ʱ��
	//���ڼ�����������֮��Ĵ���ʱ������,��λ����ms
	void  StartCountDurationTime();
	int   GetDurationTime();

	//��vector set list map�е�����Ԫ�������cout��,��Ҫ��������
	template<typename T>
	void PrintContainer(const T& vec)
	{
		for (const auto& value : vec)
			cout << value << " ";
		cout << endl;
	}
#pragma  endregion


};