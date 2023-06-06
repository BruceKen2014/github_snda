#pragma once
#include <list>
#include <vector>

using namespace std;

/*
* ����ͼ���ڽӱ�ʵ��
*/


//�ڵ㱾����Ϣ����������ơ�����λ�õȣ�����Ϊ�˼�������ֻ���һ����������
struct stNodeData
{
	int index = 0;
};

//����ͼ�е��ڽӽڵ�
struct stAdjNode
{
	struct stGraphNode*	 pConnectNode = nullptr;
	int Weight = 1; //�͸ýڵ�����ʱ���ߵ�Ȩ��
};

//����ͼ�еĽڵ�,����ڵ����������߼������ϵĽڵ�
struct stGraphNode
{
	stNodeData*  pData = nullptr; //�ڵ��Ӧ��ԭ������
	list<stAdjNode*>   pAdjList;  //�ڵ���ڽӽڵ�����
};

//�ڽӱ�ʵ�ֵ�ͼ
class AdjGraph
{
public:
	vector<stGraphNode> GraphNodes;
};
