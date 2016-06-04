/********************************************************************
*
*　 文件名：LinkedQueue.c
*
*　 文件描述：链表队列(linked list queue)
*	  1.初始化队列
*	  2.判断队列空与否
*	  3.入队:队尾
*	  4.出对:队首
*	  5.主函数测试以上功能
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

//定义链表节点
typedef struct node
{
	int data;
	struct node *next;   //struct不能省
}node;

//定义链表队列
typedef  struct LinkQueue
{
	node *head;
	node *tail;
}LinkQueue;

void initqueue(LinkQueue *LQ)
{
	node *newnode = (node *)malloc(1*sizeof(node));
	if (NULL == newnode)
	{
		newnode = (node *)malloc(1*sizeof(node));
	}
	newnode->data = -100;
	newnode->next = NULL;

	LQ->head = LQ->tail = newnode;
}

int isempty(LinkQueue *LQ)
{
	if (LQ->head == LQ->tail)
	{
		printf("空队列\n");
		return 1;
	}

	return 0;
}

void push(LinkQueue *LQ, int num)
{
	node *newnode = (node *)malloc(1*sizeof(node));
	if (NULL == newnode)
	{
		newnode = (node *)malloc(1*sizeof(node));
	}

	newnode->data = num;
	newnode->next = NULL;
	LQ->tail->next = newnode;
	LQ->tail = newnode;
}

void pop(LinkQueue *LQ, int *x)
{
	node *tmp = LQ->head->next;
	if (!isempty(LQ))
	{
		printf("%d\n", tmp->data);
		if (NULL != x)
		{
			*x = tmp->data;
		}

		LQ->head->next = tmp->next;
		if (NULL == LQ->head->next)   //不要忘记考虑tail指向要是否的元素
		{
			LQ->tail = LQ->head;
		}

		free(tmp);
		tmp = NULL;
	}
}

int gethead(LinkQueue *LQ, int *x)
{
	if (!isempty(LQ))
	{
		*x = LQ->head->next->data;
		return 1;
	}

	return 0;
}


int main(int argc, char const *argv[]) {
      LinkQueue  LQ;
      initqueue(&LQ);
      int i;
      for(i=0;i<5;i++)
      {
            push(&LQ,i+1);
      }
      pop(&LQ, NULL);
      pop(&LQ, NULL);
      pop(&LQ, NULL);
      int x;
      gethead(&LQ, &x);
      printf("head=%d\n", x);
      pop(&LQ, NULL);
      pop(&LQ, NULL);
      pop(&LQ, NULL);
      push(&LQ,300);
      push(&LQ,200);
      pop(&LQ, NULL);
      pop(&LQ, NULL);
      return 0;
}



