// Strategy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;
/*
策略模式适用的情况，以地形编辑器为例：
1、同一种情况，有不同的处理策略（地形编辑器中，编辑物体状态和刷地形状态，对于输入的处理是不一样的）
2、同时只能有一种策略存在（编辑物体状态和刷地形状态只能同时存在一种）
3、策略可能会扩展（以后可能会增加更多的编辑状态）
*/

class EditState
{
public:
	virtual void OnInput() = 0;
};

class EditStateObject : public EditState
{
public:
	virtual void OnInput() override
	{
		cout << "编辑物体响应输入" << endl;
	}
};

class EditStateBrush : public EditState
{
public:
	virtual void OnInput() override
	{
		cout << "刷地形响应输入" << endl;
	}
};

class Editor
{
public:
	Editor() :m_pEditorState(NULL) {};
public:
	void OnInput()
	{
		if (m_pEditorState != NULL)
			m_pEditorState->OnInput();
	}
	void SetEditorState(EditState* pEditState)
	{
		m_pEditorState = pEditState;
	}
protected:
	EditState* m_pEditorState;
};
int main()
{
	EditStateObject* pEditObject = new EditStateObject;
	EditStateBrush*  pEditBrush = new EditStateBrush;
	Editor* pEditor = new Editor;
	pEditor->SetEditorState(pEditObject);
	pEditor->OnInput();
	pEditor->SetEditorState(pEditBrush);
	pEditor->OnInput();
    return 0;
}

