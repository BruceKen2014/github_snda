

#include <regex>
#include <windows.h>
#include <corecrt_io.h>
#include "function_library.h"


bool function_library::IsTypeFile(const MYString& filename, const MYString& type)
{
	auto index = filename.find(type);
	return index != filename.npos;
}

bool function_library::IsTypesFile(const MYString& filename, const vector<MYString>& types)
{
	for (auto type : types)
	{
		if (IsTypeFile(filename, type))
			return true;
	}
	return false;
}

void function_library::SplitStr(const MYString& str, MYChar split_char, vector<MYString> &out)
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

std::string function_library::GetOutputString(MYString str)
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

MYString function_library::ReplaceFileNameSuffix(const MYString& FileName, const MYString& TargetType)
{
	MYRegex reg_find(MYString(MYText("(.*)\\.(.*)$")));
	MYString target_str(FileName);

	MYString format(MYText("$1"));

	MYString TempTargetType = TargetType;

	//进行一层处理，如果传入的类型不带.，则我们要加上一个.
	if (TempTargetType.find(TEXT(".")) == TempTargetType.npos)
		TempTargetType = TEXT(".") + TempTargetType;
	format.append(TempTargetType);

	MYSMatch search_result;
	MYString Ret = regex_replace(target_str, reg_find, format);

	return Ret;
}

MYString function_library::GetFileNameNoExtension(const MYString& FileName)
{
	MYString Temp(FileName);
	auto index = Temp.find_last_of('.');
	MYString substr = Temp.substr(0, index);
	return substr;
}

MYString function_library::GetFileNameExtension(const MYString& FileName)
{
	MYString Temp(FileName);
	auto index = Temp.find_last_of('.');
	MYString substr = Temp.substr(index);
	return substr;
}

int function_library::GetFileSize(const MYString& FileName)
{
	FILE* pFile = nullptr;
	MYfopen(&pFile, FileName.c_str(), MYText("rb"));
	if (pFile == nullptr)
		return 0;
	fseek(pFile,0,SEEK_END);
	int Size = ftell(pFile);
	if (pFile != nullptr)
		fclose(pFile);
	return Size;
}

MYString function_library::GetPureFileName(const MYChar* FileName)
{
	MYString Temp(FileName);
	auto index = Temp.find_last_of('\\');
	MYString substr = Temp.substr(index + 1);
	return substr;
}

MYString function_library::GetPureFilePath(const MYChar* FileName)
{
	MYString Temp(FileName);
	auto index = Temp.find_last_of('\\');
	MYString substr = Temp.substr(0,index);
	return substr;
}

void function_library::ReadFileToStringArray(const MYString& FileName, vector<MYString>& StringArray)
{
	StringArray.clear();
	FILE* pFile = nullptr;
	MYfopen(&pFile, FileName.c_str(), MYText("rb"));
	if (pFile == nullptr)
		return;
	MYChar LineText[1024];
	while(1)
	{
		memset(LineText, 0, sizeof(LineText));
		void* pOver = MYfgets(LineText, sizeof(LineText)/sizeof(MYChar), pFile);
		function_library::ReadStringEnd_r_n(LineText);
		int TextLen = MyStrLen(LineText);
		if(TextLen > 0)
			StringArray.push_back(LineText);
		if (pOver == nullptr)
			break;
	}
	if (pFile != nullptr)
		fclose(pFile);
}

void function_library::WriteStringArrayToFile(const MYString& FileName, const vector<MYString>& StringArray, const MYString SplitStr)
{
	if (StringArray.size() == 0)
		return;

	FILE* pFile = nullptr;
	MYfopen(&pFile, FileName.c_str(), MYText("wb+"));
	if (pFile == nullptr)
		return;
	int charsize = sizeof(MYChar);
	for (decltype(StringArray.size()) i = 0; i < StringArray.size(); ++i)
	{
		fwrite(StringArray[i].c_str(), sizeof(MYChar), StringArray[i].length(), pFile);
		if (i != StringArray.size() - 1)
		{
			fwrite(SplitStr.c_str(), sizeof(MYChar), SplitStr.length(), pFile);
		}
	}
	if (pFile != nullptr)
		fclose(pFile);
}

void function_library::ReadStringEnd_r_n(MYChar* String)
{
	if (String == nullptr)
		return;

	int Len = MyStrLen(String);
	if (Len == 0)
		return;
	if (String[Len - 1] == '\n')
		String[Len - 1] = 0;
	Len = MyStrLen(String);
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

bool function_library::IsFileExist(const MYString& FileName)
{
	return MYAccess(FileName.c_str(), 0) == 0;
}

void function_library::GetDirectoryFiles(const MYString& FolderPath, vector<pair<MYString, MYString>>& FileNames, const vector<MYString>& Types, bool Children /*= true*/)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	MYString p;
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
					MYString TempFolderName = wfd.cFileName;
					if (TempFolderName.find(MYChar('.')) == TempFolderName.npos)
						function_library::GetDirectoryFiles(FolderPath + MYText("\\") + wfd.cFileName, FileNames, Types, Children);
				}

			}
			else
			{//文件
				if (Types.size() == 0 || IsTypesFile(wfd.cFileName, Types))
					FileNames.push_back({ FolderPath, MYString(wfd.cFileName) });
			}
		} while (FindNextFile(hFile, &wfd));
	}
}

void function_library::DeleteDirectoryFiles(const MYString& FolderPath, const vector<MYString>& Types, 
	bool Children, bool Folder, bool Root, int Stage)
{
	HANDLE hFile = 0;
	WIN32_FIND_DATA wfd; //数据结构;
	MYString p;
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
					MYString TempFolderName = wfd.cFileName;
					if (TempFolderName.find(MYChar('.')) == TempFolderName.npos)
						function_library::DeleteDirectoryFiles(FolderPath + MYText("\\") + wfd.cFileName, Types, Children, Folder, Root, Stage+1);
				}
			}
			else
			{//文件
				if (Types.size() == 0 || IsTypesFile(wfd.cFileName, Types))
				{
					MYString RemoveFileName = FolderPath;
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

bool function_library::CensorWord(const MYString& src_str, MYString& out_str, const vector<MYString>& censor_words)
{
	//本来想用regex来处理，后来发现没必要，只用string本身的函数处理就足够了
	MYString ret = src_str;

	for (auto word : censor_words)
	{
		//对敏感词一个个扫描替换，一旦没有查找到其中一个，则返回false
		auto index = ret.find(word);
		if (index != ret.npos)
		{
			MYString replace_str;
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

