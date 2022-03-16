#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "my_shell.h"


int main(char **argv, int ar){

char *shell;   //creating a var which hold all the input data

while(1){

fprintf(stderr, "$ ");

shell = readFromShell();

if(!shell){

    exit(EXIT_SUCCESS);  // if we didnt read nothing using the readFromShall func we need to exit

}

if(strcmp(shell,"\n") == 0 || shell[0] == '\0'){  //change the "\0"  // if the user
                                                                      // just press enter we are going down in the shall  
     free(shell);  
    continue;   
}
if(strcmp(shell, "exit\n") == 0){
    free(shell);
    break;
}

printf("%s\n",shell); // if none of the above happen we want to display the message
free(shell); // and ofcourse everytime we finish to deal with the information we got we free it from our memory

}

}




char * readFromShell(void){

char buffer[512];
char *pointer = NULL;
char ptr_size = 0;


while(fgets(buffer,512, stdin)){

    int buf_size = strlen(buffer);

    if(!pointer){                  // checking if there is somthing in the pointer, if dont we give him space
                                   // buf_size +2 because we add the "$" sign.     
        pointer = malloc(buf_size+2);

    }

    else {                          // if the pointer is already in use we want to realoc for it 
                                    // the same place in memory but maybe a bigger one
        char *new_ptr = realloc(pointer, ptr_size+buf_size+2);

        if(new_ptr){  //if the memory allocation went well , we want to use only the main pointer, because 
                      // we can use it in any place in the function  

            pointer = new_ptr;
        }        
        else{
            free(pointer);
            pointer = NULL;
        }
    }

    if(!pointer){

        printf("Error: faild in attempt to allocate memory in buffer size, please try again! \n");
        return NULL;
    }

strcpy(pointer+ptr_size,buffer);  // after we allocate space we copy all the data from the buffer to the pointer

if(buffer[buf_size-1] == '\n'){

    return pointer;
    
}









}



}