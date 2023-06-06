#pragma once
#include <list>
#include <vector>

using namespace std;

/*
* 无向图的邻接表实现
*/


//节点本身信息，如城市名称、地理位置等，这里为了简便起见，只存放一个数字索引
struct stNodeData
{
	int index = 0;
};

//无向图中的邻接节点
struct stAdjNode
{
	struct stGraphNode*	 pConnectNode = nullptr;
	int Weight = 1; //和该节点连接时，边的权重
};

//无向图中的节点,这个节点是真正的逻辑意义上的节点
struct stGraphNode
{
	stNodeData*  pData = nullptr; //节点对应的原生数据
	list<stAdjNode*>   pAdjList;  //节点的邻接节点链表
};

//邻接表实现的图
class AdjGraph
{
public:
	vector<stGraphNode> GraphNodes;
};
