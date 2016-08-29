/*
   Force string to lower case。
   将字符串转换为大写。只改变字符串中出现的小写字母，不改变其他字符。
*/
#include <stdio.h>
#include <string.h>
char *strupr(char *str)
{
	char *tmp=str;
	while(*(tmp++)!='\0')
	{
		if(*tmp>='a' && *tmp<='z')
		{
			*tmp-=32;//32可以写成0x20
		}
	}
	return str;
}
int main(int argc, char const *argv[])
{
	char a[]="AaBbCcDd";
	printf("%s\n",strupr(a));
	return 0;
}