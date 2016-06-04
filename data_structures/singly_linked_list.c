/********************************************************************
*
*　 文件名：singly_linked_list.c
*
*　 文件描述：单向链表
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

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int data;
	struct  node *next;  //不能省略struct node
}node;

node* createnodes(int num)  //返回头节点,头节点不属于有效节点时
{
	node *head = (node *)malloc(1*sizeof(node));
	//防止分配失败
	while (NULL == head)
	{
		node *head = (node *)malloc(1*sizeof(node));
	}

	head->data = -100;
	head->next = NULL;

	int i = 0;
	node *curr = head;
	node *newnode = NULL;
	while (--num)
	{
		newnode = (node*)malloc(1*sizeof(node));
		while (NULL == head)
		{
			node *head = (node *)malloc(1*sizeof(node));
		}
		newnode->data = i+1;
		++i;
		newnode->next = NULL;

		curr->next = newnode;
		newnode = NULL;
		curr = curr->next;
	}
	return head;//可以返回变量(堆地址), 不能返回局部变量的地址
}

void printnodes(node *head)
{
	// node *curr = head;  传的参数head尽量避免可以修改本身的操作

	// while (NULL != curr->next)
	// {
	// 	curr = curr->next;
	// 	printf("%d\n", curr->data);
	// }
	node *curr = head->next;

	while (NULL != curr)
	{
		printf("%d\n", curr->data);
		curr = curr->next;
	}

}

void freenodes(node *head)
{
	node *curr = NULL;
	while (NULL != head)
	{
		curr = head;
		head = head->next;
		free(curr);
		curr = NULL;
	}
}

//此处不插表头头,头节点不改变
//加一个判断差前面或后面
void insertnode(node *head, int data, int newdata)
{
	node *curr = head->next;
	node *tmp = head;
	while (NULL!=curr && data!=curr->data)
	{
		tmp = curr;
		curr = curr->next;
	}

	if (NULL == curr)
	{
		printf("can't find data\n");
		return;
	}

	char flag;
	printf("请输入在前面插入还是后面插入(a/b):");
	scanf("%*[^ab]");
	scanf("%c", &flag);
	scanf("%*[^\n]%*c");

	node *newnode = (node*)malloc(1*sizeof(node));
	newnode->data = newdata;
	newnode->next = NULL;
	
	if ('b' == flag)
	{
		tmp->next = newnode;
		newnode->next = curr;
	}
	else
	{
		tmp = curr->next;
		curr->next = newnode;
		newnode->next = tmp; 
	}

	tmp = NULL;
}

void deletenode (node *head, int data)
{
	node *curr = head->next;
	node *pre = head;

	while (NULL != curr && data != curr->data)
	{
		pre = curr;
		curr = curr->next;
	}

	if (NULL == curr)
	{
		printf("can't find data\n");
		return;
	}

	pre->next = curr->next;
	free(curr);
	curr = NULL;

}

int main(int argc, char const *argv[]) {
      node * head=createnodes(10);
      printf("原链表\n");
      printnodes(head);
      insertnode(head,2,100);
      printf("插入2后链表\n");
      printnodes(head);
      deletenode(head,2);
      printf("删除1后链表\n");
      printnodes(head);
      freenodes(head);
      return 0;
}















