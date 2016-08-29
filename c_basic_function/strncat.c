#include <stdio.h>
#include <string.h>
char *strncatt(char *dest,const char *src,int n)//功能把s的前n个字符从d的'\0'
{								//字符开始连接d的大小要存的下d+n,并返回d。
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
int main(int argc, char const *argv[])
{
	char a[1000]="ABCDEF",b[]="EFGH";//a必须足够容纳d+n字符串。
	strncatt(a,b,2);
	printf("%s\n",a);
	return 0;
}							   