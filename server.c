#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUFLEN 1024  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data 
 
int main(void)
{
    struct sockaddr_in si_me, si_other;
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
    //create a UDP socket
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &si_me.sin_addr);
    bind(s , (struct sockaddr*)&si_me, sizeof(si_me)); 
    //keep listening for data
    while(1)
    {
        int buf_len=0;
        printf("Waiting for data...\n");
        //fflush(stdout);
        //try to receive some data, this is a blocking call
        recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
        buf_len = strlen(buf);
        //print details of the client/peer and the data received
        buf[buf_len-1]='\0';
        if(strlen(buf)>0)
        {  
            printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
            printf("Data: %s\n" , buf);
            sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen);
        }
        //now reply the client with the same data
        memset(&buf[0], 0, sizeof(buf));  
  }
    close(s);
    return(0);
}
