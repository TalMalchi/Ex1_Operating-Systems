#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


using namespace std;

int server()
{
    cout << "Server is ready!" << endl;
    // create a socket
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }

    //bind the ip address and port to a socket
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);

    if (bind(serverSock, (sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    listen(serverSock, SOMAXCONN);

    //wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int clientSocket = accept(serverSock, (sockaddr *)&client, &clientSize);

    char host[NI_MAXHOST];    
    char service[NI_MAXSERV]; 

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }

    //close listening socket
    close(serverSock);

    //accept and echo message back to client
    char buf[4096];

    while (true)
    {
        memset(buf, 0, 4096);

        //wait for client to send data
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cerr << "Error in recevie" << endl;
        
        }

        if (bytesReceived == 0)
        {
            cout << "Client disconnected from the server" << endl;
            close(clientSocket);
            server();
        }
        else
        {

            cout << string(buf, 0, bytesReceived) << endl;

            //send echo message back to client
            send(clientSocket, buf, bytesReceived + 1, 0);
        }
    }


    close(clientSocket);

    return 0;
}
int main()
{
    server();
    return 0;
}