#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	char *data;
	long a, b;
	printf("Content-Type:text/html;charset=gb2312\r\n");
	printf("\r\n");
	printf("<html>\r\n");
	printf("<head>\r\n");
	printf("<TITLE> 乘法结果 </TITLE>\r\n");
	printf("</head>\r\n");
	printf("<body><br>\r\n");
	printf("<H1>mult result</H1>\r\n");
	data = getenv("QUERY_STRING");

	if(data == NULL)
		printf("<P>错误！数据没有被输入或者数据传输有问题\r\n");
	else
	{
		if(sscanf(data,"a=%ld&b=%ld",&a, &b)!=2)
			printf("<P>错误！输入数据非法。表单中输入的必须是数字。</P>\r\n");
		else
			printf("<P>%ld x %ld = %ld </P>\r\n", a, b, a*b);
	}
	printf("<a href=\"http://192.168.10.2:6789/CGI.html\" target=\"_blank\">return mult</a>\r\n");
	printf("</body>\r\n");
	printf("</html>\r\n");

	return 0;
}
