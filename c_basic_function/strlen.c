#include <stdio.h>
int strlength(char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		i++;
	}
	return i;
}
int main(int argc, char const *argv[])
{
	char a[]="ABCD",b[]="EFGH";
	printf("%d\n",strlength(a));
	return 0;
}