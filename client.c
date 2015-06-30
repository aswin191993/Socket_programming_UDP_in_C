#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUFLEN 512  //Max length of buffer

int main(void)
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(8888);//port number
    inet_aton("127.0.0.1", &si_other.sin_addr);//ip address
    while(1)
    {
        printf("Enter message : ");
        char message[100],messagein[100];;
        fgets(message, 100, stdin);
        //send the message
        sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen);
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
        puts(buf);
    }
 
    close(s);
    return 0;
}
