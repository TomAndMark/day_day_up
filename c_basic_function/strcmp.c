#include <stdio.h>
int strcompare(const char *str1,const char *str2)
{
	while(*str1==*str2 && *str1)
	{
		str1++;
		str2++;
	}
	return (*str1-*str2);
}
int main(int argc, char const *argv[])
{
	char a[1000]="ABCD",b[]="EFGdH";
	char c[]="EFGHI";
	int n=strcompare(c,b);
	printf("%d\n",n);
	int i=strcmp(c,b);
	printf("%d\n",i);
	return 0;
}