cflags= -Wall -Werror -pedantic

myshell: main.o utils.o 
	gcc $(cflags) -o myshell main.o utils.o -lreadline

main.o: main.c utils.h
	gcc $(cflags) -c main.c
	
utils.o: utils.c utils.h
	gcc $(cflags) -c utils.c

clean: 
		rm *.o myshell