// function_library.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <string>
#include <regex>

#include "function_library.h"

using namespace std;




int main()
{
	wstring out_str;
	function_library::CensorWord(MYText("�˵�С�Ĳ�ƽ�Ǵ󻵵�"), out_str, { MYText("��"), MYText("С"), MYText("ƽ") });
	function_library::CensorWord(MYText("dengxiao�Ĳ�ping�Ǵ󻵵�"), out_str, { MYText("deng"), MYText("xiao"), MYText("ping") });
	
	vector<pair<wstring, wstring>> FileNames;

	function_library::GetDirectoryFiles(MYText("D:\\Github\\github_snda"), FileNames,{MYText(".cpp"),MYText(".h") }, true);
	function_library::DeleteDirectoryFiles(MYText("C:\\Users\\Daying\\Desktop\\TestDelete"), {}, true);

	wstring ReplaceRet = function_library::ReplaceFileNameSuffix(MYText("�������.mp3"), MYText(".cpp"));
	wstring ReplaceRet2= function_library::ReplaceFileNameSuffix(MYText("�������.mp3"), MYText("cpp"));

	wstring PureName = function_library::GetPureFileName(MYText("D:\\Github\\github_snda\\12.obj"));
	wstring PurePath = function_library::GetPureFilePath(MYText("D:\\Github\\github_snda\\12.obj"));

	vector<wstring>  TextContent;
	function_library::ReadFileToStringArray(MYText("����ļ�.txt"), TextContent);

	vector<wstring> WriteContent {MYText("dddd"),MYText("�й���") };
	function_library::WriteStringArrayToFile(MYText("����ļ�.txt"), WriteContent);

	std::cout << "Hello World!\n";
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�