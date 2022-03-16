#include <iostream>
#include <string>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

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
                // if isn't- print all the dir's files 
                while ((files = readdir(dir_handler)) != NULL){
                    cout << files->d_name << endl;
            }
            }
            else {
                cout << "Error" << endl; 
            }  
            closedir(dir_handler); 
    }

    if (cmd == "CD")
    {
        if (data == ".." || data == "\n")
        {
            chdir("..");
            //getenv
        }
    }
}
    return 0;
}
