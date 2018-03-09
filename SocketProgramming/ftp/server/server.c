#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>     /* defines STDIN_FILENO, system calls,etc */
#include <sys/types.h>  /* system data type definitions */
#include <sys/socket.h> /* socket specific definitions */
#include <netinet/in.h> /* INET constants and stuff */
#include <arpa/inet.h>  /* IP address conversion stuff */
#include <netdb.h>      /* gethostbyname */
     
#define  PORT 8000
#define  BACKLOG 1
#define  MAXBUF 2000
#define  NUM_THREADS 10

char message2301[] = "230-\n";
char message2302[] = "230-Welcome to my server\r\n";
char message2303[] = "230 login ok, waiting for your command\r\n";
char message2330[] = "233-port mode ready\r\n";
char message2331[] = "233 waiting for ur client to connect\r\n";
char message5551[] = "555-no such command\r\n";
char message5552[] = "555 please check it\r\n";

struct Arg
{
    int connectfd;
    struct sockaddr_in client;
    struct  sockaddr_in server;
}; 

void getInfo(char *buf,int *port, char *IP);
void *serve(void *arg);
void *serveIt(void *arg);

int main()
{
    pthread_t threads[NUM_THREADS];
	  int  listenfd, connectfd;
  	struct  sockaddr_in server;
  	struct  sockaddr_in client;
    int presentThread = 0;
    struct Arg arg[NUM_THREADS];

    int sd;
    struct sockaddr_in test;

  	socklen_t  addrlen;
  	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
 	  {
    	perror("Creating  socket failed.");
    	exit(1);
  	}
  	int opt = SO_REUSEADDR;
  	setsockopt(listenfd,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  	bzero(&server,sizeof(server));
  	server.sin_family=AF_INET;
  	server.sin_port=htons(PORT);
  	server.sin_addr.s_addr= htonl (INADDR_ANY);

  	if(bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1) 
  	{
  		perror("Binderror.");
    	exit(1);
  	}   
  	if(listen(listenfd,BACKLOG)== -1)
  	{  /* calls listen() */
       	perror("listen()error\n");
       	exit(1);
  	}

    addrlen =sizeof(client);
    while (1) 
    {
      if ((connectfd = accept(listenfd,(struct sockaddr *)&client, &addrlen)) == -1) 
      {
        printf("Error accept");
        //continue;
      }
    
      //create new thread
      int t;
      arg[presentThread].connectfd  = connectfd;
      arg[presentThread].client = client;
      arg[presentThread].server = server;
      printf("You got a connection from cient's ip is %s, port is %d\n",inet_ntoa(arg[presentThread].client.sin_addr),htons(arg[presentThread].client.sin_port));
      if((t = pthread_create(&threads[presentThread],NULL,serveIt, &arg[presentThread])) != 0)
      {
        printf("Error accept");
        exit(1);
      }
      else
      {
        printf("%d\n", t);
        presentThread++;
      }
      //printf("%d\n", presentThread);
    } 
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
        p2[i] = buf[j];
        p2[i+1] = '\0';
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

void *serveIt(void *arg)
{
  printf("1\n");
  struct Arg *p_arg = arg;
  struct sockaddr_in pasv_client;
  struct sockaddr_in client = p_arg->client;
  struct sockaddr_in server = p_arg->server;
  int connectfd = p_arg->connectfd;
  int pasv_lis, pasv_con;

  int logged = 0;
  int connected = 0;
  int sd;
  struct sockaddr_in test;
  struct sockaddr_in pasv;

  printf("You got a connection from cient's ip is %s, port is %d\n",inet_ntoa(client.sin_addr),htons(client.sin_port));
  send(connectfd,"FTP server ready.\n",17,0);
  char buf[MAXBUF];
  char message[MAXBUF];
  strcpy(message, inet_ntoa(client.sin_addr));
  strcat(message, " Guest login ok, send your complete e-mail address as password.\n");
  int mesLen = strlen(message);
  
  while(1)
  {
    int n = recv(connectfd, buf, MAXBUF, 0);
    int bufLen = strlen(buf);
    buf[bufLen - 1] = '\0';
    if(n < 0)
    {
      perror("recvError.");
      exit(1);
    }
    else
    {
      if(logged == 0)
      {
        if(strcmp("USER anonymous", buf) == 0)
        {
          send(connectfd, message, mesLen + 1, 0);
          n = recv(connectfd, buf, MAXBUF, 0);
          if(n < 0)
          {
            perror("readError.");
            exit(1);
          }
          if(strcmp("", buf) != 0)
          {
            char tem[MAXBUF];
            strcpy(tem, message2301);
            strcat(tem, message2302);
            strcat(tem, message2303);
            int temLen = strlen(tem);
            send(connectfd, tem, temLen + 1, 0);
            printf("--waiting for command--\n");
            logged = 1;
          }
        }
        else
          send(connectfd, "invalid input.\n", 16, 0);
      }
      else
      {
        if(strcmp("QUIT", buf) == 0)
        {
          send(connectfd, "bye\n", 4, 0);
          break;
        }
        else if(strcmp("ABOR", buf) == 0)
        {
          send(connectfd, "bye\n", 4, 0);
          break;
        }
        else if(strcmp("SYST", buf) == 0)
          send(connectfd, "215 UNIX Type: L8\n", 19, 0);
        else if(strcmp("TYPE I", buf) == 0)
          send(connectfd, "200 Type set to I.\n", 19, 0);
        else if(buf[0] == 'P' && buf[1] == 'O' && buf[2] == 'R' && buf[3] == 'T')
        {

          int port = 0;
          char IP[30];
          getInfo(buf, &port, IP);
          //connection
          printf("%s\n", IP);
          printf("%d\n", port);
          if((sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==-1)
          {
              printf("socket()error\n");
              exit(1);
          } 
          bzero(&test, sizeof(test));
          test.sin_family = AF_INET;
          test.sin_port = htons(port);
          if(inet_pton(AF_INET, IP, &test.sin_addr) <= 0)
          {
            perror("error");
            exit(1);
          }
            
          if(connect(sd,(struct sockaddr *)&test,sizeof(test))==-1)
          {
              printf("connect()error\n");
              exit(1);
          }
          else
            connected = 1;
        }
        else if(strcmp("PASV", buf) == 0)
        {
          int num1, num2;
          srand((unsigned)time(NULL));
          num1 = rand()%101 + 100;
          num2 = rand()%101;
          char _num1[3];
          char _num2[3];
          char temp[3];
          int port = num1*256 + num2;

          int m, n;
          m = n = 0;
          for(;num1>0;num1 /= 10, m++)
          {
            char tem = (char)(num1%10) +  '0';
            temp[m] = tem;
          }
          for(m--;m>=0;m--, n++)
            _num1[n] = temp[m];
          m = n = 0;
          for(;num2>0;num2 /= 10, m++)
          {
            char tem = (char)(num2%10) +  '0';
            temp[m] = tem;
          }
          for(m--;m>=0;m--, n++)
            _num2[n] = temp[m];

          char tem[30];
          strcpy(tem, inet_ntoa(server.sin_addr));
          printf("%s\n", tem);
          printf("%d\n", port);
          int len = strlen(tem);
          int i;
          for(i = 0;i < len;i++)
          {
            if(tem[i] == '.')
              tem[i] = ',';
          }
          tem[i] = '\0';
          char message[100];
          strcpy(message, "227 =");
          strcat(message, tem);
          strcat(message, ",");
          strcat(message, _num1);
          strcat(message, ",");
          strcat(message, _num2);
          printf("%s\n", message);
          int mesLen = strlen(message);
          send(connectfd, message, mesLen, 0);

          socklen_t addrlen;
          if((pasv_lis = socket(AF_INET, SOCK_STREAM, 0)) == -1)
          {
            perror("creating socket failed");
            exit(1);
          }
          int opt = SO_REUSEADDR;
          setsockopt(pasv_lis,SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
          bzero(&pasv,sizeof(pasv));
          pasv.sin_family=AF_INET;
          pasv.sin_port=htons(port);
          if(inet_pton(AF_INET, inet_ntoa(server.sin_addr), &pasv.sin_addr) <= 0)
          {
              perror("error");
              exit(1);
          }
          if(bind(pasv_lis, (struct sockaddr *)&pasv, sizeof(pasv)) == -1) 
          {
              perror("Binderror.");
              exit(1);
          }   
          if(listen(pasv_lis,BACKLOG)== -1)
          {  /* calls listen() */
              perror("listen()error\n");
              exit(1);
          }
          addrlen =sizeof(pasv_client);
          if((pasv_con = accept(pasv_lis,(struct sockaddr*)&pasv_client,&addrlen))==-1) 
          {
              perror("accept()error\n");
              exit(1);
          }
          else
            connected = 2;
        }
        else if(buf[0] == 'R' && buf[1] == 'E' && buf[2] == 'T' && buf[3] == 'R')
        {
          if(connected == 0)
          {
            send(connectfd, "not connected yet\n", 13, 0);
            continue;
          }
          send(connectfd, "sending\n", 8, 0);
          int i = 5;
          char fileName[20];
          int j = 0;
          for(;i<bufLen;i++)
          {
              fileName[j] = buf[i];
              j++;
          }
          fileName[j] = '\0';
          char message[MAXBUF];
          FILE *pFile = fopen(fileName, "r");
          fgets(message, MAXBUF, pFile);
          int len = strlen(message);
          if(connected == 2)
          {
            if((send(pasv_con, message, len, 0)) < 0)
            {
              perror("sendProblem\n");
              exit(1);
            }
            else
              send(connectfd, "done\n", 5, 0);
          }
          else
          {
            if((send(sd, message, len, 0)) < 0)
            {
              perror("sendProblem\n");
              exit(1);
            }
            else
              send(connectfd, "done\n", 5, 0);
          }
          fclose(pFile);
        }
        else if(buf[0] == 'S' && buf[1] == 'T' && buf[2] == 'O' && buf[3] == 'R')
        {
          if(connected == 0)
          {
            send(connectfd, "not connected yet\n", 13, 0);
            continue;
          }
          send(connectfd, "recving\n", 8, 0);
          int i = 5;
          char fileName[20];
          int j = 0;
          for(;i<bufLen;i++)
          {
              fileName[j] = buf[i];
              j++;
          }
          printf("%s\n", fileName);
          char info[MAXBUF];
          if(connected == 1)
            recv(sd, info, MAXBUF, 0);
          else
            recv(pasv_con, info, MAXBUF, 0);
          FILE *pFile = fopen(fileName, "w+");
          fputs(info, pFile);
          fflush(pFile);
          send(connectfd, "STOR done\n", 10, 0);
        }
        else
        {
          char tem[MAXBUF];
          strcpy(tem, message5551);
          strcat(tem, message5552);
          int temLen = strlen(tem);
          send(connectfd, tem, temLen+1, 0);
        }
      }
    }
  }
  pthread_exit(NULL);
}