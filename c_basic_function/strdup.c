#include <stdio.h>
#include <string.h>
#include <malloc.h>
char *strdupp (const char *src)
{
 	size_t len=strlen(src)+1;
 	void *new =malloc(len);
 	if (new == NULL)
    	return NULL;
 	return (char *) memcpy (new, src, len);
}
int main(int argc, char const *argv[])
{
	char a[]="ABCD",b[]="EFGH";
	char *c=strdupp(a);
	printf("%s\n",strdupp(a));
    free(c);
	return 0;
}