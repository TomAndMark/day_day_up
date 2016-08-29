#include <stdio.h>
#include <string.h>
void strreverse(char data[])
{
	int i;
	char tmp;//int tmp 也行没什么影响
	for(i=0;i<strlen(data)/2;i++)
	{
	  tmp=data[i];
      data[i]=data[strlen(data)-1-i];
      data[strlen(data)-1-i]=tmp;
	}
	printf("%s\n",data);
}
int main(int argc, char const *argv[])
{
	char a[]="abcdefg";
	strreverse(a);
	return 0;
}