
#pragma  once
#define DexClass(c)  class c:public CRefCount

class CRefCount
{
protected:
	int m_count;

public:
	CRefCount();
	virtual ~CRefCount();

protected:
	virtual void ShutDown() = 0;   //�����������ã�ֻ�����������ͷ��Լ�ʱ����
public:
	void AddRef();
	int GetRefCount() { return m_count; }; //�������˶��ٴ�
	void ReduceRef();
};
CRefCount::CRefCount()
{
	m_count = 1;
}

CRefCount::~CRefCount()
{

}

void CRefCount::ShutDown()
{
	//�ͷ���Դ
}

void CRefCount::AddRef()
{
	m_count++;
}

void CRefCount::ReduceRef()
{
	if (m_count == 0)
		return;
	if (--m_count == 0)
	{
		ShutDown();
	}
}

DexClass(TestTexture)
{
public:
	TestTexture(){};
	virtual ~TestTexture(){};

protected:
	virtual void ShutDown(){};   //�����������ã�ֻ�����������ͷ��Լ�ʱ����
};
template<typename T> //�����T������CRefCount��������

class CPointRef
{
private:
	T* m_member;

public:
	CPointRef(T* _in)
	{
		m_member = _in;
	}
	CPointRef(const CPointRef<T>& _in)
	{
		m_member = _in.m_member;
	}
	~CPointRef()
	{
		m_member->ReduceRef();
	}
public:
	T* Get() { return m_member; };
	T* operator->()const{ return m_member; }
	CPointRef<T>& operator=(T* _in)
	{
		if (_in != m_member)
		{
			if (m_member)
				m_member->ReduceRef();
			m_member = _in;
			m_member->AddRef();
		}
		return *this;
	}
	CPointRef<T>& operator=(const CPointRef<T>& _in)
	{
		if (_in != this && m_member != _in.m_member)
		{
			if (m_member)
				m_member->ReduceRef();
			m_member = _in;
			m_member->AddRef();
		}
		return *this;
	}
};