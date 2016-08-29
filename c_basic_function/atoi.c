#include <stdio.h>
#include <string.h>
int atoii(char *str) 
{
    int intVal = 0;              // 返回值
    int sign = 1;                // 符号, 正数为 1, 负数为 -1
    if(str == 0) 
        return NULL;      // 判断指针是否为空 str == NULL
    while(' '== *str)
        str++;   // 跳过前面的空格字符 ' ' 的 ascii 值 0x20
    if('-'==*str) 
        sign = -1;    // 判断正负号
    if('-'==*str || '+'==*str)
        str++;// 如果是符号, 指针后移
    while(*str >= '0' && *str <= '9') 
    {// 逐字符转换成整数
        // 转换说明
        // ascii 的 '0' = 0x30 转换为int以后 - 0x30即为整型的0
        // ascii 的 '1' = 0x31 转换为int以后 - 0x30即为整型的1
        // ...
        intVal = intVal * 10 + (((int)*str)-0x30);// 十进制即每位乘10, 结果累加保存
        str++;// 指针后移
    }
    return intVal*sign;// 返回结果,int32 范围是: 2147483647 ~ -2147483648, 此处会进行溢出运算
}
int main(int argc, char const *argv[])
{
    char a[1000]="321 321";
    printf("%d\n",atoii(a));
    printf("%d\n",atoi(a));
    return 0;
}               