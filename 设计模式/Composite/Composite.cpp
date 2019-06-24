// Composite.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*Composite模式：组合模式
以下面代码为例，该模式的核心在于两点：一、Folder中包含一个Content列表 二、Folder本身也是一种Content
使用情况：树形结构处理
该模式是组件编程向前走了一步，即将Folder也设计为FolderContent的子类，而在纯粹的组件编程中，只存在Object与Component的关系。
如果把Contents放到FolderContent中，这样就不必要Folder类了，但是这从设计上来说会带来冗余和定位不分，因为File作为FolderContent的子类，它是叶子节点，不能
再存放东西了，所以Contents对于它来说是无用且无意义的。
*/

class FolderCotent
{
public:
	FolderCotent(string name) :m_name(name) {}
public:
	virtual void Print() = 0;
public:
	string m_name;

};
class File :public FolderCotent
{
public:
	File(string name) :FolderCotent(name) {}
public:
	virtual void Print() { cout << "文件: " << m_name.c_str() << endl; }
};
class Folder : public FolderCotent
{
public:
	Folder(string name) :FolderCotent(name) {}
public:
	vector<FolderCotent*> Contents;
public:
	virtual void Print()
	{
		cout << "文件夹: " << m_name.c_str() << endl;
		for (auto f : Contents)
			f->Print();
	}
public:
	void AddContent(FolderCotent* pContent)
	{
		Contents.push_back(pContent);
	}
};
int main()
{
	FolderCotent* file1 = new File("图片");
	FolderCotent* file2 = new File("文档");
	Folder* pFolder = new Folder("集合");
	pFolder->AddContent(file1);
	pFolder->AddContent(file2);
	pFolder->Print();
    std::cout << "Hello World!\n"; 
}
