#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
 int sockd,sockdNew,c;
 struct sockaddr_in server,client;
 char *message,buffer[200];
 sockd = socket(AF_INET,SOCK_STREAM,0);
 if(sockd == -1)
 {
  printf("Can not create socket.\n");
 }

 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
 server.sin_port = htons(8888);

 if(bind(sockd,(struct sockaddr *)&server,sizeof(server))<0)
 {
  puts("Bind failed.\n");
 }
 puts("Bind done.\n");

 listen(sockd,3);

 puts("Waiting for connection..\n");
 c = sizeof(struct sockaddr_in);
 while(sockdNew = accept(sockd,(struct sockaddr *)&client, (socklen_t*)&c))
 {
  puts("Connection accepted.\n");
  message= "Hello Client, I have received your connection, But i have to go now. Bye.\n";
  read(sockdNew,buffer,200);
  printf("%s",buffer);
  write(sockdNew,message,strlen(message));
 }
 if(sockdNew<0)
 {
  perror("Accept failed");
  return 1;
 }
 return 0;
}
