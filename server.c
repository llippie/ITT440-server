#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
 int sockd,c,client,sockClient;
 struct sockaddr_in server;
 int port = 8888;
 sockd = socket(AF_INET,SOCK_STREAM,0);
 if(sockd < 0)
 {
  printf("Unable to create socket.\n");
 }
 else
 {
  printf("Socket created!\n");
 }
 server.sin_family = AF_INET;
 server.sin_addr.s_addr = inet_addr("");
 server.sin_port = htons(port);

 if(bind(sockd,(struct sockaddr *)&server,sizeof(server)) == -1)
 {
  printf("Can't bind the seocket.\n");
 }
 else
 {
  printf("Bind with port %d successfull\n",port);
 }

 if(listen(sockd,3)<0)
 {
  printf("Listening failed to port %d",port);
 }
 else
 {
  printf("Listening to port %d",port);
 } 
 c = sizeof(struct sockaddr_in);
 sockClient = accept(sockd,(struct sockaddr *)&client,(socklen_t*)&c);

 if(sockClient<0)
 {
  printf("Failed to accept\n");
 }
 else
  printf("Client accepted\n");
 close(sockd);
 return 0;
}
