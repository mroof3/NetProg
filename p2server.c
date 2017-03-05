/*
Joshua Hulbert & Matt Roof
Dr. Silaghi
Project Milestone 02
March 5, 2017
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE     100

int main(int argc, char *argv[])
{
    int i, len, rc, lconn, aconn;                  //variables
    char buffer[MAXLINE];                               //buffer for messages
    struct sockaddr_in addr;

    //create a socket to receive incoming connections
    lconn = socket(AF_INET, SOCK_STREAM, 0);           //create socket
    if(lconn < 0) {                                    //check for error
        perror("Socket Not Created");
        exit(-1);
    }
    else {                                             //no errors, socket created
        printf("Socket Connected");
    }
//bind socket
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;                         //address family -- IPv4
    addr.sin_addr.s_addr = htonl(INADDR_ANY);          //hostbyte to networkbyte
    addr.sin_port = htons(argc);                       //port no
    if(bind(lconn, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("Couldnt Bind");
        close(lconn);
        exit(-1);
    }
    else {
        printf("Socket Bound");
    }
//start listening
    if(listen(lconn, 10) < 0) {                         //listen for connection
        perror("Couldnt Find Connection");
    }
    else {
        printf("Found Connection");
    }    
//accept connections
    while(1){
        if(accept(lconn, NULL, NULL) < 0){
            perror("Couldnt Accept Connection");
            close(lconn);
            exit(-1);
        }
        else{
            printf("Accepted Connection");
        }
//receive message
        if(recv(aconn, buffer,sizeof(buffer), 0) <= 0) {
            perror("Couldnt Recieve Message");
            close(lconn);
            close(aconn);
            exit(-1);
        }
        else {
            printf("Client: " %s, buffer);
        }
    }
//close connections
    
//close socket

    return 0;
}
