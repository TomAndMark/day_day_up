/*

   Finds the last occurrence of ch in string.  The terminating null character is used as part of the search.

   查找在字符串中最后一次出现字符’ch’的位置。如果str中存在字符ch，返回出现ch的位置的指针；否则返回NULL。

*/

#include <stdio.h>
#include <string.h>
char *strrchrr(const char *str,int ch)
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
int main(int argc, char const *argv[])
{
   char a[]="ABCDABCDAAA",b[]="EFGH";
   char *c=strrchrr(a,67);
   printf("%s\n",c);
   char *d=strrchr(a,67);
   printf("%s\n",d);
   return 0;
}