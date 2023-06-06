
#include "../function_library/function_library.h"
#include "windows.h"
#include <regex>
using namespace std; 
using namespace function_library;

#pragma comment(lib, "function_library")


class FileContainer
{
public:
	FILE* FileHandler = nullptr;
	FileContainer(const string& FileName, const string& Flag)
	{
		fopen_s(&FileHandler, FileName.c_str(), Flag.c_str());
	}
	~FileContainer()
	{
		if (FileHandler != nullptr)
			fclose(FileHandler);
	}
};


int main()
{
	vector<pair<string, string>> CsvFileNames;
	vector<string>  Types{ "csv" };

	char CurrentDirectory[256];
	GetCurrentDirectoryA(256, CurrentDirectory);


	function_library::GetDirectoryFiles(string(CurrentDirectory), CsvFileNames, Types, false);

	string SettingShoopName = "��Ʒ����";
	string SettingCommaName = "��ע";
	vector<string > ReplaceCommaName{"�Ա���ױ��Ŀ", "donation"};
	string ReplaceTargetName = "�Ա���ױ�ʻ�"; //donation  �Ա���ױ�ʻ�



	const string SplitComma = ",";
	const char* NewLine = "\n";
	vector<string> LineContent;
	for (int i = 0; i < CsvFileNames.size(); ++i)
	{
		string& FileName = CsvFileNames[i].second;
		cout << FileName.c_str() << endl;
		int ShopNameCol = -1;
		int CommaNameCol = -1;

		FileContainer CsvSrcFile(FileName.c_str(), "rb");
		FILE* pFile = CsvSrcFile.FileHandler;
		if (pFile == nullptr)
			continue;

		string SaveFileName = string_replace(FileName, ".", "_new.");

		FileContainer CsvSaveFile(SaveFileName.c_str(), "wb+");
		FILE* pSaveFile = CsvSaveFile.FileHandler;
		if (pSaveFile == nullptr)
			continue;

		FileContainer LogFile("Log.txt", "wb+");
		FILE* pLogFile = LogFile.FileHandler;
		if (pLogFile == nullptr)
			continue;

		char LineText[1024];
		int  RowIndex = 0;
		while (1)
		{
			if (RowIndex % 10000 == 0)
				cout << "start deal " << FileName <<", line " << RowIndex << endl;
			memset(LineText, 0, sizeof(LineText));
			void* pOver = fgets(LineText, sizeof(LineText) / sizeof(char), pFile);
			if (pOver == nullptr)
				break; 
			string RealLineText(LineText);

			int r_n_index = RealLineText.find("\r\n");
			if(r_n_index != -1)
				RealLineText.insert(r_n_index, ",");
			else
			{
				string format = string_format("%s �� %d�� û�л��з�\r\n", FileName.c_str(), RowIndex);
				fwrite(format.c_str(), sizeof(char), format.length(), pLogFile);
			}

			SplitStr(RealLineText, ',', LineContent);

			//��û�ҵ���Ʒ���ƺͱ�ע�У�ɨ��
			if (ShopNameCol == -1 || CommaNameCol == -1)
			{
				for (int ColIndex = 0; ColIndex < LineContent.size(); ++ColIndex)
				{
					string& CellContent = LineContent[ColIndex];
					if (CellContent == SettingShoopName)
						ShopNameCol = ColIndex;
					else if (CellContent == SettingCommaName)
					{
						CommaNameCol = ColIndex;
						//�ҵ���ע�У�ֱ�������м���հ׵�Ԫ
						LineContent.insert(LineContent.begin() + ColIndex + 1, "����");
						break;
					}
				}
			}
			else
			{//�Ѿ��ҵ���Ʒ���ƺͱ�ע�У���ʼд��
				int NewCellIndex = CommaNameCol + 1;
				if (LineContent.size() > ShopNameCol)
				{//��������Ʒ������Ϣ
					if (LineContent.size() > CommaNameCol)
					{//�����б�ע��Ϣ
						string ShopName = LineContent[ShopNameCol];
						string CommaName = LineContent[CommaNameCol];

						bool Contains = false;
						for (auto NameCell:ReplaceCommaName)
						{
							if (CommaName.find(NameCell) != -1)
							{
								Contains = true;
								break;
							}
						}
						if (Contains)
						{//�ҵ�
							LineContent.insert(LineContent.begin() + NewCellIndex, ReplaceTargetName);
						}
						else
							LineContent.insert(LineContent.begin() + NewCellIndex, ShopName);
					}
					else
					{//û�б�ע��Ϣ��
						string format = string_format("%d������Ʒ���Ƶ�û�б�ע��Ϣ\r\n", RowIndex);
						fwrite(format.c_str(), sizeof(char), format.length(), pLogFile);
					}
				}
			}

			for (int ColIndex = 0; ColIndex < LineContent.size(); ++ColIndex)
			{
				fwrite(LineContent[ColIndex].c_str(), sizeof(char), LineContent[ColIndex].length(), pSaveFile);
				if (ColIndex != LineContent.size() - 1)
					fwrite(SplitComma.c_str(), sizeof(char), SplitComma.length(), pSaveFile);
			}
			RowIndex++;

		}
		if (ShopNameCol == -1 && CommaNameCol == -1)
		{
			string format = string_format("%s û����Ʒ���ƺͱ�ע��\r\n", FileName.c_str());
			fwrite(format.c_str(), sizeof(char), format.length(), pLogFile);
		}
	}


	return 0;
}