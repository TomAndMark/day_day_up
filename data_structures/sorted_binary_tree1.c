/********************************************************************
*
*　 文件名：sorted_binary_tree1.c
*
*　 文件描述：排序二叉树(无parent指针)
*	  1.创建新节点
*	  2.递归插入节点
*	  3.初始化树
*	  4.删除树节点
*	  5.递归前序遍历
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

//定义树节点类型
typedef struct node
{
	int data;
	struct node* left;
	struct node* right;
}node;

//创建新节点
node* createnewnode(data)
{
	node *newnode = (node *)malloc(1*sizeof(node));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

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
		return root;
	}

	if (NULL==root->right && data>root->data)
	{
		node *newnode = createnewnode(data);
		root->right = newnode;
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

//删除树节点
node* deletenode(node *root,int data)
{
	if (NULL == root)                             //data不在树中
	{
		printf("删除失败\n");
		return root;
	}

	if (data > root->data)                        //data可能在右半区
	{
		if(NULL == deletenode(root->right, data)) //当data是叶子节点时,父节点指向NULL
		{
			root->right = NULL;
		}
	}	
	else if (data < root->data)                  //data可能在左半区
	{
		if(NULL == deletenode(root->left, data)) //当data是叶子节点时,父节点指向NULL
		{
			root->left = NULL;
		}
	}
	else                                        //找到data
	{ 
		if (NULL==root->left && NULL==root->right) //data是叶子节点时
		{
			free(root);
			root = NULL;
			return root;		
		}
		else if (NULL != root->left)               //data节点有左孩子时
		{
			node *curr = root->left;
			node *p = NULL;
			if (NULL != curr->right)    //替换data节点第一个左孩子的最右孩子
			{
				while (NULL != curr->right)
				{
					p = curr;
					curr = curr->right;
				}
				root->data = curr->data;
				p->right = curr->left;
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
			node *p = NULL;
			if (NULL != curr->left)    //替换data节点第一个右孩子的最左孩子
			{
				while (NULL != curr->left)
				{
					p = curr;
					curr = curr->left;
				}
				root->data = curr->data;
				p->left = curr->right;
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

//递归前序遍历
void pretree(node *root)
{
	if (NULL == root)
		return;
	
	printf("%d\t", root->data);
	pretree(root->left);
	pretree(root->right);
}

int main(int argc, char const *argv[]) 
{
     node* root=NULL;
     int a[]={9,23,14,6,4,67,31,63};
     root=inittree(a,8);
     pretree(root);
     printf("\n");

     root=deletenode(root,63);

	 pretree(root);
     printf("\n");
     return 0;
}

