#include <iostream>
#include <map>
#include <utility> //可以不用重新声明 因为<map>中已经包含了<utility>的声明了
	//该程序抛出异常部分 未完善
	//一个map容器包括:关键字/值  pair类型
	//键值(key):可以是任意数据类型,只读,不重复,有序  （有一个修该过程）
	//值(value):任意数据类型
	//map必须有一个默认的构造
#include "rb_tree.h"


template <class Key, class T>
class Map
{  
public:

	typedef pair<Key, T> value_type;//Key 可以为 const Key 表示只读对Key
	
	typedef class rbtree<pair<Key, T> >::iterator iterator;
		//【注意 注意 这里的class 不能漏】

	typedef class rbtree<pair<Key, T> >::reverse_iterator reverse_iterator;
		//【注意 注意 这里的class 不能漏】
	
	Map();
		//定义map无参数构造

	Map(value_type *first, value_type *last);
		//一个pair类型的数组。其中的两个指针[first, last)

	Map(const Map<Key, T>& obj);
		//对象构造

	~Map();
		//析构函数

	iterator begin()
	{
		return t.begin();
	}
		//begin()函数返回一个迭代器指向map的首部。

  	iterator end()
  	{
  		return t.end();	
  	}
		//end()函数返回一个迭代器指向map的尾部。

  	reverse_iterator rbegin()
  	{
  		return t.rbegin();
  	}
		//rbegin()函数返回一个指向map尾部的逆向迭代器。

  	reverse_iterator rend()
  	{
  		return t.rend();	
  	}
		//rend()函数返回一个指向map头部的逆向迭代器。

	void clear();
		//
		
  	int count(const Key &key);
  		//count()函数返回map中键值等于key的元素的个数。
  
  	bool empty();
		//empty()函数返回真(true)如果map为空，否则返回假(false)。

  	pair<iterator, iterator> equal_range(const Key &key)
  	{
		pair<iterator, iterator> p;
		p.first = t.find(key);
		p.second = t.find(key);
		return p;
  	}
		//equal_range()函数返回两个迭代器——一个指向第一个键值为key的元素，另一个指向最后一个键值为key的元素。

  	void erase(iterator pos);
  	
  	void erase(iterator start, iterator end);
  	
  	int erase(const Key &key);

  	iterator find(const Key &key)
  	{	
  		iterator curr = begin();
  		while (curr != end())
  		{
  			if ((*curr).first == key)
  			{
  				return curr;
  			}
  		}
		return curr;  //end();
  	}
		//find()函数返回一个迭代器指向键值为key的元素，如果没找到就返回指向map尾部的迭代器。

 	// iterator insert(iterator pos, const pair<Key, T> &val);
 	// void insert(iterator start, iterator end);  //无意义 插入后还要排序

 	pair<iterator, bool> insert(const pair<Key, T> &val)
 	{
		return t.insert(val);
 	}

 	iterator lower_bound(const Key &key)
 	{
		iterator curr = begin();
		while (curr != end())
		{
			if ((*curr).first >= key)
			{
				return curr;
			}
			++curr;
		}
		return end();  //没有返回end()
 	}
		//lower_bound()函数返回一个迭代器，指向map中键值>=key的第一个元素。

  	int size();
		//size()函数返回map中保存的元素个数。

  	void swap(Map &obj);
		//swap()交换obj和现map中的元素。

  	iterator upper_bound(const Key &key)
	{
		iterator curr = begin();
		while (curr != end())
		{
			if ((*curr).first > key)
			{
				return curr;
			}
			++curr;
		}
		return end();  //没有返回end()	
	}
		//upper_bound()函数返回一个迭代器，指向map中键值>key的第一个元素。

private:
	rbtree<pair<Key, T> > t;
		//一个树对象
};

template <class Key,class T>
Map<Key, T>::Map():t()
{}

template <class Key,class T>
Map<Key, T>::Map(value_type *first, value_type *last):t(first, last)
{}

template <class Key,class T>
Map<Key, T>::Map(const Map<Key, T>& obj):t(obj.t)
{}

template <class Key,class T>
Map<Key, T>::~Map()
{}



template <class Key,class T>
void Map<Key, T>::clear()
{
	t.clear();
}
	
template <class Key,class T>
int Map<Key, T>::count(const Key &key)
{
	return 1;
}

template <class Key,class T>
bool Map<Key, T>::empty()
{
	return t.empty();
}

template <class Key,class T>
void Map<Key, T>::erase(iterator pos)
{
	t.erase(pos);
}
	
template <class Key,class T>	
void Map<Key, T>::erase(iterator start, iterator end)
{
	t.erase(start, end);
}

template <class Key,class T>	
int Map<Key, T>::erase(const Key &key)
{
	iterator curr = begin();
	while (curr != end())
	{
		if ((*curr).first == key)
		{
			return t.erase(*curr);
		}
		++curr;
	}
	return 0;
}

template <class Key,class T>
int Map<Key, T>::size()
{
	return t.size();
}
	
template <class Key,class T>	
void Map<Key, T>::swap(Map<Key, T> &obj)
{
	Map<Key, T> tmp(*this);
	t = obj.t;
	obj.t = tmp.t;
}



void output_map(Map<string,int>& m)
{
	Map<string,int>::iterator it;
	for(it = m.begin(); it != m.end(); it++)
	{
	    //it->first="acd";//key不能修改

		//it->second=400;     
		cout<<(*it).first<<"\t"<<(*it).second<<endl; 
			//真正Linux中map的实现 是这个迭代器中有一个指向pair类型的指针
	}
	cout<<endl;
}

void output_map2(Map<string,int>& m)
{
	Map<string,int>::reverse_iterator it;
	for(it = m.rbegin(); it != m.rend(); it++)
	{
	    //it->first="acd";//key不能修改
		//it->second=400;     
		cout<<(*it).first<<"\t"<<(*it).second<<endl; 
			//真正Linux中map的实现 是这个迭代器中有一个指向pair类型的指针
	}
	cout<<endl;
}

int main(int argc, char const *argv[])
{
	Map<string, int> m1;
	cout<<"m1.empty"<<m1.empty()<<endl;
	m1.insert(pair<string, int>("1223", 31));
	m1.insert(pair<string, int>("123", 31));
	m1.insert(pair<string, int>("113", 31));
	m1.insert(pair<string, int>("123", 31));
	cout<<"m1.empty"<<m1.empty()<<endl;
	Map<string, int> m2(m1);
	cout<<"m2.empty"<<m2.empty()<<endl;
	//m2.clear();
	cout<<"count"<<m1.count("123")<<endl;;  //输入关键字
	cout<<"size"<<m1.size()<<endl;  
	
	Map<string,int>::iterator i = m1.upper_bound("113");//upper_bound  lower_bound
	cout<<"i:"<<(*i).first<<"\t"<<(*i).second<<endl; 

	m1.erase(m1.begin());
	//m1.erase("123");
	output_map(m1);
	output_map2(m1);
	output_map(m2);
	output_map2(m2);

	m1.swap(m2);
	//output_map(m1);
	//output_map(m2);
	return 0;
}
