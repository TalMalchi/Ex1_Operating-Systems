CXX= g++
LDFLAGS= -g

all:run

#run: server mybash
run:  my_bash.o server.o main.o
	g++ -o run server.o my_bash.o main.o




# server: server.o 
# 	g++ -o server server.o

# mybash: mybash.o
# 	g++ -o mybash my_bash.o 

mybash.o: my_bash.cpp my_shell.h
	g++ -c my_bash.cpp


server.o: server.cpp my_shell.h
	g++ -c server.cpp 

main.o: main.cpp my_shell.h
	g++ -c main.cpp

clean:
	rm -f server mybash my_bash.o server.o

