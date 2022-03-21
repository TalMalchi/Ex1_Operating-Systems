#include <iostream>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <cstdio>
#include <sys/socket.h>
#include <sys/stat.h>
#include <filesystem>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/wait.h>
#include <netinet/tcp.h>
#include <math.h>
#include <string.h>
#include <netdb.h>

using namespace std;

int main(int argc, const char **argv)
{

    // get current lib
    char cwd[1024];

    // get input from the user
    string line, cmd, data;
    while (cmd != "EXIT")
    {
        // print current directory each time
        getcwd(cwd, sizeof(cwd));
        cout << "\u001b[33;1m" << cwd << ": "
             << "\x1B[0m";
        // cout << cwd << ": " << endl;
        // cout << "Yes Master ? " << endl;
        cout << "\u001b[31;1m"
             << "Yes Master ?"
             << "\x1B[0m" << endl;

        getline(cin, line);
        // first word is cmd
        cmd = line.substr(0, line.find_first_of(" "));

        if (cmd.size() < line.size())
        {
            // rest line is data from the user
            data = line.substr(line.find_first_of(" ") + 1);
        }
        string checkTCP = data.substr(data.find_first_of(" ") + 1);
        if (cmd == "ECHO")
        {
            // REGULAR COMMAND
            // cout << data << endl;

            // SYSTEM COMMAND
            setenv("data_paste", data.c_str(), 1);
            system("echo $data_paste"); // need to add data
        }

        if (cmd == "TCP" && checkTCP == "PORT")
        {
            // SYSTEM COMMAND
            // system("netcat 127.0.0.1 54000");

            // REGULAR COMMAND
            //	Create a socket
            int sock = socket(AF_INET, SOCK_STREAM, 0);
            if (sock == -1)
            {
                printf("\n Socket creation error \n");
                return -1;
            }

            
            int port = 54000;
            string ipAddress = "127.0.0.1";

            sockaddr_in hint;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(port);
            inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

            //connect to the server on the socket
            if(connect(sock, (sockaddr *)&hint, sizeof(hint))<0) 
            {
                printf("\nConnection Failed \n");
                return -1;            }

            
            char buf[4096];
            string userInput;

            do
            {
                //
                cout << "> ";
                getline(cin, userInput);
                if (userInput== "LOCAL")
                {
                    cout << "gotta go!" << endl; 
                    break;
                }
                
                send(sock, userInput.c_str(), userInput.size() + 1, 0);

            //     //		Send to server
            //     int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
            //     if (sendRes == -1)
            //     {
            //         cout << "Could not send to server! Whoops!\r\n";
            //         continue;
            //     }

            //     if (string(buf, 0, bytesReceived) == "LOCAL")
            //     {
            //         cout << "gotta go! " << endl;

            //         break;
            //     }
            //     else
            //     {
            //         //		Display response
            //         cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
            //     }
             } while (true);

            //	Close the socket
            close(sock);
        }
        
        if (cmd == "DIR") /// check the different between file and directory
        {
            // SYSTEM COMMAND
            // system("ls");

            // REGULAR COMMAND
            DIR *dir_handler;
            struct dirent *files;
            // open the current directory
            dir_handler = opendir(".");
            if (dir_handler)
            {
                // if isn't null- print all the dir's files
                while ((files = readdir(dir_handler)) != NULL)
                {
                    // cout << files->d_name << endl;
                    cout << "\u001b[32;1m" << files->d_name << "\x1B[0m" << endl;
                }
            }
            else
            {
                cout << "Error" << endl;
            }
            closedir(dir_handler);
        }

        /*
        The chdir command is a system function (system call) which is used to change the current directory

        */

        if (cmd == "CD")
        {
            // SYSTEM COMMAND
            // system("cd");

            // REGULAR COMMAND
            if (data == ".." || data == "\n")
            {
                // cout <<data << endl;
                chdir("..");
                // getenv
            }
            else
            {
                // const char *new_cd= data.c_str();
                string a = "";
                a.append(data);
                const char *new_cd = a.c_str(); // convert string to const char
                // cout <<a << endl;
                int check;
                cout << new_cd << endl;
                check = chdir(new_cd); // if directory was change successfully, check=0 , else -1
                cout << check << endl;
                cout << "after change" << endl;
            }
        }

        // copy file from source to dest
        if (cmd == "COPY")
        {
            string src, dst;
            char buf[BUFSIZ]; // default is 8192 bytes- one char at the time
            size_t size;      // BUFFER_SIZE = 4096;
            src = data.substr(0, data.find_first_of(" "));
            dst = data.substr(data.find_first_of(" ") + 1);

            // open src file
            FILE *src_open_file = fopen(src.c_str(), "rb");
            if (src_open_file == NULL)
            {
                cout << "Error" << endl;
                exit(EXIT_FAILURE);
            }

            // open dest file
            FILE *dst_open_file = fopen(dst.c_str(), "wb");
            if (dst_open_file == NULL)
            {
                fclose(src_open_file);
                cout << "Error" << endl;
                exit(EXIT_FAILURE);
            }
            // write to the file
            while (size = fread(buf, 1, BUFSIZ, src_open_file))
            {
                fwrite(buf, 1, size, dst_open_file);
            }

            fclose(src_open_file);
            fclose(dst_open_file);
        }

        if (cmd == "DELETE")
        {
            const char *file_name = data.c_str();
            unlink(file_name);
            cout << "file deleted successfully" << endl;
        }
    }
    return 0;

    /* ***********************ANSWERS******************
        1. DOES SYSTEM IS LIBRARY FUNCTION OR SYSTEM FUNCTION?
        1- ANSWER: "system" is SYSTEM function, because when we use it, the data we write inside
            this function command is written directly to the main shell.

        2. DOES YOUR FILE READ IMPLEMITATION USES LIBRARY FUNCTION OR SYSTEM FUNCTION?
        2- ANSWER: Our "COPY SOURCE DEST" function uses the library function,
            because we use in "fread", "fwrite", "fclose".

        3. DOES the "DELETE FILE NAME" IS LIBRARY FUNCTION OR SYSTEM FUNCTION?
        3- ANSWER: The "DELETE FILE NAME" function is a system function.


        ****************************END*****************************************

    */

    ////////////// fork /////////////

    // pid_t ch_pid = fork();

    // //// if pid == -1, fork faild
    // if (ch_pid == -1) {
    //     perror("Fork failed");
    //     exit(EXIT_FAILURE);

    // }
    // //////// if pid >0 , I'm parent
    // else if (ch_pid > 0) {
    //     cout << "spawn child with pid - " << ch_pid << endl;
    //     return ch_pid;
    //     }

    // //////// if pid ==0 , I'm child
    // else {
    //     char* args[2]= {"./check", NULL} //////////// need to do another file for this function
    //     execve(args[0], args, nullptr);
    //     perror("execve");
    //     exit(EXIT_FAILURE);
    // }
}