#pragma once




/*
enable_shared_from_this
Q��ʲô��enable_shared_from_this��
A��enable_shared_from_this��һ��ģ���࣬���һ������Ҫ���ڲ����ⲿ�����Լ�������ָ�룬��Ӧ��public�̳����ģ���ࡣ

Q��Ϊʲôһ����Ҫ���ⲿ�����Լ�������ָ�룿
A�����Ƚ���Ϊʲô���ⲿ����ָ�룬Ȼ�����Ϊʲô���ݵ�������ָ�롣
   ��һЩ����£�һ����ʵ�������Ժ���Ҫ���Լ���ָ���ṩ���ⲿĳ��ģ��ʹ�ã�������һЩģ�彫�Լ�ע���ȥ���������Ҫ���ⲿ�����Լ���
   Ϊʲô��������ָ���أ���Ϊ���ⲿע���Լ��Ժ�֮��Ĺ���thisָ������Ѿ������٣���ô�ⲿʹ���Լ���ģ��ͻ�������⣬����ʹ������ָ�뱣�ֶ��Լ������á�
   ���ⲿ��������this��ģ�鶼ȡ���˶�this������֮�����Զ����١�

Q�����ⲿ���ݹ�������ָ��ֱ�ӷ���make_shared<T>(this)����������ΪʲôҪ�̳�enable_shared_from_this��
A������Ҫ֪�����������make_shared<T>(this)���Ǿ���ζ�Ž�ԭ��ָ��Ŀ���Ȩ��������Ȩ���������Ĺ���ָ�룬���ڹ���ָ�������ǽ�ֹ�ģ���ᵼ���ⲿ�Ĺ���ָ��
   ���Լ��ڲ�����Ĺ���ָ�����ͬһ��ԭ��ָ�룬���¶���ͷŵ����⡣

Q��enable_shared_from_this��ʵ��ԭ����ʲô��
A��enable_shared_from_this�ڲ���һ��weak_ptr����������׷��shared_ptr��Ȼ��shared_from_this�����������weak_ptr������һ��ǿ���õĹ���ָ��shared_ptr��

Q��ʲôʱ������ù���ָ���أ�
A�����ǿ��Կ������ܶ�ʱ�򣬲��ù���ָ��ֻ��ԭ��ָ��Ҳ�ܹ�����ֻ��Ҫ�ǵ�new delete��ʱ�����У���ô�治����һЩ���ֻ���ù���ָ����޷���ԭ��ָ���أ�����Ϊ������һ��
�������ָ����㣬�Ǿ���һ��ʵ�������Ժ���Ҫ���ܶ�����ģ��ʹ�ã���������ģ��ȡ�����õ��Ⱥ�˳���ʱ����δ֪�ģ����ʱ��ʹ�ù���ָ�����㣬�Լ������Ժ󣬰ѹ���
ָ���Ӹ���������ģ�飬�ȵ�����ģ�鶼ȡ�������Ժ���Զ��ͷš������������ԭ��ָ��ͺ��鷳������ģ��ʹ�õ���ԭ��ָ�룬��ֻ����nullptr�������ͷţ����Ҫ�������һ������
ģ����׷������ģ���ʹ�ã�������������nullptr�Ժ��ٽ���delete����ʵ�ɵ�Ҳ����shared_ptr�����顣

ע�⣺
class�̳���enable_shared_from_this����ô���ڲ�����shared_from_this()��ʱ�򣬱��뱣֤ԭ��ָ���ѱ�shared_ptr�����������ʧ�ܡ�ԭ��ܼ򵥣�shared_from_this����
weak_ptr����shared_ptr�ģ������controll block��û�У���Ȼû��weak_ptr��
*/
shared_ptr<class TestA> other_module_ptr;

class TestA : public enable_shared_from_this<TestA>
{
public:
	TestA(int i)
	{
		cout << "Constructor" << endl;
	}
	~TestA()
	{
		cout << "DeStructor" << endl;
	}
	void Prepare()
	{
		other_module_ptr = shared_from_this();
	}

	void Print() { cout << "hello " << endl; }
};

int TestSharedFromThis()
{
	{
		//����������a��ʵ�������ҽ��Լ�ע���������ģ�飬Ȼ��a�������ھͽ����ˣ�����Ϊ�ڲ�ʹ��shared_from_this�������������Լ���ǿ���ã�������Ȼ
		//a���������Ѿ����������������ͷš�
		shared_ptr<TestA> a = make_shared<TestA>(8);
		a->Prepare();
	}

	//����ʹ��aʵ��������ģ�飬��Ȼ�����Ŷ�a��ǿ����
	if (other_module_ptr)
		other_module_ptr->Print();
	//ʹ����֮�󣬼������ü���������Ž������Զ��ͷš�
	other_module_ptr.reset();

	return 0;
}