#ifndef RB_TREE
#define RB_TREE

#include <iostream>
#include <queue>
#include <string>
#include <utility>

using namespace std;


class exception2  
{
	//*****只能这特定的divexception  exception2
template<class T>
friend class rbtree;//不要<T>
public:
	exception2(const char* str)
	{
		strcpy(msg,str);
	}
	char * what()
	{
      return msg;
	}
private:
	 char msg[20];
};
enum ColorType  //颜色枚举类型 0 1
{
	RED, BLACK
};

template <class T>
class rbnode           //node's struct type 
{
public:
	T value;        	//node's value
	rbnode<T> *parent;	//node's parent
	rbnode<T> *left;	//node's left 
	rbnode<T> *right;   //node's right
	ColorType color;	//node's color
		//rbnode no reference constructor
	rbnode()
	{}
	    //rbnode constructor
	rbnode(const T& val, rbnode<T> *l, rbnode<T> *r, rbnode<T> *p,ColorType c):value(val),
	  left(l), right(r), parent(p), color(c)
	{}

};

template <class T>
class rbtree
{
	
public:
	friend class iterator;
	class iterator
	{
		friend class rbtree<T>;
	public:
		iterator()
		{}

		iterator(rbnode<T> *_nodePtr, rbtree<T> *_tree):nodePtr(_nodePtr),tree(_tree)
		{}

		bool operator == (const iterator& rhs)const
		{
			return nodePtr == rhs.nodePtr;
		}

		bool operator != (const iterator& rhs)const
		{
			return nodePtr != rhs.nodePtr;
		}

		T& operator*()const
		{
			if (nodePtr == NIL)
				throw exception2("rbtree iterator operator* (): NULL reference");

			return nodePtr->value;
		}

		iterator& operator++ ()
		{
			rbnode<T> *p;

			if (nodePtr == NIL)
			{
				nodePtr = tree->root;

				if (nodePtr == NIL)
				{
					cout<<"tree == NIL"<<endl;
					throw exception2("rbtree iterator operator* (): NULL reference");
				}
					//最小的
				while (nodePtr->left != NIL)
					nodePtr = nodePtr->left;
			}
			else if(nodePtr->right != NIL)	// 右节点为空时
			{
				nodePtr = nodePtr->right;
					//第一个右节点后 的最左结点
				while(nodePtr->left != NIL)
					nodePtr = nodePtr->left;
			}
			else							//左节点为空时 回溯父节点
			{
				p = nodePtr->parent;

				while(p != NIL && nodePtr == p->right)
				{
					nodePtr = p;
					p = p->parent;
				}

				nodePtr = p;
					//nodePtr 可能为NIL  可能是 第一左分叉点的父结点
			}

			return *this;
		}

		iterator operator++ (int)
		{
			iterator tmp = *this;

			++*this;//注意是*this 不是指针

			// return the previous value
			return tmp;
		}

		iterator& operator-- ()
		{
			rbnode<T> *p;
			if (nodePtr == NIL)
			{
				nodePtr = tree;
				if (nodePtr == NIL)
				{
					cout<<"tree == NIL"<<endl;
					return iterator();					
				}

				while(nodePtr->right != NIL)
					nodePtr = nodePtr->right;
			}
			else if (nodePtr->left != NIL)
			{
				nodePtr = nodePtr->left;
					//第一个左节点后 的最右结点
				while (nodePtr->right != NIL)
					nodePtr = nodePtr->right;
			}
			else
			{
				p = nodePtr->parent;
				while (p != NIL && nodePtr == p->left)
				{
					nodePtr = p;
					p = p->parent;
				}

				nodePtr = p;
					//nodePtr 可能为NIL  可能是 第一右分叉点的父结点
			}
			return *this;
		}

		iterator operator-- (int)
		{
			iterator tmp = *this;

			--*this;//从右到左结合 *this
			return tmp;
		}

	private:
		rbnode<T> *nodePtr;
		rbtree<T> *tree;   //++ --时当nodePtr为NIL时 用tree代替
	};

	rbtree();
		//empty rbtree
	
	rbtree(T *first, T *last);
		//rbtree [first, last]
	
	rbtree(const rbtree<T>& obj);
		//create a copy of obj

	~rbtree();
		//destructor

	rbtree<T>& operator =(const rbtree<T>& rhs);
		//overload assignment

	bool empty() const;
	 	//empty 只读函数

	int size() const;
		//size 只读函数

	iterator find(const T& item)
	{
		rbnode<T> *curr;
		curr = findNode(item);

		if (NIL != curr)
			return iterator(curr, this);
		else
			return end();//指向NIL 结点
	}
		//查找元素


	pair<iterator, bool> insert(const T& item)
	{		//declare current node point and parent
		rbnode<T> *curr = root, *parent = NIL, *newnode;
			//loop find(through the tree)
		while (curr != NIL)
		{
			if (item == curr->value)
			{
				return pair<iterator, bool> (iterator(curr, this), false);
				//返回一个pair类对象，
				//里面相当find到了 要查如数值的迭代器，和返回了一个插入错误信息
			}

			parent = curr;
			if (item < curr->value)
			{
				curr = curr->left;
			}
			else 
			{
				curr = curr->right;
			}
		}
		//create the new node 并且指向tree的父节点中
		newnode = getRBnode(item, NIL, NIL, parent, RED);
		if (parent == NIL)
		{
			root = newnode;//特1：：：如果为root节点 只要把root变black就ok
		}
		else if (item < parent->value)
		{
			parent->left = newnode;//newnode代替原来的NIL
		}
		else
		{
			parent->right = newnode;
		}
		rbInsertFixup(newnode);
		treeSize++;
		return pair<iterator,bool> (iterator(newnode,this), true);
			//返回一个pair类对象，
			//里面相当find到了 要查如数值的迭代器，和返回了一个插入正确信息
	}	

	int erase(const T& item);

	int erase(iterator pos);

	iterator begin()
	{
		rbnode<T> *curr = root;

		if (curr != NIL)
		{
			while (curr->left != NIL)
				curr = curr->left;
		}

		return iterator(curr,this);
	}

	iterator end()
	{
		return iterator(NIL, this);
	}

private:

	int treeSize;
		//树的总节点数
	rbnode<T> *root;
		//树的根节点

	static rbnode<T> *NIL;
		//NULL 空树  静态全局变量

		//改变了 NIL使NIl无值 但是为黑，最后所有的叶子节点都是它
	void makeEmptyTree();
		// create an empty tree,by construction

	rbnode<T> *getRBnode(const T& item, rbnode<T> *leftPtr,
		rbnode<T> *rightPtr, rbnode<T> *parentPtr, ColorType c);
	
	rbnode<T> *copyTree(rbnode<T> *t);
		//copy a tree

	void deleteTree(rbnode<T> *t);
		//删除树


	rbnode<T> *findNode(const T& item)const;

	void rotateLeft (rbnode<T> *pivot);
	
	void rotateRight(rbnode<T> *pivot);

	void rbInsertFixup(rbnode<T> *x);

	void rbDeleteFixup(rbnode<T> *x);

	//rbnodeShadow *buildShadowTree(rbnode<T> *t, int level, int& column)const;

	//void deleteShadowTree(rbnodeShadow *t)const;
};	

template <class T>
rbnode<T> *rbtree<T>::NIL = 0;

template <class T>
void rbtree<T>::makeEmptyTree()
{
	if (0 == NIL)
	{
		NIL = new rbnode<T>;

		NIL->left = NULL;
		NIL->right = NULL;
		NIL->parent = NULL;
		NIL->color = BLACK;
	}
	root = NIL;
	treeSize = 0;
		//此时root没有key值 为空树
}

template <class T>
rbnode<T> *rbtree<T>::getRBnode(const T& item, rbnode<T> *leftPtr,
		rbnode<T> *rightPtr, rbnode<T> *parentPtr, ColorType c)
{
	rbnode<T> *newnode = new rbnode<T>(item, leftPtr, rightPtr,
		parentPtr, c);
	//parent为NIL，在前一个递归赋值，此时不知道他的父节点是谁
	return newnode;
}

template <class T>//递归复制树
rbnode<T> *rbtree<T>::copyTree(rbnode<T> *t)
{
	rbnode<T> *newleft, *newright, *newnode;

	if (t == NIL)
	{
		return NIL;
	}

	newleft = copyTree(t->left);
	newright = copyTree(t->right);
	newnode = getRBnode(t->value, newleft, newright, NIL, t->color);

	if (newleft != NIL)//当为NIl时，newnode->left已经为NIL 而NIL不必指向newnode
		newleft->parent = newnode;

	if (newright != NIL)
		newright->parent = newnode;

	return newnode;
		//当本身t为NIL时 , 节点就是NIL;
		//当节点不为NIL时,用newnode复制t,返回newnode；
}

template <class T>
void rbtree<T>::deleteTree(rbnode<T> *t)
{
	if (t != NIL)
	{
		deleteTree(t->left);
		deleteTree(t->right);
		delete t;
	}
}

template <class T>//找寻节点
rbnode<T> *rbtree<T>::findNode(const T& item)const
{
	//cycle t through the tree satrt root;
	rbnode<T> *curr = root;

	while (curr != NIL && !(item == curr->value))
	{
		if (item < curr->value)
		{
			curr = curr->left;
		}
		else
		{
			curr = curr->right;
		}
	}
	return curr;//在外面还要判断是否为NIL
}

template <class T>//左旋转
void rbtree<T>::rotateLeft (rbnode<T> *pivot)
{		//c 和 pivot为分别为两个中心点，支轴左转(逆时针)
	rbnode<T> *c = pivot->right;
	rbnode<T> *p = pivot->parent;

	pivot->right = c->left;
		//子节点的左孩子 成为 结点的右孩子 
	c->left = pivot;
		//结点 成为 节点的左孩子

	c->parent = p;
		//改变子结点(c)的parent指向
	pivot->parent = c;
		//改变结点(pivot)的parent指向

		//善后工作
	//原子结点(c)左孩子的parent指向，root改变，p 的左右指向
	if (pivot->right != NIL)
		pivot->right->parent = pivot;

	if (pivot == root)
		root = c;
	else if (pivot == p->right)//p不为NIL(即p不为root)
		p->right = c;
	else
		p->left = c;
}

template <class T>//右旋转
void rbtree<T>::rotateRight(rbnode<T> *pivot)
{		//c 和 pivot为分别为两个中心点，支轴左转(逆时针)
	rbnode<T> *c = pivot->left;
	rbnode<T> *p = pivot->parent;

	pivot->left = c->right;
		//子节点的右孩子 成为 结点的左孩子 
	c->right = pivot;
		//结点 成为 节点的右孩子

	c->parent = p;
		//改变子结点(c)的parent指向
	pivot->parent = c;
		//改变结点(pivot)的parent指向

		//善后工作
	//原 子结点(c)右孩子的parent指向，root改变，p 的左右指向
	if (pivot->left != NIL)
		pivot->left->parent = pivot;

	if (pivot == root)
		root = c;  //旋转时涉及根结点  此时调整
	else if (pivot == p->right)//p不为NIL(即p不为root)
		p->right = c;
	else
		p->left = c;
}

template <class T>//一红变两黑
void rbtree<T>::rbInsertFixup(rbnode<T> *x)
{	
	rbnode<T> *y;//保存叔父结点的
		//区分特1(NIL也为黑).特2  和 3种情况
 	while (RED == x->parent->color)	//结束条件
 	{	
 		if (x->parent == x->parent->parent->left)//用了②后，若能用③；确保下个是③ 不是用另一个②
 		{
 			y = x->parent->parent->right;
 				//case1:①->① ② ③ 注意 ②不能到另一个②  所以才会用最前面的if限制 使② 之后 用③而不用另一个②
 			if (RED == y->color)
 			{
 				x->parent->color = BLACK;
 				y->color = BLACK;
 				y->parent->color = RED;
 				x = y->parent;
 			}			
 			else if (x == x->parent->right)		//case2:②->① ③//无法用原来的② 也不能用后来的②无意义
 			{
 				x = x->parent;
 				rotateLeft(x);
 			}
 			else	//case 3: ③->① ② ③
 			{
	 			x->parent->color = BLACK;
	 			x->parent->parent->color = RED;
	 			rotateRight(x->parent->parent);			
 			}
 		}
 		else
 		{
 			y = x->parent->parent->left;

 			if (RED == y->color)
 			{
 				x->parent->color = BLACK;
 				y->color = BLACK;
 				y->parent->color = RED;
 				x = y->parent; 				
 			}
 			else if (x == x->parent->left)
 			{
 				x = x->parent;
 				rotateRight(x);
 			}
 			else
 			{
	 			x->parent->color = BLACK;
	 			x->parent->parent->color = RED;
	 			rotateLeft(x->parent->parent);	 				
 			}
 		}
 	}
 	root->color = BLACK;//特1
}

template <class T>
int rbtree<T>::erase(const T& item)	//1:删除成功，0 :删除失败
{
	rbnode<T> *x = findNode(item);	//看是否找的到
	rbnode<T> *p = x->parent, *c, *old; 
	ColorType old_color;
	if (x != NIL)
	{
		if (NIL == x->left && NIL == x->right)	//当左右节点（都为空）
		{
			c = NIL;
			old = x;						
		}
		else if (NIL == x->left)			//当右节点不为空时（一个为空）
		{
			c = x->right;
			old = x;
		}
		else if(NIL == x->right)	//当左节点不为空时(一个为空)
		{
			c = x->left;
			old = x;
		}
		else						//当左右节点都不为空时 找后继节点
		{
			c = x->right;
			while (c->left != NIL)
			{
				p = c->parent;
				c = c->left;
			}
			old = c;
			p = c->parent;
			c = c->right;
			x->value = old->value; //不能p->left->value  不能c->parent 值调换  应该为old
		}
		if (old == p->left)
		{
			p->left = c;
		}
		else
		{
			p->right = c;
		}
		c->parent = p;
		old_color = old->color;//保存旧颜色
		delete old;
		old = NULL;

		if (BLACK == old_color)
		{
			x = c; //此时x为新  最深的 不平衡点
			rbDeleteFixup(x);
		}
	}
	else
	{
		return 0;
	}
	return 1;
}
template <class T>
int rbtree<T>::erase(iterator pos)
{
	//return erase(pos.nodePtr->value);//nodePtr私有的
	return erase(*pos);
}

template <class T>//删除（节点后）修理树
void rbtree<T>::rbDeleteFixup(rbnode<T> *x)
{
	rbnode<T> *y;
		//双黑情况
	while (x != root && BLACK == x->color) //如果不平衡点到了根节点，他只要满足x支平衡,整个树接平衡了
	{									  //注意NIL也是黑的涵盖了 x为null的情况
		if (x == x->parent->left)
		{	
			y = x->parent->right;
				//case 1:y为红 不平衡点不改变 	①->②③④
				//支轴上两节点颜色互换后,以p左旋转
			if (RED == y->color)
			{
				y->parent->color = RED;
				y->color = BLACK;	//颜色互换 已知双方颜色不需要tmp 也不需要赋值先后顺序
				rotateLeft(y->parent);
				y = x->parent->right; //旋转后y变化了
			}
			
				//case 2:y为黑 且y的两个孩子都为黑，y->P可黑和红分别对应两种状态②->①②③④（当新x为root时结束） 或 ②->结束  平衡点上移
				//做法：y变红. x平衡点上移为p
			if (BLACK == y->color && BLACK == y->left->color && BLACK == y->right->color)
			{	
				y->color = RED;
				x = x->parent; //不平衡点上移了  需要给y重新赋值
			}
			else
			{		//case 3:y为黑，且y的左孩子为红，右孩子为黑 ③->④ 
					//做法:y->left 和 y颜色互换（明确颜色） 已y为节点右转
				if (BLACK == y->color && BLACK == y->right->color &&
					RED == y->left->color)
				{
					y->left->color = BLACK;
					y->color = RED;
					rotateRight(y);
					y = x->parent->right;//旋转后y变化了
				}
					//case 4:y为黑，且y的右孩子为红 ④->结束
					//做法：只明确颜色y下（先给y颜色赋值） y与y->p颜色互换（x+1 y-1） y的右孩子变为黑(y+1) 再左y->p旋转（整个树平衡）
				if (BLACK == y->color && RED == y->right->color)
				{
					y->color = y->parent->color;
					y->parent->color = BLACK;
					y->right->color = BLACK;	//这一步必不可少
					rotateLeft(y->parent);      //别忘了
					break;	//这是里面语句中唯一的显式调用
				}
			}
		}
		else
		{
			y = x->parent->left;
				//case 1:y为红 不平衡点不改变 	①->②③④
				//支轴上两节点颜色互换后,以p右旋转
			if (RED == y->color)
			{
				y->parent->color = RED;
				y->color = BLACK;	//颜色互换 已知双方颜色不需要tmp 也不需要赋值先后顺序
				rotateRight(y->parent);
				y = x->parent->left; //旋转后y变化了
			}
				//case 2:y为黑 且y的两个孩子都为黑，y->P可黑和红分别对应两种状态②->①②③④（当新x为root时结束） 或 ②->结束  平衡点上移
				//做法：y变红. x平衡点上移为p
			if (BLACK == y->color && BLACK == y->right->color &&
				BLACK == y->left->color)
			{
				y->color = RED;
				x = x->parent; //不平衡点上移了  需要给y重新赋值
			}
			else
			{		//case 3:y为黑，且y的右孩子为红，左孩子为黑 ③->④ 
					//做法:y->right 和 y颜色互换（明确颜色） 已y为节点左转
				if (BLACK == y->color && BLACK == y->left->color &&
					RED == y->right->color)
				{
					y->right->color = BLACK;
					y->color = RED;
					rotateLeft(y);
					y = x->parent->left;
				}
					//case 4:y为黑，且y的左孩子为红 ④->结束
					//做法：只明确颜色y下（先给y颜色赋值） y与y->p颜色互换（x+1 y-1） y的左孩子变为黑(y+1) 再左旋转（整个树平衡）
				if (BLACK == y->color && RED == y->left->color)
				{
					y->color = y->parent->color;
					y->parent->color = BLACK;
					y->left->color = BLACK;	//这一步必不可少
					rotateRight(y->parent);      //别忘了
					break;	//这是里面语句中唯一的显式调用
				}
			}
		}
	}
	x->color = BLACK; 		
		//有3中情况1.通过case4，x为NIL时（如果用NULL表示这需要考虑if (x) ，此时NIL指向不为空）
	//2.通过case2.1，x为root时；3.通过case2.2 x为红时（y->p）  
}


template <class T>
rbtree<T>::rbtree()
{
	makeEmptyTree();
}

template <class T>
rbtree<T>::rbtree<T>::rbtree(T *first, T *last)
{
	makeEmptyTree();
	while (first != last)
		insert(*first++);
}	
	
template <class T>
rbtree<T>::rbtree(const rbtree<T>& obj):treeSize(obj.treeSize)
{
	root = copyTree(obj.root);

	root = NIL;
	treeSize = 0;
}

template <class T>
rbtree<T>::~rbtree()
{
	deleteTree(root);
}

template <class T>
rbtree<T>& rbtree<T>::operator =(const rbtree<T>& rhs)
{
	if (this != &rhs)
	{
		deleteTree(root);
		root = copyTree(rhs.root);
		treeSize = rhs.treeSize;
	}
	return *this;
}

template <class T>
bool rbtree<T>::empty() const
{
	return treeSize == 0;
}

template <class T>
int rbtree<T>::size() const
{
	return treeSize;
}

#endif
