/********************************************************************
*
*　 文件名：SeStack.c
*
*　 文件描述：顺序栈(sequential stack)
*	  1.初始化栈
*	  2.判断栈空与否
*	  3.判断栈满与否
*	  4.进栈:top
*	  5.出栈:top
*	  6.获取top元素
*     7.主函数测试以上功能
*
*　 创建人：MARK, 2016年6月4日
*
*　 版本号：1.0
*
*　 修改记录：无
*
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>      //必须加该头文件

#define N 100

typedef struct SeStack
{
	int data[N];
	int top;
}SeStack;

//初始化栈
void initstack(SeStack *S)
{
	S->top = -1;          //S->top = -1 空栈
}

//判断栈空与否
bool isempty(SeStack *S)
{
	if (-1 == S->top)
	{
		printf("空栈\n");
		return true;
	}

	return false;
}

//判断栈满与否
bool isfull(SeStack *S)
{
	if (N-1 == S->top)
	{
		printf("满栈\n");
		return true;
	}

	return false;
}

//进栈
void push(SeStack *S, int num)
{
	if (!isfull(S))
	{
		S->data[++S->top] = num;
	}
}

//出栈
void pop(SeStack *S, int *x)
{
	if (!isempty(S))
	{
		printf("%d\n", S->data[S->top]);
		if (NULL != x)
		{
			*x = S->data[S->top];
		}
		--S->top;
	}
}

bool gettop(SeStack *S, int *x)
{
	if (!isempty(S))
	{
		*x = S->data[S->top];	
		return true;
	}

	return false;
}

int main(int argc, char const *argv[])
{
	SeStack S;
	initstack(&S);

	int i;
	for (i = 0; i < 5; ++i)
	{
		push(&S, i+1);
	}

	pop(&S, NULL);
	pop(&S, NULL);
	pop(&S, NULL);
	
	int x;
	gettop(&S, &x);
	printf("TOP:%d\n", x);

	pop(&S, NULL);
	pop(&S, NULL);
	pop(&S, NULL);

	push(&S, 200);
	push(&S, 300);
	pop(&S, NULL);
	pop(&S, NULL);

	return 0;
}












