/* Assignment 5: CSCI 3171: Summer 2017
 *
 * Program for client to connect to the Prison Game server
 *
 * Initial connection setup was referenced from suggested resource
 * codeproject.com
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(void) {

  //begin connection setup
  int sockfd = 0, n = 0;
  char sendBuff[1024]; //buffer used to contain messages sent to server
  char recvBuff[1024];
  struct sockaddr_in serv_addr;
  char inputBuff[1024];

  memset(recvBuff, 0 ,sizeof(recvBuff));
  memset (inputBuff, 0 ,sizeof(inputBuff));

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0) {
    printf("\n Error : Could not create socket \n");
    return 1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0) {
    printf("\n Error : Connect Failed \n");
    return 1;
  }

  while((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0) {
    recvBuff[n] = 0; //terminate message line at the end of the string
    printf("...%s....\n", recvBuff);
    printf("\n Enter decision (S or B) or enter 'x' to quit: ");
    fgets(inputBuff, sizeof (inputBuff) -1, stdin);

    if (inputBuff[0] == 'x') {break;}

    strcpy(sendBuff, inputBuff);
    write(sockfd, sendBuff, sizeof(sendBuff)-1);

    memset(recvBuff, 0 ,sizeof(recvBuff)); //reset buffer
    memset (inputBuff, 0 ,sizeof(inputBuff)); //reset buffer
    
    printf("\n");
  }

  if( n < 0) printf("\n Read Error \n");

  return 0;
}
