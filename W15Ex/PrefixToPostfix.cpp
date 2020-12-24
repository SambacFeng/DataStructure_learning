#include "MyStack.h"
#include "PrefixToPostfix.h"

#include <iostream>
using namespace std;

void main()
{
	MyStack<int> stack;
	stack.init();

	//char pre[] ="22/(5*2+1)#";
	char exp[100];
	cout << "输入表达式(中缀，以#结束)：";
	cin >> exp;

	char post[100];
	//cout <<"中缀表达式为："<< pre << endl;

	int n = 0;			// 返回后缀表达式的长度
	postfix(exp, post, n);
	cout << "后缀表达式为：";
	for (int i = 0; i < n; i++)
		cout << post[i];

	cout << "\n由后缀表达式计算出的数值结果:  ";
	cout << postfix_value(post) << endl;

	system("pause");
}

bool isoperator(char op)
{
	switch (op)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		return 1;
	default:
		return 0;
	}
}


int priority(char op)
{
	switch (op)
	{
	case '#':
		return -1;
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return -1;
	}
}

//	 把中缀表达式转换为后缀表达式，返回后缀表达式的长度（包括空格）
void postfix(char pre[], char post[], int& n)
{
	int i = 0, j = 0;
	MyStack<char> stack;
	stack.init();		// 初始化存储操作符的栈

	stack.push('#');	// 首先把结束标志‘#’放入栈底

	while (pre[i] != '#')
	{
		if ((pre[i] >= '0' && pre[i] <= '9') || pre[i] == '.') // 遇到数字和小数点直接写入后缀表达式
		{
			post[j++] = pre[i];
			n++;
		}
		else if (pre[i] == '(')	// 遇到“（”不用比较直接入栈
			stack.push(pre[i]);
		else if (pre[i] == ')')  // 遇到右括号将其对应左括号后的操作符（操作符栈中的）全部写入后缀表达式
		{
			while (stack.gettop() != '(')
			{
				post[j++] = stack.pop();
				n++;
			}
			stack.pop(); // 将“（”出栈，后缀表达式中不含小括号
		}
		else if (isoperator(pre[i]))
		{
			post[j++] = ' '; // 用空格分开操作数(
			n++;
			while (priority(pre[i]) <= priority(stack.gettop()))
			{
				// 当前的操作符小于等于栈顶操作符的优先级时，将栈顶操作符写入到后缀表达式，重复此过程
				post[j++] = stack.pop();
				n++;
			}

			stack.push(pre[i]);	// 当前操作符优先级大于栈顶操作符的优先级，将该操作符入栈
		}

		i++;
	}
	while (stack.top) // 将所有的操作符加入后缀表达式
	{
		post[j++] = stack.pop();
		n++;
	}
}

double read_number(char str[], int* i)
{
	double x = 0.0;
	int k = 0;
	while (str[*i] >= '0' && str[*i] <= '9')  // 处理整数部分
	{
		x = x * 10 + (str[*i] - '0');
		(*i)++;
	}

	if (str[*i] == '.') // 处理小数部分
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			x = x * 10 + (str[*i] - '0');
			(*i)++;
			k++;
		}
	}
	while (k != 0)
	{
		x /= 10.0;
		k--;
	}

	return x;
}

double postfix_value(char post[])
{
	MyStack<double> stack;	// 操作数栈
	stack.init();

	int i = 0;
	double x1, x2;

	while (post[i] != '#')
	{
		if (post[i] >= '0' && post[i] <= '9')
			stack.push(read_number(post, &i));
		else if (post[i] == ' ')
			i++;
		else if (post[i] == '+')
		{
			x2 = stack.pop();
			x1 = stack.pop();
			stack.push(x1 + x2);
			i++;
		}
		else if (post[i] == '-')
		{
			x2 = stack.pop();
			x1 = stack.pop();
			stack.push(x1 - x2);
			i++;
		}
		else if (post[i] == '*')
		{
			x2 = stack.pop();
			x1 = stack.pop();
			stack.push(x1 * x2);
			i++;
		}
		else if (post[i] == '/')
		{
			x2 = stack.pop();
			x1 = stack.pop();
			stack.push(x1 / x2);
			i++;
		}
	}
	return stack.gettop();
}