#include <stdio.h>
#include <string.h>
char *strcatt(char *dest,const	char *src)//实现把字符串s连接在字符串d后面，返回d
{                       //d的大小必须足够容纳d字符串和s字符串。
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
int main(int argc, char const *argv[])
{
	char a[20]="ABCD",b[]="EFGH";//a必须足够容纳a字符串和b字符串。
	char c[]="EFGH";
	strcat(a,b);
	printf("%s\n",a);
	return 0;
}