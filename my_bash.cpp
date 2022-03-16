#include <iostream>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

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
}
    return 0;

    ////////////// fork /////////////

    pid_t ch_pid = fork();

    if (ch_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);

    } 
    ////////parent
    else if (ch_pid > 0) {
        cout << "spawn child with pid - " << ch_pid << endl;
        return ch_pid;
        }

    ////////child 
    else {
        execve(program, arg_list, nullptr);
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

