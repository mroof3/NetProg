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
    int i, len, num, rc, lconn, aconn;          //variables
    char buffer[MAXLINE];                           //buffer for messages
    struct sockaddr_in addr;

    //control number of connections

    //create a socket to receive incoming connections
    lconn = socket(AF_INET, SOCK_STREAM, 0);           //create socket
    if(lconn < 0) {
        perror("Socket Not Created");
        exit(-1);
    }
    else {
        printf("Socket Connected");
    }
    //bind socket
    
    //server ready

    //wait for connections

    //receive message

    //close connections
    
    //close socket

    return 0;
}
