#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
 int sockd,newsockd,c;
 struct sockaddr_in server,client;
 char *message;

 if((sockd= socket(AF_INET,SOCK_STREAM,0))==-1)
 {
  puts("Create socket failed\n");
  return 1;
 }
 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
 server.sin_port = htons(8888);

 if(bind(sockd,(struct sockaddr *)&server, sizeof(server))<0)
 {
  puts("Bind failed\n");
  return 1;
 }
 puts("Binded\n");
 listen(sockd,2);
 puts("waiting...\n");
 c = sizeof(struct sockaddr_in);
 while(newsockd = accept(sockd,(struct sockaddr *)&client,(socklen_t*)&c))
 {
  char buffer[100]="";
  puts("Connection Accepted");
  read(newsockd,buffer,100);
  printf("Client: %s",buffer);
  printf("You: ");
  fgets(message,100,stdin);
  write(newsockd,message,strlen(message));
 }
 if(newsockd<0)
 {
  perror("accept failed");
  return 1;
 }
 close(sockd);
 return 0;
}
