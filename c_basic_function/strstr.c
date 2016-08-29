
/*功能: 找出s2字符串在s1字符串中第一次出现的位置（不包括s2的串结束符）
返回结果:返回该位置的指针，如找不到，返回空指针。*/
#include <stdio.h>
#include <string.h>
char *strstrr(const char *str1,const char *str2)
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
int main(int argc, char const *argv[])
{
   char a[]="ABCDABCD",b[]="CD";
   char *c=strstrr(a,b);
   printf("%s\n",c);
   char *d=strstr(a,b);
   printf("%s\n",d);
   return 0;
}