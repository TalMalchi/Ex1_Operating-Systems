#include <iostream>
#include <errno.h>
#include <string>
#include <strings.h>
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
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/wait.h>
#include <netinet/tcp.h>
#include <math.h>



using namespace std;

#define SIZE 1024


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
                //cout << data << endl;
                //system("echo"); //need to add data
                    pid_t ch_pid = fork();

        //// if pid == -1, fork faild
        if (ch_pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);

        } 
        //////// if pid >0 , I'm parent
        else if (ch_pid > 0) {
            cout << "spawn child with pid - " << ch_pid << endl;
            wait(NULL); 
            cout<< "atfer waiting" <<endl; 


            //return ch_pid;
            }

        //////// if pid ==0 , I'm child
        else {
            //const char* cmd_fork= cmd.c_str(); 
            char* a = "echo"; 
            char* args[2]= {(char*)a , NULL}; //////////// need to do another file for this function 
            cout<< "got here!!!!!" <<endl; 
            execv(args[0], args);
            cout<< "got here" <<endl; 
            perror("execve");
            exit(EXIT_FAILURE);
        }
}

        //}

        if (cmd == "TCP")
        {



        struct sockaddr_in dest_info;

        // ------------------------------------------------------------
        // STEP 1: Open Socket TCP
        // ------------------------------------------------------------
        int sockfd = socket(AF_INET, SOCK_STREAM /*TCP*/, 0);
        if (sockfd == -1)
        {
            printf("\t------ open socket FAILED ------\n");
            exit(0);
        }
        printf("\t------ Socket created SUCCEES ------\n");

        // all the data dest are reload to "dest_info"
        dest_info.sin_family = AF_INET;         /*sending type - IpV6*/ //tells which way to pass the information
        dest_info.sin_addr.s_addr = INADDR_ANY; /*read all interfaces*/ //socket that send information // 
        dest_info.sin_port = 8080;              /*protocol kind*/

        bzero(&dest_info, sizeof(dest_info)); // turn &dest_info to "0" --> (need before reload)


        // ------------------------------------------------------------
        // STEP 2: Conection with - measure
        // ------------------------------------------------------------
        int check = connect(sockfd, (struct sockaddr *)&dest_info, sizeof(dest_info)); // if == 0 => is connected
        if (check != 0)
        {
            printf("\t------ connection FAILED ------\n");
            exit(0);
        }
        printf("\t------ connection SUCCEES ------\n");

        //char data1[SIZE] = data; /*Send FILE*/
        const void* a= data.c_str();
        int i=0;
        while(i<10)
        {
            send(sockfd , a , sizeof(a) , 0 ); 
            printf("Message sent\n"); 
            //valread = read( sockfd , buffer, 1024); 
            //printf("%s\n",buffer );
            i++;
        }
                

                // ------------------------------------------------------------
                // STEP 6: Close conection
                // ------------------------------------------------------------
                close(sockfd);
            }

        //}
        //system("./server");
        

        if(cmd == "LOCAL")
        {
        }

        if (cmd == "DIR") /// check the different between file and directory
        {
            // DIR *dir_handler;
            // struct dirent *files;
            // // open the current directory
            // dir_handler = opendir(".");
            // if (dir_handler)
            // {
            //     // if isn't null- print all the dir's files 
            //     while ((files = readdir(dir_handler)) != NULL){
            //         //cout << files->d_name << endl;
            //         cout << "\u001b[32;1m" << files->d_name << "\x1B[0m" << endl;
            // }
            // }
            // else {
            //     cout << "Error" << endl; 
            // }  
            // closedir(dir_handler); 
            system("ls");
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

}
    

    ////////////// fork /////////////

//     pid_t ch_pid = fork();

//     //// if pid == -1, fork faild
//     if (ch_pid == -1) {
//         perror("Fork failed");
//         exit(EXIT_FAILURE);

//     } 
//     //////// if pid >0 , I'm parent
//     else if (ch_pid > 0) {
//         cout << "spawn child with pid - " << ch_pid << endl;
//         return ch_pid;
//         }

//     //////// if pid ==0 , I'm child
//     else {
//         //const char* cmd_fork= cmd.c_str(); 
//         char* args[2]= {(char*)cmd.c_str(), NULL}; //////////// need to do another file for this function 
//         execvp(args[0], args);
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
//}

