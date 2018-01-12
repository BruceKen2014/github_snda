#pragma once


/*
@Bruce 
@2018.1.12
通用的可变长宏参数定义,本文件可实现两个功能
1、计算变长宏的个数
2、遍历变长宏中的每个参数，并且对参数进行特地处理，并且支持扩展，可以实例化无数个定制的变长宏
SERIALIZE_IN与SERIALIZE_OUT两个宏提供对于序列化的默认支持


例子1：向控制台输出变长的参数
a、定义宏来输出单个参数
b、实例化变长宏
#define _COUT_X(X)	cout << X << endl;
#define _COUT_CHANGE_VAR(...)	_MACRO_DO__REAL(_COUT_X, __VA_ARGS__)
调用：
int i = 0;
short j = 1;
string str = "ccc";
_COUT_CHANGE_VAR(i,j,str);

例子1：对所有指针进行自增操作
a、定义宏来操作单个指针
b、实例化变长宏
#define _PTR_PLUS_X(X)	X++;
#define _PTR_PLUS_VAR(...)	_MACRO_DO__REAL(_PTR_PLUS_X, __VA_ARGS__)
调用：
int i[2];
short j[2];
Object o[2];
_PTR_PLUS_VAR(i,j,o);

*/

//_MACRO_ATTR_用来消除__VA_ARGS__作为一个宏参数的弊端
#define _MACRO_ATTR_(X) X  
#define  COUNT_MACRO_IMP(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,NUM)  NUM 

//该宏计算宏个数的原理是往COUNT_MACRO_IMP里面一个一个占坑，前面的被填上了，第一个没被填的就是宏参数个数
#define  COUNT_MACRO(...)  _MACRO_ATTR_(COUNT_MACRO_IMP(__VA_ARGS__,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))

//单纯的MACRO_CAT，如果##两边包含宏的话，宏不会展开，所以中间MACRO_CAT_MACRO加了一层包装，用以展开##两边的宏（如果有的话）
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
