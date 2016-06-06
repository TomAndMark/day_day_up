/********************************************************************
*
*　 文件名：recursive_tree.c
*
*　 文件描述：递归树(recursive_tree)
*	  1.前序初始化树
*	  2.前序遍历
*	  3.中序遍历
*	  4.后序遍历
*     5.主函数测试以上功能
*
*　 创建人：MARK, 2016年6月6日
*
*　 版本号：1.0
*
*　 修改记录：无
*
********************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
	char ch;
	struct node *left;    //struct 不要漏了
	struct node *right;   //struct 不要漏了
}node;

//前序初始化
node* inittree()
{
	node *root = NULL;
	char ch;
	if ((ch = getchar()) == '0')
	{
		scanf("%*c");
		//getchar();
		return NULL;
	}
	else
	{
		scanf("%*c");
		//getchar();
		root = (node *)malloc(1*sizeof(node));
		root->ch = ch;
		root->left = inittree();
		root->right = inittree();
		return root;
	}
}

//前序遍历
void pretree(node *root)
{
	if (NULL == root)
		return;
	printf("%c\t", root->ch);
	pretree(root->left);
	pretree(root->right);	
}

//中序遍历
void midtree(node *root)
{
	if (NULL == root)
		return;
	midtree(root->left);
	printf("%c\t", root->ch);
	midtree(root->right);	
}


//后序遍历
void lasttree(node *root)
{
	if (NULL == root)
		return;
	lasttree(root->left);
	lasttree(root->right);	
	printf("%c\t", root->ch);
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
	node *root = inittree();
	pretree(root);
	printf("\n");

	midtree(root);
	printf("\n");

	lasttree(root);
	printf("\n");

	freetree(root);
	return 0;
}







