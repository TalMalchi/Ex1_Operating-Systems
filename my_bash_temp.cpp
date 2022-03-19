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

using namespace std;

#define PORT 8080
void writeNewTer(){
    cout<<"test"<< endl;
}

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
        //cout << cwd << ": " << endl;
        //cout << "Yes Master ? " << endl;
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

        if (cmd == "ECHO")
        {
            
            cout << data << endl;
            //system("echo"); //need to add data

        }

        if (cmd == "TCP")
        { 
        char *serverIp = "127.0.0.1"; 
        int port = 8080; 
    //create a message buffer 
    char msg[1500]; 
    //setup a socket and connection tools 
    //struct hostent* host = gethostname(serverIp, size_t(serverIp)); 
    sockaddr_in sendSockAddr;   
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = INADDR_ANY;
        
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; break;
    }
    cout << "Connected to the server!" << endl;
    int bytesRead, bytesWritten = 0;
  
    while(1)
    {
        cout << ">";
       
        memset(&msg, 0, sizeof(msg));//clear the buffer
        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            send(clientSd, (char*)&msg, strlen(msg), 0);
            break;
        }
        bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
        cout << "Awaiting server response..." << endl;
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
        if(!strcmp(msg, "exit"))
        {
            cout << "Server has quit the session" << endl;
            break;
        }
        cout << "Server: " << msg << endl;
    }

    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead << endl;
    //cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      //<< " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;  
} 
            

            
            
                
        

        if (cmd == "LOCAL")
        {
        }

        if (cmd == "DIR") /// check the different between file and directory
        {
            DIR *dir_handler;
            struct dirent *files;
            // open the current directory
            dir_handler = opendir(".");
            if (dir_handler)
            {
                // if isn't null- print all the dir's files 
                while ((files = readdir(dir_handler)) != NULL){
                    //cout << files->d_name << endl;
                    cout << "\u001b[32;1m" << files->d_name << "\x1B[0m" << endl;
            }
            }
            else {
                cout << "Error" << endl; 
            }  
            closedir(dir_handler); 
            //system("ls");
    }

   /*
   The chdir command is a system function (system call) which is used to change the current 
   */

    if (cmd == "CD") 
    {
        // 
        if (data == ".." || data == "\n")
        {
            //cout <<data << endl;
            chdir("..");
            //getenv
        }
        else {
            //const char *new_cd= data.c_str(); 
            string a = "";
            a.append(data);
            const char *new_cd= a.c_str(); // convert string to const char 
            //cout <<a << endl;
            int check ; 
            cout <<new_cd << endl;
            check = chdir(new_cd);// if directory was change successfully, check=0 , else -1 
            cout << check << endl;
            cout << "after change" << endl;


        }
        //system("cd");

    }

    //copy file from source to dest
    if (cmd == "COPY")
    {
        string src, dst; 
        char buf[BUFSIZ]; //default is 8192 bytes- one char at the time
        size_t size; // BUFFER_SIZE = 4096;
        src = data.substr(0, data.find_first_of(" "));
        dst = data.substr(data.find_first_of(" ") + 1);

        // open src file
        FILE* src_open_file= fopen(src.c_str(), "rb");
        if (src_open_file == NULL)
        {
            cout << "Error" << endl; 
            exit(EXIT_FAILURE);
        }

        // open dest file
        FILE* dst_open_file= fopen(dst.c_str(), "wb");
        if (dst_open_file == NULL)
        {
            fclose(src_open_file);
            cout << "Error" << endl; 
            exit(EXIT_FAILURE);
        }
        // write to the file 
        while (size = fread(buf, 1, BUFSIZ, src_open_file)) {
            fwrite(buf, 1, size, dst_open_file);
    }

    fclose(src_open_file);
    fclose(dst_open_file);


    }

     if(cmd == "DELETE"){
        const char *file_name= data.c_str(); 
        unlink(file_name); 
        cout <<"file deleted successfully" << endl;
     }
    
}
    return 0;

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


