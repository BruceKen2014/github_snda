

#include <regex>
#include <windows.h>
#include <corecrt_io.h>
#include "function_library.h"


bool function_library::IsTypeFile(const wstring& filename, const wstring& type)
{
	auto index = filename.find(type);
	return index != filename.npos;
}

bool function_library::IsTypeFile(const string& filename, const string& type)
{
	auto index = filename.find(type);
	return index != filename.npos;
}

bool function_library::IsTypesFile(const wstring& filename, const vector<wstring>& types)
{
	for (auto type : types)
	{
		if (IsTypeFile(filename, type))
			return true;
	}
	return false;
}

bool function_library::IsTypesFile(const string& filename, const vector<string>& types)
{
	for (auto type : types)
	{
		if (IsTypeFile(filename, type))
			return true;
	}
	return false;
}

void function_library::SplitStr(const wstring& str, wchar_t split_char, vector<wstring> &out)
{
	wchar_t* pt = (wchar_t*)str.c_str();
	wchar_t* begin = pt;
	wchar_t* end = wcschr(pt, split_char);
	while (end != NULL)
	{
		wstring temp;
		temp.insert(0, begin, end - begin);
		out.push_back(temp);
		begin = end + 1;
		end = wcschr(begin, split_char);
	}
	if (end == NULL && begin != NULL)
	{
		wstring temp;
		temp.insert(0, begin, pt + str.size() - begin);
		out.push_back(temp);
	}
}

void function_library::SplitStr(const string& str, char split_char, vector<string> &out)
{
	auto pt = (char*)str.c_str();
	auto begin = pt;
	auto end = strchr(pt, split_char);
	while (end != NULL)
	{
		string temp;
		temp.insert(0, begin, end - begin);
		out.push_back(temp);
		begin = end + 1;
		end = strchr(begin, split_char);
	}
	if (end == NULL && begin != NULL)
	{
		string temp;
		temp.insert(0, begin, pt + str.size() - begin);
		out.push_back(temp);
	}
}

std::string function_library::GetOutputString(wstring str)
{
#ifdef _UNICODE
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, str.c_str(), -1, NULL, 0, NULL, FALSE);

	char psText[128];
	memset(psText, 0, 128);
	WideCharToMultiByte(CP_OEMCP, NULL, str.c_str(), -1, psText, dwNum, NULL, FALSE);
	return string(psText);
#else
	return str;
#endif
}

std::string function_library::GetOutputString(string str)
{
	return str;
}

wstring function_library::ReplaceFileNameSuffix(const wstring& FileName, const wstring& TargetType)
{
	wregex reg_find(wstring(MYText("(.*)\\.(.*)$")));
	wstring target_str(FileName);

	wstring format(MYText("$1"));

	wstring TempTargetType = TargetType;

	//进行一层处理，如果传入的类型不带.，则我们要加上一个.
	if (TempTargetType.find(TEXT(".")) == TempTargetType.npos)
		TempTargetType = TEXT(".") + TempTargetType;
	format.append(TempTargetType);

	smatch search_result;
	wstring Ret = regex_replace(target_str, reg_find, format);

	return Ret;
}

std::string function_library::ReplaceFileNameSuffix(const string& FileName, const string& TargetType)
{
	regex reg_find(string("(.*)\\.(.*)$"));
	string target_str(FileName);

	string format("$1");

	string TempTargetType = TargetType;

	//进行一层处理，如果传入的类型不带.，则我们要加上一个.
	if (TempTargetType.find(".") == TempTargetType.npos)
		TempTargetType = (".") + TempTargetType;
	format.append(TempTargetType);

	smatch search_result;
	string Ret = regex_replace(target_str, reg_find, format);

	return Ret;
}

wstring function_library::GetFileNameNoExtension(const wstring& FileName)
{
	wstring Temp(FileName);
	auto index = Temp.find_last_of('.');
	wstring substr = Temp.substr(0, index);
	return substr;
}

std::string function_library::GetFileNameNoExtension(const string& FileName)
{
	auto index = FileName.find_last_of('.');
	string substr = FileName.substr(0, index);
	return substr;
}

wstring function_library::GetFileNameExtension(const wstring& FileName)
{
	auto index = FileName.find_last_of('.');
	auto substr = FileName.substr(index);
	return substr;
}

std::string function_library::GetFileNameExtension(const string& FileName)
{
	auto index = FileName.find_last_of('.');
	auto substr = FileName.substr(index);
	return substr;
}

int function_library::GetFileSize(const wstring& FileName)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FileName.c_str(), MYText("rb"));
	if (pFile == nullptr)
		return 0;
	fseek(pFile,0,SEEK_END);
	int Size = ftell(pFile);
	if (pFile != nullptr)
		fclose(pFile);
	return Size;
}

int function_library::GetFileSize(const string& FileName)
{
	FILE* pFile = nullptr;
	fopen_s(&pFile, FileName.c_str(), "rb");
	if (pFile == nullptr)
		return 0;
	fseek(pFile, 0, SEEK_END);
	int Size = ftell(pFile);
	if (pFile != nullptr)
		fclose(pFile);
	return Size;
}

wstring function_library::GetPureFileName(const wstring& FileName)
{
	auto index = FileName.find_last_of('\\');
	wstring substr = FileName.substr(index + 1);
	return substr;
}

std::string function_library::GetPureFileName(const string& FileName)
{
	auto index = FileName.find_last_of('\\');
	string substr = FileName.substr(index + 1);
	return substr;
}

wstring function_library::GetPureFilePath(const wstring&  FileName)
{
	auto index = FileName.find_last_of('\\');
	wstring substr = FileName.substr(0,index);
	return substr;
}

std::string function_library::GetPureFilePath(const string& FileName)
{
	auto index = FileName.find_last_of('\\');
	string substr = FileName.substr(0, index);
	return substr;
}

void function_library::ReadFileToStringArray(const wstring& FileName, vector<wstring>& StringArray)
{
	StringArray.clear();
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FileName.c_str(), MYText("rb"));
	if (pFile == nullptr)
		return;
	wchar_t LineText[1024];
	while(1)
	{
		memset(LineText, 0, sizeof(LineText));
		void* pOver = fgetws(LineText, sizeof(LineText)/sizeof(wchar_t), pFile);
		function_library::ReadStringEnd_r_n(LineText);
		auto TextLen = wcslen(LineText);
		if(TextLen > 0)
			StringArray.push_back(LineText);
		if (pOver == nullptr)
			break;
	}
	if (pFile != nullptr)
		fclose(pFile);
}

void function_library::ReadFileToStringArray(const string& FileName, vector<string>& StringArray)
{
	StringArray.clear();
	FILE* pFile = nullptr;
	fopen_s(&pFile, FileName.c_str(), "rb");
	if (pFile == nullptr)
		return;
	char LineText[1024];
	while (1)
	{
		memset(LineText, 0, sizeof(LineText));
		void* pOver = fgets(LineText, sizeof(LineText) / sizeof(wchar_t), pFile);
		function_library::ReadStringEnd_r_n(LineText);
		auto TextLen = strlen(LineText);
		if (TextLen > 0)
			StringArray.push_back(LineText);
		if (pOver == nullptr)
			break;
	}
	if (pFile != nullptr)
		fclose(pFile);
}

void function_library::WriteStringArrayToFile(const wstring& FileName, const vector<wstring>& StringArray, const wstring SplitStr)
{
	if (StringArray.size() == 0)
		return;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, FileName.c_str(), MYText("wb+"));
	if (pFile == nullptr)
		return;
	for (decltype(StringArray.size()) i = 0; i < StringArray.size(); ++i)
	{
		fwrite(StringArray[i].c_str(), sizeof(wchar_t), StringArray[i].length(), pFile);
		if (i != StringArray.size() - 1)
		{
			fwrite(SplitStr.c_str(), sizeof(wchar_t), SplitStr.length(), pFile);
		}
	}
	if (pFile != nullptr)
		fclose(pFile);
}

void function_library::WriteStringArrayToFile(const string& FileName, const vector<string>& StringArray, const string SplitStr /*="\r\n"*/)
{
	if (StringArray.size() == 0)
		return;

	FILE* pFile = nullptr;
	fopen_s(&pFile, FileName.c_str(), "wb+");
	if (pFile == nullptr)
		return;
	for (decltype(StringArray.size()) i = 0; i < StringArray.size(); ++i)
	{
		fwrite(StringArray[i].c_str(), sizeof(char), StringArray[i].length(), pFile);
		if (i != StringArray.size() - 1)
			fwrite(SplitStr.c_str(), sizeof(char), SplitStr.length(), pFile);
	}
	if (pFile != nullptr)
		fclose(pFile);
}

void function_library::ReadStringEnd_r_n(wchar_t* String)
{
	if (String == nullptr)
		return;

	auto Len = wcslen(String);
	if (Len == 0)
		return;
	if (String[Len - 1] == '\n')
		String[Len - 1] = 0;
	Len = wcslen(String);
	if (Len == 0)
		return;
	if (String[Len - 1] == '\r')
		String[Len - 1] = 0;
}

void function_library::ReadStringEnd_r_n(char* String)
{
	if (String == nullptr)
		return;

	auto Len = strlen(String);
	if (Len == 0)
		return;
	if (String[Len - 1] == '\n')
		String[Len - 1] = 0;
	Len = strlen(String);
	if (Len == 0)
		return;
	if (String[Len - 1] == '\r')
		String[Len - 1] = 0;
}

int function_library::GetBinaryOneCount(int Value)
{
	int count = 0;
	int flag = 1;
	while(flag)
	{
		if(flag & Value)
			count++;
		flag = flag << 1;
	}
	return count;
	/*
	//以下方法亦可，原理是：整数减去1后，整数最右边的1变成1,1之后的0全部变成1，这时把两个整数与操作，等于清空了最右边的1
	int count = 0;
	while (Value)
	{
		count++;
		Value = Value & (Value - 1);
	}
	*/
}

bool function_library::IsFileExist(const wstring& FileName)
{
	return _waccess(FileName.c_str(), 0) == 0;
}

bool function_library::IsFileExist(const string& FileName)
{
	return _access(FileName.c_str(), 0) == 0;

}

void function_library::GetDirectoryFiles(const wstring& FolderPath, vector<pair<wstring, wstring>>& FileNames, const vector<wstring>& Types, bool Children /*= true*/)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	wstring p;
	hFile = FindFirstFile(p.assign(FolderPath).append(MYText("\\*")).c_str(), &wfd);
	int count = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
				if (Children)
				{//递归扫描
					wstring TempFolderName = wfd.cFileName;
					if (TempFolderName.find(wchar_t('.')) == TempFolderName.npos)
						function_library::GetDirectoryFiles(FolderPath + MYText("\\") + wfd.cFileName, FileNames, Types, Children);
				}

			}
			else
			{//文件
				if (Types.size() == 0 || IsTypesFile(wfd.cFileName, Types))
					FileNames.push_back({ FolderPath, wstring(wfd.cFileName) });
			}
		} while (FindNextFile(hFile, &wfd));
	}
}

void function_library::GetDirectoryFiles(const string& FolderPath, vector<pair<string, string>>& FileNames, const vector<string>& Types, bool Children /*= true*/)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATAA wfd; //数据结构;
	string p;
	hFile = FindFirstFileA(p.assign(FolderPath).append(string("\\*")).c_str(), &wfd);
	int count = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
				if (Children)
				{//递归扫描
					string TempFolderName = wfd.cFileName;
					if (TempFolderName.find('.') == TempFolderName.npos)
						function_library::GetDirectoryFiles(FolderPath + "\\" + wfd.cFileName, FileNames, Types, Children);
				}

			}
			else
			{//文件
				if (Types.size() == 0 || IsTypesFile(wfd.cFileName, Types))
					FileNames.push_back({ FolderPath, wfd.cFileName});
			}
		} while (FindNextFileA(hFile, &wfd));
	}
}

void function_library::DeleteDirectoryFiles(const wstring& FolderPath, const vector<wstring>& Types, 
	bool Children, bool Folder, bool Root, int Stage)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	wstring p;
	hFile = FindFirstFile(p.assign(FolderPath).append(MYText("\\*")).c_str(), &wfd);
	int count = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
				if (Children)
				{//迭代
					wstring TempFolderName = wfd.cFileName;
					if (TempFolderName.find(wchar_t('.')) == TempFolderName.npos)
						function_library::DeleteDirectoryFiles(FolderPath + MYText("\\") + wfd.cFileName, Types, Children, Folder, Root, Stage+1);
				}
			}
			else
			{//文件
				if (Types.size() == 0 || IsTypesFile(wfd.cFileName, Types))
				{
					wstring RemoveFileName = FolderPath;
					RemoveFileName = RemoveFileName.append(MYText("\\")).append(wfd.cFileName);
					DeleteFile(RemoveFileName.c_str());
				}
			}
		} while (FindNextFile(hFile, &wfd));
	}
	FindClose(hFile);
	if (Folder)
	{//删除文件夹
		if (Stage == 1)
		{
			if (Root)
				RemoveDirectory(FolderPath.c_str());
		}
		else
		{
			RemoveDirectory(FolderPath.c_str());
		}
	}
}

void function_library::DeleteDirectoryFiles(const string& FolderPath, const vector<string>& Types, bool Children /*= true*/, bool Folder /*= true*/, bool Root /*= false*/, int Stage /*= 1*/)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATAA wfd; //数据结构;
	string p;
	hFile = FindFirstFileA(p.assign(FolderPath).append("\\*").c_str(), &wfd);
	int count = 0;
	if (hFile != INVALID_HANDLE_VALUE)
	{//find
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{//文件夹
				if (Children)
				{//迭代
					string TempFolderName = wfd.cFileName;
					if (TempFolderName.find(wchar_t('.')) == TempFolderName.npos)
						function_library::DeleteDirectoryFiles(FolderPath + "\\" + wfd.cFileName, Types, Children, Folder, Root, Stage + 1);
				}
			}
			else
			{//文件
				if (Types.size() == 0 || IsTypesFile(wfd.cFileName, Types))
				{
					auto RemoveFileName = FolderPath;
					RemoveFileName = RemoveFileName.append("\\").append(wfd.cFileName);
					DeleteFileA(RemoveFileName.c_str());
				}
			}
		} while (FindNextFileA(hFile, &wfd));
	}
	FindClose(hFile);
	if (Folder)
	{//删除文件夹
		if (Stage == 1)
		{
			if (Root)
				RemoveDirectoryA(FolderPath.c_str());
		}
		else
		{
			RemoveDirectoryA(FolderPath.c_str());
		}
	}
}

bool function_library::CensorWord(const wstring& src_str, wstring& out_str, const vector<wstring>& censor_words)
{
	//本来想用regex来处理，后来发现没必要，只用string本身的函数处理就足够了
	wstring ret = src_str;

	for (auto word : censor_words)
	{
		//对敏感词一个个扫描替换，一旦没有查找到其中一个，则返回false
		auto index = ret.find(word);
		if (index != ret.npos)
		{
			wstring replace_str;
			for (decltype(word.length()) i = 0; i < word.length(); ++i)
				replace_str += MYText("*");
			while (index != ret.npos)
			{
				ret.replace(index, word.length(), replace_str);
				index = ret.find(word);
			}

		}
		else
			return false;
	}

	out_str = ret;
	return true;
}

bool function_library::CensorWord(const string& src_str, string& out_str, const vector<string>& censor_words)
{
	//本来想用regex来处理，后来发现没必要，只用string本身的函数处理就足够了
	auto ret = src_str;

	for (auto word : censor_words)
	{
		//对敏感词一个个扫描替换，一旦没有查找到其中一个，则返回false
		auto index = ret.find(word);
		if (index != ret.npos)
		{
			string replace_str;
			for (decltype(word.length()) i = 0; i < word.length(); ++i)
				replace_str += "*";
			while (index != ret.npos)
			{
				ret.replace(index, word.length(), replace_str);
				index = ret.find(word);
			}
		}
		else
			return false;
	}

	out_str = ret;
	return true;
}

