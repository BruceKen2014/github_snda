// stl_map.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include<map>

using namespace std;

template<typename T1, typename T2>
void print_map(std::map<T1, T2> m)
{
	cout<<endl;
	for(std::map<T1, T2>::iterator it = m.begin(); it != m.end(); it++)
	{
		cout<<it->first<<":"<<it->second<<endl;
	}
	cout<<endl;
}
int _tmain(int argc, _TCHAR* argv[])
{
	map<string, string> feeling;	//心情和原因的关联
	pair<map<string, string>::iterator, bool> ret;

	//map插入
	feeling.insert(pair<string, string>("啊开心","刚才拿到了一血！"));
	ret = feeling.insert(pair<string, string>("悲剧","我擦，刚才被拿了一血！"));
	if(ret.second)	
		cout<<"插入成功！"<<endl;

	//map插入
	ret = feeling.insert(map<string, string>::value_type("感觉无敌","五杀！"));
	if(ret.second)	
		cout<<"插入成功！"<<endl;
	feeling.insert(map<string, string>::value_type("愤怒","被队友卖了！"));

	//map插入
	feeling["霸气"] = "塔下强势反杀！";
	feeling["绝望"] = "被破三路！";

	//map遍历
	map<string, string>::iterator it = feeling.begin();
	for(; it != feeling.end(); it++)
		cout<<"心情："<<(it->first)<<"~~~原因:"<<it->second<<endl;
	//map遍历
	for (auto pair : feeling)
		cout << "心情：" << (pair.first) << "~~~原因:" << pair.second << endl;

	//map查找
	it = feeling.find("喜悦");
	if(it != feeling.end())
		cout<<"找到了 \"喜悦\" 心情";

	it = feeling.find("霸气");
	if(it != feeling.end())
		cout<<"找到了 \"霸气\" 心情";

	//map判空
	if (feeling.empty())
		cout << "map is empty" << endl;

	if(feeling.count("悲剧"))
		cout<<"找到了心情\"悲剧\""<<endl;

	feeling.insert(pair<string, string>("畅快","哥20杀0死，哈哈！"));

	//map删除
	it = feeling.find("喜悦");
	if(it != feeling.end())
		feeling.erase(it);
	if(feeling.erase("霸气") == 0)
		cout<<"删除成功"<<endl;


	cout<<(feeling.lower_bound("啊开心"))->first<<endl;
	it= (feeling.upper_bound("不"));
	if(it == feeling.end())
	{
		cout<<"没找到该迭代器,uppder_bound调用失败"<<endl;
	}
	else
	{
		cout<<"找到了该迭代器，迭代器调用成功"<<endl;
		cout<<it->first<<endl;
	}
	map<int, int> m;
	map<int, int>::iterator it2;
	m[1] = 5;
	m[2] = 9;
	m[4] = 12;
	m[6] = 3;
	m[3] = 4;
	it2 = m.lower_bound(2);
	cout<<it2->first<<":"<<it2->second<<endl;
	it2 = m.lower_bound(6);
	cout<<it2->first<<":"<<it2->second<<endl;
	it2 = m.upper_bound(4);
	cout<<it2->first<<":"<<it2->second<<endl;
	it2 = m.upper_bound(4);
	cout<<it2->first<<":"<<it2->second<<endl;
	print_map(m);
	
	return 0;
}


