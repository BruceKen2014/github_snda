// stl_map.cpp : �������̨Ӧ�ó������ڵ㡣
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
	map<string, string> feeling;	//�����ԭ��Ĺ���
	pair<map<string, string>::iterator, bool> ret;

	//map����
	feeling.insert(pair<string, string>("������","�ղ��õ���һѪ��"));
	ret = feeling.insert(pair<string, string>("����","�Ҳ����ղű�����һѪ��"));
	if(ret.second)	
		cout<<"����ɹ���"<<endl;

	//map����
	ret = feeling.insert(map<string, string>::value_type("�о��޵�","��ɱ��"));
	if(ret.second)	
		cout<<"����ɹ���"<<endl;
	feeling.insert(map<string, string>::value_type("��ŭ","���������ˣ�"));

	//map����
	feeling["����"] = "����ǿ�Ʒ�ɱ��";
	feeling["����"] = "������·��";

	//map����
	map<string, string>::iterator it = feeling.begin();
	for(; it != feeling.end(); it++)
		cout<<"���飺"<<(it->first)<<"~~~ԭ��:"<<it->second<<endl;
	//map����
	for (auto pair : feeling)
		cout << "���飺" << (pair.first) << "~~~ԭ��:" << pair.second << endl;

	//map����
	it = feeling.find("ϲ��");
	if(it != feeling.end())
		cout<<"�ҵ��� \"ϲ��\" ����";

	it = feeling.find("����");
	if(it != feeling.end())
		cout<<"�ҵ��� \"����\" ����";

	//map�п�
	if (feeling.empty())
		cout << "map is empty" << endl;

	if(feeling.count("����"))
		cout<<"�ҵ�������\"����\""<<endl;

	feeling.insert(pair<string, string>("����","��20ɱ0����������"));

	//mapɾ��
	it = feeling.find("ϲ��");
	if(it != feeling.end())
		feeling.erase(it);
	if(feeling.erase("����") == 0)
		cout<<"ɾ���ɹ�"<<endl;


	cout<<(feeling.lower_bound("������"))->first<<endl;
	it= (feeling.upper_bound("��"));
	if(it == feeling.end())
	{
		cout<<"û�ҵ��õ�����,uppder_bound����ʧ��"<<endl;
	}
	else
	{
		cout<<"�ҵ��˸õ����������������óɹ�"<<endl;
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


