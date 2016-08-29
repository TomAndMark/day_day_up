#ifndef  BASIC_FUNCTION
#define BASIC_FUNCTION

using namespace std;

char * Strchr(const char *str, int ch)
{
   while (*str && *str!=(char)ch)
   {
     str++;
   }
   if (*str==(char)ch)
   {
     return (char*)str;
   }
   return NULL;
}

char *Strstr(const char *str1,const char *str2) //查找第一个字符串
{
	int len=strlen(str2);
	if(!(len))
		return (char *)str1;
	while(*str1)    //*s1==*s2 && strncmp( s1, s2, len2 )==0  //增加效率*s1==*s2
	{
		if(*str1==*str2 && strncmp(str1,str2,len)==0)
		{
			return (char *)str1;
		}
		str1++;
	}
	return NULL;
}

char *Strrstr(const char *str1,const char *str2) //查找最后一个字符串
{
	int len = strlen(str2);
	if(!(len))
		return (char *)str1;
	int len1 = strlen(str1);
	const char *curr = str1 + len1 -1;
	while(len1-- && curr >= str1)    //*s1==*s2 && strncmp( s1, s2, len2 )==0  //增加效率*s1==*s2
	{
		if(*curr==*str2 && strncmp(curr,str2,len)==0)
		{
			return (char *)curr;
		}
		curr--;
	}
	return NULL;
}

void reverse(char *s, int from, int to)//已经是0--2
{
	char tmp;
	while (from < to)
	{
		tmp = s[to];
		s[to--] = s[from];
		s[from++] = tmp;
	}
}

void LestRotateStr(char *s, int m, int n)
{
	/*考虑左移大于n的情况*/
	m %= n;
	reverse(s, 0, n-1);
	reverse(s, 0, m-1);
	reverse(s, m, n-1);//注意是m->n-1
}

int Strlen(const char *str)//控制了str等于空的情况当访问str[i]，或*str是会报断错误;而且当dest为常字符时会报段错误
{
	int i=0;
	while(str[i]!='\0')
	{
		i++;
	}
	return i;
}

char *Strcpy(char *dest,const char *src)//把字符串s传入字符串d中。返回d
{//控制了str等于空的情况当访问str[i]，或*str是会报断错误;
	char *tmp=dest;
	while(*src!='\0')
	{
		*tmp = *src;
		tmp++;
		src++;
	}  
	*tmp='\0';
	return dest;
}

char* Strncpy(char *d, const char *s, int n)//把s所指向的字符串中以s地址开始的前n个
{                           //字节复制到d所指的数组首元素中（后面保留，并返回d。
	char *c = d;
	
	while (n-- && *s != '\0')
	{
		*(c++) = *(s++);
	}

	while (n--)
	{
		*(c++) = '\0';
	}

	return d;	
}

char *Strcat(char *dest,const char *src)//实现把字符串s连接在字符串d后面，返回d
{                       //d的大小必须足够容纳d字符串和s字符串。
	//控制了str等于空的情况当访问str[i]，或*str是会报断错误;而且当dest为常字符时会报段错误
	int len;
	len=strlen(dest);
	char *tmp=dest+len;
	while(*src!='\0')
	{
		*tmp=*src;
		tmp++;
		src++;
	}
	*tmp='\0';
	return dest;
}

char *Strncat(char *dest,const char *src,int n)//功能把s的前n个字符从d的'\0'
{							//字符开始连接d的大小要存的下d+n,并返回d。
	//控制了str等于空的情况当访问str[i]，或*str是会报断错误;而且当dest为常字符时会报段错误
	int len;
	len=strlen(dest);
	char *tmp=dest+len;
	while(n--)//需要判定（赋值）（自加）n次
	{
		*tmp=*src;
		tmp++;
		src++;
	}
	*tmp='\0';
	return dest;
}

int Strcmp(const char *str1,const char *str2)
{//控制了str等于空的情况当访问str[i]，或*str是会报断错误;而且当dest为常字符时会报段错误
	while(*str1==*str2 && *str1)
	{
		str1++;
		str2++;
	}
	return (*str1-*str2);
}

int Strncmp(char *str1,char *str2,int n)
{
	while(--n && *str1 && *str1==*str2)//确保str1、str2不同时为0
	{//注意在--n 不是n--  第n个只需判定前面n-1个第n个为0必须有结果。
		str1++;
		str2++;
	}
	return (*str1-*str2);
}

char *Strrchr(const char *str,int ch)//返回最后一个ch的位置
{
	char *p=(char *)str;
	while (*str)
	{
		str++;
	} 
	while(str--!=p && *str!=(char)ch)//str!=p判断str是否为NULL①一开始就为NULL
   	{                               //②一直没有找到ch
   		;//srt--;
   	}
   	if (*str == (char)ch)
		return (char *)str;
	return NULL;
}


#endif
