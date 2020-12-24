#pragma once

#include <vector>
using namespace std;

bool isoperator(char op);						  // 判断是否为运算符
int priority(char op);						  	  // 求运算符优先级
void postfix(char pre[], char post[], int& n);    // 把中缀表达式转换为后缀表达式
double read_number(char str[], int* i);			  // 将数字字符串转变成相应的数字
double postfix_value(char post[]);