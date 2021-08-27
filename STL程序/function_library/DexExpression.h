
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
�������ʽ
*/

#define MAX_EXPR_STRING 256

//* / % ��ͬ�����ȼ�
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
	OP_COMMA   = ',',       // ,  ����
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

//����������ʽ��ֵ���������㣬��ô�������͸���ʲô�������㡣����int + float���򷵻�float
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
			string this_str = GetString();
			string val_str = val.GetString();
				if(this_str.length() + val_str.length() < MAX_EXPR_STRING)
				{
					strcat_s(ret.s_value, this_str.c_str());
					strcat_s(ret.s_value, val_str.c_str());
				}	
				else
				{
					cout << "�ַ������ȹ���" << endl;
					//DexLog::getSingleton()->Log(log_allert, "�ַ������ȹ���\n");
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
		//& | ��+-*/��һ��������Ҫ��int������float,ȫ����int��ݲ���
		stExpStackValue ret;
		ret.SetInt(GetInt() & val.GetInt());
		return ret;
	}
	stExpStackValue operator | (const stExpStackValue& val) const
	{
		//& | ��+-*/��һ��������Ҫ��int������float,ȫ����int��ݲ���
		stExpStackValue ret;
		ret.SetInt(GetInt() | val.GetInt());
		return ret;
	}
	stExpStackValue operator % (const stExpStackValue& val) const
	{
		//& | ��+-*/��һ��������Ҫ��int������float,ȫ����int��ݲ���
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
extern bool Bigger(EExprOp op1, EExprOp op2); //op1�Ƿ��op2���ȼ���

//�ַ����ָ�Ϊ��׺���ʽ
extern void StrToExpr(const char* str, vector<stExpStackValue>& value_stack);
//��׺ת��Ϊ��׺���ʽ
extern void MiddleToHou(const vector<stExpStackValue>& middle, vector<stExpStackValue>& hou);
//�����׺���ʽ��ֵ
extern void ExcuteHouExp(vector<stExpStackValue>& hou);
//ִ�б��ʽ
extern void ExcuteExp(const char* str);


using IntefaceDelegate_Type = std::function<void(stExpStackValue[], int, stExpStackValue&)>;
extern map<string, IntefaceDelegate_Type> g_ExprMap;

//ע���ⲿ�������
#define REGISTER_COMMAND(command_function)	g_ExprMap[#command_function] = command_function;

//�ڲ�ע��⺯��
#define REGISTER_COMMAND_LIB \
REGISTER_COMMAND(ex_print) \
REGISTER_COMMAND(ex_max)\
REGISTER_COMMAND(ex_min) \
REGISTER_COMMAND(ex_sin)\
REGISTER_COMMAND(ex_cos)

#define DECLARE_COMMAND(cmd)	extern void cmd(stExpStackValue value1[], int valueCount, stExpStackValue& retValue)

//�ű����ṩ�ĺ���֧��
DECLARE_COMMAND(ex_print);
DECLARE_COMMAND(ex_max);
DECLARE_COMMAND(ex_min);
DECLARE_COMMAND(ex_sin);
DECLARE_COMMAND(ex_cos);

/*
�ⲿʹ����ʹ�ñ��ʽ���裺
1����Ӻ�������ʽ��ͬex_print
2������REGISTER_COMMANDע�ắ��

���Ա��ʽ��	
function_library::ExcuteExpression("print(\"hello world!\")");
*/

#endif