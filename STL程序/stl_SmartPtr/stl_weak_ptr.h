#pragma once

/*
����weak_ptr�����·���
1���½�һ���յ�������ָ��			weak_ptr<int> ptr;		
2���ù�������ָ���ʼ��			weak_ptr<int> ptr(sha_ptr);
1���ñ��������ָ���ʼ��			weak_ptr<int> ptr(other_weak_ptr);

�ͷ�
��Ϊֻ����ָ�룬���Բ����������ͷ����ڴ棬ֻ�Ƿ������Լ���ԭ��ָ������ã�����֮�⣬�����ı��κ���
1�� ptr = nullptr;
2�� ptr.reset();

��ȡԭ��ָ���ǿ��������
ptr.use_count();

�ж�ԭ��ָ���Ƿ���Ч
1��ptr.expired(); ���use_count()==0,����true�����򷵻�false
2��ptr.lock(); ��ȡshared_ptr���ж����shared_ptr�Ƿ���Ч

ʹ��ԭ��ָ��
�������lock��������ȡshared_ptr��Ȼ��ʹ�����shared_ptr����
shared_ptr<int> sp = ptr0.lock();
if(sp)
  do someting...
*/
void TestWeakPtr()
{
	weak_ptr<int> ptr0;				//�½�һ���յĿ���ָ��int��������ָ��
	shared_ptr<int> sha_ptr = make_shared<int>(3);
	weak_ptr<int> ptr1(sha_ptr);	//�½�һ��ָ��������ָ���������ָ��
	weak_ptr<int> ptr2(ptr1);		//�ñ�Ĺ�������ָ���ʼ��

	if (shared_ptr<int> sp = ptr2.lock())
	{
		cout << *sp << endl;
	}
}