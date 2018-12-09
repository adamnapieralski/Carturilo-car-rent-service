Carturilo: Carturilo.o shell3.o database3.o
	gcc Carturilo.o shell3.o database3.o -o Carturilo

database.o: database3.c database3.h
	gcc -c database3.c

shell.o: shell3.c shell3.h database3.h
	gcc -c shell3.c

Carturilo.o: Carturilo.c shell3.h database3.h
	gcc -c Carturilo.c