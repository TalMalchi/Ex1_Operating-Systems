#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <math.h>

#include <unistd.h>

int main(int argc, const char** argv) {

 int sockfd, n_sock;
        socklen_t addr_size;
        struct sockaddr_in s_addr, n_addr;

        // ------------------------------------------------------------
        // STEP 1: Open Socket TCP
        // ------------------------------------------------------------
        sockfd = socket(AF_INET, SOCK_STREAM, 0); //sock stream- send information
        if (sockfd < 0)
        {
            perror("\t------- Open socket is FAILED -------\n");
            exit(1);
        }
        printf("\t------- Socket created SUCCEES -------\n");

        // all the data dest are reload to "s_addr"
        s_addr.sin_family = AF_INET;         /*sending type*/ //tells which way to pass the information
        s_addr.sin_addr.s_addr = INADDR_ANY; /*read all interfaces*///socket that send information
        s_addr.sin_port = 8080;              /*protocol kind*/

        if (bind(sockfd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0) //connect the address to the socket 
        {
            perror("\t------- bind is FAILED -------\n");
            exit(1);
        }
        printf("\t------- bind SUCCEES -------\n");

        // ------------------------------------------------------------
        // STEP 2: Listening
        // ------------------------------------------------------------
        if (listen(sockfd, 10) == 0) //wait for incoming connection- till 10 request. zero is succsesful
        {
            printf("\t------ Listening SUCCEES ------\n");
        }
        else
        {
            perror("\t------ Listening FAILED ------\n");
            exit(1);
        }

        // ------------------------------------------------------------
        // STEP 3: Accept connection from - Sender
        // ------------------------------------------------------------
        addr_size = sizeof(n_addr);
        n_sock = accept(sockfd, (struct sockaddr *)&n_addr, &addr_size); //accept request fron sender
                int n_bytes = 0, counter_bytes = 0;
            char *buffer = (char *)malloc(sizeof(char) * 1024);

            while (n_bytes < pow(1024, 2)) //check that the file was sent successfuly
            {
                counter_bytes = recv(n_sock, buffer, 1024, 0); //check the file accept according to bytes's numbers
                if (counter_bytes <= 0)
                {
                    break;
                }
                n_bytes += counter_bytes;
                bzero(buffer, 1024);
            }
            free(buffer);





























}