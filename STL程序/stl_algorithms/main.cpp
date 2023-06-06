
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//算法网址：https://en.cppreference.com/w/cpp/algorithm

/*
* 
* 
最常用的算法：swap sort reverse find remove fill
* 交换 swap
* 排序 sort
* 逆序 reverse
* 查找 finid
* 删除 remove
* 填充 fill
* 
算法适用场景：
===========================================非修改算法========================================================

查找
*《求个数》count 想知道无序区间内元素的个数：count count_if
*《判存在》any_of 想知道无序区间内满足条件的某个元素是否存在《》：any_of 

*《判存在》binary_search 想知道有序区间内满足条件的某个元素是否存在(binary_search内部是通过lower_bound实现的，它和lower_bound的关系就像是any_of和find的关系)
determines if an element exists in a partially-ordered range
========>bool：bool binary_search( ForwardIt first, ForwardIt last, const T& value );

*《判存在 找位置》find 想知道区间内满足条件的元素位置：find find_if find_if_not

*《判连续》adjacent_find 想知道区间内连续两个元素相等的位置
Searches the range [first, last) for two consecutive equal elements.
========>adjacent_find：ForwardIt adjacent_find( ForwardIt first, ForwardIt last );



*《找N连》search_n 想知道区间内连续N个元素相等的位置
Searches the range [first, last) for the first sequence of count identical elements, each equal to the given value.
========>search_n：ForwardIt search_n( ForwardIt first, ForwardIt last, Size count,const T& value );

*《全合法》all_of 想知道区间内是否全部为某个值：all_of 
*《全非法》none_of 想知道区间是否全不是某个值：none_of
*《批处理》for_ech 想批量对区间内的元素进行某种行为处理：for_ech for_each_n

*《分隔检测》is_partitioned 满足条件的都在前面，不满足条件的都在后面
determines if the range is partitioned by the given predicate
========>is_partitioned：bool is_partitioned( InputIt first, InputIt last, UnaryPredicate p );

*《判升序》is_sorted 判断容器是否按照升序排列
Checks if the elements in range [first, last) are sorted in non-descending order.
========>is_sorted：bool is_sorted( ForwardIt first, ForwardIt last );
========>is_sorted：bool is_sorted( ForwardIt first, ForwardIt last, Compare comp );

*《查找升序区间》is_sorted_until 判断容器是否按照升序排列
Examines the range [first, last) and finds the largest range beginning at first in which the elements are sorted in non-descending order.
========>is_sorted_until：ForwardIt is_sorted_until( ForwardIt first, ForwardIt last );
========>is_sorted_until：ForwardIt is_sorted_until( ForwardIt first, ForwardIt last, Compare comp );

*《找割点》partition_point 如果满足分割条件，查找分割点
Examines the partitioned (as if by std::partition) range [first, last) and locates the end of the first partition, that is, the first element that does not satisfy p or last if all elements satisfy p.
========>partition_point：ForwardIt partition_point( ForwardIt first, ForwardIt last, UnaryPredicate p );

*《升序序列找下限》lower_bound 在一个升序序列中，找出第一个大于等于目标元素的位置
returns an iterator to the first element not less than the given value
========>lower_bound：ForwardIt lower_bound( ForwardIt first, ForwardIt last, const T& value );

*《升序序列找上限》upper_bound 在一个升序序列中，找出第一个大于目标元素的位置
returns an iterator to the first element greater than a certain value
========>upper_bound：ForwardIt upper_bound( ForwardIt first, ForwardIt last, const T& value );

*《升序序列找等价区间》equal_range 在一个升序序列中，找出等于目标元素的迭代器区间
Returns a range containing all elements equivalent to value in the range [first, last).
========>equal_range：std::pair<ForwardIt,ForwardIt> equal_range( ForwardIt first, ForwardIt last, const T& value );
返回的首尾迭代器，区间中全部都是value。

------------------双容器算法---------------------------
*《两容器 找不同》mismatch 想找出两对区间内第一个不同的元素：mismatch
* 


*《两容器 找首个》find_first_of 想知道子串内的任意元素首先出现在第二区间内的位置： 
Searches the range [first, last) for any of the elements in the range [s_first, s_last).
========>find_first_of

*《两容器 找首串》search 想知道子串在第二个区间内第一个出现的位置
Searches for the first occurrence of the sequence of elements [s_first, s_last) in the range [first, last)
========>search

*《两容器 找末串》find_end 想知道子串在第二个区间内最后出现的位置：
Searches for the last occurrence of the sequence [s_first, s_last) in the range [first, last).
========>find_end

* 
* Q:同样是找元素，any_of 和find find_if的区别是什么？
* A：any_of直接返回bool，而find find_if返回迭代器，你需要判断迭代器和end的关系。如果只需要判存在，应用any_of，如果还需要处理存在的位置和元素，则应用find
*    它们的区别有点像是Unreal里面TArray的Contains和Find的区别。
* 
* Q:mismatch接受两个不同类型的迭代器，意味着什么？
* A:mismatch意味着两个容器可以是不同类型的容器！如vector<int> vector<float>二者是可以对比的！
* 
* Q:同样是找连续，adjacent_find是找两个连续相等的值，search_n是找n个连续相等的值，似乎后者完全覆盖了前者的功能？
* A:看似覆盖，其实不然。adjacent_find只需要传入首尾迭代器，不需要传入比较的值，只要序列中相邻两个元素相等就通过检测。
*   search_n必须传入要找的值，才能进行对比查找。如果只是想知道序列是否有相邻元素相等，则adjacent_find更简单。
* 
* 
* 注意点：
* find_end(ite1, ite2,_ite1,_ite2) 子串是后者_ite1 _ite2,前者ite1 ite2是要进行查找的目标区间
* search和search_n虽然只相差一个n，但二者的意义完全不一样。search是找首串，而seach_n是找n连。



==========================================修改算法========================================================
------------------单容器算法---------------------------
*《填充》fill 想把容器元素设置为指定的value
* Assigns the given value to the elements in the range [first, last).
========>fill:void fill( ForwardIt first, ForwardIt last, const T& value );
* Assigns the given value to the first count elements in the range beginning at first if count > 0. Does nothing otherwise.
========>fill_n:void fill_n( OutputIt first, Size count, const T& value );

*《生成》generate 想把元素批量生成到指定区间
* Assigns each element in range [first, last) a value generated by the given function object g.
========>generate:void generate( ForwardIt first, ForwardIt last, Generator g );
* Assigns values, generated by given function object g, to the first count elements in the range beginning at first, if count>0. Does nothing otherwise.
========>generate_n:void generate_n( OutputIt first, Size count, Generator g );

*《排序-不稳定》sort 默认升序排序，即元素要事先<运算符,不稳定排序，相同元素的前后顺序不保证
* Sorts the elements in the range [first, last) in non-descending order. The order of equal elements is not guaranteed to be preserved.
========>sort:void sort( RandomIt first, RandomIt last );

*《排序-稳定》stable_sort 默认升序排序，即元素要事先<运算符,稳定排序，相同元素的前后顺序有保证
* Sorts the elements in the range [first, last) in non-descending order. The order of equivalent elements is guaranteed to be preserved.
========>stable_sort:void stable_sort( RandomIt first, RandomIt last );

*《排序-查找第N小（大）的元素》nth_element 顾名思义，这个函数就是用来查找序列中第N个元素
* N位置前面的元素都比它小，后面的元素都比它大，但前后区间的内部元素的相对位置不保证。
* partially sorts the given range making sure that it is partitioned by the given element.
========>nth_element:void nth_element( RandomIt first, RandomIt nth, RandomIt last );
========>nth_element:void nth_element( RandomIt first, RandomIt nth, RandomIt last,Compare comp );

*《部分排序》partial_sort 默认升序排序，即元素要事先<运算符，只取first last区间里面的N个元素，排序到first second里面
* Rearranges elements such that the range [first, middle) contains the sorted middle − first smallest elements in the range [first, last).
* //这个算法这么理解呢？假设有一个容器，它保存了 100 万个数值，但我们只对其中最小的 100 个感兴趣。可以对容器的全部内容排序，然后选择前 100 个元素，但这可能有点消耗时间。这时候需要使用部分排序，只需要这些数中的前100个是有序放置的。
* //这里first表示首迭代器，last表示尾迭代器，middle表示中间区间，怎么理解这个中间区间？假设我们只要首尾的100个有序元素，那么middle就是first+100
* //算法最终会把first last里面的排好序的100个元素放置到fisrt-middle，后面的元素顺序没有保证。这种做法，要比全部排序效率高很多。
========>partial_sort:void partial_sort( RandomIt first, RandomIt middle, RandomIt last );
========>partial_sort:void partial_sort( RandomIt first, RandomIt middle, RandomIt last,Compare comp );

*《排序拷贝》partial_sort_copy 默认升序排序，即元素要事先<运算符，将first end里面的元素排序后拷贝进d_first d_last
* Sorts some of the elements in the range [first, last) in ascending order, storing the result in the range [d_first, d_last).
* 这个算法中只排序n个元素，n怎么计算？n = min(last - first, d_last - d_first)
========>partial_sort_copy:RandomIt partial_sort_copy( InputIt first, InputIt last,RandomIt d_first, RandomIt d_last );

*《替换》replace 想将容器内指定的值替换为新的值
* Replaces all elements satisfying specific criteria with new_value in the range [first, last).
========>replace:void replace( ForwardIt first, ForwardIt last, const T& old_value, const T& new_value );
========>replace_if:void replace_if( ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value );
* Copies the elements from the range [first, last) to another range beginning at d_first replacing all elements satisfying specific criteria with new_value.
========>replace_copy:OutputIt replace_copy( InputIt first, InputIt last, OutputIt d_first, const T& old_value, const T& new_value );
========>replace_copy_if:OutputIt replace_copy_if( InputIt first, InputIt last, OutputIt d_first,UnaryPredicate p, const T& new_value );

*《旋转》rotate 想把容器内的元素整体左移或者右移N位
* Performs a left rotation on a range of elements.
========>rotate:void rotate( ForwardIt first, ForwardIt n_first, ForwardIt last );
* Copies the elements from the range [first, last), to another range beginning at d_first in such a way, that the element *(n_first) becomes the first element of the new range and *(n_first - 1) becomes the last element.
========>rotate_copy:OutputIt rotate_copy( ForwardIt first, ForwardIt n_first,ForwardIt last, OutputIt d_first );

*《删除》remove 想删除容器内的满足条件的元素
* Removes all elements satisfying specific criteria from the range [first, last) and returns a past-the-end iterator for the new end of the range.
========>remove remove_if:ForwardIt remove( ForwardIt first, ForwardIt last, const T& value );

*《去重》unique 想删除容器内的相邻的重复的元素，只保留一份
* Eliminates all except the first element from every consecutive group of equivalent elements from the range [first, last) and returns a past-the-end iterator for the new logical end of the range.
========>unique:ForwardIt unique( ForwardIt first, ForwardIt last );

*《拷贝时去重》unique_copy 将容器内的元素拷贝另一个容器中，只保留相邻重复元素的第一个
* Copies the elements from the range [first, last), to another range beginning at d_first in such a way that there are no consecutive equal elements. Only the first element of each group of equal elements is copied.
========>unique_copy:OutputIt unique_copy( InputIt first, InputIt last, OutputIt d_first );

*《逆序》reverse reverse_copy 想将容器内元素的顺序颠倒
*  Reverses the order of the elements in the range [first, last).
========>reverse，原地逆序:void reverse( BidirIt first, BidirIt last );
*  Copies the elements from the range [first, last) to another range beginning at d_first in such a way that the elements in the new range are in reverse order.
========>reverse_copy，换地逆序:OutputIt reverse_copy( BidirIt first, BidirIt last, OutputIt d_first );

*《分列》partition 让容器内满足条件的排前面，不满足条件的排后面
* Reorders the elements in the range [first, last) in such a way that all elements for which the predicate p returns true precede the elements for which predicate p returns false. Relative order of the elements is not preserved.
========>partition:ForwardIt partition( ForwardIt first, ForwardIt last, UnaryPredicate p );这个版本排序后原先元素的相对顺序有可能改变
* Reorders the elements in the range [first, last) in such a way that all elements for which the predicate p returns true precede the elements for which predicate p returns false. Relative order of the elements is preserved.
========>stable_partition: stable_partition( BidirIt first, BidirIt last, UnaryPredicate p );这个版本是稳定版本，会保持原先元素的相对位置

*《打乱顺序》random_shuffle 想删除容器内的元素顺序打乱
* Reorders the elements in the given range [first, last) such that each possible permutation of those elements has equal probability of appearance.
========>random_shuffle:void random_shuffle( RandomIt first, RandomIt last );

*《随机样本》sample 想从容器内随机拿出N个元素
* Selects n elements from the sequence [first; last) (without replacement) such that each possible sample has equal probability of appearance, and writes those selected elements into the output iterator out. Random numbers are generated using the random number generator g.
========>sample:SampleIterator sample( PopulationIterator first, PopulationIterator last,SampleIterator out, Distance n,URBG&& g );

*《两容器 相拷贝》copy 想把第一个容器的元素拷贝给第二个容器
Copies the elements in the range, defined by [first, last), to another range beginning at d_first.
========>copy:OutputIt copy( InputIt first, InputIt last, OutputIt d_first );
========>copy_if:copy_if( InputIt first, InputIt last,OutputIt d_first,UnaryPredicate pred );
Copies exactly count values from the range beginning at first to the range beginning at result.
========>copy_n:OutputIt copy_n( InputIt first, Size count, OutputIt result );
Copies elements from the range [first, last), to another range beginning at d_first, omitting the elements which satisfy specific criteria. Source and destination ranges cannot overlap.
========>remove_copy:OutputIt remove_copy( InputIt first, InputIt last, OutputIt d_first,const T& value );
========>remove_copy_if:OutputIt remove_copy_if( InputIt first, InputIt last, OutputIt d_first,UnaryPredicate p );

* 《分类拷贝进容器》把满足条件的元素拷贝进第一个容器，不满足条件的元素拷贝进第二个容器
*  Copies the elements from the range [first, last) to two different ranges depending on the value returned by the predicate p. The elements that satisfy the predicate p are copied to the range beginning at d_first_true. The rest of the elements are copied to the range beginning at d_first_false.
========>partition_copy：partition_copy( InputIt first, InputIt last,OutputIt1 d_first_true, OutputIt2 d_first_false, UnaryPredicate p );

*《两容器 相移动》move 想把第一个容器内的元素移动到第二个容器中
* Moves the elements in the range [first, last), to another range beginning at d_first, starting from first and proceeding to last - 1. After this operation the elements in the moved-from range will still contain valid values of the appropriate type, but not necessarily the same values as before the move.
========>move：OutputIt move( InputIt first, InputIt last, OutputIt d_first );

*《两容器 后移动》move_backward 想把第一个容器内的元素逆向移动到第二个容器中，从后向前移动
* Moves the elements from the range [first, last), to another range ending at d_last. The elements are moved in reverse order (the last element is moved first), but their relative order is preserved.
========>move_backward：BidirIt2 move_backward( BidirIt1 first, BidirIt1 last, BidirIt2 d_last );

*《两容器，批转接》transform 想依次对容器内的元素进行处理，并将结果保存到另一个容器中
* std::transform applies the given function to a range and stores the result in another range, keeping the original elements order and beginning at d_first.
========>transform：OutputIt transform( InputIt first1,InputIt last1,OutputIt d_first,UnaryOperation unary_op );
========>transform：OutputIt transform( InputIt1 first1,InputIt1 last1,InputIt2 first2,OutputIt d_first,BinaryOperation binary_op );

交换
*《两容器，相交换》swap_ranges 想交换两个容器的元素
 * Exchanges elements between range [first1, last1) and another range starting at first2.
 ========>swap_range：ForwardIt2 swap_ranges( ForwardIt1 first1, ForwardIt1 last1,ForwardIt2 first2 );
 *《迭代器交换》iter_swap 交换两个迭代器指向的值
 * Swaps the values of the elements the given iterators are pointing to.
 ========>iter_swap：void iter_swap( ForwardIt1 a, ForwardIt2 b );

 * 
* 注意点：
* move函数调用了对象的移动赋值操作符，移动后，前者虽然未被销毁，但逻辑数据已被移走。
* for_each transform都有批处理的功能，不同的是for_each原地批处理，不涉及其他容器，而transfrom需要将结果保存到外部容器中。
* fill generate都有批量填充元素的功能，fill直接传要填充的值，更简单，而generate则传一个生成函数，能够做到更灵活的填充操作。
* remove在C++ reference官网给出的算法是快慢指针法，remove算法并没有改变容器的大小.
* reverse在C++ reference官网给出的算法是首尾指针法
* 同样是两容器间的拷贝，copy和remove_copy的区别在于copy只拷贝合法元素，而remove_copy会忽略合法元素。
	remove_copy对"remove"的含义体现得不准确。
* unique函数只删除相邻的重复元素，隔开的重复元素不处理。如果想要整体去重，应先排序，再去重。

---------------------------------其他算法---------------------------
*《二者交换》swap
* Exchanges the given values.
========>swap：void swap( T& a, T& b );
*《区间交换》swap_ranges
* Exchanges elements between range [first1, last1) and another range starting at first2
========>swap_ranges：ForwardIt2 swap_ranges( ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2 );
*《迭代器交换》iter_swap
* Swaps the values of the elements the given iterators are pointing to.
========>iter_swap：void iter_swap( ForwardIt1 a, ForwardIt2 b );
*/
struct Base
{
	Base(int v) :_v(v) { cout << "Base Default" << endl; }
	Base(const Base& Other) :_v(Other._v) {}
	Base(Base&& Other) :_v(Other._v) { cout << "Base Move" << endl; Other._v = -1; }
	int _v;

	Base& operator=(const Base& Other) { _v = (Other._v); return *this; }
	Base& operator=(Base&& Other) { _v = (Other._v); Other._v = -1; cout << "move operator" << endl; return *this; }

};
void test_algorithms()
{
	std::string s("hello");
	std::for_each(s.begin(), s.end(),[](auto& c){ c= std::toupper(c); });

	vector<Base>    vecint{ 1,2,3,4 };
	vector<Base>	vecfloat{ 5, 6,7,8,9 };
	std::move(vecint.begin(), vecint.end(), vecfloat.begin());

}

int main()
{
	{
		vector ve{ 1,2,2,3,3,4,4,5,5,6,6,7 };
		auto ite1 = lower_bound(ve.begin(), ve.end(), 4);
		auto ite2 = upper_bound(ve.begin(), ve.end(), 4);
		cout << *ite1 << ": " << ite1 - ve.begin() << endl;
		cout << *ite2 << ": " << ite2 - ve.begin() << endl;
	}
	vector ve{1,2,2,3,3,6,6,7};
	auto ite1 = lower_bound(ve.begin(), ve.end(), 4);
	auto ite2 = upper_bound(ve.begin(), ve.end(), 4);
	cout << *ite1 << ": " << ite1 - ve.begin() << endl;
	cout << *ite2 << ": " << ite2 - ve.begin() << endl;
	test_algorithms();
	cout << "hello world" << endl;
	return 0;
}