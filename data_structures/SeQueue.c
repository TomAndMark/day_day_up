/********************************************************************
*
*　 文件名：SeQueue.c
*
*　 文件描述：顺序队列(sequential queue)
*	  1.初始化队列
*	  2.判断队列空与否
*	  3.判断队列满与否
*	  4.入队:队尾
*	  5.出对:队首
*	  6.获取head元素
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
#define N 100

typedef struct SeQueue
{
	int data[N];
	int head;
	int tail;
}SeQueue;

void initqueue(SeQueue *SQ)
{
	SQ->head = SQ->tail = 0;
}

int isempty(SeQueue *SQ)
{
	if (SQ->head == SQ->tail)  // 不能SQ->head == 0 && SQ->tail == 0
	{
		printf("空了\n");
		return 1;
	}

	return 0;
}

int isfull(SeQueue *SQ)
{
	if (SQ->head == (SQ->tail+1)%N)// 不能SQ->tail - SQ->head == N-1
	{
		printf("满了\n");
		return 1;
	}

	return 0;
}

void push(SeQueue *SQ, int num)
{
	if (!isfull(SQ))
	{
		SQ->data[SQ->tail] = num;
		SQ->tail = (SQ->tail+1)%N;    //不能++SQ->tail
	}
}

void pop(SeQueue *SQ, int *x)
{
	if (!isempty(SQ))
	{	
		printf("%d\n", SQ->data[SQ->head]);
		if (NULL != x)
		{
			*x = SQ->data[SQ->head];
		}
		SQ->head = (SQ->head+1)%N;     //不能++SQ->head
	}
}

int gethead(SeQueue *SQ, int *x)
{
	if (!isempty(SQ))
	{
		*x = SQ->data[SQ->head];
		return 1;
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	SeQueue SQ;
	initqueue(&SQ);
    
    int i;
    for(i=0; i<5; ++i)
    {
    	push(&SQ, i+1);
    }

	pop(&SQ, NULL);
	pop(&SQ, NULL);
	pop(&SQ, NULL);

	int x;
	gethead(&SQ, &x);
	printf("head=%d\n", x);
	
	pop(&SQ, NULL);
	pop(&SQ, NULL);
	pop(&SQ, NULL);
	push(&SQ,300);
	push(&SQ,200);
	pop(&SQ, NULL);
	pop(&SQ, NULL);

	return 0;
}
