


#include "DexExpression.h"	

extern bool IsEExprTypeValue(EExprType type)
{
	switch (type)
	{
	case Expr_None:
		return false;
	case Expr_OP:
		return false;
	case Expr_Int:
		break;
	case Expr_Float:
		break;
	case Expr_String:
		break;
	case Expr_Fun:
		return false;
	default:
		break;
	}
	return true;
}

extern EExprType GetEExprTypeOpType(EExprType type1, EExprType type2)
{
	//Ŀǰֻ��EExprType�Ĵ�С��������������������ȼ���ǰ���Ҫ��
	//��ʱ����������ǰ�int ������ float
	return type1 > type2 ? type1 : type2;
}

std::ostream& operator <<(std::ostream& os, const stExpStackValue& Value)
{
	switch (Value.type)
	{
	case Expr_None:
		std::cout << "none";
		break;
	case Expr_OP:
		std::cout << (char)Value.op_value;
		break;
	case Expr_Int:
		std::cout << Value.i_value;
		break;
	case Expr_Float:
		std::cout << Value.f_value;
		break;
	case Expr_String:
		std::cout << Value.s_value;
		break;
	case Expr_Fun:
		std::cout << Value.fun_value;
		break;
	default:
		break;
	}
	return os;
}

map<string, IntefaceDelegate_Type> g_ExprMap;

extern void Say(stExpStackValue value1[], int valueCount, stExpStackValue& retValue)
{
	string str = value1[0].GetString();
	cout << str << endl;
}
extern void SetHp(stExpStackValue value1[], int valueCount, stExpStackValue& retValue)
{
	int Hp = value1[0].GetInt();
	cout <<"Player SetHp Success ! Now Hp:"<< Hp << endl;
}
extern void GetHp(stExpStackValue value1[], int valueCount, stExpStackValue& retValue)
{
	retValue.SetInt(99);
}

bool IsDoubleCharOpType(char* c)
{
	if(strlen(c) != 2)
		return false;
	switch(c[0])
	{
	case '&':
	case '|':
		if(c[1] != c[0])
			return false;
		return true;
	}
	return false;
}
bool IsSingleCharOpType(char c)
{
	switch(c)
	{
	case '+':
	case '-':
	case '*':
	case '/':
	case '(':
	case ')':
	case '&':
	case '|':
	case ',':
	case '%':
		return true;
	}
	return false;
}
bool IsNumber( char c)
{
	switch(c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':	 
	case '8':
	case '9':
	case '.':
		return true;
	}
	return false;
}
bool IsFloat(char* number_str)
{
	char* temp = number_str;
	while(*temp != '\0')
	{
		if(*temp == '.')
			return true;
		temp++;
	}
	return false;
}
bool Bigger(EExprOp op1, EExprOp op2) //op1�Ƿ��op2���ȼ���
{
	//op2���ڷ���ջ�У�ͬ�����Ҫ����op1
	if (op1 == op2)
		return false;
	switch(op1)
	{
	case OP_ADD:
		{
		switch (op2)
		{
		case OP_MINUS:
		{
			return false;
		}
		case OP_MUL:
		{
			return false;
		}
		case OP_DIVIDE:
		{
			return false;
		}
		case OP_BIT_AND:
		{
			return true;
		}
		case OP_COMMA:
		{
			return true;
		}
		case OP_MO:
		{
			return false;
		}
		}
		break;
		}
	case OP_MINUS:
		{
			switch(op2)
			{
			case OP_ADD:
				{
					return false;
				}
			case OP_MUL:
				{
					return false;
				}
			case OP_DIVIDE:
				{
					return false;
				}
			case OP_BIT_AND:
				{
					return true;
				}
			case OP_COMMA:
				{
					return true;
				}
			case OP_MO:
				{
					return false;
				}
			}
			break;
		}
	case OP_MUL:
		{
			switch(op2)
			{
			case OP_ADD:
				{
					return true;
				}
			case OP_MINUS:
				{
					return true;
				}
			case OP_DIVIDE:
				{
					return false;
				}
			case OP_BIT_AND:
				{
					return true;
				}
			case OP_COMMA:
				{
					return true;
				}
			case OP_MO:
				{
					return false;
				}
			}
			break;
		}
	case OP_DIVIDE:
		{
			switch(op2)
			{
			case OP_ADD:
				{
					return true;
				}
			case OP_MINUS:
				{
					return true;
				}
			case OP_MUL:
				{
					return false;
				}
			case OP_BIT_AND:
				{
					return true;
				}
			case OP_COMMA:
				{
					return true;
				}
			case OP_MO:
				{
					return false;
				}
			}
			break;
		}
	case OP_BIT_AND:
		{
			switch(op2)
			{
			case OP_ADD:
				{
					return false;
				}
			case OP_MINUS:
				{
					return false;
				}
			case OP_MUL:
				{
					return false;
				}
			case OP_DIVIDE:
				{
					return false;
				}
			case OP_COMMA:
				{
					return true;
				}
			case OP_MO:
				{
					return false;
				}
			}
			break;
		}
	case OP_COMMA:
		{
			switch(op2)
			{
			case OP_ADD:
				{
					return false;
				}
			case OP_MINUS:
				{
					return false;
				}
			case OP_MUL:
				{
					return false;
				}
			case OP_DIVIDE:
				{
					return false;
				}
			case OP_BIT_AND:
				{
					return false;
				}
			case OP_MO:
				{
					return false;
				}
			}
			break;
		}
	case OP_MO:
		{
			switch(op2)
			{
			case OP_ADD:
				{
					return true;
				}
			case OP_MINUS:
				{
					return true;
				}
			case OP_MUL:
				{
					return false;
				}
			case OP_DIVIDE:
				{
					return false;
				}
			case OP_BIT_AND:
				{
					return true;
				}
			case OP_COMMA:
				{
					return true;
				}
			case OP_MO:
				{
					return false;
				}
			}
			break;
		}
	}
	return true;
}
//�ַ����ָ�Ϊ��׺���ʽ
void StrToExpr(const char* str, vector<stExpStackValue>& value_stack)
{
	char* temp = (char*)str;
	string temp_value; //�洢��ʱ��ֵ
	string temp_string; //�洢��ʱ�ַ���
	string temp_op;	   //�洢��ʱ������(����һ��������֮���ж���һ���ַ�����һ���Ƿ����˫�ֽڲ�������&& ||)
	bool is_seeking_number = false; //�Ƿ����ڲ�����ֵ	  
	bool is_seeking_doubleop = false; 
	bool is_seeking_function = false;  //�Ƿ����ڽ�����������
	bool is_seeking_string = false;	   //�Ƿ����ڽ����ַ���
	while(*temp != '\0')
	{
		char tempChar = *temp;
		if(IsNumber(tempChar))
		{//���������
			if(is_seeking_function || is_seeking_string)
			{//���֮ǰ���ڶ�λ���������ַ�������Ѹ����ֹ��뵽�ַ�������ȥ�����������ֿ�ͷ�򲻻ᵱ���ַ������� 
				//��temp1���Ϸ� Ϊһ���ַ���
				//1temp:�Ƿ�
				temp_string.append(1, tempChar);
			}
			else
			{
				temp_value.append(1, tempChar); //��������ӵ�ĩβ
				if(!is_seeking_number)
				{//��ʼ����������ֵ
					is_seeking_number = true;
				}
			}
		}
		else if(IsSingleCharOpType(tempChar))
		{//������
			//char* next_char = temp;
			//next_char++;
			//if(next_char == tempChar && (|| tempChar == '|'))
			//{//��˫�ֽڲ�����
			//	if(tempChar == '&')
			//	{
			//		op_Stack.push(OP_AND);
			//	}
			//}
			if(is_seeking_function)
			{//���֮ǰ���ڶ�λ�������ƣ�������������ƵĶ�λ
				stExpStackValue val;
				val.type = Expr_Fun;
				strcpy_s(val.fun_value, temp_string.c_str());
				value_stack.push_back(val);	
				temp_string.clear();
				is_seeking_function = false;
			}
			if(is_seeking_number)
			{
				stExpStackValue val;
				if(IsFloat((char*)temp_value.c_str()))
				{
					val.type = Expr_Float;
					val.f_value = static_cast<float>(atof(temp_value.c_str()));
				}
				else
				{
					val.type = Expr_Int;
					val.i_value = atoi(temp_value.c_str());
				}
				value_stack.push_back(val);	
				temp_value.clear();
				is_seeking_number = false;
			}
			stExpStackValue val;
			val.type = Expr_OP;
			val.op_value = (EExprOp)tempChar; 
			value_stack.push_back(val);
		}
		else if(*temp == ' ')
		{
			if(is_seeking_number)
			{//���֮ǰ���ڶ�λ���ݣ���������ݵĶ�λ
				stExpStackValue val;
				if(IsFloat((char*)temp_value.c_str()))
				{
					val.type = Expr_Float;
					val.f_value = static_cast<float>(atof(temp_value.c_str()));
				}
				else
				{
					val.type = Expr_Int;
					val.i_value = atoi(temp_value.c_str());
				}
				value_stack.push_back(val);	
				temp_value.clear();
				is_seeking_number = false;
			}
			else if(is_seeking_function)
			{//���֮ǰ���ڶ�λ�������ƣ�������������ƵĶ�λ
				stExpStackValue val;
				val.type = Expr_Fun;
				strcpy_s(val.fun_value, temp_string.c_str());
				value_stack.push_back(val);	
				temp_string.clear();
				is_seeking_function = false;
			}
			else if(is_seeking_string)
			{//�ڶ�λ�ַ��� ��ո�ӽ�ȥ
				temp_string.append(1, tempChar);
			}
		}
		else if(*temp == '"')
		{//
			if(is_seeking_string)
			{//���֮ǰ�Ѿ��ڶ�λ�ַ���
				//�����ַ����Ķ�λ
				stExpStackValue val;
				val.type = Expr_String;
				strcpy_s(val.s_value, temp_string.c_str());
				value_stack.push_back(val);	
				temp_string.clear();
				is_seeking_string = false;
			}
			else
			{
				is_seeking_string = true;
			}

		}
		else
		{//ֻ��һ����ͨ���ַ�  
			if(is_seeking_number)
			{//���֮ǰ���ڶ�λ���ݣ���������ݵĶ�λ
				stExpStackValue val;
				if(IsFloat((char*)temp_value.c_str()))
				{
					val.type = Expr_Float;
					val.f_value = static_cast<float>(atof(temp_value.c_str()));
				}
				else
				{
					val.type = Expr_Int;
					val.i_value = atoi(temp_value.c_str());
				}
				value_stack.push_back(val);	
				temp_value.clear();
				is_seeking_number = false;
			}
			if(is_seeking_string)
			{//���ڶ�λ�ַ��� �����ַ���
				temp_string.append(1, tempChar);
			}
			else
			{//���ڶ�λ���� ����������
				temp_string.append(1, tempChar);
				if(!is_seeking_function)
				{//��ʼ���Һ���
					is_seeking_function = true;
				}
			}
		}
		temp++;
	}
	//��ֹ������ڲ������ݣ��ж�һ��
	if(is_seeking_number)
	{
		stExpStackValue val;
		is_seeking_number = false;
		if(IsFloat((char*)temp_value.c_str()))
		{
			val.type = Expr_Float;
			val.f_value = static_cast<float>(atof(temp_value.c_str()));
		}
		else
		{
			val.type = Expr_Int;
			val.i_value = atoi(temp_value.c_str());
		}
		value_stack.push_back(val);
	}
	if(is_seeking_function)
	{//���֮ǰ���ڶ�λ�������ƣ�������������ƵĶ�λ
		stExpStackValue val;
		val.type = Expr_Fun;
		strcpy_s(val.fun_value, temp_string.c_str());
		value_stack.push_back(val);	
		temp_string.clear();
		is_seeking_function = false;
	}
}
//��׺ת��Ϊ��׺���ʽ
void MiddleToHou(const vector<stExpStackValue>& middle, vector<stExpStackValue>& hou)
{
	stack<stExpStackValue>   temp_stack; //��Ҫ�洢��ʱֵ
	for(size_t i = 0 ; i < middle.size();)
	{	
		if(middle[i].type == Expr_Fun)
		{//����
			temp_stack.push(middle[i]);//����������ʱջ
		}
		else if(middle[i].type == Expr_OP)
		{
			if(middle[i].op_value == OP_LEFT_B)
			{//������ 
				if(!temp_stack.empty() && temp_stack.top().type == Expr_Fun)
				{//���ǰһ���Ǻ���
					//����һ�����ŷ���hou ��ʾһ�������Ŀ�ʼ���ڼ����׺���ʽʱ ������Ž���־һ�������Ľ���
					stExpStackValue comma;
					comma.type = Expr_OP;
					comma.op_value = OP_COMMA;
					hou.push_back(comma);
				}
				temp_stack.push(middle[i]);   //����������ʱջ

			}
			else if(middle[i].op_value == OP_RIGHT_B)
			{//������
				stExpStackValue temp = temp_stack.top();
				while(!(temp.type == Expr_OP && temp.op_value == OP_LEFT_B))
				{
					hou.push_back(temp);
					temp_stack.pop();
					temp = temp_stack.top();
				}
				temp_stack.pop(); // �������ŵ���ȥ
				//��������������Ǻ��� ȡ�����Ž�hou
				if(!temp_stack.empty() && temp_stack.top().type == Expr_Fun)
				{
					hou.push_back(temp_stack.top());
					temp_stack.pop();
				}
			}
			else if(middle[i].op_value == OP_COMMA)
			{//����
				while(temp_stack.top().type == Expr_OP)
				{
					if(temp_stack.top().op_value == OP_LEFT_B)
					{//���������� 
						break;
					}
					hou.push_back(temp_stack.top());
					temp_stack.pop();
				}
				//���ź��Ե�
				//hou.push_back(middle[i]);
			}
			else
			{//һ�������
				if(!temp_stack.empty() && temp_stack.top().type == Expr_OP)
				{
					if(Bigger(middle[i].op_value, temp_stack.top().op_value))
					{
						temp_stack.push(middle[i]);
					}
					else
					{
						hou.push_back(temp_stack.top());
						temp_stack.pop();
						if(temp_stack.empty())
						{
							temp_stack.push(middle[i]);
						}
						else
						{
							while(!temp_stack.empty())
							{
								if(temp_stack.top().type == Expr_OP)
								{
									if(temp_stack.top().op_value != OP_LEFT_B)
									{
										if(Bigger(middle[i].op_value, temp_stack.top().op_value))
										{
											temp_stack.push(middle[i]);
											break;
										}
										else
										{
											hou.push_back(temp_stack.top());
											temp_stack.pop();
										}
									}
									else
									{
										temp_stack.push(middle[i]);
										break;
									}
								}
								else
									break;
							}
						}
					}
				}
				else
				{
					temp_stack.push(middle[i]);
				}

			}
		}
		else
		{//��һ�������� ֱ�ӷ��� ��׺vector
			hou.push_back(middle[i]);
		}
		i++;
	}

	while(!temp_stack.empty())
	{	
		stExpStackValue temp = temp_stack.top();
		hou.push_back(temp);
		temp_stack.pop();
	}
}

//�����׺���ʽ��ֵ
extern void ExcuteHouExp(vector<stExpStackValue>& value_hou)
{
	stack<stExpStackValue> value_stack;
	for (size_t i = 0; i < value_hou.size(); i++)
	{
		stExpStackValue temp = value_hou[i];
		if (temp.type == Expr_OP)
		{//��һ�������
			if (temp.op_value == OP_COMMA)
			{//�Ƕ���
				//�Ѷ���ֱ��push��ȥ
				value_stack.push(temp);
				continue;
			}
			else if (value_stack.size() < 2)
			{
				//cout<<"��׺���ʽ�����쳣��"<<endl;
				return;
			}
			else
			{
				stExpStackValue second_value = value_stack.top();
				value_stack.pop();
				stExpStackValue first_value = value_stack.top();
				value_stack.pop();
				value_stack.push(StackValueOp(temp.op_value, first_value, second_value));
			}
		}
		else if (temp.type == Expr_Fun)
		{//��һ������
			//��ǰȡ������ ֱ���������Ž��� 
			vector<stExpStackValue> params;
			while (!value_stack.empty())
			{
				stExpStackValue top_value = value_stack.top();
				value_stack.pop();
				if (!(top_value.type == Expr_OP && top_value.op_value == OP_COMMA))
				{//���Ƕ���
					params.push_back(top_value);
				}
				else
				{
					//�������� ���������������
					break;
				}
			}
			stExpStackValue arr[10];
			int count = 0;
			for (int i = params.size() - 1; i >= 0; i--)
			{
				arr[count] = params[i];
				count++;
			}
			auto command_function = g_ExprMap.find(temp.fun_value);
			if (command_function != g_ExprMap.end())
			{
				stExpStackValue ret;
				command_function->second(arr, params.size(), ret);
				value_stack.push(ret);
			}
			else
			{
				cout<<"�Ҳ������ʽ�еĺ�����"<<temp.fun_value << endl;
				return;
			}
		}
		else
		{//������
			value_stack.push(temp);
		}
	}
	if (value_stack.size() != 1)
	{//������������Ϊ1 ��ô value_stack����һ�������ź����� ����
		//�Ӷ����²��Һ���
		int i = 0;
		stExpStackValue param[10];
		deque<stExpStackValue> container;	//�洢���� ��֤ǰ��˳����ȷ
		while (!value_stack.empty())
		{
			if (value_stack.top().type != Expr_Fun)
			{
				container.push_front(value_stack.top());
				value_stack.pop();
			}
			else
			{
				stExpStackValue ret;
				size_t size = container.size();
				for (size_t s = 0; s < size; s++)
				{
					param[s] = container.front();
					container.pop_front();
				}
				g_ExprMap[value_stack.top().fun_value](param, i, ret);
				value_stack.pop();//�Ѻ���pop��
				value_stack.push(ret); //�������ջ
				container.clear();
				i = 0;
				if (value_stack.size() == 1)
				{
					break;
				}
			}
		}
	}
}

stExpStackValue StackValueOp(EExprOp op, stExpStackValue first_value, stExpStackValue second_value)
{
	stExpStackValue ret;
	ret.type = Expr_None;
	switch(op)
	{
	case OP_ADD:
		ret = first_value + second_value;
		break;
	case OP_MINUS:
		ret = first_value - second_value;
		break;
	case OP_MUL:
		ret = first_value * second_value;
		break;
	case OP_DIVIDE:
		ret = first_value / second_value;
		break;
	case OP_BIT_AND:
		ret = first_value & second_value;
		break;
	case OP_BIT_OR:
		ret = first_value | second_value;
		break;
	case OP_MO:
		ret = first_value % second_value;
		break;
	}
	return ret;
}

void ExcuteExp(const char* str)
{
	vector<stExpStackValue> value_vec;
	vector<stExpStackValue> value_hou;
	StrToExpr(str, value_vec);
	MiddleToHou(value_vec, value_hou);
	ExcuteHouExp(value_hou);
}

void stExpStackValue::SetOperation(EExprOp value)
{
	op_value = value;
	type = EExprType::Expr_OP;
}

void stExpStackValue::SetInt(int value)
{
	i_value = value;
	type = Expr_Int;
}

void stExpStackValue::SetFloat(float value)
{
	f_value = value;
	type = Expr_Float;
}

void stExpStackValue::SetString(const char* value)
{
	strcpy_s(s_value, value);
	type = Expr_String;
}

void stExpStackValue::SetFunction(const char* value)
{
	strcpy_s(fun_value, value);
	type = Expr_Fun;
}

int stExpStackValue::GetInt()const
{
	switch (type)
	{
	case Expr_None:
		return 0;
	case Expr_OP:
		return 0;
	case Expr_Int:
		return i_value;
	case Expr_Float:
		return static_cast<int>(f_value);
	case Expr_String:
		return 0;
	case Expr_Fun:
		return 0;
	default:
		break;
	}
	return 0;
}

float stExpStackValue::GetFloat()const
{
	switch (type)
	{
	case Expr_None:
		return 0.0f;
	case Expr_OP:
		return 0.0f;
	case Expr_Int:
		return static_cast<float>(i_value);
	case Expr_Float:
		return f_value;
	case Expr_String:
		return 0.0f;
	case Expr_Fun:
		return 0.0f;
	default:
		break;
	}
	return 0.0f;
}

std::string stExpStackValue::GetString()const
{
	string Ret;
	switch (type)
	{
	case Expr_None:
		return Ret;
	case Expr_OP:
		return Ret;
	case Expr_Int:
		return Ret;
	case Expr_Float:
		return Ret;
	case Expr_String:
		return s_value;
	case Expr_Fun:
		return fun_value;
	default:
		break;
	}
	return Ret;
}
