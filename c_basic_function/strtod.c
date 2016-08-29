#include <stdio.h>
#include <string.h>
//"12345.6789"   --> 12345.6789
//double strtod(const char *nptr, char **endptr);
double strtod(const char *str)
{   
	int s=0;
    int d=1;
    int f=1;//标记标量 1:小数点之前 0:小数点之后
    char *p=(char *)str;
    while(*p)
    {
       	if(*p=='.')
        {
        	p++;
         	f=0;
         	continue;
        }
        s=s*10+*p-'0';
        if(f==0)
        {
        	d=d*10;
        }        
       	p++;
    }
    return (double)s/d;
}
int main(int argc, char const *argv[])
{
	char a[]="12345.6789";
	printf("%lf\n",strtod(a));
	return 0;
}