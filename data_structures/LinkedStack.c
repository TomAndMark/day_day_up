/********************************************************************
*
*　 文件名：LinkedStack.c
*
*　 文件描述：链表栈(Linked list stack)
*	  1.初始化栈
*	  2.判断栈空与否
*	  3.进栈:top
*	  4.出栈:top
*	  5.获取top元素
*     6.主函数测试以上功能
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
#include <stdbool.h>

typedef struct node
{
	int data;
	struct node *next;   //指针类型
}node;

typedef struct LinkStack
{
	node *top;
}LinkStack;

void initstack(LinkStack *S)
{
	S->top = NULL;
}

bool isempty(LinkStack *S)
{
	if (NULL == S->top)
	{
		printf("空栈\n");
		return true;
	}

	return false;
}

void push(LinkStack *S, int num)
{
	node *newnode = (node *)malloc(1*sizeof(node));
	newnode->data = num;
	newnode->next = S->top;

	S->top = newnode;
}

void pop(LinkStack *S, int *x)
{
	if (!isempty(S))        //别漏了。
	{
		node *tmp = S->top;
		printf("%d\n", tmp->data);
		if (NULL != x)
		{
			*x = tmp->data;
		}

		S->top = S->top->next;
		free(tmp);
		tmp = NULL;	
	}
}

bool gettop(LinkStack *S, int *x)
{
	if (!isempty(S))
	{
		*x = S->top->data;
		return true;
	}

	return false;
}

int main(int argc, char const *argv[])
{
	LinkStack S;
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






