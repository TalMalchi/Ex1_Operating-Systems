# Ex1_Operating-Systems
* Written by Guy Azoulay - 207709734 
             Tal Malchi -  208278556

In this assigment we asked to built our own shell, we chose to implement this assigment in CPP languge.

## Main Goal Of The Project
The main goal of this project is deep understanding of how a simple shell is actually works.

We were implemented commends like:
* ECHO
* DIR
* CD
* TCP connection between client and server
* Delete files
* Copy files

The implementaion in our project is in a three different ways:
* Using code only
* Using the System commends
* Using forks

While we wrote this project we achived a good knowledge of what is happaning behind the scene when we
are using the system commend or fork commend.
At first, it was a little bit difficult to understand how truly the fork commends actually works,
but after a little bit research in the internet and previous lessons, we achived our main goal : Runnig shell using different kind og implementaion.


## Explenation about the Shell class:

Our shell class is devided to 3 parts as we mention earlier.
In aim to create a differences between those 3, command with capital letters will be implemented via the basic code part,
and commends as we use to write to any type of shell will be in lower case type via the system commends or the fork commends.


## How to run?

So how do we run this project?

first of all we need to compile both of the cpp files:
* In aim compile the shell : g++ my_bash.cpp -o my_bash
* In aim to compile the server : g++ server.cpp -o server

Now we create 2 exe files, we simply type in the first terminal "   ./my_bash    "
and in the other "    ./server    ", now you can use all the commends above in aim
to see how this project works.


We attaching a simple video which explain how to run this program:
https://user-images.githubusercontent.com/87694635/161732931-0f4ae0b9-0447-4b8b-9397-d565e71ffba3.mp4












