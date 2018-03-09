#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>     /* defines STDIN_FILENO, system calls,etc */
#include <sys/types.h>  /* system data type definitions */
#include <sys/socket.h> /* socket specific definitions */
#include <netinet/in.h> /* INET constants and stuff */
#include <arpa/inet.h>  /* IP address conversion stuff */
#include <netdb.h>      /* gethostbyname */
 
#define  PORT 8000
#define  BACKLOG 1
#define  MAXDATASIZE 100
#define  MAXBUF 1024*1024

void getInfo(char *buf,int *port, char *IP);
 
int main(int argc, char *argv[])
{
    int  sockfd, num;
    char  buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server;

    int pasv_sd;
    int listensd, connectfd;
    struct sockaddr_in test;
    struct sockaddr_in pasv;
    struct sockaddr_in client;
    int connected = 0;

    if (argc!=2) 
    {
       printf("Usage:%s <IP Address>\n",argv[0]);
       exit(1);
    }
    if((he=gethostbyname(argv[1]))==NULL)
    {
        printf("gethostbyname()error\n");
        exit(1);
    }
    if((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
    {
       printf("socket()error\n");
       exit(1);
    }
    bzero(&server,sizeof(server));
    server.sin_family= AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr =*((struct in_addr *)he->h_addr);
    if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1)
    {
       printf("connect()error\n");
       exit(1);
    }
    if((num=recv(sockfd,buf,MAXDATASIZE,0)) == -1)
    {
       printf("recv() error\n");
       exit(1);
    }
    buf[num-1]='\0';
    printf("Server Message: %s\n",buf);

    char message[MAXDATASIZE];
    while(1)
    {
        fgets(message, MAXDATASIZE, stdin);
        size_t mes_len = strlen(message);
        if(message[0] == 'P' && message[1] == 'O' && message[2] == 'R' && message[3] == 'T')
        {
            int n_sent = send(sockfd, message, MAXDATASIZE, 0);
            if(n_sent < 0)
            {
                perror("Problem sending data");
                exit(1);
            }
            else
                printf("--sent--\n");
            int port = 0;
            char IP[30];
            getInfo(message, &port, IP);
            printf("%s\n", IP);
            printf("%d\n", port);
            socklen_t  addrlen;
            if((listensd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
            {
                perror("Creating  socket failed.");
                exit(1);
            }
            int opt = SO_REUSEADDR;
            setsockopt(listensd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
            bzero(&test,sizeof(test));
            test.sin_family=AF_INET;
            test.sin_port=htons(port);
            if(inet_pton(AF_INET, IP, &test.sin_addr) <= 0)
            {
                perror("error");
                exit(1);
            }
            if(bind(listensd, (struct sockaddr *)&test, sizeof(test)) == -1) 
            {
                perror("Binderror.");
                exit(1);
            }   
            if(listen(listensd,BACKLOG)== -1)
            {  /* calls listen() */
                perror("listen()error\n");
                exit(1);
            }
            addrlen =sizeof(client);
            if((connectfd = accept(listensd,(struct sockaddr*)&client,&addrlen))==-1) 
            {
                perror("accept()error\n");
                exit(1);
            }
            else
            {
                printf("connected\n");
                connected = 1;
                continue;
            }
        }
        if(message[0] == 'P' && message[1] == 'A' && message[2] == 'S' && message[3] == 'V')
        {
            int n_sent = send(sockfd, message, MAXDATASIZE, 0);
            if(n_sent < 0)
            {
                perror("Problem sending data");
                exit(1);
            }
            else
                printf("--sent--\n");
            int port;
            char IP[30];
            int n_buf = recv(sockfd, buf, MAXBUF, 0);
            buf[n_buf] = '\0';
            getInfo(buf, &port, IP);
            //connection
            if((pasv_sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1)
            {
                printf("socket()error\n");
                exit(1);
            } 
            bzero(&pasv, sizeof(pasv));
            pasv.sin_family = AF_INET;
            pasv.sin_port = htons(port);
            if(inet_pton(AF_INET, IP, &pasv.sin_addr) <= 0)
            {
                perror("error");
                exit(1);
            }
            
            if(connect(pasv_sd,(struct sockaddr *)&pasv,sizeof(pasv))==-1)
            {
                printf("connect()error\n");
                exit(1);
            }
            else
            {
                connected = 2;
                continue;
            }
        }
        if(message[0] == 'R' && message[1] == 'E' && message[2] == 'T' && message[3] == 'R')
        {
            int n_sent = send(sockfd, message, MAXDATASIZE, 0);
            if(n_sent < 0)
            {
                perror("Problem sending data");
                exit(1);
            }
            else
                printf("--sent--\n");
            int i = 5;
            char fileName[20];
            int j = 0;
            for(;i<mes_len;i++)
            {
                fileName[j] = message[i];
                j++;
            }
            fileName[j-1] = '\0';
            //char *_fileName = NULL;
            //_fileName = (char *)malloc(j*sizeof(char));
            //strcmp(_fileName, fileName);
            //printf("%s\n", _fileName);
            char content[MAXBUF];
            int n_buf = recv(sockfd, buf, MAXBUF, 0);
            buf[n_buf] = '\0';
            write(STDOUT_FILENO, buf, n_buf);
            if(strcmp("not connected yet\n", buf) != 0)
            {
                int n_read;
                if(connected == 1)
                    n_read = recv(connectfd, content, MAXBUF, 0);
                else
                    n_read = recv(pasv_sd, content, MAXBUF, 0);
                int n_buf = recv(sockfd, buf, MAXBUF, 0);
                buf[n_buf] = '\0';
                write(STDOUT_FILENO, buf, n_buf);
                FILE *pFile = fopen(fileName, "w+");
                fputs(content, pFile);
                fflush(pFile);
            }
            else
            {
                if(write(STDOUT_FILENO, buf, n_buf) < 0)
                {
                    perror("Problem writing to stdout");
                    exit(1);
                }
            }
            //free(_fileName);
            continue;
        }
        if(message[0] == 'S' && message[1] == 'T' && message[2] == 'O' && message[3] == 'R')
        {
            int n_sent = send(sockfd, message, MAXDATASIZE, 0);
            if(n_sent < 0)
            {
                perror("Problem sending data");
                exit(1);
            }
            else
                printf("--sent--\n");
            int n_buf = recv(sockfd, buf, MAXBUF, 0);
            buf[n_buf] = '\0';
            write(STDOUT_FILENO, buf, n_buf);
            int i = 5;
            char fileName[20];
            int j = 0;
            for(;i<mes_len;i++)
            {
                fileName[j] = message[i];
                j++;
            }
            //char *_fileName = NULL;
            //_fileName = (char *)malloc(j*sizeof(char));
            //strcmp(_fileName, fileName);
            //printf("%s\n", _fileName);
            fileName[j-1] = '\0';
            char content[MAXBUF];
            FILE *pFile = fopen(fileName, "r");
            fgets(content, MAXBUF, pFile);
            int len = strlen(content);
            if(connected == 1)
            {
                if((send(connectfd, content, len, 0)) < 0)
                {
                    perror("sendProblem\n");
                    exit(1);
                }
            }
            else
            {
                if((send(pasv_sd, content, len, 0)) < 0)
                {
                    perror("sendProblem\n");
                    exit(1);
                }
            }
            int n = recv(sockfd, buf, MAXBUF, 0);
            buf[n] = '\0';
            write(STDOUT_FILENO, buf, n);
            continue;
        }

        int n_sent = send(sockfd, message, MAXDATASIZE, 0);
        if(n_sent < 0)
        {
            perror("Problem sending data");
            exit(1);
        }
        else
            printf("--sent--\n");

        int n_read = recv(sockfd, buf, MAXDATASIZE, 0);
        buf[n_read] = '\0';
        if(strcmp("bye", buf) == 0)
        {
            write(STDOUT_FILENO, buf, n_read);
            break;
        }

        if(write(STDOUT_FILENO, buf, n_read) < 0)
        {
            perror("Problem writing to stdout");
            exit(1);
        }
    }
    return 0;
}

void getInfo(char *buf,int *port, char *IP)
{
    int len = strlen(buf);
    char p1[10];
    char p2[10];
    int i = 0;
    int j = 5;
    int count = 0;
    for(;j < len;i++, j++)
    {
        if(buf[j] == ',')
        {
            count++;
            if(count != 4 && count != 5)
                IP[i] = '.';
            else
            {
                i = -1;
                continue;
            }
        }
        else
        {
            if(count == 4)
            {
                p1[i] = buf[j];
                p1[i+1] = '\0';
            }
            else if(count == 5)
            {
                if(buf[j] == '\n')
                    p2[i] = '\0';
                else
                {
                    p2[i] = buf[j];
                    p2[i + 1] = '\0'; 
                }
            }
            else
                IP[i] = buf[j];
        }
    }
    int len1 = strlen(p1);
    int len2 = strlen(p2);
    int temSave = 0;
    int k = 0;
    for(i=len1;i>=1;i--, k++)
    {
        char tem = p1[k];
        int temNum = (int)(tem - '0');
        for(j=i;j>1;j--)
            temNum = temNum * 10;
        temSave += temNum;
    }
    temSave *= 256;
    for(i=len2, k=0;i>=1;i--, k++)
    {
        char tem = p2[k];
        int temNum = (int)(tem - '0');
        for(j=i;j>1;j--)
            temNum = temNum * 10;
        temSave += temNum;
    }
    *port = temSave;
    return;
}