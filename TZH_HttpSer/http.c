#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>   //htons
#include <netinet/in.h>  //inet_addr
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SERVER_STRING "Server: TZH_Service"

//设置socket 地址 可重复绑定
void  setaddreuse(int socketfd)
{
    int  isreuse = 1;
    setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR,&isreuse,sizeof(isreuse));
}

/*线程handle函数  处理套接字上监听到的一个HTTP 请求*/
void accept_request(int clientfd);

/*处理请求信息 主要体现服务器处理请求流程。*/
void request_message(int clientfd, char *input);

/*回应正确报文*/
void response_message(int clientfd, const char *content, const char *content_type, int file_size); //回应报文




/*返回给浏览器表明收到的 HTTP 请求所用的 method不被支持。*/
void unimplemented(int clientfd);     

/*主要处理找不到请求的文件时的情况。*/
void file_not_found(int clientfd);

/*返回给客户端这是个错误请求，HTTP 状态吗 400 BAD REQUEST. */
void error_request(int clientfd);





//返回给浏览器表明收到的 HTTP 请求所用的 method不被支持。HTTP 状态码 501 Method Not Implemented.
void unimplemented(int clientfd)
{
	char err_message[4096] = {0};
	char *initial_line = "HTTP/1.1 501 Method Not Implemented\r\n";
	char *Content_Type = "Content-Type: text/html\r\n";
	char *br = "\r\n";
	char *html = "<html>\r\n<head>\r\n<title>Method Not Implemented</title>\r\n</head>\r\n\
<body>\r\n<h1>Error: 501</h1>\r\n<p>HTTP request method not supported.</p>\r\n</body>\r\n</html>\r\n";
	
	snprintf(err_message, sizeof(err_message), "%s%s%s%s%s", initial_line, 
	 	SERVER_STRING, Content_Type, br, html);
	send(clientfd, err_message, strlen(err_message), 0);
	close(clientfd);
}


//主要处理找不到请求的文件时的情况 HTTP 状态吗 404 NOT FOUND.
void file_not_found(int clientfd)
{
	char err_message[4096] = {0};
	char *initial_line = "HTTP/1.1 404 NOT FOUND\r\n";
	char *Content_Type = "Content-Type: text/html\r\n";
	char *br = "\r\n";
	char *html = "<html>\r\n<head>\r\n<title>Not Found</title>\r\n</head>\r\n\
<body>\r\n<h1>Error: 404</h1>\r\n<p>The server could not fulfill.</p>\r\n\
<hr />\r\n<p>the resource specified is unavailable or nonexistent.</p>\r\n</body>\r\n</html>\r\n";
	
	snprintf(err_message, sizeof(err_message), "%s%s%s%s%s", initial_line, 
	 	SERVER_STRING, Content_Type, br, html);
	send(clientfd, err_message, strlen(err_message), 0);	
	close(clientfd);
}


//返回给客户端这是个错误请求，HTTP 状态吗 400 BAD REQUEST.
void error_request(int clientfd)
{
	char err_message[4096] = {0};
	char *initial_line = "HTTP/1.1 400 BAD REQUEST\r\n";
	char *Content_Type = "Content-Type: text/html\r\n";
	char *br = "\r\n";
	char *html = "<html>\r\n<head>\r\n<title>BAD REQUEST</title>\r\n</head>\r\n\
<body>\r\n<h1>Error: 400</h1>\r\n<p>Your browser sent a bad request.</p>\r\n\
<hr />\r\n<p>such as a POST without a Content-Length.</p>\r\n</body>\r\n</html>\r\n";
	
	snprintf(err_message, sizeof(err_message), "%s%s%s%s%s", initial_line, 
	 	SERVER_STRING, Content_Type, br, html);
	send(clientfd, err_message, strlen(err_message), 0);
	close(clientfd);
}


//cannot_execute_CGI 
void cannot_execute_CGI(int clientfd)
{
    char err_message[4096] = {0};

    /* 回应客户端 cgi 无法执行*/
	char *initial_line = "HTTP/1.1 500 Internal Server Error\r\n";
	char *Content_Type = "Content-Type: text/html\r\n";
	char *br = "\r\n";
	char *html = "<html>\r\n<head>\r\n<title>BAD CGI</title>\r\n</head>\r\n\
<body>\r\n<h1>Error: 500</h1>\r\n<p>Internal Server Error.</p>\r\n\
<hr />\r\n</body>\r\n</html>\r\n";

    snprintf(err_message, sizeof(err_message), "%s%s%s%s%s", initial_line, 
	 	SERVER_STRING, Content_Type, br, html);
	send(clientfd, err_message, strlen(err_message), 0);
    close(clientfd);
}


void execute_cgi(int clientfd, char *method, char *query_string, char *path)
{
	printf("path1::%s\n", path);
	printf("query_string::%s\n", query_string);
    char buf[1024];
    int CGI_output[2];
    int CGI_input[2];
    pid_t pid;
    strcpy(buf, "HTTP/1.1 200 OK\r\n");  
    send(clientfd, buf, strlen(buf), 0);

    //创建管道  
    if(pipe(CGI_output) < 0)
    {
        cannot_execute_CGI(clientfd);
        return;
    }
    // if(pipe(CGI_input) < 0)
    // {
    //     cannot_execute_CGI(clientfd);
    //     return;
    // }
    if((pid = fork()) < 0)
    {
       cannot_execute_CGI(clientfd);
        return;
    }
    
    if(pid == 0)
    {
        char method_env[30];
        char query_string_env[30];

        // 把 STDOUT 重定向到 cgi_output 的写入端 
        dup2(CGI_output[1],1);

        //把 STDIN 重定向到 cgi_input 的读取端
        //dup2(CGI_input[0],0);

        //关闭 cgi_input 的写入端 和 cgi_output 的读取端
        close(CGI_output[0]);
        //close(CGI_input[1]);

        //设置 request_method 的环境变量
        sprintf(method_env,"REQUEST_METHOD=%s",method);
        putenv(method_env);

        //设置 query_string 的环境变量
        sprintf(query_string_env, "QUERY_STRING=%s", query_string);
        putenv(query_string_env);

        //用 execl 运行 cgi 程序
        execl(path, path, NULL);
        exit(0);
    }
    if(pid > 0)
    {
        //关闭 cgi_input 的读取端 和 cgi_output 的写入端
        close(CGI_output[1]);
        //close(CGI_input[0]);
        
        //读取 cgi_output 的管道输出到客户端，该管道输入是 STDOUT
        bzero(buf,sizeof(buf));
        if(read(CGI_output[0],buf,sizeof(buf)-1) > 0)
        {
           printf("read::%s\n", buf);
           send(clientfd,buf,strlen(buf),0);
        }

        //关闭管道
        //close(CGI_input[1]);
        close(CGI_output[0]);

        //等待子进程结束
        wait(NULL);
    }

}

//回应正确报文
void response_message(int clientfd, const char *content, const char *content_type, int file_size)  
{  
    char header[1024];   

    /*正常的 HTTP header */  
    snprintf(header, sizeof(header), "HTTP/1.1 200 OK\r\n%sContent-Type: %s\r\n\
Content-Length: %d\r\n\r\n", SERVER_STRING, content_type, file_size);

    ///发送header
    send(clientfd, header, strlen(header), 0);

    ///发送content
    send(clientfd, content, file_size, 0);
}  


//处理请求信息
void request_message(int clientfd, char *input)
{
	char method[32] = {0};   
	char url[64] = {0};
	char versions[64] = {0};
	char content_type[128] = {0};
	char *query_string = NULL;
	char file[64] = {0};
	char path[64] = {0};

	//分别读取请求报文的每一部分 请求类型 请求文件 版本号 及文件类型
	sscanf(input, "%[^ ]%*[^/]/%[^ ]%*c%[^\r]\r\n%*[^\n]\n%*[^\n]\nAccept: %[^\r]", method, url, versions, content_type);
	printf("method::%s\n",method);
	printf("url::%s\n",url);
	printf("versions::%s\n",versions);
	printf("content_type::%s\n",content_type);


	if (strcmp(method, "GET"))
	{	
		unimplemented(clientfd);
		return ;
	}

	int i, j;
	query_string = url;
	while (*query_string != '?' && *query_string != '\r' && *query_string != '\n' && *query_string != '\0')
	{
		++query_string;
	}

	if (*query_string == '?')
	{
		*query_string = '\0';
		++query_string;

		//说明是CGI文件
		sprintf(path, "CGI/%s", url);

		execute_cgi(clientfd, method, query_string, path);
	}
	else
	{
		sprintf(file, "%s", url);
		struct stat st;
		int ret = stat(file, &st);
		if (-1 == ret)
		{
			file_not_found(clientfd);
			return ;
		}

		int file_size = st.st_size;
		if (file_size < 0)
		{
			error_request(clientfd);
			return ;
		}

		int fd = open(file, O_RDONLY);
		if (-1 == fd)
		{
			perror("open file failed:");
			return ;
		}

		char *content = (char *)malloc(file_size + 1);

		ret = read(fd, content, file_size);
		if (ret < 0)
		{
			perror("read failed:");
			return ;
		}

		response_message(clientfd, content, content_type, file_size);

		free(content);  
		close(fd); 
	}

    close(clientfd);
}


//线程handle函数  处理套接字上监听到的一个HTTP 请求
void accept_request(int clientfd)
{
	int recv_bytes;
	char buf[1024] = {0};
	if ((recv_bytes = recv(clientfd, buf, sizeof(buf)-1, 0)) == -1)
	{
		perror("recv request failed:");
		exit(-1);
	}

	printf("recv_bytes=%d\n", recv_bytes);
	printf("recv=%s\n", buf);

	//处理请求信息
	request_message(clientfd, buf);
}


int main(int argc, char const *argv[])
{
	int serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == serverfd)
	{
		perror("create serverfd failed:");
		exit(-1);
	}

	struct sockaddr_in seraddr;
	bzero(&seraddr, sizeof(seraddr));

	//服务器地址
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(6789);
	seraddr.sin_addr.s_addr = inet_addr("192.168.10.2");

	//绑定服务
	setaddreuse(serverfd);

	int ret = bind(serverfd, (struct sockaddr*)&seraddr, sizeof(struct sockaddr));
	if (-1 == ret)
	{
		perror("bind failed:");
		exit(-1);
	}

	//开始监听
	ret = listen(serverfd, 10);
	if (-1 == ret)
	{
		perror("listen failed:");
		exit(-1);
	}

	pthread_t pthread;
	struct sockaddr_in cliaddr;
	int addrlen = sizeof(struct sockaddr);

	while (1)
	{
		int clientfd = accept(serverfd, (struct sockaddr*)&cliaddr, &addrlen);
		if (clientfd < 0)
		{
			perror("accept clientfd failed:");
			exit(-1);
		}
		printf("IP:%s\tport:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		//产生线程 调用accept_request 函数处理新请求
		ret = pthread_create(&pthread, NULL, (void *)accept_request, (void*)clientfd);
		while (0 != ret)
		{
			ret = pthread_create(&pthread, NULL, (void *)accept_request, (void*)clientfd);
		}
	}

	return 0;
}
