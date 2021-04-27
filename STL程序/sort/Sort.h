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

//ð������:������һ����һ��㽻��ð��ȥ
template<typename T>
void BubbleSort(vector<T>& Array)
{
	//��һ��ѭ����Ϊð�ݶ��ٴ�
	//��һ��ѭ���Ĵ���Ϊsize-1������1 2 3��1 ��2 ð��֮��3���Զ�ȷ����λ�ã�����Ҫ�ٽ���һ��ð����
	for (size_t i = 0; i < Array.size()-1; ++i)
	{
		//�ڶ���ѭ����Ϊ����ð�ݹ����е�Ԫ�ؽ���
		//ÿ��ð�ݶ��ӵ�0��Ԫ�ؿ�ʼ�����յ���ݵ�ǰð�ݲ�����أ���Ϊ����ǰ����ð��֮�󣬺����Ԫ���Ѿ��Ǵ���ˣ�û��Ҫ�ٽ��жԱ�
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

//�������������α�������м伷ѹ
template<typename T>
void QuickSort(vector<T>& Array, size_t left, size_t right)
{
	if (Array.size() <= 1)
		return;
	if (left >= right)
		return;
	if (left > Array.size() - 1 || right > Array.size() - 1)
		return;
	//�Ա������������ߵ�ֵΪ����
	int Flag = Array[left];
	int i = left;
	int j = right;
	while (i < j)
	{
		//���α������ߣ��ұȲ���ֵС��Ԫ��
		while (j > i && Array[j] >= Flag)
			j--;
		if (i < j)
		{
			//�����Ԫ�ط������α��ϣ���ʱ���α��Ԫ�ؿ϶��Ȳ���ֵС���������α�����ǰ��1��
			Array[i++] = Array[j];
			PrintVector(Array);
		}
		//���α������ߣ��ұȲ���ֵ���Ԫ��
		while (j > i && Array[i] <= Flag)
			i++;
		if (i < j)
		{
			//�����Ԫ�ط������α��ϣ���ʱ���α��Ԫ�ؿ϶��Ȳ���ֵ���������α�����ǰ��1��
			Array[j--] = Array[i];
			PrintVector(Array);
		}
	}
	//�����α��غϣ������λ������Ϊ����Ԫ��
	Array[i] = Flag;

	//�ָ�Ϊ���Σ���������
	QuickSort(Array, left, i - 1);
	QuickSort(Array, i + 1, right);
}

//ѡ������ÿ�ζ�ѡ����С��ֵ
template<typename T>
void SelectionSort(vector<T>& Array)
{
	//��һ��ѭ���Ĵ���Ϊsize-1������1 2 3��1 ��2 ѡ��֮��3���Զ�ȷ����λ�ã�����Ҫ�ٽ���һ��ѡ����
	for (size_t i = 0; i < Array.size() - 1; ++i)
	{
		int MinIndex = i;
		//�ڶ���ѭ��������ѭ�������һ��Ԫ��
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

//��������һ�δβ�������
template<typename T>
void InsertSort(vector<T>& Array)
{
	//i���Ѿ�����õ�Ԫ�ظ�����Ĭ�ϵ�0����������ģ��ӵ�1����ʼ
	for (size_t i = 1; i < Array.size(); ++i)
	{
		//�ӵ�ǰ�ź�������һ����ʼ�Ա�
		//��������˵��ֱ�Ӳ��뼴�ɣ���ʵ�ʲ������ǲ�ȡ��ð�ݶԱȣ��ѵ�ǰ��Ԫ����ǰ�潻���Աȹ�ȥ
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

//�鲢����
template<typename T>
void MergeSort(vector<T>& Array)
{
	if (Array.size() <= 1)
		return;

	//���϶�Array���в�֣�ֱ��ֻ��1��Ԫ��
	//�ڲ���ڼ䣬ԭArray��Ԫ�ؾͱ����浽����Array��
	vector<T> leftArray { Array.begin(), Array.begin() + Array.size()/2 };
	vector<T> RightArray{ Array.begin() + Array.size() / 2, Array.end() };

	//�����������н��зֱ������ڲ�ֵ���СΪ1֮ǰ���ǲ�������κ�merge������
	MergeSort(leftArray);
	MergeSort(RightArray);

	//��ʱ�������ж���������ˣ����Ƕ�����������������merge

	//�����α꣬���α긺�������У����α긺��������
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
	//��ʣ�µ��������н��м�飬�������ʣ��Ԫ�أ���ӵ�ԭ����ĩβ
	while (LeftPoint < leftArray.size())
		Array[Element++] = leftArray[LeftPoint++];
	while (RightPoint < RightArray.size())
		Array[Element++] = RightArray[RightPoint++];
	PrintVector(Array);
}

//ϣ������
template<typename T>
void ShellSort(vector<T>& Array)
{
	for (auto GroupCount = Array.size() / 2; GroupCount >= 1; GroupCount = GroupCount / 2)
	{//ϣ������ѭ��
		//���������У����鱻��Ϊ��GroupCount�飬��������ÿһ����в�������
		for (decltype(GroupCount) group = 0; group < GroupCount; ++group)
		{//��ѭ��
			//һ������
			//����Ĵ�����ʵ���ǲ�������ĸĽ���
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



