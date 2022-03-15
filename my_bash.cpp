#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

int main(int argc, const char *argv[])
{

    cout << "Yes Master ? " << endl;

    //get current lib
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    cout << cwd << ": " << endl;

    //get input from the user
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
        if(cmd == "ECHO"){

        }
        if(cmd == "TCP PORT"){
            
        }
        if(cmd == "LOCAL"){
            
        }
        if(cmd == "DIR"){
            
        }
        if(cmd == "CD"){
            
        }
    }
}