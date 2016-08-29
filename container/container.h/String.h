/************************************************************************
*	file   :  String.h
*	desc   :  自定义string顺序容器头文件
*			  1.size_type 返回值不能和int类型进行运算 eg：size(),capacity()等
*             2.部分成员函数未完善，replace一部分、insert一部分
*   author :  Mark  2016.3.20
*	version:  2.0
*	modify :  2016.6.21~2016.6.22 更新优化了除find_first_of、find_first_not_of、find_last_of
*             find_last_not_of外的代码
**************************************************************************/
#ifndef _STRING_
#define _STRING_

#include <iostream>
#include "basic_function.h"

using namespace std;

class String;
class exception2
{
	friend class String;
public:
	exception2(const char* str)
	{
		Strcpy(msg,str);
	}
	char * what()
	{
      return msg;
	}
private:
	 char msg[20];
};


typedef size_t size_type;

class String 
{
	/*friend operator overload*/
	friend ostream& operator <<(ostream &out, const String &obj);
	friend istream& operator >>(istream &in, String &obj);

	friend String operator +(const String &lhs, const String &rhs);
	friend String operator +(const char *str, const String &rhs);

	friend bool operator ==(const String &lhs, const String &rhs);
	friend bool operator ==(const char *str, const String &rhs);

	friend bool operator !=(const String &lhs, const String &rhs);
	friend bool operator !=(const char *str, const String &rhs);

	friend bool operator <(const String &lhs, const String &rhs);
	friend bool operator <(const char *str, const String &rhs);

	friend bool operator <=(const String &lhs, const String &rhs);
	friend bool operator <=(const char *str, const String &rhs);

	friend bool operator >(const String &lhs, const String &rhs);
	friend bool operator >(const char *str, const String &rhs);

	friend bool operator >=(const String &lhs, const String &rhs);
	friend bool operator >=(const char *str, const String &rhs);
public:
  /*constructor*/
  String();
  String(size_type length, char ch);
  String(const char *str);
  String(const char *str, size_type length );
  String(const char* str, size_type index, size_type length);//String &str
  String(const char *start, const char *end);

  /*copy constructor*/
  String(const String &obj);

  /*disconstructor*/
  ~String();

  /*member operator overload*/
  String& operator = (const String &rhs);  
  String& operator += (const String &rhs);

  char& operator [] (size_type index)const;//************************返回的值不不能改变  内容
  
  /*append*/
  String& append(const String &obj);
  String& append(const char *str);
  String& append(const String &obj, size_type index, size_type len);
  String& append(const char *str, size_type num);
  String& append(size_type num, char ch);
  String& append(const char *start, const char *end);
  
  /*赋值 assign*/
  String& assign(const String &obj);
  String& assign(const char *str);
  String& assign(const char *str, size_type num);
  String& assign(const String &obj, size_type index, size_type len);
  String& assign(size_type num, char ch);

  /*at 返回一个引用"out of range"*/
  char& at(size_type index);

  /*begin()函数返回一个迭代器,指向字符串的第一个元素.*/
  char* begin();

  /*end()函数返回一个迭代器，指向字符串的末尾(最后一个字符的下一个位置).*/
  char* end();

  /*返回一个指向正规C字符串的指针, 内容与本字符串相同.*/
  char* c_str();
  
  /*函数返回字符元素个数*/
  size_type size();

  /*函数返回在重新申请更多的空间前字符串可以容纳的字符数. 这个数字至少与 size()一样大.*/
  size_type capacity();

  /*compare()函数以多种方式比较本字符串和str,返回：*/
  int compare(const String &obj);
  int compare(const char *str);
  int compare(size_type index, size_type length, const String &obj);
  int compare(size_type index, size_type length, const String &obj, size_type index2,size_type length2);
  int compare(size_type index, size_type length, const char *str, size_type length2);
  
  /*copy()函数拷贝自己的num个字符到str中（从索引index开始）。返回值是拷贝的字符数*/
  size_type copy(char *str, size_type num, size_type index);
  
  /*data()函数返回指向自己的第一个字符的指针.*/
  char *data();

  /*如果字符串为空则empty()返回真(true)，否则返回假(false).*/
  bool empty();

  /*erase*/
  char* erase(char *pos);
  char* erase(char *start, char *end);	
  String& erase(size_type index = 0, size_type num = npos);
  
  /*find*/
  size_type find(const String &obj, size_type index);
  size_type find(const char *str, size_type index);
  size_type find(const char *str, size_type index, size_type length);
  size_type find(char ch, size_type index);

  /*********length()函数返回字符串的长度. 这个数字应该和size()返回的数字相同.*/
  size_type length();

  /*max_size()函数返回字符串能保存的最大字符数。max_size - 当前对象string大小  = 剩余string大小*/
  size_type max_size();

  /*交换*/
  void swap(String &obj);
  /*替换*/
  String& replace(size_type index, size_type num, const String &obj);
  String& replace(size_type index1, size_type num1, const String &obj, size_type index2, size_type num2);
  String& replace(size_type index, size_type num, const char *str);
  String& replace(size_type index, size_type num1, const char *str, size_type num2);
  String& replace(size_type index, size_type num1, size_type num2, char ch);
  String& replace(char *start, char *end, const String &obj);
  String& replace(char *start, char *end, const char *str);
  String& replace(char *start, char *end, const char *str, size_type num);
  String& replace(char *start, char *end, size_type num, char ch);
  
  /*rfind()函数*/
  size_type rfind(const String &obj, size_type index = npos);
  size_type rfind(const char *str, size_type index = npos);
  size_type rfind(const char *str, size_type index, size_type num);
  size_type rfind(char ch, size_type index = npos);

  /*substr()返回本字符串的一个子串，从index开始，长num个字符。如果没有指定，
  将是默认值 string::npos。这样，substr()函数将简单的返回从index开始的剩余的字符串。*/
  String substr(size_type index = 0, size_type num = npos) const;
  
  /*插入(insert) */
  char* insert(char *i, const char &ch);
  String& insert(size_type index, const String &obj);
  String& insert(size_type index, const char *str);
  String& insert(size_type index1, const String &obj, size_type index2, size_type num);
  String& insert(size_type index, const char *str, size_type num);
  String& insert(size_type index, size_type num, char ch);
  void insert(char *i, size_type num, const char &ch);
  void insert(char *i, char *start, char *end);
  /*find_first_of*/
  int find_first_of( const String &str, int index = 0 );
  int find_first_of( const char *str, int index = 0 );
  int find_first_of( const char *str, int index, int num );
  int find_first_of( char ch, int index = 0 );
  /*find_first_not_of*/
  int find_first_not_of( const String &str, int index = 0 );
  int find_first_not_of( const char *str, int index = 0 );
  int find_first_not_of( const char *str, int index, int num );
  int find_first_not_of( char ch, int index = 0 );
  /*find_last_of*/
  int find_last_of( const String &str, int index = -1 );
  int find_last_of( const char *str, int index = -1 );
  int find_last_of( const char *str, int index, int num );
  int find_last_of( char ch, int index = -1 );
  /*find_last_not_of*/
  int find_last_not_of( const String &str, int index = -1 );
  int find_last_not_of( const char *str, int index = -1);
  int find_last_not_of( const char *str, int index, int num );
  int find_last_not_of( char ch, int index = -1 );

private:
	char *Str;
	size_type str_len;
	size_type Capacity;
	static size_type npos;
};

size_type String::npos = -1;

/*重载 <<*/
ostream& operator << (ostream &out, const String &obj)
{ 
	out << obj.Str;
	return out;
}

/*重载 >>*/
istream& operator >>(istream &in, String &obj)
{
	in >> obj.Str;
	return in;
}

/*friend operator +*/
String operator +(const String &lhs, const String &rhs)
{
	String tmp;
	tmp.str_len = lhs.str_len + rhs.str_len;
	tmp.Capacity = tmp.str_len;
	tmp.Str = new char[tmp.Capacity + 1];
	Strcpy(tmp.Str, lhs.Str);
	Strcat(tmp.Str, rhs.Str);
	return tmp;
}
/*friend operator char* + String*/
String operator +(const char *str, const String &rhs)
{
	String tmp;
	tmp.str_len = Strlen(str) + rhs.str_len;
	tmp.Capacity = tmp.str_len;
	tmp.Str = new char[tmp.Capacity + 1];
	Strcpy(tmp.Str, str);
	Strcat(tmp.Str, rhs.Str);
	return tmp;
}

/*friend operator ==*/
bool operator ==(const String &lhs, const String &rhs)
{
	if (!Strcmp(lhs.Str, rhs.Str))
	{
		return true;
	}
	return false;
}

/*friend operator char* == String*/
bool operator ==(const char *str, const String &rhs)
{
	if (!Strcmp(str, rhs.Str))
	{
		return true;
	}
	return false;
}

/*friend operator !=*/
bool operator !=(const String &lhs, const String &rhs)
{
	return !(lhs == rhs);
}

/*friend operator char* != String*/
bool operator !=(const char *str, const String &rhs)
{
	return !(str == rhs);
}

/*friend operator <*/
bool operator <(const String &lhs, const String &rhs)
{
	if (Strcmp(lhs.Str, rhs.Str) < 0)
	{
		return true;
	}
	return false;
}

/*friend operator char* < String*/
bool operator <(const char *str, const String &rhs)
{
	if (Strcmp(str, rhs.Str) < 0)
	{
		return true;
	}
	return false;
}

/*friend operator <=*/
bool operator <=(const String &lhs, const String &rhs)
{
	if (Strcmp(lhs.Str, rhs.Str) <= 0)
	{
		return true;
	}
	return false;
}

/*friend operator char* <= String*/
bool operator <=(const char *str, const String &rhs)
{
	if (Strcmp(str, rhs.Str) <= 0)
	{
		return true;
	}
	return false;
}

/*friend operator >*/
bool operator >(const String &lhs, const String &rhs)
{
	if (Strcmp(lhs.Str, rhs.Str) > 0)
	{
		return true;
	}
	return false;
}

/*friend operator char* > String*/
bool operator >(const char *str, const String &rhs)
{
	if (Strcmp(str, rhs.Str) > 0)
	{
		return true;
	}
	return false;
}

/*friend operator >=*/
bool operator >=(const String &lhs, const String &rhs)
{
	if (Strcmp(lhs.Str, rhs.Str) >= 0)
	{
		return true;
	}
	return false;
}

/*friend operator char* >= String*/
bool operator >=(const char *str, const String &rhs)
{
	if (Strcmp(str, rhs.Str) >= 0)
	{
		return true;
	}
	return false;
}

/*无参构造*/
String::String()
{
	Str = new char('\0');
	str_len = 0;
	Capacity = str_len;
}

/*由length个ch组成的串 构造*/
String::String(size_type length, char ch)
{
	str_len = length;
	Capacity = str_len;
	Str = new char[Capacity + 1];
	int i;
	for ( i = 0; i < str_len; ++i)
	{
		Str[i] = ch;
	}
	Str[i] = '\0';
}

/*由const char* str 构造*/
String::String(const char *str)
{
	str_len = Strlen(str);
	Capacity = str_len;
	Str = new char[Capacity + 1];
	Strcpy(Str, str);
}

/*由const char* str 前面length个元素 构造*/
String::String(const char *str, size_type length)
{
	str_len = length;
	Capacity = str_len;
	Str = new char[Capacity + 1];
	int i;
	for (i = 0; i < str_len; ++i)
	{
		Str[i] = str[i];
	}
	Str[i] = '\0';
}

/*由const char* str 从下标index开始的length个元素 构造*/
String::String(const char *str, size_type index, size_type length)
{
	if (length <= Strlen(str) - index)
	{
		str_len = length;
	}
	else
	{
		str_len = Strlen(str) - index;
	}

	Capacity = str_len;
	Str = new char[Capacity + 1];
	int i;
	for (i = 0; i < str_len; ++i)
	{
		Str[i] = str[index + i];
	}
	Str[i] = '\0';
}

/*由字符串中两个char *类型的指针 构造*/
String::String(const char* start, const char* end)
{
	str_len = Strlen(start) - Strlen(end);
	Capacity = str_len;
	Str = new char[Capacity + 1];
	int i = 0;
	while (start != end)
	{	
		Str[i] = *start;
		++i;
		++start;
	}
    Str[i] = '\0';
}


/*拷贝构造函数*/
String::String(const String &obj)
{
	str_len = obj.str_len;
	Capacity = str_len;
	Str = new char[Capacity + 1];
	Strcpy(Str, obj.Str);
}


/*析构函数*/
String::~String()
{
	delete Str;
	Str = NULL;
}

/*operator =*/
//用引用只能const String & 不能 String& eg:当s3 = s3+"123";时不匹配
String& String::operator =(const String &rhs)
{
	if (Capacity < rhs.str_len)
	{
		delete Str;
		str_len = rhs.str_len;
		Capacity = str_len;
		Str = new char[Capacity + 1];
	}
	else
	{
		str_len = rhs.str_len;
	}

	Strcpy(Str, rhs.Str);
	return *this;
}

/*operator +=*/
String& String::operator +=(const String &rhs)
{
	String tmp;
	tmp.str_len = str_len + rhs.str_len;
	tmp.Capacity = tmp.str_len;
	tmp.Str = new char[tmp.Capacity + 1];
	Strcpy(tmp.Str, Str);
	Strcat(tmp.Str, rhs.Str);
	*this = tmp;
	return *this;
}

/*operator []*/
char& String::operator [](size_type index)const    //const别忘了
{
    if (index > Capacity || 0 == str_len)
    {
    	throw exception2("out of range");
    }
	return *(Str + index); 					      //*号别忘了
}

/*append const String& obj*/
String& String::append(const String &obj)
{
	*this += obj;
	return *this;
}

/*append const char *str*/
String& String::append(const char *str)
{
	*this += str;
	return *this;
}

/*append const String &obj, size_type index, size_type len*/
String& String::append(const String &obj, size_type index, size_type len)
{
	String tmp(obj.Str, index, len);
	*this += tmp;
	return *this;
}

/*append const char *str, size_type num*/
String& String::append(const char *str, size_type num)
{
	String tmp(str, num);
	*this += tmp;
	return *this;
}

/*append size_type num, char ch*/
String& String::append(size_type num, char ch)
{
	String tmp(num, ch);
	*this += tmp;
	return *this;
}

/*append const char *start, const char *end*/
String& String::append(const char *start, const char *end)
{
	String tmp(start, end);
	*this += tmp;
	return *this;
}


/*assign const String &obj*/
String& String::assign(const String &obj)
{
	*this = obj;
	return *this;
}

/*assign const char *str*/
String& String::assign(const char *str)
{
	*this = str;
	return *this;
}

/*assign const char *str, size_type num*/
String& String::assign(const char *str, size_type num)
{
	String tmp(str, num);
	*this = tmp;
	return *this;
}

/*assign const String &obj, size_type index, size_type len*/
String& String::assign(const String &obj, size_type index, size_type len)
{
	String tmp(obj.Str, index, len);
	*this = tmp;
	return *this;
}

/*assign size_type num, char ch*/
String& String::assign(size_type num, char ch)
{
	String tmp(num, ch);
	*this = tmp;
	return *this;
}


/*at char&*/
char& String::at(size_type index)
{
    if (index > Capacity || 0 == str_len)
    {
    	throw exception2("out of range");
    }
	return *(Str + index); 
}

/*begin()函数返回一个迭代器,指向字符串的第一个元素.*/
char* String::begin()
{
	return Str;
}

/*end()函数返回一个迭代器，指向字符串的末尾(最后一个字符的下一个位置).*/
char* String::end()
{
	return Str + str_len + 1;
}

/*返回一个指向正规C字符串的指针, 内容与本字符串相同.const返回值只用在引用有效果*/
char* String::c_str()
{
	return Str;
}

/*函数返回字符元素个数*/
size_type String::size()
{
	return str_len;
}

/*函数返回在重新申请更多的空间前字符串可以容纳的字符数. 这个数字至少与 size()一样大.*/
size_type String::capacity()
{
	return Capacity;
}


/*compare()函数以多种方式比较本字符串和str,返回：int*/
int String::compare(const String &obj)
{
	return Strcmp(Str, obj.Str);
}

int String::compare(const char *str)
{
	return Strcmp(Str, str);
}

int String::compare(size_type index, size_type length, const String &obj)
{
	String tmp(Str, index, length);
	return Strcmp(tmp.Str, obj.Str);
}

int String::compare(size_type index, size_type length, const String &obj, size_type index2,size_type length2)
{
	String tmp1(Str, index, length);
	String tmp2(obj.Str, index2, length2);
	return Strcmp(tmp1.Str, tmp2.Str);
}

int String::compare(size_type index, size_type length, const char *str, size_type length2)
{
	String tmp1(Str, index, length);
	String tmp2(str, 0, length2);
	return Strcmp(tmp1.Str, tmp2.Str);
}


/*copy()函数拷贝自己的num个字符到str中（从索引index开始）。返回值是拷贝的字符数*/

size_type String::copy(char *str, size_type num, size_type index)
{
	if (num > str_len - index)
	{
		num = str_len - index;
	}

	char *curr = Str + index;
	int len = num;             //这后面不能改变num的值
	while (len--)
	{
		*str = *curr;
		++str;
		++curr;
	}
	return num;
}

/*data()函数返回指向自己的第一个字符的指针.*/
char *String::data()
{
	return Str;
}

/*如果字符串为空则empty()返回真(true)，否则返回假(false).*/
bool String::empty()
{
	if (0 == str_len)     //只要str_len==0就行,不考虑Capacity是否==0.
	{
		return true;
	}
	return false;
}

/*erase*/
char* String::erase(char *pos)
{
	char *curr = pos;
	while (curr+1 != end())
	{
		*curr = *(curr+1);
		 ++curr;
	}

	str_len -= 1;
	return pos;
}

char* String::erase(char *start,  char *end)
{
	char *curr = start; 
	while (end != String::end())
	{
		*curr = *end;
		++curr;
		++end;	
	}

	str_len -= end - curr;
	return start;
}

String& String::erase(size_type index, size_type num)//0 ,0
{
	if (-1 == num)
	{
		num = str_len - index;
	}	

	char *curr1 = Str + index;
	char *curr2 = Str + index + num;
	while (curr2 <= Str + str_len)
	{
		*(curr1++) = *(curr2++);
	}

	str_len -= curr2 - curr1;
	return *this;
}

/*find*/
size_type String::find(const String &obj, size_type index)
{
	if (NULL != Strstr(Str + index, obj.Str))
	{
		return Strstr(Str + index, obj.Str) - Str;
	}
	else 
	{
		return npos;
	}
}

size_type String::find(const char *str, size_type index)
{
	if (NULL != Strstr(Str + index, str))
	{
		return Strstr(Str + index, str) - Str;
	}
	else
	{
		return npos;
	}
}

size_type String::find(const char *str, size_type index, size_type length)
{
	String tmp(Str, 0, length);
	if (NULL != Strstr(tmp.Str + index, str))
	{
		return Strstr(tmp.Str + index, str) - tmp.Str;
	}
	else
	{
		return npos;
	}
}

size_type String::find(char ch, size_type index)
{	
	if (NULL != Strchr(Str + index, (int)ch))
	{
		return Strchr(Str + index, (int)ch) - Str;
	}
	else
	{
		return npos;
	}
}

/*length()函数返回字符串的长度. 这个数字应该和size()返回的数字相同.*/
size_type String::length()
{
	return str_len;
} 

/*max_size()函数返回字符串能保存的最大字符数。*/
size_type String::max_size()//错误,max_size - 当前对象string大小  = 剩余string大小
{
	return npos;  
} 

/*交换 swap*/
void String::swap(String &obj)
{
	String tmp(*this);    //String tmp = *this; //默认是浅层拷贝不是深度拷贝   可以重载拷贝构造
	*this = obj;
	obj = tmp;
}
/*用str中所有的替换本字符串中的num个字符,从index开始 */
String& String::replace(size_type index, size_type num, const String &obj)
{
	char *tmp = new char[str_len + obj.str_len - num + 1];
	int len = obj.str_len;
	char *curr1 = tmp;
	char *curr2 = Str;
	char *curr3 = obj.Str;
	
	while (index--)
	{
		*(curr1++) = *(curr2++);
	}

	while (len--)
	{
		*(curr1++) = *(curr3++);
	}

	curr2 += num;
	while (*curr2 != '\0')
	{
		*(curr1++) = *(curr2++);
	}

	*curr1 = '\0';
	*this = tmp;
	delete [] tmp;

	return *this;
}

/*用str中的num2个字符（从index2开始）替换本字符串中的字符，从index1开始，num1个字符*/
String& String::replace(size_type index1, size_type num1, const String &obj, size_type index2, size_type num2)
{
	String tmp(obj.Str, index2, num2);
	replace(index1, num1, tmp);
	return *this;
}

/*用str中所有字符替换本字符串中的num个字符（从index开始）的字符 */
String& String::replace(size_type index, size_type num, const char *str)
{
	char *tmp = new char[str_len + Strlen(str) - num + 1];
	int len = Strlen(str);
	char *curr1 = tmp;
	char *curr2 = Str;
	
	while (index--)
	{
		*(curr1++) = *(curr2++);
	}

	while (len--)
	{
		*(curr1++) = *(str++);
	}

	curr2 += num;
	while (*curr2 != '\0')
	{
		*(curr1++) = *(curr2++);
	}

	*curr1 = '\0';
	*this = tmp;
	delete [] tmp;

	return *this;
}

/*用str中的num2个字符（从0开始）替换本字符串中的字符，从index1开始，num1个字符 */
String& String::replace(size_type index, size_type num1, const char *str, size_type num2)
{
	String tmp(str, 0, num2);
	replace(index, num1, tmp);
	return *this;
}
/*用num2个ch字符替换本字符串中的字符，从index开始 */
String& String::replace(size_type index, size_type num1, size_type num2, char ch)
{
	String s1;
	s1.assign(num2, ch);
	this->replace(index, num1, s1);
	return *this;
}

// /*用str中的字符替换本字符串中的字符,迭代器start和end指示范围 */
// String& String::replace(char *start, char *end, const String &obj)
// {
// 	replace(0, end-start, start);
// 	return *this;//错
// }

// /*用num个ch字符替换本字符串中的内容，迭代器start和end指示范围.*/
// String& String::replace(char *start, char *end, const char *str)
// {
// 	return *this;//错
// }

// /*用str中的num个字符替换本字符串中的内容,迭代器start和end指示范围，*/
// String& String::replace(char *start, char *end, const char *str, size_type num)
// {
// 	replace(0, end-start, start);
// 	return *this;//错
// }

// /*用num个ch字符替换本字符串中的内容，迭代器start和end指示范围.*/
// String& String::replace(char *start, char *end, size_type num, char ch)
// {
// 	return *this;//错
// }


/*rfind()函数*/
/*返回最后一个与obj中的某个字符匹配的字符的首下标，从0-index开始查找。如果没找到就返回string::npos */
size_type String::rfind(const String &obj, size_type index)
{
	String tmp(Str, 0, index);
	if ((index = (Strrstr(tmp.Str, obj.Str) - tmp.Str)) >= 0 )
	{
		return index;
	}
	else
	{
		return npos;
	}
}
/*返回最后一个与str中的某个字符匹配的字符的首下标，从0-index开始查找。如果没找到就返回string::npos*/
size_type String::rfind(const char *str, size_type index)
{
	if (npos == index)
	{
		index = str_len;
	}

	String tmp(Str, 0, index);
	if ((index = (Strrstr(tmp.Str, str) - tmp.Str)) >= 0 )
	{
		return index;
	}
	else
	{
		return npos;
	}	
}
/*返回最后一个与str中的某个字符匹配的字符，从0-index开始查找,最多查找num个字符。如果没找到就返回string::npos */
size_type String::rfind(const char *str, size_type index, size_type num)
{
	if (npos == index)
	{
		index = str_len;
	}

	String tmp(Str, index - num, index);
	if ((index = (Strrstr(tmp.Str, str) - tmp.Str)) >= 0 )
	{
		return index;
	}
	else
	{
		return npos;
	}
}

/*返回最后一个与ch匹配的字符，从0-index开始查找。如果没找到就返回string::npos*/ 
size_type String::rfind(char ch, size_type index)
{
	if (npos == index)
	{
		index = str_len;
	}

	String tmp(Str, 0, index);
	if ((index = (Strrchr(tmp.Str, (int)ch) - tmp.Str)) >= 0)
	{
		return index;
	}
	else
	{
		return npos;
	}
}


/*substr()返回本字符串的一个子串，从index开始，长num个字符。如果没有指定，
将是默认值 string::npos。这样，substr()函数将简单的返回从index开始的剩余的字符串。*/
String String::substr(size_type index, size_type num) const  //****前面在类内部声明了默认，类外定义时就不用了
{
	if (npos == num)
	{
		num = str_len - index;
	}

	String tmp(Str, index, num);
	return tmp;
}


/*插入insert*/
/*在迭代器i表示的位置前面插入一个字符ch, */
char* String::insert(char *i, const char &ch)
{
	char *tmp = new char[str_len + 2];
	int len = 0;
	char *curr1 = tmp;
	char *curr2 = Str;
	
	while (curr2 != i)
	{
		++len;
		*(curr1++) = *(curr2++);
	}

	*(curr1++) = ch;

	while (*curr2 != '\0')
	{
		*(curr1++) = *(curr2++);
	}

	*curr1 = '\0';
	*this = tmp;
	delete [] tmp;

	return begin()+len;
}

/*在字符串的位置index插入字符串str, */
String& String::insert(size_type index, const String &obj)
{
	char *tmp = new char[str_len + obj.str_len + 1];
	int len = obj.str_len;
	char *curr1 = tmp;
	char *curr2 = Str;
	char *curr3 = obj.Str;
	
	while (index--)
	{
		*(curr1++) = *(curr2++);
	}

	while (len--)
	{
		*(curr1++) = *(curr3++);
	}

	while (*curr2 != '\0')
	{
		*(curr1++) = *(curr2++);
	}

	*curr1 = '\0';
	*this = tmp;
	delete [] tmp;

	return *this;
}

/*在字符串的位置index插入字符串str, */
String& String::insert(size_type index, const char *str)
{
	char *tmp = new char[str_len + Strlen(str) + 1];
	int len = Strlen(str);
	char *curr1 = tmp;
	char *curr2 = Str;
	
	while (index--)
	{
		*(curr1++) = *(curr2++);
	}

	while (len--)
	{
		*(curr1++) = *(str++);
	}

	while (*curr2 != '\0')
	{
		*(curr1++) = *(curr2++);
	}

	*curr1 = '\0';
	*this = tmp;
	delete [] tmp;

	return *this;
}

/*在字符串的位置index1插入字符串obj的子串(从index2开始，长num个字符), */
String& String::insert(size_type index1, const String &obj, size_type index2, size_type num)
{
	String tmp = obj.substr(index2, num);   //obj为常对象，只能调用常成员函数
	return (*this).insert(index1, tmp);         
}

/*在字符串的位置index插入字符串str的num个字符, */
String& String::insert(size_type index, const char *str, size_type num)
{
	char *tmp = new char[num + 1];
	Strncpy(tmp, str, num);
	(*this).insert(index, tmp);
	delete [] tmp;
	return *this;
}

/*在字符串的位置index插入num个字符ch的拷贝 */
String& String::insert(size_type index, size_type num, char ch)
{
	String s1;
	s1.assign(*this);
		delete Str;
   	str_len += num;
   	Str = new char[str_len+1];
   	char *curr = Str;
   	int i = 0;
   	while (index--)
   	{
   		*curr = s1[i];
   		curr++;
   		i++;
   	}

   	while (num--)
   	{
   		*curr = ch;
   		curr++;   		
   	}

   	while (s1[i] != '\0')
   	{
   		*curr = s1[i];
   		curr++;
   		i++;
   	}
   	*curr = '\0';
   	return *this;		
}

///* 在迭代器i表示的位置前面插入num个字符ch的拷贝 */
// void String::insert(char *i, size_type num, const char &ch)

///*在迭代器i表示的位置前面插入一段字符，从start开始，以end结束.*/
// void String::insert(char *i, char *start, char *end)


/*find_first_of************/
/*查找在字符串中第一个与str中的某个字符匹配的字符，返回它的位置。搜索从index开始，如果没找到就返回npos*/
int String::find_first_of(const String &str, int index)
{
	int i,j;
	for (j = index; j < str_len; j++)
	{
		for (i = 0; i < str.str_len; i++)
		{
			if (Str[j] == str[i])
			{
				return j;
			}
		}
	}
	return npos;
}
int String::find_first_of( const char *str, int index )
{
	int i,j;
	for (j = index; j < str_len; j++)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_first_of( const char *str, int index, int num )
{
	int i,j;
	for (j = index; j < index+num; j++)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_first_of( char ch, int index )
{
	int i;
	for (i = index; i < str_len; i++)
	{
		if (Str[i] == ch)
		{
			return i;
		}
	}
	return -1;
}

/*find_first_not_of*/
int String::find_first_not_of( const String &str, int index )
{
	int i,j;
	for (j = index; j < str_len; j++)
	{
		for (i = 0; i < str.str_len; i++)
		{
			if (Str[j] == str[i])
			{
				break;
			}
			if (i == str.str_len)
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_first_not_of( const char *str, int index )
{
	int i,j;
	for (j = index; j < str_len; j++)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				break;
			}
			if (i == Strlen(str))
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_first_not_of( const char *str, int index, int num )
{
	int i,j;
	for (j = index; j < index+num; j++)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				break;
			}
			if (i == Strlen(str))
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_first_not_of( char ch, int index )
{
	int i;
	for (i = index; i < str_len; i++)
	{
		if (Str[i] != ch)
		{
			return i;
		}
	}
	return -1;
}


/*find_last_of*/
int String::find_last_of( const String &str, int index)
{
	int i, j;
	if (index == -1)
	{
		index = str_len;
	}
	for (j = str_len-1; j >= index; j--)
	{
		for (i = 0; i < str.str_len; i++)
		{
			if (Str[j] == str[i])
			{
				return j;
			}
		}
	}
	return -1;	
}
int String::find_last_of( const char *str, int index )
{
	int i,j;
	if (index == -1)
	{
		index = str_len;
	}

	for (j = str_len-1; j >= index; j--)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				return j;
			}
		}
	}
	return -1;	
}
int String::find_last_of( const char *str, int index, int num )
{
	int i,j;
	for (j = index+num-1; j >= index; j--)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_last_of( char ch, int index )
{
	int i;
	if (index == -1)
	{
		index = str_len;
	}

	for (i = str_len-1; i >= index; i--)
	{
		if (Str[i] == ch)
		{
			return i;
		}
	}
	return -1;
}


/*find_last_not_of*/
int String::find_last_not_of( const String &str, int index )
{
	int i,j;
	if (index == -1)
	{
		index = str_len;
	}

	for (j = str_len-1; j >= index; j--)
	{
		for (i = 0; i < str.str_len; i++)
		{
			if (Str[j] == str[i])
			{
				break;
			}
			if (i == str.str_len)
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_last_not_of( const char *str, int index)
{
	int i,j;
	if (index == -1)
	{
		index = str_len;
	}

	for (j = str_len-1; j >= index; j--)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				break;
			}
			if (i == Strlen(str))
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_last_not_of( const char *str, int index, int num )
{
	int i,j;
	for (j = index+num-1; j >= index; j--)
	{
		for (i = 0; i < Strlen(str); i++)
		{
			if (Str[j] == str[i])
			{
				break;
			}
			if (i == Strlen(str))
			{
				return j;
			}
		}
	}
	return -1;
}
int String::find_last_not_of( char ch, int index )
{
	int i;
	if (index == -1)
	{
		index = str_len;
	}

	for (i = str_len-1; i >= index; i--)
	{
		if (Str[i] != ch)
		{
			return i;
		}
	}
	return -1;
}

#endif
