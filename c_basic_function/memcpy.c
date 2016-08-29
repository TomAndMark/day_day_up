/*定义函数: void *memcpy(void *dest, const void *src, size_t n)
函数说明: memcpy()用来拷贝src所指的内存内容前n个字节到dest所指的内存地址上。与strcpy()不同的是,memcpy()会完整的复制n个字节,不会因为遇到字符串结束'\0'而结束
返回值:   返回指向dest的指针*/
#include <stdio.h>
#include <string.h>
void *memcopy(void *dest, const void *src, size_t n)
{
	if(NULL == dest || NULL == src)
	{
		return NULL;
	}
	
	void *ret = dest;

	while(n--)
	{
		*(char *)dest = *(char *)src; //复制内存  相当于复制 *(char *)
		dest = (char *)dest + 1;
		src = (char *)src + 1;
	}

	return ret;
}

//细节总结:1.参数为void *dest, const void *src, size_t n
//		   2.首先判断 dest 和 src 是不是NULL 如果为 NULL结束
//         3.while (--n)...
//		   4.可能会出现越界问题,等段错误问题

int main(int argc, char const *argv[])
{
	char a[1000]="ABCD",b[]="EFGH";
	char c[1000]="ABCD";
	memcopy(a,b,2);
	printf("%s\n",a);
	memcpy(c,b,2);
	printf("%s\n",c);
	return 0;
}
