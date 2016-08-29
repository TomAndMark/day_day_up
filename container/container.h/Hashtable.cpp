/************************************************************
  FileName: Hashtable.cpp
  Author:Mark      Version :1.1         Date:2016.4.5
  Description:     this is a minilist container        
  Version:         1.1
  Function List:   some class hash_node  and some class hashtable functions
  History:         
      <author>  <time>   <version >   <desc>
      Mark    2016.3.28     1.0     build this moudle
      Mark    2016.4.5   	1.1     modify some notes
***********************************************************/
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#define N 20

using namespace std;

/*声明hashtable类*/
template <class T>
class hashtable;

template <class T>
class hash_node
{
	/*声明友元类*/
	friend class hashtable<T>;

	/*通过类外友元函数重载<<*/
	template <class T1>
	friend ostream& operator <<(ostream out, hash_node<T1> &tmp);
public:
	/*构造函数*/
	hash_node(T item):value(item), next(NULL)
	{}

private:
	T value;
	hash_node<T> *next;
};

template<class T>
ostream& operator <<(ostream out, hash_node<T> &tmp)
{
	out<<tmp.value;
	return out;
}

template <class T>
class hashtable
{
	/*为hash方法的函数指针类型 取别名*/
	typedef int (*hash)(const T& value);
public:
	/*构造空hash表 并且给方法赋值*/
	hashtable<T>(hash _fptr)
	{
		int i;
		for (i = 0; i < N; i++)
		{
			table[i] = NULL;
		} 
		fptr = _fptr;
	}

	/*************************************************
	  Function:       hash_insert
	  Description:    把val元素插入hash表中，插入前判断链表是否已经存在
	  Input:          val是一个类型为T的元素
	  Return:         void
	*************************************************/
	void hash_insert(const T& val) 
	{
		int key = fptr(val);
		hash_node<T>* newnode = NULL;
		if (NULL == table[key])
		{	
			newnode = new hash_node<T>(val);
			table[key] = newnode;
		}
		else
		{
			newnode = new hash_node<T>(val);
			hash_node<T> *curr = table[key];//curr为指针类型
			while (NULL != curr->next)
			{
				curr = curr->next;
			}
			curr->next = newnode;
		}
	}
	
	/*************************************************
	  Function:       hash_find
	  Description:    判断值为val的元素是否存在
	  Input:          val是一个类型为T的元素
	  Return:         boll类型，查找到了返回true，为查找到返回false
	*************************************************/
	bool hash_find(T val)
	{
		int key = fptr(val);
		if (NULL == table[key])
		{
			return false;
		}
		else
		{
			hash_node<T> *curr = table[key];
			while (NULL != curr && curr->value != val)
			{
				curr = curr->next;
			}

			if (NULL == curr)
			{
				return false;
			}
			else
			{
				return true;//也可以定义一个bool变量
			}
		}
	}

	/*************************************************
	  Function:       hash_delete
	  Description:    删除元素（所在节点）没有该元素 则输出"not find"
	  Input:          val是一个类型为T的元素
	  Return:         void
	*************************************************/
	void hash_delete(T value)  
  	{
    	int key=fptr(value);              
    	if(table[key] != NULL)
   	 	{
   	 		hash_node<T> *curr = table[key]; // * 指针
   	 		hash_node<T> *tmp = NULL;
   	 		int flag = 0;
   	 		while (NULL != curr)
   	 		{
   	 			if (value == curr->value)
   	 			{
   	 				if (NULL == tmp)
   	 				{
   	 					table[key] = curr->next;
   	 					delete curr;
   	 					curr = table[key];
   	 					if (0 == flag)
	   	 				{
	   	 					flag = 1;
	   	 				}	
   	 					continue;
   	 				}
   	 				else
   	 				{
   	 					tmp->next = curr->next;
   	 					delete curr;
   	 					curr = tmp;
   	 				}

   	 				if (0 == flag)
   	 				{
   	 					flag = 1;
   	 				}		    
   	 			}
   	 			tmp = curr;
   	 			curr = curr->next;
   	 		}

   	 		if (0 == flag)
   	 		{
   	 			cout<<"not find"<<endl;
   	 		}
    	}
 	}

 	/*************************************************
	  Function:       output_hash
	  Description:    输出hashtable中的元素
	  Return:         void
	*************************************************/
	void output_hash()
	{
		int i;
		hash_node<T> *curr;
		for (i = 0; i < N; i++)
		{
			if (NULL != table[i])
			{
				curr = table[i];
				while (NULL != curr)
				{
					cout<<curr->value<<"\t";
					curr = curr->next;
				}
				cout<<endl;
			}
		}
	}

private:
	hash_node<T> *table[N];
	hash fptr;	//函数方法

};

/*参数类型前后一致 在给hash方法的函数指针类型 取别名时*/
int hash_fun(const string& val)
{
	int i, sum = 0;
	for (i = 0; i < val.length(); i++)
	{
		sum += val[i];
	}
	return sum % N;
}
 
 /*主函数测试代码*/
int main(int argc, char const *argv[])
{
	hashtable<string> h(hash_fun);
	h.hash_insert("123445");
	h.hash_insert("123445");
	h.hash_insert("123445");
	h.hash_insert("123445");
	h.hash_insert("sdffdslkfk");
	h.hash_insert("1wel");
	h.output_hash();
	cout<<"\n\n";
	h.hash_delete("123445");
	h.output_hash();
	return 0;
}
