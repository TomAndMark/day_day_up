#include <stdio.h>
#include <string.h>
void bzeroo(void *s,int n)//置字节字符串s的前n个字节为零。
{
	char *c=s;//注意这是char型，若s是其他类型指针，注意char值指向一个字节
	int i=0;
	while(i<n)
	{
		*c='\0';
		c++;
		i++;
	}
}

//细节补充:1.参数是void* 和 int .
//         2.在内部,需要把void* 强制转换为char *
//         3.while中 *tmp = '\0'

int main(int argc, char const *argv[])
{
	char a[1000]="ABCD";//n小于等于sizeof（a）
	bzeroo(a,4);
	printf("%d\n",b[0]);
	printf("%d\n",b[1]);
	printf("%d\n",b[2]);
	printf("%d\n",b[3]);
	return 0;
}