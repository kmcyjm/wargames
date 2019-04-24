/* * ===================================================================================== * *       
 * Filename:  challenge01.c   
 *
 * Description:  overthewire/vortex challenge level 0 -> level 1        
 *
 * Version:  1.0       
 *
 * Created:  03/21/2019 12:18:33       
 *
 * Revision:  none       
 *
 * Compiler:  gcc
 * 
 * Author:  Jiaming 
 * 
 * Organization:  
 *
 * Level Goal
 * ----------
 *   
 * Your goal is to connect to port 5842 on vortex.labs.overthewire.org and read in 4 unsigned integers in host byte order. 
 *
 * Add these integers together and send back the results to get a username and password for vortex1. This information can be used to log in using SSH.
 *   
 * Note: vortex is on an 32bit x86 machine (meaning, a little endian architecture)
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "hacking.h"

int main(int argc, char *argv[]) {
    int sockfd = 0, i = 0;
    unsigned int sum = 0;
    struct hostent *host_info;
    struct sockaddr_in target_addr;
    unsigned char buffer[1024];
    unsigned int *uint32_p = NULL;

    if(argc < 2) {
        printf("Usage: %s <hostname> <port>\n", argv[0]);
        exit(1);
    }

    if((host_info = gethostbyname(argv[1])) == NULL)
        fatal("looking up hostname");

    if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        fatal("in socket");

    target_addr.sin_family = AF_INET;
    // use atoi() to translate numeric literal to integer
    target_addr.sin_port = htons(atoi(argv[2]));
    target_addr.sin_addr = *((struct in_addr *)host_info->h_addr);
    memset(&(target_addr.sin_zero), '\0', 8);

    if(connect(sockfd, (struct sockaddr *)&target_addr, sizeof(struct sockaddr)) == -1)
        fatal("connecting to target server");

    while(recv(sockfd, buffer, 1024, 0)) {
        dump(buffer, 64);
        uint32_p = (unsigned int *)buffer;
        for(i = 0; i < 4; i++) {
            sum += *uint32_p;
            uint32_p++;
        }

    if(send(sockfd, &sum, sizeof(int), 0) == -1)
        fatal("sending data");
    }
}
