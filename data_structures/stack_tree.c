/********************************************************************
*
*　 文件名：stack_tree.c
*
*　 文件描述：栈,树(stack_tree)
*	  1.初始化栈
*	  2.栈节点进栈
*	  3.判断栈是否为空
*	  4.栈节点出栈
*	  5.前序初始化树
*     6.前、中、后非递归遍历树
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
#include <stdbool.h>

//声明树节点
typedef struct node
{
	char ch;
	struct node *left;
	struct node *right;
}node;

//声明栈节点
typedef struct stacknode
{
	node *tnode;
	struct stacknode *next;
}stacknode;


//声明栈
typedef struct stack
{
	stacknode *top;
}stack;

//初始化栈
void initstack(stack *s)
{
	s->top = NULL;
}


//节点进栈
void push(stack *s, node *tnode)
{
	stacknode *newnode = (stacknode *)malloc(1*sizeof(stacknode));
	newnode->tnode = tnode;
	newnode->next = s->top;

	s->top = newnode;
	newnode = NULL;
}

//栈是否为空
bool isempty(stack *s)
{
	if (NULL == s->top)
		return true;
	return false;
}

//节点出栈
void pop(stack *s)
{
	if (!isempty(s))
	{
		stacknode *tmp = s->top;
		s->top = s->top->next;
		free (tmp);
		tmp = NULL;
	}
}


node *gettop(stack *s)
{
	if (!isempty(s))
		return s->top->tnode;
	return NULL;
}

node *initstree()
{
	node *root = NULL;
	char ch;

	if ((ch = getchar()) == '0')
	{
		// scanf("%*c");
		return NULL;
	}
	else
	{
		// scanf("%*c");
		root = (node *)malloc(1*sizeof(node));
		root->ch = ch;
		root->left = initstree();
		root->right = initstree();
		return root;
	}
}

//非递归前序遍历
void pretree(node *root)
{
	stack s;
	initstack(&s);

	while (NULL != root || !isempty(&s))   //!isempty(&s)不能少 当右节点为NULL时,判断是否继续
	{
		while (NULL != root)
		{
			printf("%c\t", root->ch);
			push(&s, root);
			root = root->left;
		}	

		if (!isempty(&s))
		{
			root = gettop(&s);
			root = root->right;
			pop(&s);
		}
	}
}

//非递归中序遍历
void midtree(node *root)
{
	stack s;
	initstack(&s);

	while (NULL != root || !isempty(&s))
	{
		while (NULL != root)
		{
			push(&s, root);
			root = root->left;
		}

		if (!isempty(&s))
		{
			root = gettop(&s);
			printf("%c\t", root->ch);
			root = root->right;
			pop(&s);
		}
	}
}

//非递归后序遍历
void lasttree(node *root)
{
	stack s;
	initstack(&s);

	while (NULL != root || !isempty(&s))  ////!isempty(&s)不能少 当右节点为NULL时,判断是否继续
	{
		if (NULL == root)
		{
			root = gettop(&s);
			if (NULL == root->right)
			{
				printf("%c\t", root->ch);   //输出根节点
				root = NULL;
				pop(&s);
				continue;
			}
			
			root = root->right;	
			gettop(&s)->right = NULL;      //给根节点标记为已经读了他的右孩子
			continue;
		}

		while (NULL != root)
		{
			push(&s, root);
			root = root->left;
		}

		if (!isempty(&s))
		{
			root = gettop(&s);
			printf("%c\t", root->ch);
			root = root->right;
			pop(&s);
		}
	}
}

void freetree(node *root)
{
	if (NULL != root)
	{	
		freetree(root->left);
		freetree(root->right);
		free(root);
	}
}




int main(int argc, char const *argv[])
{
	node *root = initstree();
	pretree(root);
	printf("\n");

	midtree(root);
	printf("\n");

	lasttree(root);
	printf("\n");

	freetree(root);
	return 0;
}

