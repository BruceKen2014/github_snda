// Strategy.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;
/*
����ģʽ���õ�������Ե��α༭��Ϊ����
1��ͬһ��������в�ͬ�Ĵ�����ԣ����α༭���У��༭����״̬��ˢ����״̬����������Ĵ����ǲ�һ���ģ�
2��ͬʱֻ����һ�ֲ��Դ��ڣ��༭����״̬��ˢ����״ֻ̬��ͬʱ����һ�֣�
3�����Կ��ܻ���չ���Ժ���ܻ����Ӹ���ı༭״̬��
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
		cout << "�༭������Ӧ����" << endl;
	}
};

class EditStateBrush : public EditState
{
public:
	virtual void OnInput() override
	{
		cout << "ˢ������Ӧ����" << endl;
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

