/********************************************************************
*
*　 文件名：AVL_tree.c
*   平衡二叉树的定义: //AVL是3个发现者的首字母, 自平衡的二叉查找树
*    平衡二叉树或是一棵空树，或是具有下列性质的二叉排序树：
*     ①它的左子树和右子树的高度之差的绝对值不超过1；
*     ②它的左、右子树都是平衡二叉树。
*　 文件描述：平衡二叉树
*	  1.
*	  2.
*	  3.
*	  4.
*	  5.
*	  6.主函数测试以上功能
*
*　 创建人：MARK, 2016年8月21日
*
*　 版本号：1.0
*
*　 修改记录：无
*http://blog.csdn.net/tiny39st/article/details/18326945
********************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*定义AVL节点结构类型*/
typedef struct AVL_node 
{
	int key;
	struct AVL_node *left;
	struct AVL_node *right;
	int height;
}AVL_node;


/*创建新节点*/
AVL_node* New_Node(int key, AVL_node *left, AVL_node *right, int height)
{
	AVL_node *newnode = (AVL_node *)malloc(1 * sizeof(AVL_node));
	newnode->key = key;
	newnode->left = left;
	newnode->right = right;
	newnode->height = height;

	return newnode;
}


/*获得树高度  #由于NULL节点无法获得height#*/
int getHeight(AVL_node *node)
{
	return !node ? 0 : node->height;
}


/*获得左右子节点，高度较大的高度*/
int max(int left, int right)
{
	return left > right ? left : right;
}


/*左旋(返回旋转节点)
*     p                    pivot      
*   /   \                 /     \
*  x    pivot  -->       p      y
*      /   \           /  \
*     c    y          x   c
*/
AVL_node* Left_Rotate(AVL_node *p)   //没有parent指针时，要用pivot(旋转节点)的父节点p作传参
{
	AVL_node *pivot = pivot->right;
    AVL_node *c = pivot->left;
    pivot->left = p;
    p->right = c;
    p->height = max(getHeight(p->left), getHeight(p->right)) + 1;
	pivot->height = max(getHeight(pivot->left), getHeight(pivot->right)) + 1;

	return pivot;
}


/*右旋(返回旋转节点)
*        p              pivot
*      /   \           /     \
*    pivot  y  -->    x       p
*     / \                    / \
*    x  c                   c   y
*/
AVL_node* Right_Rotate(AVL_node *p)
{
	AVL_node *pivot = p->left;
	AVL_node *c = pivot->right;
	pivot->right = p;
	p->left = c;
	p->height = max(getHeight(p->left), getHeight(p->right)) + 1;
	pivot->height = max(getHeight(pivot->left), getHeight(pivot->right)) + 1;

	return pivot;
}


/*
AVL的四种需要调整的情况(返回的旋转节点相当于子树的root)
LL:插入点是"最近失衡节点"的左节点的左节点（调整操作：右旋转）
RR:插入点是"最近失衡节点"的右节点的右节点（调整操作：左旋转）
LR:插入点是"最近失衡节点"的左节点的右节点（调整操作：先左旋转 再右旋转）
RL:插入点是"最近失衡节点"的右节点的左节点（调整操作：先右旋转 再左旋转）
*/

/*LL型(返回失衡节点的左节点：即旋转节点)
*        p              pivot
*      /   \           /     \
*    pivot  y  -->    x       p
*     / \            /       / \
*    x  c           ?       c   y
*   /
*  ?
*/
AVL_node* LL_Rotate(AVL_node *p)
{
	return Right_Rotate(p);
}


/*RR型(返回失衡节点的右节点：即旋转节点)
*     p                    pivot      
*   /   \                 /     \
*  x    pivot    -->     p      y
*      /   \           /  \    /
*     c    y          x   c   ?
*         /
*        ?
*/
AVL_node* RR_Rotate(AVL_node *p)
{
	return Left_Rotate(p);
}


/*LR型(返回失衡节点的左节点的右节点：即两次旋转的同一旋转节点)
*       p                  p                pivot
*     /  \               /   \             /    \
*    p1   y           pivot   y           p1     p
*   / \       -->      /           -->   /  \     \
*  x  pivot          p1                 x    ?     y
*     /             / \
*    ?             x   ?
*/
AVL_node* LR_Rotate(AVL_node *p)
{
	p->left = Left_Rotate(p->left);   //注意：别忘了改变p的父节点指向也需要改变
	return Right_Rotate(p);
}


/*RL型(返回失衡节点的右节点的左节点：即两次旋转的同一旋转节点)
*     p                p                 pivot           
*   /  \             /   \               /   \
*  x    p1          x    pivot          p    p1        
*      /  \   -->        /  \    -->   / \    \
*   pivot  y            ?    p1       x   ?    y
*    /                        \
*   ?                         y
*/
AVL_node* RL_Rotate(AVL_node *p)
{
	p->right = Right_Rotate(p->right);
	return Left_Rotate(p);          
}


/*插入操作:返回一棵树的root*/
AVL_node* Insert(AVL_node *root, int key)
{
	if (!root)
	{
		root = (AVL_node *)New_Node(key, NULL, NULL, 1);   //返回的是整数(地址)，强制转换不会有警告
        return root;
	}
	else
	{
	    if (key == root->key)   //可以已经存在
            return root;
        else if (key < root->key)
        	root->left = Insert(root->left, key);   //旋转后p的父节点指向可能变了
        else
        	root->right = Insert(root->right, key); //不能漏掉父节点赋值
	}

	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	if (getHeight(root->left) - getHeight(root->right) == 2)
	{
		if (key < root->left->key)
			root = LL_Rotate(root); //LL 返回的旋转节点相当于子树的root
		else
			root = LR_Rotate(root); //LR
	}
	else if (getHeight(root->right) - getHeight(root->left) == 2)
	{
		if (key > root->right->key)
			root = RR_Rotate(root); //RR
		else
			root = RL_Rotate(root); //RL
	}

	return root;
}


/*删除操作：返回一棵树的root*/
AVL_node* Delete(AVL_node *root, int key)
{
    if (!root)
    {
        return NULL;
    }

    if (key == root->key)
    {
     	if (!root->right)    //右节点为空,直接删除不用找后继节点
     	{                           //而且左节点的高度不会变
     		AVL_node *tmp = root;
     		root = root->left;
     		free(tmp);
     		tmp = NULL;
     		return root;
     	}  
     	else                       //右节点不为空，找后继节点，
     	{                          //因为右子树每个节点的高度可能改变了
     		AVL_node *tmp = root->right;	
     		while (tmp->left)
     		    tmp = tmp->left;
    		root->key = tmp->key;
     		root->right = Delete(root->right, tmp->key);
     	}
    }
    else if (key < root->key)
    {
    	root->left = Delete(root->left, key);
    }
   	else
   	{
   		root->right = Delete(root->right, key);
   	}

   	//除了等于key且右节点为NULL的情况，其他情况都要经过这
   	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	if (getHeight(root->left) - getHeight(root->right) == 2)
	{
		if (key < root->left->key)
			root = LL_Rotate(root); //LL 返回的旋转节点相当于子树的root
		else
			root = LR_Rotate(root); //LR
	}
	else if (getHeight(root->right) - getHeight(root->left) == 2)
	{
		if (key > root->right->key)
			root = RR_Rotate(root); //RR
		else
			root = RL_Rotate(root); //RL
	}

	return root;
}

int main(int argc, char const *argv[])
{
	AVL_node *root = NULL;
	root = Insert(root, 4);
	printf("%d, %d\n", root->key, root->height);
	root = Insert(root, 7);
	printf("%d, %d\n", root->right->key, root->right->height);
	root = Insert(root, 2);
	printf("%d, %d\n", root->left->key, root->left->height);
    
    root = Delete(root, 4);
	printf("%d, %d\n", root->key, root->height);
	return 0;
}




