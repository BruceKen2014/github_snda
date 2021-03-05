// function_library.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <regex>

using namespace std;
//判断文件是否是type类型的文件,如filename=123.mp3 type=mp3
bool IsTypeFile(string filename, string type);

//过滤掉源字符串中的敏感词
//src_str源字符串，如邓小平是大坏蛋，六四杀了很多人
//censor_words敏感词，如={邓,小,平}
//返回string如 ***是大坏蛋，六四杀了很多人 //这里的六四需要再进行一波处理
bool CensorWord(string src_str, string& out_str, const vector<string>& censor_words);


int main()
{
	string out_str;
	CensorWord("邓邓小的才平是大坏蛋", out_str, { "邓", "小", "平"});
	CensorWord("dengxiao的才ping是大坏蛋", out_str, { "deng", "xiao", "ping" });
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
bool IsTypeFile(string filename, string type)
{
	regex reg(string("(.+)\\.") + type + string("$"), regex_constants::icase); //忽略大小写
	smatch search_result;


	bool Ret = regex_search(filename, search_result, reg);
	return Ret;
}

bool CensorWord(string src_str, string& out_str, const vector<string>& censor_words)
{
	//本来想用regex来处理，后来发现没必要，只用string本身的函数处理就足够了
	string ret = src_str;

	for (auto word : censor_words)
	{
		//对敏感词一个个扫描替换，一旦没有查找到其中一个，则返回false
		auto index = ret.find(word);
		if(index != ret.npos)
		{
			string replace_str;
			for (decltype(word.length()) i = 0; i < word.length(); ++i)
				replace_str += '*';
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
