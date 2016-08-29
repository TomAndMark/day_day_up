#include <stdio.h>
#include <string.h>
char *strncopy(char *d,char *s,int n)//把s所指向的字符串中以s地址开始的前n个
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

int main(int argc, char const *argv[])
{
	char a[1000]="ABCDEF",b[]="EFGH";//a必须足够容纳n个字符串。
	// strncopy(a,b,2);
	// printf("%s\n",a);
	strncpy(a,b,2);
	printf("%s\n",a);
	return 0;
}		