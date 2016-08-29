/************************************************************
  FileName: Vector.h
  Author:Mark      Version :1.1         Date:2016.4.5
  Description:     this is a minivector container        
  Version:         1.1
  Function List:   some class iterator functions and some class Vector functions
  History:         
      <author>  <time>   <version >   <desc>
      Mark    2016.3.24     1.0     build this moudle
      Mark    2016.4.5     	1.1     modify some notes
      Mark    2016.6.23     2.1     modify size_type, 算法未优化
***********************************************************/
#ifndef _VECTOR_
#define _VECTOR_

#include <iostream>
// #include <vector>
// #include <algorithm>

using namespace std;
	
/*降序*/
template <class T>
bool down(T a, T b)
{
	return a < b;
}	

/*升序*/
template <class T>
bool up(T a, T b)
{
	return a > b;
}

/*声明Vector类*/
template <class T>
class Vector;

/*构造异常exception2类*/
class exception2
{
	template <class T>
	friend class Vector;//不要<T>
public:
	/*异常类构造函数*/
	exception2(const char* str)
	{
		strcpy(msg, str);
	}

	/*返回异常信息函数*/
	char * what()
	{
      	return msg;
	}
private:
	 char msg[20];
};

typedef size_t size_type;

template <class T>
class Vector
{
	/*友元函数重载“<<”*/
	template <class T1>
	friend ostream& operator <<(ostream &out, const Vector<T1> v);

	/*友元函数重载“>>”*/
	template <class T2>
	friend istream& operator >>(istream &in, Vector<T2>& v);
public:
	/*对一个特定函数指针类型改名 排序（一元）谓词*/
	typedef bool (*sortfunp)(T a, T b);
	
	/*定义非逆迭代器（未定义迭代器类）用指针别名代替*/
    typedef T*  input_iterator;
    typedef T*  iterator;
    typedef const T*  cosnt_iterator;
	
	class reverse_iterator 
	{
		friend class Vector<T>;      //声明友元类（在类中类中声明外层类需要加<T>）
	public:
		reverse_iterator()			//缺省构造
		{
			curr = NULL;
		}

		reverse_iterator(T * s1):curr(s1)			//有参构造
		{}

		bool operator ==(const reverse_iterator &It)//重载 “==”
		{
			return curr == It.curr;
		}

		bool operator !=(const reverse_iterator &It)//重载 “！=”
		{
			return curr != It.curr;
		}

		reverse_iterator operator ++()	 //重载 前置“++”
		{
			curr--;
			return *this;
		}

		reverse_iterator operator ++(int)//重载 后置“++”
		{
			reverse_iterator it;
			it = *this;//*this
			curr--;
			return it;
		}

		reverse_iterator operator --()    //重载 前置“--”
		{
			curr++;
			return *this;
		}

		reverse_iterator operator --(int)//重载 后置“--”
		{
			reverse_iterator it;
			it = *this;//*this
			curr++;
			return it;
		}

		T& operator *()                  //引用 可改值
		{
			return *(curr-1);
		}
	private:
		T *curr;
	};

    /*begin()函数返回一个指向当前vector起始元素的迭代器.*/
	iterator begin()
	{
		return ptr;
	}

	/*end()函数返回一个指向当前vector末尾元素下一位置的迭代器.*/
	iterator end()
	{
		return ptr + sizes;
	}

	/*修改size的大小*/
	void mod_size(size_type size)
	{
		sizes = size;
	}

	/*修改capacity的大小*/
	void mod_capacity(size_type capacity)
	{
		capacities = capacity;
	}

	/*	erase函数要么删作指定位置loc的元素,要么删除区间[start, end)的所有元素.
    返回值是指向删除的最后一个元素的下一位置的迭代器*/
	iterator erase(iterator loc)
    {
    	if (loc >= end() || loc < begin())
	    {
		    throw exception2("out of range");//迭代器不在范围内，抛出异常
	    }

		iterator curr = loc;
		while (curr+1 != end())//若不抛出异常 此处超出报断错误
		{
			*curr = *(curr+1);
			curr++;
		}

		bzero(curr, sizeof(T));
		sizes -= 1;
		return loc;
    }

    iterator erase(iterator start, iterator end)
    {
    	if (end > Vector::end() || start < begin() || start > end)
	    {
		    throw exception2("out of range");
	    }

	    if (start == end)
	    {
	    	return start;
	    }

    	iterator curr = start;
		while (end != Vector::end())//若不抛出异常 此处超出报断错误
		{
			*curr = *end;
			curr++;
			end++;
		}

		bzero(curr, (end - curr)*sizeof(T));
		sizes -= end - curr;
		return start;
    }

	/*   rbegin函数返回指向当前vector末尾的逆迭代器.
    (译注:实际指向末尾的下一位置,而其内容为末尾元素的值,详见逆迭代器相关内容)*/
    reverse_iterator rbegin()
    {
    	return reverse_iterator(end());
    }

    /*rend()函数返回指向当前vector起始位置的逆迭代器.*/
  	reverse_iterator rend()
  	{
    	return reverse_iterator(begin());
  	}

	/*各种构造*/
	Vector();
	Vector(size_type num, const T &val);
	Vector(const Vector<T> &from);
	Vector(input_iterator start, input_iterator end);
	
	/*析构*/
	~Vector()
	{
		delete [] ptr;
		ptr = NULL;
	}

    /*重载运算符*/
    Vector<T>& operator =(const Vector<T> &rhs);
	bool operator == (Vector<T> &v);
	bool operator != (Vector<T> &v);
	bool operator < (Vector<T> &v);
	bool operator <= (Vector<T> &v);
	bool operator > (Vector<T> &v);
	bool operator >= (Vector<T> &v);
	T& operator [](size_type index)const;//const确保访问的值不被改变
	
	//at 引用
	T& at( size_type loc );

	// back() 函数返回当前vector最末一个元素的引用 
    T& back();

	// clear()函数删除当前vector中的所有元素.不改变sizes
	void clear();

	// 如果当前vector没有容纳任何元素,则empty()函数返回true,否则返回false.
    bool empty();

    // pop_back()函数删除当前vector最末的一个元素
    void pop_back();

    /*push_back()添加值为val的元素到当前vector末尾*/
	void push_back(const T &val);

	//sizes() 函数返回当前vector所容纳元素的数目 
    size_type size();

    //front()函数返回当前vector起始元素的引用
    T& front();

    // cpacity() 函数 返回当前vector在重新进行内存分配以前所能容纳的元素数量.
    size_type capacity();

    //insert() 函数有以下三种用法: 
	//insert() 函数有以下三种用法:
	// 在指定位置loc前插入值为val的元素,返回指向这个元素的迭代器,
	iterator insert(iterator loc, const T &val)
	{
		int i;
		int n = loc - begin();
		T v[sizes];
		for (i = 0; i < sizes; i++)
		{
			v[i] = ptr[i];
		}

		sizes += 1;
		if (sizes > capacities)
		{
			capacities = 2*sizes;
			delete [] ptr;
			ptr = new T[capacities];
		}

		iterator curr = begin();
		i = 0;
		while (n--)
		{
			ptr[i] = v[i];
			i++;
			curr++;
		}
		ptr[i] = val;
		for (i += 1; i < sizes; i++)
		{
			ptr[i] = v[i-1];
		}
		return curr;
	}

	//在指定位置loc前插入num个值为val的元素 
	void insert(iterator loc, int num, const T &val)
	{
		int i;
		int n = loc - begin();
		T v[sizes];
		for (i = 0; i < sizes; i++)
		{
			v[i] = ptr[i];
		}

		sizes += num;
		if (sizes > capacities)
		{
			capacities = 2*sizes;
			delete [] ptr;
			ptr = new T[capacities];
		}

		iterator curr = begin();
		i = 0;
		while (n--)
		{
			ptr[i] = v[i];
			i++;
			curr++;
		}

		int len = num;
		while (len--)
		{
			ptr[i] = val;
			i++;
		}

		for (; i < sizes; i++)
		{
			ptr[i] = v[i-num];
		}
	}

	//在指定位置loc前插入区间[start, end)的所有元素 .
	void insert(iterator loc, input_iterator start, input_iterator end)
	{
		int i;
		int n = loc - begin();
		T v[sizes];
		for (i = 0; i < sizes; i++)
		{
			v[i] = ptr[i];
		}
		int len = end - start;
		sizes += len;
		if (sizes > capacities)
		{
			capacities = 2*sizes;
			delete [] ptr;
			ptr = new T[capacities];
		}

		iterator curr = begin();
		i = 0;
		while (n--)
		{
			ptr[i] = v[i];
			i++;
			curr++;
		}

		while (start != end)
		{
			ptr[i] = *start;
			i++;
			start++;
		}

		for (; i < sizes; i++)
		{
			ptr[i] = v[i-len];
		}
	}

    // reserve()函数为当前vector预留至少共容纳size个元素的空间.(译注:实际空间可能大于size)
  	void reserve(size_type size);

  	// resize() 函数改变当前vector的大小为size,且对新创建的元素赋值val
	void resize(size_type size, T val);

	// swap()函数交换当前vector与vector from的元素
    void swap(Vector<T> &from);

    // 查找[begin, end)
    iterator find(input_iterator begin, input_iterator end, T val)
    {
    	iterator curr = begin;
    	while (curr < end)
    	{
    		if (val == *curr)
    		{
    			return curr;
    		}
    		curr++;
    	}
    	return Vector::end();
    }
    
	/*排序（一元）谓词 sort(FUN)
    定义一个函数指针类型，在code中参数为一个函数名/&函数名都行，
    因为执行一个函数可以用函数指针也可以用函数名，他们的地址相同
    通过该函数的传参和函数的返回值，例如：bool  sortdirection(T a,T b)  来达到类似对（）重载的效果*/
 	void sort(sortfunp fp = up)
    {	
	  	int i,j;
	    for(i = 0;i < sizes; i++)
	    {
	    	for(j = 0;j < sizes - i - 1; j++)
	    	{
	    		if(fp(ptr[j], ptr[j+1]))//可以用fp也可以用(*fp)
	    		{
	    			T tmp = ptr[j];
	    			ptr[j] = ptr[j+1];
	    			ptr[j+1] = tmp;
	    		}
	    	}
	    }
    }

private:
	T *ptr;
	size_type sizes;
	size_type capacities;
};

template <class T>
ostream& operator <<(ostream &out, const Vector<T> v)
{	
	int i;
	for (i = 0; i < v.sizes; ++i)
	{
		out<<v[i];
	}
	return out;
}

template <class T>
istream& operator >>(istream& in, Vector<T>& v)
{
	int i;
	for (i = 0; i < v.sizes; i++)
	{
		in>>v.ptr[i];
	}
	return in;
}

/*无参数 - 构造一个空的vector*/
template <class T>
Vector<T>::Vector()
{
	sizes = 0;
	capacities = 0;
	ptr = NULL;
}

/*数量(num)和值(val) - 构造一个初始放入num个值为val的元素的Vector */
template <class T>
Vector<T>::Vector(size_type num, const T &val)
{
	sizes = num;
	capacities = 2*sizes;
	ptr = new T[capacities];
	int i;
	for(i = 0; i < sizes; i++)
	{
		ptr[i] = val;
	}
}

/*vector(from) - 构造一个与vector from 相同的vector*/
template <class T>
Vector<T>::Vector(const Vector<T> &from)
{
	sizes = from.sizes;
	capacities = 2*sizes;
	ptr = new T[capacities];
	int i;
	for(i = 0; i < sizes; i++)
	{
		ptr[i] = from.ptr[i];
	}
}

/*迭代器(start)和迭代器(end) - 构造一个初始值为[start,end)区间元素的Vector(注:半开区间).*/
template <class T>
Vector<T>::Vector(input_iterator start, input_iterator end)
{
	sizes = end - start;
	capacities = 2*sizes;
	ptr = new T[capacities];
	int i = 0;
	while (start < end)
	{
		ptr[i] = *start;
		i++;
		start++;
	}
}

/*运算符 两个vectors被认为是相等的,如果: 
它们具有相同的容量 
所有相同位置的元素相等. 
vectors之间大小的比较是按照词典规则. */

template <class T>
Vector<T>& Vector<T>::operator =(const Vector<T> &rhs)
{
	delete [] ptr;
	ptr = NULL;
	
	sizes = rhs.sizes;
	capacities = 2*sizes;
	ptr=new T[capacities];
	int i;
	for(i = 0; i < sizes; i++)
	{
		ptr[i] = rhs.ptr[i];
	}
}

template <class T>
bool Vector<T>::operator ==(Vector<T> &v)
{
	if (v.capacities == capacities && v.sizes == sizes)
	{
		int i;
		for (i = 0; i < sizes; i++)
		{
			if (v.ptr[i] != ptr[i])
			{
				break;
			}
		}
		if (sizes == i)
		{
			return true;
		}
		return false;
	}
	return false;
}

template <class T>
bool Vector<T>::operator !=(Vector<T> &v)
{
	if (v.capacities != capacities || v.sizes != sizes)
	{
		return true;
	}
	else
	{
		int i;
		for (i = 0; i < sizes; i++)
		{
			if (v.ptr[i] != ptr[i])
			{
				break;
			}
		}
		if (sizes == i)
		{
			return false;
		}
		return true;
	}
}

template <class T>
bool Vector<T>::operator <(Vector<T> &v)
{
	int i;
	for (i = 0; i < sizes; i++)
	{
		if (ptr[i] < v.ptr[i])
		{
			return true;
		}
		if (ptr[i] > v.ptr[i])
		{
			return false;
		}
	}
	return false;
}

template <class T>
bool Vector<T>::operator <=(Vector<T> &v)
{
	int i;
	for (i = 0; i < sizes; i++)
	{
		if (ptr[i] > v.ptr[i])
		{
			return false;
		}
		if (ptr[i] < v.ptr[i])
		{
			return true;
		}
	}
	return true;
}

template <class T>
bool Vector<T>::operator >(Vector<T> &v)
{
	int i;
	for (i = 0; i < sizes; i++)
	{
		if (ptr[i] > v.ptr[i])
		{
			return true;
		}
		if (ptr[i] < v.ptr[i])
		{
			return false;
		}
	}
	return false;
}

template <class T>
bool Vector<T>::operator >=(Vector<T> &v)
{
	int i;
	for (i = 0; i < sizes; i++)
	{
		if (ptr[i] < v.ptr[i])
		{
			return false;
		}
		if (ptr[i] > v.ptr[i])
		{
			return true;
		}
	}
	return true;
}

template <class T>
T& Vector<T>::operator [](size_type index)const
{
	if (index >= sizes)
	{
		throw exception2("out of range");
	}
	return *(ptr+index);
}

/*at throw 异常 引用*/
template <class T>
T& Vector<T>::at(size_type loc)
{
	if (loc >= sizes)
	{
		throw exception2("out of range");
	}
	return *(ptr+loc);
}

/*back() 函数返回当前vector最末一个元素的引用 */
template <class T>
T& Vector<T>::back()
{
	return *(ptr + sizes - 1);
}

/*clear()函数删除当前vector中的所有元素  不改变sizes.*/
template <class T>
void Vector<T>::clear()
{
  memset(ptr, '\0', sizes*sizeof(T));  //可用bzero(ptr, sizes*sizeof(T))替换;
  sizes = 0;
}

/*如果当前vector没有容纳任何元素,则empty()函数返回true,否则返回false.*/
template <class T>
bool Vector<T>::empty()
{
	if (0 == sizes)
	{
		return true;
	}
	return false;
}

/*push_back()添加值为val的元素到当前vector末尾*/
template <class T>
void Vector<T>::push_back(const T &val)
{
	sizes += 1;
	if (sizes > capacities)
	{
		int i;
		T v[sizes-1];
		for (i = 0; i < sizes-1; i++)
		{
			v[i] = ptr[i];
		}
		capacities = 2*sizes;
		delete [] ptr;
		ptr = new T[capacities];
		for (i = 0; i < sizes-1; i++)
		{
			ptr[i] = v[i];
		}
	}
	ptr[sizes-1] = val; 
	return;
}

/*sizes() 函数返回当前vector所容纳元素的数目 */
template <class T>
size_type Vector<T>::size()
{
	return sizes;
}

/*front()函数返回当前vector起始元素的引用*/
template <class T>
T& Vector<T>::front()
{
	return *ptr;
}

/*capacity() 函数 返回当前vector在重新进行内存分配以前所能容纳的元素数量.*/
template <class T>
size_type Vector<T>::capacity()
{
	return capacities;
}

/*pop_back()函数删除当前vector最末的一个元素*/
template <class T>
void Vector<T>::pop_back()
{
  bzero(end()-1, sizeof(T));	
  sizes -= 1;
}

/*reserve()函数为当前vector预留至少共容纳size个元素的空间.(译注:实际空间可能大于size)*/
template <class T>
void Vector<T>::reserve(size_type size)
{
	if (size > capacities)
	{
		int i;
		T v[sizes];
		for (i = 0; i < sizes; i++)
		{
			v[i] = ptr[i];
		}
		capacities = 2*size;
		delete [] ptr;
		ptr = new T[capacities];
		for (i = 0; i < sizes; i++)
		{
			ptr[i] = v[i];
		}
	}
}

/*resize() 函数改变当前vector的大小为size,且对新创建的元素赋值val*/
template <class T>
void Vector<T>::resize(size_type size, T val)
{
	if (size >= sizes)
	{
		reserve(size);
		int n = size - sizes;
		int i;
		for (i = 0; i < n; i++)
		{
			ptr[sizes+i] = val;
		}
	}
	if (size < sizes)
	{
		int len = sizes - size;
		bzero(end()-len, len*sizeof(T));
	}
	sizes = size;
}

/*swap()函数交换当前vector与vector from的元素*/
template <class T>
void Vector<T>::swap(Vector<T> &from)
{
	int i;
	int size_from = from.size();
	int capacity_from = from.capacity();
	T f[from.capacity()];
	for (i = 0; i < from.size(); i++)
	{
		f[i] = from.ptr[i];
	}

	T v[sizes];
	for (i = 0; i < sizes; i++)
	{
		v[i] = ptr[i];
	}	

	from.mod_size(sizes);
	from.mod_capacity(capacities);
	delete [] from.ptr;
	from.ptr = new T[from.capacity()];
	for (i = 0; i < from.size(); i++)
	{
		from.ptr[i] = v[i];
	}

	sizes = size_from;
	capacities = capacity_from;
	delete [] ptr;
	ptr = new T[capacities];
	for (i = 0; i < sizes; i++)
	{
		ptr[i] = f[i];
	}
}

// /*通过逆迭代器输出Vector的值*/
// void out_put_vector(Vector<int> &v)
// {
// 	Vector<int>::reverse_iterator it;
// 	for(it = v.rbegin(); it != v.rend(); ++it)
// 	{
// 		cout<<*it<<"\t";
// 	}
// 	cout<<endl;
// }
#endif
