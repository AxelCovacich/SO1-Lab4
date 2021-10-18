cflags= -Wall -Werror -pedantic -g

myshell: main.o utils.o shell.o
	gcc $(cflags) -o myshell main.o utils.o shell.o -lreadline

main.o: main.c utils.h shell.h
	gcc $(cflags) -c main.c
	
utils.o: utils.c utils.h
	gcc $(cflags) -c utils.c

shell.o: shell.c shell.h utils.h
	gcc $(cflags) -c shell.c

clean: 
		rm *.o myshell