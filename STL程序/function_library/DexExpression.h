
#ifndef _DEX_EXPRESSION_H
#define _DEX_EXPRESSION_H

#include <map>
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

/*
解析表达式
*/

#define MAX_EXPR_STRING 256

//* / % 在同级优先级
enum EExprOp
{
	OP_ADD     = '+',	    // +
	OP_MINUS   = '-',		// -
	OP_MUL     = '*',       // *
	OP_DIVIDE  = '/',	    // /
	OP_LEFT_B  = '(',		// (   
	OP_RIGHT_B = ')',		// )  
	OP_BIT_AND = '&',       // &
	OP_BIT_OR  = '|',       // |
	OP_COMMA   = ',',       // ,  逗号
	OP_MO      = '%',
	OP_AND,                 // &&
	OP_OR,                  // ||
	
};
enum EExprType
{
	Expr_None,
	Expr_OP, 
	Expr_Int,  
	Expr_Float,
	Expr_String,
	Expr_Fun,
};

//如果两个表达式的值进行了运算，那么两个类型该以什么类型运算。比如int + float，则返回float
extern EExprType GetEExprTypeOpType(EExprType type1, EExprType type2);

struct stExpStackValue
{
	EExprType type;
	union
	{
		EExprOp op_value;
		int     i_value;
		float   f_value;
		char    s_value[64];
		char    fun_value[64];
	};
	stExpStackValue()
	{
		type = EExprType::Expr_None;
		memset(s_value, 0, sizeof(s_value));
	}

	void SetOperation(EExprOp value);
	void SetInt(int value);
	void SetFloat(float value);
	void SetString(const char* value);
	void SetFunction(const char* value);

	int	   GetInt()const;
	float  GetFloat()const;
	string GetString()const;

	stExpStackValue operator + (const stExpStackValue& val) const
	{
		stExpStackValue ret;
		ret.type = GetEExprTypeOpType(type, val.type);
		switch(ret.type)
		{
		case Expr_Int:
			{
				ret.i_value = GetInt() + val.GetInt();
				break;
			}
		case Expr_Float:
			{
				ret.f_value = GetFloat() + val.GetFloat();
				break;
			}
		case Expr_String:
			{
				if(strlen(s_value) + strlen(val.s_value) < MAX_EXPR_STRING)
				{
					strcat_s(ret.s_value, s_value);
					strcat_s(ret.s_value, val.s_value);
				}	
				else
				{
					cout << "字符串长度过长" << endl;
					//DexLog::getSingleton()->Log(log_allert, "字符串长度过长\n");
					//DexLog::getSingleton()->EndLog();
				}
				break;
			}
		} 
		return ret;
	}
	stExpStackValue operator - (const stExpStackValue& val) const
	{
		stExpStackValue ret;
		ret.type = GetEExprTypeOpType(type, val.type);
		switch (ret.type)
		{
		case Expr_Int:
		{
			ret.i_value = GetInt() - val.GetInt();
			break;
		}
		case Expr_Float:
		{
			ret.f_value = GetFloat() - val.GetFloat();
			break;
		}
		case Expr_String:
		{
			break;
		}
		}
		return ret;
	}
	stExpStackValue operator * (const stExpStackValue& val) const
	{
		stExpStackValue ret;
		ret.type = GetEExprTypeOpType(type, val.type);
		switch (ret.type)
		{
		case Expr_Int:
		{
			ret.i_value = GetInt() * val.GetInt();
			break;
		}
		case Expr_Float:
		{
			ret.f_value = GetFloat() * val.GetFloat();
			break;
		}
		case Expr_String:
		{
			break;
		}
		}
		return ret;
	}
	stExpStackValue operator / (const stExpStackValue& val) const
	{
		stExpStackValue ret;
		ret.type = GetEExprTypeOpType(type, val.type);
		switch (ret.type)
		{
		case Expr_Int:
		{
			ret.i_value = GetInt() / val.GetInt();
			break;
		}
		case Expr_Float:
		{
			ret.f_value = GetFloat() / val.GetFloat();
			break;
		}
		case Expr_String:
		{
			break;
		}
		}
		return ret;
	}
	stExpStackValue operator & (const stExpStackValue& val) const
	{
		//& | 和+-*/不一样，不需要把int提升成float,全部以int身份操作
		stExpStackValue ret;
		ret.SetInt(GetInt() & val.GetInt());
		return ret;
	}
	stExpStackValue operator | (const stExpStackValue& val) const
	{
		//& | 和+-*/不一样，不需要把int提升成float,全部以int身份操作
		stExpStackValue ret;
		ret.SetInt(GetInt() | val.GetInt());
		return ret;
	}
	stExpStackValue operator % (const stExpStackValue& val) const
	{
		//& | 和+-*/不一样，不需要把int提升成float,全部以int身份操作
		stExpStackValue ret;
		ret.SetInt(GetInt() % val.GetInt());
		return ret;
	}
};
extern stExpStackValue StackValueOp(EExprOp op, stExpStackValue first_value, stExpStackValue second_value);


extern std::ostream& operator <<(std::ostream& os, const stExpStackValue& Value);

extern bool IsDoubleCharOpType(char* c);
extern bool IsSingleCharOpType(char c);
extern bool IsNumber( char c);
extern bool IsFloat(char* number_str);
extern bool Bigger(EExprOp op1, EExprOp op2); //op1是否比op2优先级高

//字符串分割为中缀表达式
extern void StrToExpr(const char* str, vector<stExpStackValue>& value_stack);
//中缀转换为后缀表达式
extern void MiddleToHou(const vector<stExpStackValue>& middle, vector<stExpStackValue>& hou);
//计算后缀表达式的值
extern void ExcuteHouExp(vector<stExpStackValue>& hou);
//执行表达式
extern void ExcuteExp(const char* str);


using IntefaceDelegate_Type = std::function<void(stExpStackValue[], int, stExpStackValue&)>;
extern map<string, IntefaceDelegate_Type> g_ExprMap;

//注册外部的命令函数
#define DECLARE_COMMAND(command_function)	g_ExprMap[#command_function] = command_function;

//内部注册测试函数
#define DECLARE_COMMAND_TEST \
DECLARE_COMMAND(Say) \
DECLARE_COMMAND(SetHp)\
DECLARE_COMMAND(GetHp)

//测试函数
extern void Say(stExpStackValue value1[], int valueCount, stExpStackValue& retValue);
extern void SetHp(stExpStackValue value1[], int valueCount, stExpStackValue& retValue);
extern void GetHp(stExpStackValue value1[], int valueCount, stExpStackValue& retValue);

/*
外部使用者使用表达式步骤：
1、添加函数，格式如同Say
2、调用DECLARE_COMMAND注册函数

测试表达式：	
function_library::ExcuteExpression("Say(\"hello world!\")");
function_library::ExcuteExpression("SetHp(2.0*3 + GetHp())");
*/

#endif