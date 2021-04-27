#pragma once

#include <vector>
using namespace std;
template<typename T>
void PrintVector(vector<T>& Array)
{
	for (auto Data : Array)
		cout << Data << " ";
	cout << endl;
}

//冒泡排序:像泡泡一样，一层层交换冒上去
template<typename T>
void BubbleSort(vector<T>& Array)
{
	//第一层循环意为冒泡多少次
	//第一层循环的次数为size-1，比如1 2 3，1 和2 冒泡之后，3就自动确定了位置，不需要再进行一次冒泡了
	for (size_t i = 0; i < Array.size()-1; ++i)
	{
		//第二层循环意为本次冒泡过程中的元素交换
		//每次冒泡都从第0个元素开始，但终点根据当前冒泡层数相关，因为经过前面层的冒泡之后，后面的元素已经是大的了，没必要再进行对比
		for (size_t j = 0; j < Array.size() - 1 - i; ++j)
		{
			if (Array[j] > Array[j + 1])
			{
				int temp = Array[j];
				Array[j] = Array[j+1];
				Array[j + 1] = temp;
				PrintVector(Array);
			}
		}
	}
}

//快速排序，两个游标快速往中间挤压
template<typename T>
void QuickSort(vector<T>& Array, size_t left, size_t right)
{
	if (Array.size() <= 1)
		return;
	if (left >= right)
		return;
	if (left > Array.size() - 1 || right > Array.size() - 1)
		return;
	//以本次排序的最左边的值为参照
	int Flag = Array[left];
	int i = left;
	int j = right;
	while (i < j)
	{
		//右游标往左走，找比参照值小的元素
		while (j > i && Array[j] >= Flag)
			j--;
		if (i < j)
		{
			//把这个元素放在左游标上，此时左游标的元素肯定比参照值小，所以左游标往右前进1。
			Array[i++] = Array[j];
			PrintVector(Array);
		}
		//左游标往右走，找比参照值大的元素
		while (j > i && Array[i] <= Flag)
			i++;
		if (i < j)
		{
			//把这个元素放在右游标上，此时右游标的元素肯定比参照值大，所以右游标往左前进1。
			Array[j--] = Array[i];
			PrintVector(Array);
		}
	}
	//两个游标重合，把这个位置设置为参照元素
	Array[i] = Flag;

	//分割为两段，继续排序
	QuickSort(Array, left, i - 1);
	QuickSort(Array, i + 1, right);
}

//选择排序，每次都选择最小的值
template<typename T>
void SelectionSort(vector<T>& Array)
{
	//第一层循环的次数为size-1，比如1 2 3，1 和2 选择之后，3就自动确定了位置，不需要再进行一次选择了
	for (size_t i = 0; i < Array.size() - 1; ++i)
	{
		int MinIndex = i;
		//第二层循环，必须循环到最后一个元素
		for (size_t j = i + 1; j < Array.size(); ++j)
		{
			if(Array[j] < Array[MinIndex])
				MinIndex = j;
		}
		if (MinIndex != i)
		{
			int temp = Array[i];
			Array[i] = Array[MinIndex];
			Array[MinIndex] = temp;
		}
	}
}

//插入排序，一次次插入排序
template<typename T>
void InsertSort(vector<T>& Array)
{
	//i是已经插入好的元素个数，默认第0个就是有序的，从第1个开始
	for (size_t i = 1; i < Array.size(); ++i)
	{
		//从当前排好序的最后一个开始对比
		//理论上来说，直接插入即可，但实际操作，是采取了冒泡对比，把当前的元素向前面交换对比过去
		for (size_t j = i; j > 0; --j)
		{
			if (Array[j] >= Array[j - 1])
				break;
			auto value = Array[j];
			Array[j] = Array[j - 1];
			Array[j - 1] = value;
			PrintVector(Array);
		}
	}
}

//归并排序
template<typename T>
void MergeSort(vector<T>& Array)
{
	if (Array.size() <= 1)
		return;

	//不断对Array进行拆分，直到只有1个元素
	//在拆分期间，原Array的元素就被保存到了子Array中
	vector<T> leftArray { Array.begin(), Array.begin() + Array.size()/2 };
	vector<T> RightArray{ Array.begin() + Array.size() / 2, Array.end() };

	//对左右子序列进行分别排序，在拆分到最小为1之前，是不会进行任何merge操作的
	MergeSort(leftArray);
	MergeSort(RightArray);

	//此时左右序列都是有序的了，我们对两个有序的数组进行merge

	//两个游标，左游标负责左序列，由游标负责右序列
	decltype(leftArray.size()) LeftPoint = 0;
	decltype(leftArray.size()) RightPoint = 0;

	int Element = 0;
	while (LeftPoint < leftArray.size() && RightPoint < RightArray.size())
	{
		if (leftArray[LeftPoint] <= RightArray[RightPoint])
			Array[Element++] = leftArray[LeftPoint++];
		else
			Array[Element++] = RightArray[RightPoint++];
	}
	//对剩下的左右序列进行检查，如果还有剩余元素，添加到原数组末尾
	while (LeftPoint < leftArray.size())
		Array[Element++] = leftArray[LeftPoint++];
	while (RightPoint < RightArray.size())
		Array[Element++] = RightArray[RightPoint++];
	PrintVector(Array);
}

//希尔排序
template<typename T>
void ShellSort(vector<T>& Array)
{
	for (auto GroupCount = Array.size() / 2; GroupCount >= 1; GroupCount = GroupCount / 2)
	{//希尔增量循环
		//本次增量中，数组被分为了GroupCount组，接下来对每一组进行插入排序
		for (decltype(GroupCount) group = 0; group < GroupCount; ++group)
		{//组循环
			//一组排序
			//下面的代码其实就是插入排序的改进版
			for (size_t i = group + GroupCount; i < Array.size(); i += GroupCount)
			{
				for (size_t j = i; j > group; j -= GroupCount)
				{
					if (Array[j] >= Array[j - GroupCount])
						break;
					auto value = Array[j];
					Array[j] = Array[j - GroupCount];
					Array[j - GroupCount] = value;
					PrintVector(Array);
				}
			}
		}
		cout << endl;
	}
}



