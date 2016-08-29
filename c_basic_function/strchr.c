#include <stdio.h>
#include <string.h>
/*
   Searches a string for a given character, which may be the null character '\0'.
   查找字符串string中首次出现字符ch的位置。如果string中存在字符ch，返回首次出现ch的位置的指针；否则返回NULL。
*/
char * strchrr(const char *str, int ch)
{
   while (*str && *str!=(char)ch)
      {
         str++;
      }
   if (*str==(char)ch)
      {
         return (char *)str;
      }
   return NULL;
}
int main(int argc, char const *argv[])
{
   char a[]="ABCD",b[]="EFGH";
   char *c=strchrr(a,67);
   printf("%s\n",c);
   return 0;
}