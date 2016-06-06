/********************************************************************
*
*　 文件名：sorted_binary_tree2.c
*
*　 文件描述：排序二叉树(有parent指针)
*	  1.创建新节点
*	  2.递归插入节点
*	  3.初始化树
*	  4.删除树节点
*	  5.递归前序遍历
*	  6.主函数测试以上功能
*
*　 创建人：MARK, 2016年6月7日
*
*　 版本号：1.0
*
*　 修改记录：无
*
********************************************************************/
#include <stdio.h>
#include <stdlib.h>

//定义树节点类型
typedef struct node
{
	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
}node;

//创建新节点
node* createnewnode(data)
{
	node *newnode = (node *)malloc(1*sizeof(node));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;

	return newnode;
}

//递归插入节点
node *insertnode(node *root, int data)
{
	if (NULL == root)
	{
		node *newnode = createnewnode(data);
		root = newnode;
		return root;
	}

	if (NULL==root->left && data<root->data)
	{
		node *newnode = createnewnode(data);
		root->left = newnode;
		newnode->parent = root;
		return root;
	}

	if (NULL==root->right && data>root->data)
	{
		node *newnode = createnewnode(data);
		root->right = newnode;
		newnode->parent = root;
		return root;
	}

	if (NULL != root->left && data<root->data)
	{
		insertnode(root->left, data);
		return root;
	}

	if (NULL != root->right && data>root->data)
	{
		insertnode(root->right, data);
		return root;
	}	
}

//初始化树
node* inittree(int *s, int len)
{
	int i;
	node *root = NULL;
	for (i = 0; i < len; ++i)
	{
		root = insertnode(root, s[i]);  //root 不能忘
	}

	return root;
}

//删除
node* deletenode(node *root,int data)
{
	if (NULL == root)                             //data不在树中
	{
		printf("删除失败\n");
		return root;
	}

	if (data > root->data)                        //data可能在右半区
		deletenode(root->right, data);
	else if (data < root->data)                  //data可能在左半区
		deletenode(root->left, data); 
	else                                        //找到data
	{ 
		if (NULL==root->left && NULL==root->right) //data是叶子节点时
		{
			if (root->parent->right == root)
				root->parent->right = NULL;
			else
				root->parent->left = NULL;
			
			free(root);
			root = NULL;
			return root;		
		}
		else if (NULL != root->left)               //data节点有左孩子时
		{
			node *curr = root->left;
			if (NULL != curr->right)    //替换data节点第一个左孩子的最右孩子
			{
				while (NULL != curr->right)
				{
					curr = curr->right;
				}

				root->data = curr->data;
				root->parent->right = curr->left;
			}
			else                       //直接替换data节点第一个左孩子(右孩子为空时)
			{
				root->data = curr->data;
				root->left = curr->left;
			}

			free(curr);
			curr = NULL;
		}
		else                                      //data节点只有右孩子时
		{
			node *curr = root->right;
			if (NULL != curr->left)    //替换data节点第一个右孩子的最左孩子
			{
				while (NULL != curr->left)
				{
					curr = curr->left;
				}

				root->data = curr->data;
				root->parent->left = curr->right;
			}
			else                      //直接替换data节点第一个右孩子(左孩子为空时)
			{
				root->data = curr->data;
				root->right = curr->right;
			}

			free(curr);
			curr = NULL;
		}
	}

	return root;
}

//前序遍历
void midetree(node *root)
{
	if (NULL == root)
		return;
	
	printf("%d\t", root->data);
	midetree(root->left);
	midetree(root->right);
}

int main(int argc, char const *argv[]) 
{
     node* root=NULL;
     int a[]={9,23,14,6,4,67,31,63};
     root=inittree(a,8);
     midetree(root);
     printf("\n");

     root=deletenode(root,4);

	 midetree(root);
     printf("\n");
     return 0;
}
