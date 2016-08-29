/************************************************************
  FileName: List.cpp
  Author:Mark      Version :1.1         Date:2016.4.5
  Description:     this is a minilist container        
  Version:         1.1
  Function List:   some class iterator , reverse_iterator functions and some class Vector functions
  History:         
      <author>  <time>   <version >   <desc>
      Mark    2016.3.26     1.0     build this moudle
      Mark    2016.4.5   	1.1     modify some notes
      Mark    2016.6.23     2.1     modify size_type, 算法未优化
***********************************************************/

#include <iostream>
#include <string>
#include <list>
using namespace std;

/*降序*/
template <class T>
bool  down(T a,T b)
{
	return a < b;
}	

/*升序*/
template<class T>
bool  up(T a,T b)
{
	return a > b;
}

/*unique谓词  用于去除特定的重复值*/
template <class T>
bool isunique(T data)
{
	if(data == 300)
		return true;
	else
		return false;
}

/*remove_if谓词 用于指定删除值*/
template <class T>
bool isremove(T data)
{
	if(data == 200)
		return true;
	else
		return false;
}

typedef size_t size_type;

/*声明List类  方便Lt_node类声明友元*/
template <class T>
class List;
	
/*定义节点类*/
template <class T>
class Lt_node
{
	template <class T1>
	friend class List;
public:
	T value;
	Lt_node<T> *prev;
	Lt_node<T> *next;

	/*当新建一个节点时，缺省构造*/ 
	Lt_node<T>()
	{
		next = this;
		prev = this;
	}	

	/*Lt_node<T> l(10); */
	Lt_node<T>(const T& val):value(val)
	{
		next = this;
		prev = this;
	}
};

/*定义List类*/
template <class T>
class List
{
public:
	class iterator
	{
		friend class List<T>;//外部类可以访问内部类 （外部类原本不能访问内部类的成员）
	public:
		/*缺省构造 iterator it;*/
		iterator()
		{}
		/*不缺省构造 iterator it(_prt)*/
		iterator(Lt_node<T> *_ptr):ptr(_ptr)
		{}

		/*重载运算符 此处为正迭代器  don’t overload < > <= >= 影响效率 无可取性*/
		bool operator ==(const iterator &It)
		{
			return ptr == It.ptr;
		}

		bool operator !=(const iterator &It)
		{
			return ptr != It.ptr;
		}

		iterator& operator ++() //加引用 后续方便改值
		{
			ptr = ptr->next;
			return *this;//【注意】返回的是*this---对象
		}

		iterator operator ++(int)//后置加加 不引用 返回的是临时对象
		{
			iterator it;
			it = *this;//*this
			ptr = ptr->next;
			return it;
		}

		iterator& operator --() //加引用
		{
			ptr = ptr->prev;
			return *this;
		}

		iterator operator --(int)//后置减减 不引用
		{
			iterator it;
			it = *this;//*this
			ptr = ptr->prev;
			return it;//【注意】返回的是*this
		}

		T& operator *()//引用 后续方便改值
		{
			return ptr->value;
		}

	private:
		Lt_node<T> *ptr;
	};

	class reverse_iterator
	{
		friend class List<T>;
	public:
		/*缺省构造 reverse_iterator it;*/
		reverse_iterator()
		{}

		/*不缺省构造 reverse_iterator it(_prt)*/
		reverse_iterator(Lt_node<T> *_ptr): ptr(_ptr)
		{}

		/*重载运算符 此处为逆迭代器  don’t overload < > <= >= 影响效率 无可取性*/
		bool operator == (const reverse_iterator& It)
		{
			return ptr == It.ptr;
		}

		bool operator != (const reverse_iterator& It)
		{
			return ptr != It.ptr;
		}

		reverse_iterator& operator ++() //加引用
		{
			ptr = ptr->prev;
			return *this;//【注意】返回的是*this
		}

		reverse_iterator operator ++(int)//不加 引用
		{
			reverse_iterator it;
			it = *this;//*this
			ptr = ptr->prev;
			return it;
		}

		reverse_iterator& operator --() //加引用
		{
			ptr = ptr->next;
			return *this;
		}

		reverse_iterator operator --(int)//后置减减 不引用
		{
			reverse_iterator it;
			it = *this;//*this
			ptr = ptr->next;
			return it;//【注意】返回的是*this
		}

		T& operator *()
		{
			return ptr->prev->value;
		}

	private:
		Lt_node<T> *ptr;
	};
	/*排序（一元）谓词*/
	typedef bool (*cmpfunp) (T a, T b);

	/*remove_if(一元)谓词*/
	typedef bool (*BinPred) (T a);

	/*unique(一元)谓词*/
	typedef bool (*	UnPred) (T a);

	/*给iterator重命名为input_iterator*/
	typedef iterator input_iterator;
	
	friend ostream& operator <<(ostream& out, List<T> &obj)
	{
		obj.curr = obj.head;
		while (obj.curr->next != obj.head)
		{
			obj.curr = obj.curr->next;
			out<<obj.curr->value<<"\t";
		}
		return out;
	}
	/*一个空的构造*/
	List();
		
	/*一个数为n，元素为item的构造	*/
	List(size_type n, const T& item);

	/*[ first ,last) 数据数组/指针*/
	List(T* first, T* last);

	/*[ begin ,end ) 迭代器*/
	List(iterator begin, iterator end);
	
	/*copy a List*/	
	List(const List<T>& obj);

	/*destuctor*/
	~List();

	/*//overloaded =*/
	List<T>& operator =(const List<T>& obj);	

	/*back()函数返回一个引用，指向list的最后一个元素。*/
  	T& back();
		
	/*返回begin()函数返回一个迭代器，指向list的第一个元素。*/
  	iterator begin()
	{
		return iterator(head->next);
	}
		
	/*end()函数返回一个迭代器，指向链表的末尾。*/
 	iterator end()
 	{
 		return iterator(head);
 	}

 	/*rbegin()函数返回一个逆向迭代器，指向链表的末尾。*/
	reverse_iterator rbegin()
	{
		return reverse_iterator(head);
	}

	/*rend()函数迭代器指向链表的头部。*/
 	reverse_iterator rend()
 	{
 		return reverse_iterator(head->next);
 	}
		
 	/*clear()函数删除list的所有元素。*/
    void clear();
		
    /*empty List*/
	bool empty() const;

	/*erase()函数删除以pos指示位置的元素,
    返回值是一个迭代器，指向最后一个被删除元素的下一个元素。*/
    iterator erase(iterator pos)
    {
    	pos.ptr->prev->next = pos.ptr->next;
    	pos.ptr->next->prev = pos.ptr->prev;
    	iterator it(pos.ptr->next);
    	delete pos.ptr;
    	--sizes;
    	return it;
    }

    /*或者删除start和end之间的元素。*/
  	iterator erase(iterator start, iterator end)
  	{
  		while (start != end)
  		{
  			start.ptr->prev->next = start.ptr->next;
    		start.ptr->next->prev = start.ptr->prev;
    		delete start.ptr;
    		++start;
    		--sizes;
  		}
  		return iterator(end.ptr);
  	}
  		
	/*front()函数返回一个引用，指向链表的第一个元素。*/
  	T& front();
  		
	/*insert()插入元素item到位置pos，*/
	iterator insert(iterator pos, const T &item)
	{
		pos_insert(pos, item);
		++sizes;
		return pos;
	}
		
	/*插入num个元素item到pos之前，*/
	void insert(iterator pos, size_type num, const T &item)
	{
		while (num--)
		{
			pos_insert(pos, item);
			++sizes;		
		}
	}	
		
	/*插入start到end之间的元素到pos的位置。
	返回值是一个迭代器，指向被插入的元素。*/ 
	void insert(iterator pos, input_iterator start, input_iterator end)
	{
		while (start != end)
		{
			pos_insert(pos, *start);
			++start;
			++sizes;
		}
	}
		
	/*merge()函数把自己和lst链表连接在一起，产生一个整齐排列的组合链表。
	如果指定compfunction，则将指定函数作为比较的依据。*/
	void merge(List<T> &lst, cmpfunp fp=up);
		
	/*pop_back()函数delete the last of lists。*/
    void pop_back();

    /*pop_front()delete the first of lists。*/	
    void pop_front();
    	
    /*push_back()make item connect to the last of lists。*/
	void push_back(const T &item);
		
 	/*push_front()make item connect to the first of lists*/
	void push_front(const T &item);
	
	/*remove()函数删除链表中所有值为val的元素。*/
  	void remove( const T &item );
  		
  	/*remove_if()以一元谓词pr为判断元素的依据，遍历整个链表。如果pr返回true则删除该元素。*/
	void remove_if(UnPred pr);
  		
	/*reverse()函数把list所有元素倒转。*/
	void reverse();
		
 	/*return size of List*/
	size_type size() const;
		
	/*sort*/
	void sort(cmpfunp fp = up);
		
	/*splice()函数把lst连接到pos的位置。或者用start和end指定范围。*/
	void splice(iterator pos, List<T> &lst);
		
	/*则插入lst中del所指元素到现链表的pos上，*/
	void splice(iterator pos, List<T> &lst, iterator del);
		
	/*splice()函数把lst连接到pos的位置。或者用start和end指定范围。 
	不能设定默认值。start 和 end  在这里无法调用lst.end()*/
	void splice(iterator pos, List<T> &lst, iterator start, iterator end);
		
	/*swap()函数交换lst和现链表中的元素。*/
 	void swap(List<T> &lst);
 		
 	/*unique()函数删除链表中所有重复的元素。如果指定pr，则使用pr来判定是否删除。*/	
 	void unique();

    void unique(BinPred pr);
		
    /*找到第一个  返回迭代器*/
    iterator find(iterator first, iterator last, const T &item)
    {
    	while (first != last)
    	{
    		if (item == *first)
    		{
    			return first;
    		}
    		++first;
    	}
    }

private:
	Lt_node<T> *curr;
	Lt_node<T> *head;
	size_type sizes;

	/*构造+插入新建节点*/
	void cst_insert(Lt_node<T>*& curr, const T &item)
	{
		Lt_node<T> *newnode = new Lt_node<T>(item);
		newnode->prev = curr;
		curr->next = newnode;
		curr = curr->next;	
	}

	/*删除节点*/
	void tmp_delete(Lt_node<T>* &curr, Lt_node<T>* &tmp)
	{
		tmp = curr;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		curr = curr->next;
		delete tmp;
	}

	/*插入新节点*/
	void pos_insert(iterator& pos, const T &item)
	{
		Lt_node<T>* newnode = new Lt_node<T>(item);
		pos.ptr->prev->next = newnode;
		newnode->prev = pos.ptr->prev;
		newnode->next = pos.ptr;
		pos.ptr->prev = newnode;		
	}
};

template <class T>
List<T>::List():sizes(0)
{
	head = new Lt_node<T>;
	curr = head;
}

template <class T>
List<T>::List(size_type n, const T &item):sizes(n)
{
	int i;
	head = new Lt_node<T>;
	curr = head;
	for (i = 0; i < n; i++)//定义一个函数用来赋值操作
	{
		cst_insert(curr, item);
	}
	curr->next = head;
	head->prev = curr;
}

template <class T>
List<T>::List(T* first, T* last):sizes(0)
{
	T *tmp = first;
	head = new Lt_node<T>;
	curr = head;
	while (tmp != last)
	{
		cst_insert(curr, *tmp);
		tmp++;
		sizes++;
	}
	curr->next = head;
	head->prev = curr;
}
template <class T>
List<T>::List(iterator begin, iterator end)
{
	head = new Lt_node<T>;
	curr = head;
	while (begin != end)
	{
		cst_insert(curr, *begin);
		begin++;
		sizes++;
	}
	curr->next = head;
	head->prev = curr;
}

template <class T>
List<T>::List(const List<T> &obj):sizes(obj.sizes)
{
	head = new Lt_node<T>;
	curr = head;
	Lt_node<T> *tmp = obj.head;
	while (tmp->next != obj.head)
	{
		tmp = tmp->next;
		cst_insert(curr, tmp->value);
	}
	curr->next = head;
	head->prev = curr;
}

template <class T>
List<T>::~List()
{
	Lt_node<T> *tmp;
	curr = head->next;
	head->next = head;
    while (curr != head)
    {
 	  tmp_delete(curr, tmp);
    }
	delete head;
}

template <class T>
List<T>& List<T>::operator =(const List<T> &obj)
{
	Lt_node<T> *tmp;
	curr = head->next;
	head->next = head;
    while (curr != head)
    {
 	  tmp_delete(curr, tmp);
    }

    obj.curr = obj.head;
    while (obj.curr->next != obj.head)
	{
		obj.curr = obj.curr->next;
		cst_insert(curr, obj.curr->value);
	}
	sizes = obj.sizes;
	curr->next = head;
	head->prev = curr;
}

template <class T>
T& List<T>::back()
{
	curr = head;
	while (curr->next != head)
	{
		curr = curr->next;
	}
	return curr->value;
}

template <class T>
void List<T>::clear()
{
	Lt_node<T> *tmp;
	curr = head->next;
	head->next = head;
    while (curr != head)
    {
 	  tmp_delete(curr, tmp);
    }
    sizes = 0;
}

template <class T>
bool List<T>::empty() const
{
	return sizes == 0;
}

template <class T>
T& List<T>::front()
{
	return head->next->value;
}

/*merge()函数把自己和lst链表连接在一起，产生一个整齐排列的组合链表。
如果指定compfunction，则将指定函数作为比较的依据。*/
template <class T>
void List<T>::merge(List<T> &lst, cmpfunp fp)
{
	iterator tmp = lst.begin();
	while (tmp != lst.end())//pos_insert(end(), *tmp); 再此不能调用
	{
		Lt_node<T>* newnode = new Lt_node<T>(*tmp);
		head->prev->next = newnode;
		newnode->prev = head->prev;
		newnode->next = head;
		head->prev = newnode;	

		++tmp;
		++sizes;
	}
	sort(fp);
}

template <class T>
void List<T>::pop_back()
{
	erase(--end());
}

template <class T>
void List<T>::pop_front()
{
	erase(begin());
}

template <class T>
void List<T>::push_back(const T &item)
{
	insert(end(), item);
}

template <class T>
void List<T>::push_front(const T &item)
{
	insert(begin(), item);
}

template <class T>
void List<T>::remove(const T &item)
{
	iterator it = begin();
	while (it != end())
	{
		if (item == *it)
		{
			erase(it++);
		}
		else
		{
			++it;
		}
	}
}

template <class T>
void List<T>::remove_if(UnPred pr)
{
	iterator it = begin();
	while (it != end())
	{
		if (pr(*it))
		{
			erase(it++);
		}
		else
		{
			++it;
		}
	}
}

template <class T>
void List<T>::reverse()
{
	iterator it_begin = begin();
	iterator it_end = --end();
	while (it_begin != it_end )
	{
		T tmp = *it_begin;
		*(it_begin++) = *it_end;
		*(it_end--) = tmp;
		if (it_begin.ptr->prev == it_end.ptr)
		{
			break;
		}
	} 
}

template <class T>
size_type List<T>::size()const
{
	return sizes;
}

template <class T>
void List<T>::sort(cmpfunp fp)
{	
  	int i,j;
    for(i=0; i < sizes; i++)
    {
    	curr = head->next;
    	for(j=0; j < sizes-i-1; j++)
    	{
    		if(fp(curr->value, curr->next->value))//可以用fp也可以用(*fp)
    		{
    			T tmp = curr->value;
    			curr->value = curr->next->value;
    			curr->next->value = tmp;
    		}
    		curr = curr->next;//【注意】不能漏
    	}
    }
}

template <class T>
void List<T>::splice(iterator pos, List<T> &lst)
{
	iterator start = lst.begin();
	while (start != lst.end())
	{
		insert(pos, *start);
		++start;
	}	
}

template <class T>
void List<T>::splice(iterator pos, List<T> &lst, iterator del)
{
	insert(pos, *del);
}

template <class T>
void List<T>::splice(iterator pos, List<T> &lst, iterator start, iterator end)
{
	while (start != end)
	{
		insert(pos, *start);
		++start;
	}
}

template <class T>
void List<T>::swap(List<T> &lst)
{
	iterator this_begin = begin();
	iterator lst_begin = lst.begin();
	T tmp;
	while (this_begin != end() || lst_begin != lst.end())
	{
		if (this_begin != end() && lst_begin != lst.end())
		{
			tmp = *this_begin;
			*(this_begin++) = *lst_begin;
			*(lst_begin++) = tmp;		
		}
		else if(this_begin != end())
		{
			insert(lst_begin, *this_begin);
			erase(this_begin++);
		}
		else
		{
			insert(this_begin, *lst_begin);
			erase(lst_begin++);
		}
	}
}

template <class T>
void List<T>::unique()
{
	iterator it_a = begin();
	iterator it_b(it_a.ptr->next);
	while (it_b != end())
	{
		if (*it_a == *it_b)
		{
			erase(it_b++);
		}
		it_a++;
		it_b++;
	}
}

template <class T>
void List<T>::unique(BinPred pr)
{
	iterator it_a = begin();
	iterator it_b(it_a.ptr->next);
	while (it_b != end())
	{
		if (*it_a == *it_b && pr(*it_a))
		{
			erase(it_b++);
		}
		it_a++;
		it_b++;
	}
}

/*按正迭代器输出*/
void output_list(List<int> &l)
{
	List<int>::iterator it;
	for (it = l.begin(); it != l.end(); ++it)
	{
		cout<<*it<<"\t";
	}
	cout<<endl;
}

/*按逆迭代器输出*/
void output_list_reverse(List<int> &l)
{
	List<int>::reverse_iterator it;
	for (it = l.rbegin(); it != l.rend(); ++it)
	{
		cout<<*it<<"\t";
	}
	cout<<endl;
}


//排序位置  注意     旋转问题分 奇数 偶数
int main(int argc, char const *argv[])
{
	List<int>  list1;
	//List<int>  list2(4);
	List<int>  list3(4,5);
	list1.push_back(20);
	list1.push_back(30);
	list1.push_back(50);
	list1.push_front(2);
	list1.push_front(5);
	list1.push_front(6);
	list1.push_back(200);
	list1.push_front(30);
	output_list(list1);

	/*cout<<list1.back()<<endl;
	cout<<list1.front()<<endl;

    list1.merge(list3);//
    //list1.pop_back();
    //list1.pop_front();
    //output_list(list1);
    //list1.remove(30);
	//list1.remove_if(isremove);

	//list1.reverse();
	List<int>::iterator retit=list1.find(list1.begin(),list1.end(),30);
	if(retit==list1.end())
	{
		cout<<"not found"<<endl;
	}
	cout<<*retit<<endl;
	//list1.erase(retit);
	//list1.insert(retit,5000);
	//list1.insert(retit,2,5000);
	//list1.insert(retit,list3.begin(),list3.end());
	//output_list(list1);
    //output_list_reverse(list1);*/
    //list1.sort(up);//默认是升序
   	list1.insert(list1.end(),5000);
    //list1.sort(down);
    //list1.sort(cmp);
	//list1.unique();//必须先排序
	// list1.splice(list1.begin(),list3);
    output_list(list1);
    //output_list_reverse(list1);
	return 0;
}
