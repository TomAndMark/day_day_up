#include <stdio.h>
char *strcopy(char *dest,const char *src)//把字符串s传入字符串d中。返回d
{
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
int main(int argc, char const *argv[])
{
	char a[]="ABCD",b[]="EFGH";
	strcopy(a,b);
	printf("%s\n",a);
	return 0;
}