/*定义函数: void *memccpy(void *dest, const void *src, int ch, size_t n);
函数说明: memccpy()用来拷贝src所指的内存内容前n个字节到dest所指的地址上。与memcpy()不同的是,memccpy()如果在src中遇到某个特定值(int c)立即停止下一个复制。
返回值:   返回指向dest中值为c的下一个字节指针。返回值为0表示在src所指内存前n个字节中没有值为c的字节。*/
// eg:dest="abcdefg" src=""
#include <stdio.h>
#include <string.h>
void *memccopy(void *dest, const void *src, int ch,size_t n)
{
	if(NULL == dest || NULL == src)
	{
		return NULL;
	}

	while(n--)
	{	
		*(char *)dest=*(char *)src;
		dest= (char *)dest+1;
		if(*(char *)src==(char)ch)
		{   
			return (char *)dest;
		}
		src = (char *)src + 1;
	}
	return NULL;
}
//细节补充:1.参数为 void *dest, const void *src, int ch,size_t n 其中ch为int类型 
//         2.首先判断 dest 和 src 是不是NULL 如果为 NULL结束
//         3.返回值为NULL,在n中没找到值为c的字符。
//         4.找到了c的话返回值为c的下一个地址
//         5.当n越界超过src大小不用担心。一定会有'\0'的


int main(int argc, char const *argv[])
{
	char a[1000]="ABCDABCD",b[]="EFGH";
	char c[1000]="ABCDABCD";

	// memccopy(a,b,79,4);
	// memccpy(c,b,79,4);

	printf("%s\n",memccopy(a,b,71,4));
	printf("%s\n",memccpy(c,b,71,4));

    printf("%s\n",a);
	
	printf("%s\n",c);
	return 0;
}