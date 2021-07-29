// stl_multimap.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <map>

using namespace std;

/*
1、multimap不支持下标查找如map[6]，因为multimap里面可能有多个相同的值，所以下标查找没有意义，只能通过find函数返回迭代器。

*/
int main()
{
	//插入
	multimap<int, int> map;
	map.emplace(3, 301);
	map.emplace(3, 302);

 	map.insert(pair<int,int>(1, 101));
	map.insert({1, 102});
	map.emplace(1, 103);

	//插入，这里注意，multimap不仅允许相同的Key存在，而且允许相同的Key、Value存在！
	map.insert(pair<int, int>(2, 201));
	map.insert(pair<int, int>(2, 201));
	map.emplace(2, 202);

	//查找，获取某个Key的数量
	int count_1 = map.count(1);
	int count_2 = map.count(2);

	//查找，不等于map.end则找到，但这个函数无法知道具体数量
	auto ite = map.find(1);

	//修改
	ite->second = 1011;

	//第一种遍历方法，记录下key的数量count，获得迭代器后，迭代器++ count次
	for (int t = 0; t < count_1; ++t)
	{
		cout << "key:" << ite->first << " value:" << ite->second << endl;
		ite++;
	}

	//第二种遍历方法，获取key的上下限迭代器，要注意的是，下限迭代器指向的是有效数据，而上限是有效数据的下一个，也就是STL设计中的前闭后开原则。
	//这里ite_l指向{2,201}即第一个有效数据，ite_u指向{3,301}，即最后一个有效数据的下一个位置，如果没有的话就是end
	auto ite_l = map.lower_bound(2);
	auto ite_u = map.upper_bound(2);
	while (ite_l != ite_u)
	{
		cout << "key:" << ite_l->first << " value:" << ite_l->second << endl;
		ite_l++;
	}

	//第三种遍历方法，获取key的区间迭代器，和lower_bound upper_bound类似，first迭代器指向的是有效数据，而second是有效数据的下一个
	//这里range_ite.first指向{3,301}即第一个有效数据，range_ite.second指向end，即最后一个有效数据{3, 302}的下一个位置，这里是end
	using map_iterator = multimap<int, int>::iterator;
	pair<map_iterator, map_iterator> range_ite = map.equal_range(3);
	for (map_iterator ite1 = range_ite.first; ite1 != range_ite.second; ++ite1)
	{
		cout << "key:" << ite1->first << " value:" << ite1->second << endl;
	}

	//删除指定的key对应的所有键值对
	map.erase(2);

	//删除指定迭代器指向的键值对，这个方法只删除一个键值对
	ite = map.find(1);
	map.erase(ite);

	//获取multimap中所有键值对的数量
	int size = map.size();

	//判空
	if (map.empty())
		cout << "empty map" << endl;

	//multimap交换，和stl的其他容器操作相同
	multimap<int, int> map2;
	map2.emplace(6, 601);
	map2.emplace(6, 602);
	map.swap(map2);

	//multimap清空
	map.clear();
	if (map.empty())
		cout << "empty map" << endl;



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
