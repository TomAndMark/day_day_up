/********************************************************************
*
*　 文件名：doubly_linked_list.c
*
*　 文件描述：双向链表
*	  1.定义链表节点
*	  2.初始化链表(创建单链表)
*	  3.插入链表
*	  4.删除链表
*	  5.释放链表
*	  6.主函数测试以上功能
*
*　 创建人：MARK, 2016年6月3日
*
*　 版本号：1.0
*
*　 修改记录：无
*
********************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node   //【注意】链表内部的next 或 pre域前面不能漏struct
{
	int data;
	struct node *pre;
	struct node *next;
}node;

node* createnodes(int num)
{
	node *head = (node *)malloc(1*sizeof(node));
	while (NULL == head)
	{
		head = (node *)malloc(1*sizeof(node));
	}

	head->data = -100;
	head->pre = head;
	head->next = head;
	node *newnode = NULL;
	node *curr = head;

	int i;
	for (i = 0; i < num; ++i)
	{
		newnode = (node *)malloc(1*sizeof(node));
		while (NULL == newnode)
		{
			newnode = (node *)malloc(1*sizeof(node));
		}

		newnode->data = i+1;
		newnode->pre = curr;
		newnode->next = head;  //注意不要漏写 newnode->next = NULL;

		curr->next = newnode;
		curr = curr->next;     //注意不要漏写
		newnode = NULL;
	}
	head->pre = curr;         //注意不要漏写漏写

	return head;
}

void printnodes(node *head)
{
	node *curr = head->next;

	while (head != curr)
	{
		printf("%d\n", curr->data);
		curr = curr->next;
	}

}


void printnodesf(node *head)
{
	node *curr = head->pre;

	while (head != curr)
	{
		printf("%d\n", curr->data);
		curr = curr->pre;
	}

}

void insertnode(node *head, int data, int newdata)
{
	node *curr = head->next;
	
	while (head != curr && data != curr->data)
	{
		curr = curr->next;
	}

	if (head == curr)
	{
		printf("can't find data\n");
		return;
	}

	node *newnode = (node *)malloc(1*sizeof(node));
	newnode->data = newdata;
	newnode->pre = NULL;
	newnode->next = NULL;

	char flag;
	printf("请输入a/b:");

	scanf("%*[^ab]");

	scanf("%c", &flag);     //scanf & 中    

	scanf("%*[^\n]%*c");

	if ('b' == flag)
	{
		curr->pre->next = newnode;
		newnode->pre = curr->pre;
		newnode->next = curr;
		curr->pre = newnode;
	}
	else
	{
		curr->next->pre = newnode;
		newnode->next = curr->next;
		curr->next = newnode;
		newnode->pre = curr;
	}
}

void deletenode(node *head, int data)
{
	node *curr = head->next;

	while (head != curr && data != curr->data)
	{
		curr = curr->next;
	}

	if (head == curr)
	{
		printf("can't find data:");
		return;
	}

	curr->pre->next = curr->next;
	curr->next->pre = curr->pre;
	free(curr);
	curr = NULL;
}	

void freenodes(node *head)
{
	// node *curr = head;

	// while (NULL != curr)
	// {
	// 	curr->pre->next = NULL;
	// 	curr = curr->next;
	// 	free(head);
	// 	head = curr;
	// }

	node *curr = NULL;
	while (NULL != head)
	{
		head->pre->next = NULL;
		curr = head;
		head = head->next;
		free(curr);
		curr = NULL;
	}

}


int main(int argc, char const *argv[]) {
      node * head=createnodes(10);
      printf("原链表\n");
      printnodes(head);
      insertnode(head,4,100);
      printf("插入2后链表\n");
      printnodes(head);
      deletenode(head,2);
      printf("删除1后链表\n");
      printnodes(head);
      //反序输出
      printnodesf(head);
      freenodes(head);
      return 0;
}


