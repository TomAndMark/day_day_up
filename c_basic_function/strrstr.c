#include <stdio.h>
#include <string.h>
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