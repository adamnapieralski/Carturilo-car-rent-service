#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell3.h"
#include "database3.h"


void main(void){
	Car *carHead = NULL;					//glowa listy samochodow
	ParkingPlace *parkingPlaceHead = NULL;	//glowa listy miejsc postojowych
	User *userHead = NULL;					//glowa listy uzytkownikow
	int exit = 1;
	char *line;								//wskaznik na linie wpisywane w wierszu polecen
	char **args;							//wskaznik na argumenty wyczytane z linii
	sh_welcome();
	//dopoki uzytkownik nie chce wyjsc
	do {
		line = shReadLine();
		args = shSplitLine(line);
		exit = sh_commandsExe(args, &userHead, &carHead, &parkingPlaceHead);
		freeCommands(line, args);

	} while (exit);
	freeCommands(line, args);
}