// RemoveColon.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;
int main()
{
	FILE* ReadHandler= fopen("word.txt", "rb");
	char buffer[4096];
	const char*tt = "：";
	unsigned char t1 = tt[0];
	unsigned char t2 = tt[1];
	memset(buffer, 0, sizeof(buffer));
	if (ReadHandler == nullptr)
	{
		cout << "not find word.txt" << endl;
		return 0;
	}
	FILE* WriteFileHandle = fopen("wordnew.txt", "wb+");
	while (fgets(buffer, 4096, ReadHandler) != nullptr)
	{
		int index = 0;
		unsigned char* flag =(unsigned char*) buffer;
		bool endll = true;
		while (* flag !=0)
		{
			if ((*flag == 163 && flag[1] == 186))
			{
				fwrite("\r\n", 1, 2, WriteFileHandle);
				break;
			}
			if (*flag == ':')
			{
				fwrite("\r\n", 1, 2, WriteFileHandle);
				break;
			}
			fwrite(flag, 1, 1, WriteFileHandle);
			cout << *flag;
			flag++;
		}
		
		cout << endl;
		memset(buffer, 0, sizeof(buffer));
	}
	fclose(ReadHandler);
	fclose(WriteFileHandle);
    return 0;
}

