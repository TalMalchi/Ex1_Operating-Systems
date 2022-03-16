#include <iostream>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <cstdio>

using namespace std;

int main(int argc, const char **argv)
{

    // get current lib
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    cout << cwd << ": " << endl;

    cout << "Yes Master ? " << endl;

    // get input from the user
    string line, cmd, data;
    while (cmd != "EXIT")
    {
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
            system("echo"); //need to add data

        }
        if (cmd == "TCP PORT")
        {
        }
        if (cmd == "LOCAL")
        {
        }
        if (cmd == "DIR")
        {
            DIR *dir_handler;
            struct dirent *files;
            // open the current directory
            dir_handler = opendir(".");
            if (dir_handler)
            {
                // if isn't null- print all the dir's files 
                while ((files = readdir(dir_handler)) != NULL){
                    cout << files->d_name << endl;
            }
            }
            else {
                cout << "Error" << endl; 
            }  
            closedir(dir_handler); 
            system("ls");
    }

    if (cmd == "CD")
    {
        if (data == ".." || data == "\n")
        {
            chdir("..");
            //getenv
        }
        system("cd");

    }
    //copy file from source to dest
    if (cmd == "COPY")
    {
    //     string src, dst; 
    //     char buf[BUFSIZ]; //default is 8192 bytes- one char at the time
    //     size_t size; // BUFFER_SIZE = 4096;
    //     src = data.substr(0, data.find_first_of(" "));
    //     dst = data.substr(data.find_first_of(" ") + 1);

    //     // open src file
    //     FILE* src_open_file= fopen(src, "r");
    //     if (src_open_file == NULL)
    //     {
    //         cout << "Error" << endl; 
    //         exit(EXIT_FAILURE);
    //     }
        
    //     FILE* dst_open_file= fopen(dst, "w");
    //     if (dst_open_file == NULL)
    //     {
    //         fclose(src_open_file);
    //         cout << "Error" << endl; 
    //         exit(EXIT_FAILURE);
    //     }

    //     while (size = fread(buf, 1, BUFSIZ, src_open_file)) {
    //         fwrite(buf, 1, size, dst_open_file);
    // }

    // fclose(src_open_file);
    // fclose(dst_open_file);


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

