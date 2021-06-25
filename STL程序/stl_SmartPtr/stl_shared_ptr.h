#pragma once

struct SharedPtrCls {
	int mId;
	SharedPtrCls(int id) :mId(id) {
		std::cout << "SharedPtrCls::Constructor" << std::endl;
	}
	~SharedPtrCls() {
		std::cout << "SharedPtrCls::Destructor" << std::endl;
	}
};
/*
����shared_ptr�����·�����
1���½�һ���յ�shared_ptr		std::shared_ptr<SharedPtrCls> ptr1
2����ԭ��ָ�봴��һshared_ptr	std::shared_ptr<SharedPtrCls> ptr2(new SharedPtrCls(2)); 
3��make_shared���죬�Ƽ���	std::shared_ptr<SharedPtrCls> ptr3 = make_shared<SharedPtrCls>(6);
4����������					std::shared_ptr<SharedPtrCls> ptr4 = ptr2; //��ptr4(ptr2)��Ч
5���ӹ�unique_ptrָ��        std::shared_ptr<SharedPtrCls> ptr5(std::move(u_ptr)); //�ӹ�֮��u_ptr������ָ�����Ȩ���൱��ptr5(u_ptr.release())
6������ԭ��ָ�룬ָ������������std::shared_ptr<int> ptr(new int, CallableObject);
�ɴ˿ɼ�shared_ptr���캯���ȿ��Խ���ԭ��ָ�룬Ҳ���Խ��ܹ�������ָ�롣
	����ԭ��ָ�룬��ӹܵ���ԭ��ָ��Ŀ���Ȩ���ӹܹ�������ָ�룬��������Ŀ�깲��ָ������ü���

�ж��Ƿ�Ϊ�գ�
1��if (!ptr1)
2��if (ptr1 == nullptr)

��ȡ���ü���
ptr.use_count();

�жϵ�ǰ�Ƿ���Ψһ����,���use_count()==1,�򷵻�true
ptr.unique();

��ֵ��
ptr1 = ptr2;  ptr1ԭ�������ü���-1��ptr2�����ü���+1
ptr.reset(raw_ptr);ԭ�������ü���-1��ptr����ָ���µ�ԭ��ָ��raw_ptr

ʹ�ã�
������ָ��һ��ʹ��
��ȡ��Ա������ptr->m_a;
ȡ����*ptr;
��ȡ����ָ�룺SharedPtrCls* p = ptr.get();

�ͷ�
1���Զ��ͷţ��뿪������֮��shared_ptr���ü���-1��Ϊ0��deleteָ��
2���ֶ��ͷ� ptr.reset();ǿ�������ü���-1

ע�⣺
1����ԭ��ָ�빹�칲������ָ��Ĺ��캯����explicit�ģ����Ա�����shared_ptr<int> p(new int)���ָ�ʽ����������shared_ptr p = new int���ָ�ʽ��
2��ʹ��ptr.get()��ȡԭ��ָ��󣬲�Ӧ��ɾ�����ԭ��ָ�룬���Ҳ��������ԭ��ָ��ȥ��ʼ���������ָ�롣
3�����Ҫ�����ԭ��ָ�벻���������������٣���ô���Դ�����������������Ը�������Ŀ��ָ�롣
*/
void TestSharedPtr()
{
	shared_ptr<SharedPtrCls> sha_ptr;								  //һ���յġ����Թ���SharedPtrCls�Ĺ�������ָ��
	shared_ptr<SharedPtrCls> sha_ptr2(new SharedPtrCls(2));			  //��ԭ��ָ�봴��һ��shared_ptr
	shared_ptr<SharedPtrCls> sha_ptr3 = make_shared<SharedPtrCls>(6); //make_shared������������Ĳ�������SharedPtrCls���캯���Ĳ���
	shared_ptr<SharedPtrCls> sha_ptr4 = sha_ptr2;					  //������ֵ
	shared_ptr<SharedPtrCls> sha_ptr5 = sha_ptr2;

	unique_ptr<SharedPtrCls> u_ptr(new SharedPtrCls(7));
	shared_ptr<SharedPtrCls> sha_ptr6(u_ptr.release());						   //�ӹ�unique_ptr��ָ��

	{
		auto destructor = [](int* p) { delete p; cout << "special destructor " << endl; };
		shared_ptr<int> temp_sha_ptr(new int, destructor);
	}
	if (sha_ptr6)
		cout << "sha_ptr6 is valid" << endl;
	if (u_ptr)
		cout << "u_ptr is valid" << endl;

	//�жϹ���ָ��ֻ���Ƿ���Ч
	if (sha_ptr)
		cout << "sha_ptr is not nullptr" << endl;
	if(sha_ptr2 != nullptr)
		cout << "sha_ptr2 is not nullptr" << endl;

	cout << "sha_ptr2 use_count:" << sha_ptr2.use_count() << endl;
	cout << "sha_ptr2 is unique:" << sha_ptr2.unique() << endl;
	cout << "sha_ptr3 is unique:" << sha_ptr3.unique() << endl;

	cout << "sha_ptr2 use_count:" << sha_ptr2.use_count() << endl;
	sha_ptr5 = sha_ptr3; //ptr5ԭ�������ü���-1��ptr3�����ü���+1
	cout << "sha_ptr2 use_count:" << sha_ptr2.use_count() << endl;

	SharedPtrCls* raw_ptr = sha_ptr2.get();  //��ȡԭ��ָ��
	sha_ptr4.reset();		//���ü���-1
	sha_ptr4 = sha_ptr2;
	sha_ptr4.reset(new SharedPtrCls(23));
	

}