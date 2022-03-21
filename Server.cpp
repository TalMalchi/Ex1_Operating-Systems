#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main()
{
    cout << "Server is ready!" << endl;
    // create a socket
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }

    // bind the ip address and port to a socket
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

    // wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    int clientSocket = accept(serverSock, (sockaddr *)&client, &clientSize);
    if (clientSocket < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    char buf[4096];

    while (true)
    {
        try
        {
            int data = recv(clientSocket, buf, 4096, 0);
            if (data== -1)
            {
                cerr << "Error in recv(). Quitting" << endl;

            }
            
            if (data == 0)
            {
            cout << "Client disconnected " << endl;
            close(clientSocket);
            main();
            }
            
            
            else {
                printf("%s\n", buf);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            exit(EXIT_FAILURE);
        }
    }
        close(clientSocket);
        return 0; 

}
