/*************************************************
  File name: d_rb_tree.h
  Author: Mark     Version:1.1        Date: 2016.4.5
  Description:    该头文件定义了一个红黑树类，主要用于关联容器调用等
  Function List:  some class iterator , reverse_iterator functions，exception2 
  					and some class rbnode, rbtree functions
  History:         
      <author>  <time>   <version >   <desc>
      Mark    2016.3.31     1.0     build this moudle
      Mark    2016.4.5   	1.1     modify some notes and add class reverse_iterator
*************************************************/

#ifndef D_RB_TREE
#define D_RB_TREE

#include <iostream>
#include <queue>
#include <string>
#include <utility>
//#include <strstream>

using namespace std;
/*声明Cmpstd类*/
template <class T>
class Cmpstd;

/*声明rbtree类 第一次声明的时候就要规定默认模板参数（模板参数可以是一个模板类Cmpstd<T>）*/
template <class T, class T2 = Cmpstd<T> >
class rbtree;

template <class T>
class Cmpstd
{
public:
	 bool operator ()(T a,T b)
     {
         return a < b;
     }
};

class exception2  
{
	/*声明友元类rbtree*/
	template <class T, class T2>
	friend class rbtree;
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

/*定义rbtree颜色枚举类型 0 1*/
enum ColorType
{
	RED, BLACK
};

/*定义rbnode's class*/
template <class T>
class rbnode            
{
public:
	T value;        	//node's value
	rbnode<T> *parent;	//node's parent
	rbnode<T> *left;	//node's left 
	rbnode<T> *right;   //node's right
	ColorType color;	//node's color

	/*rbnode no reference constructor*/
	rbnode()
	{}

	/*rbnode constructor*/
	rbnode(const T& val, rbnode<T> *l, rbnode<T> *r, rbnode<T> *p,ColorType c):value(val), 
		left(l), right(r), parent(p), color(c)
	{}
};

/*定义rbtree类*/
template <class T, class T2>
class rbtree
{	
	/*声明内部友元类iterator(可省略)*/
	friend class iterator;
	friend class reverse_iterator;
public:
	class iterator
	{
		/*声明外部友元类rbtree(不可省略)*/
		friend class rbtree<T, T2>;
	public:
		/*缺省构造*/
		iterator()
		{}

		/*有参构造:rbtree对象指针 和 rbnode对象指针*/
		iterator(rbnode<T> *_nodePtr, rbtree<T, T2> *_tree):nodePtr(_nodePtr),tree(_tree)
		{}

		/*友元成员函数重载 ==, !=, *, ++, --*/
		bool operator == (const iterator& rhs)const
		{
			return nodePtr == rhs.nodePtr;
		}

		bool operator != (const iterator& rhs)const
		{
			return nodePtr != rhs.nodePtr;
		}

		/*返回引用, 常函数,若rbnode对象为NIL 抛出异常exception2*/
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
				
				//最小节点
				while (nodePtr->left != NIL)
					nodePtr = nodePtr->left;
			}
			else if(nodePtr->right != NIL)	// 右节点不为空时
			{
				nodePtr = nodePtr->right;
				
				//第一个右节点后 的最左结点
				while(nodePtr->left != NIL)
					nodePtr = nodePtr->left;
			}
			else//右结点为空时， 回溯父节点（到子节点为左）
			{								
				p = nodePtr->parent;

				while(p != NIL && nodePtr == p->right)
				{
					nodePtr = p;
					p = p->parent;
				}

				//nodePtr 可能为NIL  可能是 第一左分叉点的父结点
				nodePtr = p;			
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
				nodePtr = tree->root;
				if (nodePtr == NIL)
				{
					cout<<"tree == NIL"<<endl;
					throw exception2("rbtree iterator operator* (): NULL reference");					
				}
				//最大节点
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

				//nodePtr 可能为NIL(他前一个节点可能为最小节点可能为root) 可能是 第一右分叉点的父结点
				nodePtr = p;
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
		rbtree<T, T2> *tree;  //++ --时当nodePtr为NIL时 用tree->root代替进而求出最小值
	};

	class reverse_iterator
	{
		/*声明外部友元类rbtree(不可省略)*/
		friend class rbtree<T, T2>;
	public:
		/*缺省构造*/
		reverse_iterator()
		{}

		/*有参构造:rbtree对象指针 和 rbnode对象指针*/
		reverse_iterator(rbnode<T> *_nodePtr, rbtree<T, T2> *_tree):nodePtr(_nodePtr),tree(_tree)
		{}

		/*友元成员函数重载 ==, !=, *, ++, --*/
		bool operator == (const reverse_iterator& rhs)const
		{
			return nodePtr == rhs.nodePtr;
		}

		bool operator != (const reverse_iterator& rhs)const
		{
			return nodePtr != rhs.nodePtr;
		}

		/*返回引用, 常函数,若rbnode对象为NIL 抛出异常exception2*/
		T& operator*()const
		{
			reverse_iterator tmp = *this;
			++tmp;

			/*root 为外部类的私有数据成员 可以在内部类中访问*/
			rbnode<T> *curr = tree->root;

			if (curr == NIL)
			{
				cout<<"tree == NIL"<<endl;
				throw exception2("rbtree reverse_iterator operator* (): NULL reference");					
			}

			while (curr->left != NIL)
				curr = curr->left;

			/*curr为最小节点*/
			if (nodePtr == curr)
			{
				throw exception2("rbtree reverse_iterator operator* (): NULL reference");
			}
			return tmp.nodePtr->value;
		}

		reverse_iterator& operator++ ()
		{
			rbnode<T> *p;
			if (nodePtr == NIL)
			{
				nodePtr = tree->root;
				if (nodePtr == NIL)
				{
					cout<<"tree == NIL"<<endl;
					throw exception2("rbtree reverse_iterator operator* (): NULL reference");					
				}
				// 最大节点
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

				//nodePtr 可能为NIL(他前一个节点可能为最小节点可能为root) 可能是 第一右分叉点的父结点
				nodePtr = p;
			}
			return *this;
		}

		reverse_iterator operator++ (int)
		{
			reverse_iterator tmp = *this;

			++*this;//注意是*this 不是指针

			// return the previous value
			return tmp;
		}

		reverse_iterator& operator-- ()
		{
			rbnode<T> *p;

			if (nodePtr == NIL)
			{
				nodePtr = tree->root;

				if (nodePtr == NIL)
				{
					cout<<"tree == NIL"<<endl;
					throw exception2("rbtree reverse_iterator operator* (): NULL reference");
				}
				
				//最小节点
				while (nodePtr->left != NIL)
					nodePtr = nodePtr->left;
			}
			else if(nodePtr->right != NIL)	// 右节点不为空时
			{
				nodePtr = nodePtr->right;
				
				//第一个右节点后 的最左结点
				while(nodePtr->left != NIL)
					nodePtr = nodePtr->left;
			}
			else//右结点为空时， 回溯父节点（到子节点为左）
			{								
				p = nodePtr->parent;

				while(p != NIL && nodePtr == p->right)
				{
					nodePtr = p;
					p = p->parent;
				}

				//nodePtr 可能为NIL  可能是 第一左分叉点的父结点
				nodePtr = p;			
			}

			return *this;			
		}

		reverse_iterator operator-- (int)
		{
			reverse_iterator tmp = *this;

			--*this;//从右到左结合 *this
			return tmp;
		}

	private:
		rbnode<T> *nodePtr;
		rbtree<T, T2> *tree;  //++ --时当nodePtr为NIL时 用tree->root代替进而求出最大值
	};

	/*empty rbtree*/
	rbtree();

	/*rbtree [first, last]*/
	rbtree(T *first, T *last);
		
	/*create a copy of obj*/
	rbtree(const rbtree<T, T2>& obj);
		
	/*destructor*/
	~rbtree();
		
	/*清除*/
	void clear();
		
	/*overload assignment*/
	rbtree<T, T2>& operator =(const rbtree<T, T2>& rhs);
		
	/*empty 只读函数*/
	bool empty() const;
	 
	/*size 只读函数*/
	int size() const;
		
	/*查找元素*/
	iterator find(const T& item)
	{
		rbnode<T> *curr;
		curr = findNode(item);

		if (NIL != curr)
			return iterator(curr, this);
		else
			return end();//指向NIL 结点
	}
		
	/*插入*/
	pair<iterator, bool> insert(const T& item)
	{	
		/*定义一个排序类对象变量*/	
		T2 c;
		rbnode<T> *curr = root, *parent = NIL, *newnode;
		// loop find(through the tree)
		while (curr != NIL)
		{
			if (item == curr->value)
			{
				/*返回一个pair类对象，
				里面相当find到了 要查如数值的迭代器，和返回了一个插入错误信息*/
				return pair<iterator, bool> (iterator(curr, this), false);
			}

			parent = curr;

			/*排序 查询方向*/
			if (c(item, curr->value))
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
		else if (c(item, parent->value))//排序 连接新节点
		{
			parent->left = newnode;//newnode代替原来的NIL
		}
		else
		{
			parent->right = newnode;
		}
		rbInsertFixup(newnode);
		treeSize++;

		/*返回一个pair类对象，
		里面相当find到了 要查如数值的迭代器，和返回了一个插入正确信息*/
		return pair<iterator,bool> (iterator(newnode,this), true);
	}	

	int erase(const T& item);

	void erase(iterator pos);

	void erase(iterator start, iterator end);

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

	reverse_iterator rbegin()
	{
		return reverse_iterator(NIL, this);
	}

	reverse_iterator rend()
	{
		rbnode<T> *curr = root;

		if (curr != NIL)
		{
			while (curr->left != NIL)
				curr = curr->left;
		}

		return reverse_iterator(curr,this);
	}

private:
	/*树的总节点数*/
	int treeSize;
	
	/*树的根节点*/
	rbnode<T> *root;
		
	/*NULL 空树  静态全局变量
	改变了 NIL使NIl无值 但是为黑，最后所有的叶子节点都是它*/
	static rbnode<T> *NIL;
		
	/*create an empty tree,by construction*/
	void makeEmptyTree();
		
	/*create a new rbnode*/
	rbnode<T> *getRBnode(const T& item, rbnode<T> *leftPtr,
		rbnode<T> *rightPtr, rbnode<T> *parentPtr, ColorType c);
	
	/*copy a tree*/
	rbnode<T> *copyTree(rbnode<T> *t);
		
	/*删除树*/
	void deleteTree(rbnode<T> *t);

	rbnode<T> *findNode(const T& item)const;

	void rotateLeft (rbnode<T> *pivot);
	
	void rotateRight(rbnode<T> *pivot);

	void rbInsertFixup(rbnode<T> *x);

	void rbDeleteFixup(rbnode<T> *x);
};	

template <class T, class T2>
rbnode<T> *rbtree<T, T2>::NIL = 0;

template <class T, class T2>
void rbtree<T, T2>::makeEmptyTree()
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

	//此时root没有key值 为空树
	treeSize = 0;
}

template <class T, class T2>
rbnode<T> *rbtree<T, T2>::getRBnode(const T& item, rbnode<T> *leftPtr,
		rbnode<T> *rightPtr, rbnode<T> *parentPtr, ColorType c)
{
	rbnode<T> *newnode = new rbnode<T>(item, leftPtr, rightPtr,
		parentPtr, c);
	return newnode;
}

template <class T, class T2>//递归复制树
rbnode<T> *rbtree<T, T2>::copyTree(rbnode<T> *t)
{
	rbnode<T> *newleft, *newright, *newnode;

	if (t == NIL)
	{
		return NIL;
	}

	newleft = copyTree(t->left);
	newright = copyTree(t->right);

	//parent为NIL，在前一个递归赋值，此时不知道他的父节点是谁
	newnode = getRBnode(t->value, newleft, newright, NIL, t->color);

	//当为NIL时，newnode->left已经为NIL 而NIL不必指向newnode
	if (newleft != NIL)
	{
		newleft->parent = newnode;
	}

	if (newright != NIL)
	{
		newright->parent = newnode;
	}

	/*当本身t为NIL时 , 节点就是NIL;
	当节点不为NIL时,用newnode复制t,返回newnode;*/
	return newnode;
}

template <class T, class T2>
void rbtree<T, T2>::deleteTree(rbnode<T> *t)
{
	if (t != NIL)
	{
		deleteTree(t->left);
		deleteTree(t->right);
		delete t;
	}
}

/*找寻节点*/
template <class T, class T2>
rbnode<T> *rbtree<T, T2>::findNode(const T& item)const
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

	//在外面还要判断是否为NIL
	return curr;
}

/*左旋转:c 和 pivot为分别为两个中心点，支轴左转(逆时针)*/
template <class T, class T2>
void rbtree<T, T2>::rotateLeft (rbnode<T> *pivot)
{		
	rbnode<T> *c = pivot->right;
	rbnode<T> *p = pivot->parent;

	//子节点的左孩子 成为 结点的右孩子 
	pivot->right = c->left;
		
	//结点 成为 节点的左孩子	
	c->left = pivot;
		
	//改变子结点(c)的parent指向
	c->parent = p;

	//改变结点(pivot)的parent指向
	pivot->parent = c;
		

	//善后工作
	//原子结点(c)左孩子的parent指向，root改变，p 的左右指向
	if (pivot->right != NIL)
	{
		pivot->right->parent = pivot;
	}

	if (pivot == root)
	{
		root = c;
	}
	else if (pivot == p->right)//p不为NIL(即p不为root)
	{
		p->right = c;
	}
	else
	{
		p->left = c;
	}
}

/*右旋转:c 和 pivot为分别为两个中心点，支轴左转(顺时针)*/
template <class T, class T2>
void rbtree<T, T2>::rotateRight(rbnode<T> *pivot)
{		
	rbnode<T> *c = pivot->left;
	rbnode<T> *p = pivot->parent;

	//子节点的右孩子 成为 结点的左孩子 
	pivot->left = c->right;
		
	//结点 成为 节点的右孩子	
	c->right = pivot;
		
	//改变子结点(c)的parent指向
	c->parent = p;
		
	//改变结点(pivot)的parent指向	
	pivot->parent = c;
		

	//善后工作
	//原 子结点(c)右孩子的parent指向，root改变，p 的左右指向
	if (pivot->left != NIL)
	{
		pivot->left->parent = pivot;
	}

	if (pivot == root)
	{
		root = c;  //旋转时涉及根结点  此时调整
	}
	else if (pivot == p->right)//p不为NIL(即p不为root)
	{
		p->right = c;
	}
	else
	{
		p->left = c;
	}
}

template <class T, class T2>//一红变两黑
void rbtree<T, T2>::rbInsertFixup(rbnode<T> *x)
{	
	rbnode<T> *y;//保存叔父结点的

	//区分特1(NIL也为黑).特2  和 3种情况
 	while (RED == x->parent->color)	//结束条件
 	{	
 		if (x->parent == x->parent->parent->left)//区分case2 和 case3是 左旋还是右旋
 		{
 			y = x->parent->parent->right;

 			//case1:①->① ② ③ 注意 ②不能到另一个②  所以才会用最前面的if限制 使② 之后 用③而不用另一个②
 			if (RED == y->color)
 			{
 				x->parent->color = BLACK;
 				y->color = BLACK;
 				y->parent->color = RED;
 				x = y->parent;    //不平衡点上移了*******
 			}			
 			else
 			{
 				//case2:②->③//无法用原来的② 也不能用后来的②无意义
 				if (x == x->parent->right)
	 			{
	 				x = x->parent;	//不平衡点上移了（实际下移了）*******
	 				rotateLeft(x);	//主分叉点增加+1
	 			}
	 			//case 3: ③->结束
	 			x->parent->color = BLACK;
	 			x->parent->parent->color = RED;
	 			rotateRight(x->parent->parent);	 //主分叉点减少-1	
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
 			else 
 			{
	 			if (x == x->parent->left)
	 			{
	 				x = x->parent;
	 				rotateRight(x);
	 			}
	 			x->parent->color = BLACK;
	 			x->parent->parent->color = RED;
	 			rotateLeft(x->parent->parent);	 				
 			}
 		}
 	}
 	root->color = BLACK;//特1
}

template <class T, class T2>
int rbtree<T, T2>::erase(const T& item)	//1:删除成功，0 :删除失败
{
	rbnode<T> *x = findNode(item);	//看是否找的到
	rbnode<T> *p = x->parent, *c, *old; 
	ColorType old_color;
	if (x != NIL)
	{
		if (NIL == x->left)			//当右节点不为空时（一个为空）
		{							//包括当左右节点（都为空）
			c = x->right;
			old = x;
		}
		else if(NIL == x->right)	//当左节点不为空时(一个为空)
		{	
			c = x->left;
			old = x;
		}
		else						//当左右节点都不为空时 找后继节点
		{							//右结点为空时， 回溯父节点（到子节点为左）包括在上面了
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


		if (1 == treeSize)	//删除root节点时（只有一个root结点时）
		{	
			delete old;	
			root = NIL;
		}
		else//不删除root节点时
		{
			if (NIL == p)		//删除root节点时（存在多个结点时结点）
			{
				root = c;
			}	
			else if (old == p->left)
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
	}
	else
	{
		return 0;
	}
	--treeSize;
	return 1;
}

template <class T, class T2>
void rbtree<T, T2>::erase(iterator pos)
{
	erase(*pos);//不能用erase(pos.nodePtr->value);//nodePtr私有的
}

/*切记删除的时候从end开始删除  因从start删除可能会造成后面迭代器保存的节点(被删除了)*/
template <class T, class T2> 
void rbtree<T, T2>::erase(iterator start, iterator end)
{
	iterator curr = end;
	--curr;
	if (start == begin() && end == rbtree<T, T2>::end())  //节约效率
	{
		clear();
	}
	else				//从后面删除
	{
		while (curr != start)
		{
			erase(curr--);
		}
		erase(curr);
	}
}

/*删除（节点后）修理树*/
template <class T, class T2>
void rbtree<T, T2>::rbDeleteFixup(rbnode<T> *x)
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
	//有3种情况1.通过case4，x为NIL时（如果用NULL表示这需要考虑if (x) ，此时NIL指向不为空）
	//2.通过case2.1，x为root时；3.通过case2.2 x为红时（y->p）  
}


template <class T, class T2>
rbtree<T, T2>::rbtree()
{
	makeEmptyTree();
}

template <class T, class T2>
rbtree<T, T2>::rbtree<T, T2>::rbtree(T *first, T *last)
{
	makeEmptyTree();
	while (first != last)
		insert(*first++);
}	
	
template <class T, class T2>
rbtree<T, T2>::rbtree(const rbtree<T, T2>& obj)  //为何在这里：treeSize（obj.treeSize）不管用呀？？
{
	makeEmptyTree();
	root = copyTree(obj.root);
	treeSize = obj.treeSize;
}



template <class T, class T2>
rbtree<T, T2>::~rbtree()
{
	deleteTree(root);
}

template <class T, class T2>
void rbtree<T, T2>::clear()
{
	deleteTree(root);

	root = NIL;
	treeSize = 0;
}

template <class T, class T2>
rbtree<T, T2>& rbtree<T, T2>::operator =(const rbtree<T, T2>& rhs)
{
	if (this != &rhs)
	{
		deleteTree(root);
		root = copyTree(rhs.root);
		treeSize = rhs.treeSize;
	}
	return *this;
}

template <class T, class T2>
bool rbtree<T, T2>::empty() const
{
	return treeSize == 0;
}

template <class T, class T2>
int rbtree<T, T2>::size() const
{
	return treeSize;
}

void output_rbtree(rbtree<int>& t)//必须要引用
{
	rbtree<int>::iterator it;
	for (it = t.begin(); it != t.end(); it++)
	{
		cout<<*it<<"\t";
	}
	cout<<endl;
}

#endif
