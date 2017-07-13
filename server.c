/* Assignment 5: CSCI 3171: Summer 2017
 *
 * Program for client to connect to the Prison Game server
 *
 * Initial connection setup was referenced from suggested resource
 * codeproject.com
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void) {
  int listenfd = 0,connfd = 0;
  struct sockaddr_in serv_addr;
  char sendBuff[1025];
  char recvBuff[1025];
  int numrv;

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("server is running successfully\n");
  memset(&serv_addr, 0, sizeof(serv_addr));
  memset(sendBuff, 0, sizeof(sendBuff));

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

  if(listen(listenfd, 10) == -1) {
      printf("Failed to listen\n");
      return -1;
  }

  while(1) {
    connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request
    strcpy(sendBuff, "Server acknowledges client connection. Game initiated."); 
    write(connfd, sendBuff, strlen(sendBuff));
    int n;
    while((n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
      recvBuff[n] = 0; //terminate message line at the end of the string
      int serverToss = rand() %2;
      //if serverToss is 0 then is S
      //if serverToss is 1 then is B


      if(fputs(recvBuff, stdout) == EOF) printf("\n Error : Fputs error");

      //printf("%s\n", recvBuff);

      if (recvBuff[0] == 'S' && serverToss == 0) //both are silent
      {
        strcpy(sendBuff, "Both prisoners spend 1 years in jail.");
      }
     
      else if (recvBuff[0] == 'S' && serverToss == 1) // A is silent, B betrays
      {
        strcpy(sendBuff, "Prisoner A spends 3 years in jail, prisoner B goes free.");
      }

      else if (recvBuff[0] == 'B' && serverToss == 0) // A betrays, B stays silent
      {
        strcpy(sendBuff, "Prisoner B spends 3 years in jail, prisoner A goes free.");
      }

      else if (recvBuff[0] == 'B' && serverToss == 1) //both betray
      {
        strcpy(sendBuff, "Both prisoners spend 2 years in jail.");
      }

      else {
        strcpy(sendBuff, "Wrong input, please try again.");
      }

      write(connfd, sendBuff, sizeof(sendBuff)-1);
      memset(recvBuff, 0, sizeof(recvBuff));
      memset(sendBuff, 0, sizeof(sendBuff));


    }

   close(connfd);
    sleep(1);
  }
  return 0;
}
