#pragma once


/*
@Bruce 
@2018.1.12
ͨ�õĿɱ䳤���������,���ļ���ʵ����������
1������䳤��ĸ���
2�������䳤���е�ÿ�����������ҶԲ��������صش�������֧����չ������ʵ�������������Ƶı䳤��
SERIALIZE_IN��SERIALIZE_OUT�������ṩ�������л���Ĭ��֧��


����1�������̨����䳤�Ĳ���
a��������������������
b��ʵ�����䳤��
#define _COUT_X(X)	cout << X << endl;
#define _COUT_CHANGE_VAR(...)	_MACRO_DO__REAL(_COUT_X, __VA_ARGS__)
���ã�
int i = 0;
short j = 1;
string str = "ccc";
_COUT_CHANGE_VAR(i,j,str);

����1��������ָ�������������
a�����������������ָ��
b��ʵ�����䳤��
#define _PTR_PLUS_X(X)	X++;
#define _PTR_PLUS_VAR(...)	_MACRO_DO__REAL(_PTR_PLUS_X, __VA_ARGS__)
���ã�
int i[2];
short j[2];
Object o[2];
_PTR_PLUS_VAR(i,j,o);

*/

//_MACRO_ATTR_��������__VA_ARGS__��Ϊһ��������ı׶�
#define _MACRO_ATTR_(X) X  
#define  COUNT_MACRO_IMP(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,NUM)  NUM 

//�ú����������ԭ������COUNT_MACRO_IMP����һ��һ��ռ�ӣ�ǰ��ı������ˣ���һ��û����ľ��Ǻ��������
#define  COUNT_MACRO(...)  _MACRO_ATTR_(COUNT_MACRO_IMP(__VA_ARGS__,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))

//������MACRO_CAT�����##���߰�����Ļ����겻��չ���������м�MACRO_CAT_MACRO����һ���װ������չ��##���ߵĺ꣨����еĻ���
#define MACRO_CAT(A,B) A##B
#define MACRO_CAT_MACRO(A,B) MACRO_CAT(A,B)

#define _MACRO_DO__1(_DO,X)      _DO(X)
#define _MACRO_DO__2(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__1(_DO,__VA_ARGS__))
#define _MACRO_DO__3(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__2(_DO,__VA_ARGS__))
#define _MACRO_DO__4(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__3(_DO,__VA_ARGS__))
#define _MACRO_DO__5(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__4(_DO,__VA_ARGS__))
#define _MACRO_DO__6(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__5(_DO,__VA_ARGS__))
#define _MACRO_DO__7(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__6(_DO,__VA_ARGS__))
#define _MACRO_DO__8(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__7(_DO,__VA_ARGS__))
#define _MACRO_DO__9(_DO,X,...)  _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__8(_DO,__VA_ARGS__))
#define _MACRO_DO__10(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__9(_DO,__VA_ARGS__))
#define _MACRO_DO__11(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__10(_DO,__VA_ARGS__))
#define _MACRO_DO__12(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__11(_DO,__VA_ARGS__))
#define _MACRO_DO__13(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__12(_DO,__VA_ARGS__))
#define _MACRO_DO__14(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__13(_DO,__VA_ARGS__))
#define _MACRO_DO__15(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__14(_DO,__VA_ARGS__))
#define _MACRO_DO__16(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__15(_DO,__VA_ARGS__))
#define _MACRO_DO__17(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__16(_DO,__VA_ARGS__))
#define _MACRO_DO__18(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__17(_DO,__VA_ARGS__))
#define _MACRO_DO__19(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__18(_DO,__VA_ARGS__))
#define _MACRO_DO__20(_DO,X,...) _MACRO_DO__1(_DO,X)	_MACRO_ATTR_(_MACRO_DO__19(_DO,__VA_ARGS__))


#define _MACRO_DO__REAL(_DO, ...)	_MACRO_ATTR_(MACRO_CAT_MACRO(_MACRO_DO__,_MACRO_ATTR_(COUNT_MACRO(__VA_ARGS__)))(_DO,__VA_ARGS__)) 



#define _SERIALIZE_IN_1(X)    serializer << X;
#define SERIALIZE_IN(...)	  _MACRO_DO__REAL(_SERIALIZE_IN_1, __VA_ARGS__)

#define _SERIALIZE_OUT_1(X)   serializer >> X;
#define SERIALIZE_OUT(...)	  _MACRO_DO__REAL(_SERIALIZE_OUT_1, __VA_ARGS__)
