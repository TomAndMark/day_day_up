#include <stdio.h>//143行
#include <string.h>
/*原型：char * strtok(char * s,const char * ct)
用途：在s中找出以ct中的字符为分隔的字符串，即是源串中除去了含有分隔串中的
所有字符后余下的一段段的字符串，每调用一次找到一串，找不到则返回空串。
第一次调用必须传给它有效的字符串，
第二次传NULL就可以了，每次调用返回找到的子串的时候都会把源串中
该子串的尾部字符（原来是搜索串中的某一字符）
修改成'/0'字符返回值为每次调用得到的字串。
下面看一下它的使用*/
//strtok  查找由指定的分界符分隔开的单词
	//abc,erer,123
	// char ch[20];
	// //char splitchar=',';
	// char splitchar=' ';
	// gets(ch);
char * strtok(char *str,const char ch)
{
	char *p=NULL;
	int i=0;
	while()
	{
	
	}

}

	// char *p=NULL;
	// int i=0;
	// while(1)
	// {
	//   if(p==NULL)
	//   {
	//   	 p=&ch[i];
	//   }	 
 //      if(ch[i]!=splitchar)
 //      {
 //      	if(ch[i]=='\0')
 //      	{
 //      		printf("%s\n",p);
 //      		break;
 //      	}      		
 //      	i++;
 //      }
 //      else
 //      {
 //      	ch[i]='\0';
 //      	printf("%s\n",p);
 //      	p=NULL;
 //      	i++;
 //      }      
	// }   