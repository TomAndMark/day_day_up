#include <stdio.h>
#include <string.h>
int strncompare(char *str1,char *str2,int n)
{
	while(--n && *str1 && *str1==*str2)//确保str1、str2不同时为0
	{//注意在--n 不是n--  第n个只需判定前面n-1个第n个为0必须有结果。
		str1++;
		str2++;
	}
	return (*str1-*str2);
}
int main(int argc, char const *argv[])
{
	char a[1000]="ABCD",b[]="EFGdH";
	char c[]="EFGHI";
	int n=strncompare(c,b,4);
	printf("%d\n",n);
	int i=strncmp(c,b,4);
	printf("%d\n",i);
	return 0;
}