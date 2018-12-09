#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell3.h"

//funkcja czytajaca linie
char *shReadLine(void) {
	char *line = NULL;
	ssize_t buffer = 0;
	getline(&line, &buffer, stdin);
	return line;
}


/*char **shSplitLine(char *line) {
	int bufsize = 64;
	int position = 0;

	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "shell: blad alokacj\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");							//tokenizacja linii

	while (token != NULL) {
		tokens[position] = token;
		position++;

		//jesli przekroczono okreslony wczesniej bufor pamieci
		if (position >= bufsize) {
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char*));	//przydzielenie wiecej pamieci
			if (!tokens) {
				fprintf(stderr, "shell: blad alokacji\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n\a");						//tokenizacja linii
	}
	tokens[position] = NULL;
	return tokens;
}*/
//funkcja tokenizujaca linie na argumenty
char **shSplitLine(char *line) {
	int position = 0;

	char **tokens = malloc(MAX_ARGS_BUFFER_SIZE * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "shell: blad alokacj\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");							//tokenizacja linii

	while (token != NULL) {
		tokens[position] = token;
		position++;

		//jesli przekroczono okreslony wczesniej bufor pamieci
		if (position >= MAX_ARGS_BUFFER_SIZE) {
			puts("Ilosc argumentow przekracza maksymalna mozliwa ilosc.");
		}
		token = strtok(NULL, " \t\r\n\a");						//tokenizacja linii
	}
	tokens[position] = NULL;
	return tokens;
}

//funkcja zwalniajaca pamiec po linii i argumentach
void freeCommands(char* line, char** tokens) {
	free(line);
	free(tokens);
}

//zamiana kolorow wyswietlanego tekstu
void textColorCyan(void) {
	printf("\033[1;36m");
}
void textColorYellow(void) {
	printf("\033[1;33m");
}
void textColorReset(void) {
	printf("\033[0m");
}

void sh_welcome(void) {
	puts("\n\n\t\tWITAJ W SYSTEMIE WYPOZYCZALNI SAMOCHODOW");
	textColorYellow();
	printf("\t\t\tC A R T U R I L O\n\n\n\n\n");
	textColorReset();
	sh_help_addCar();
	sh_help_addUser();
	sh_help_addParkingPlace();
	sh_help_showCars();
	sh_help_showUsers();
	sh_help_showParkingPlaces();
	sh_help_carRent();
	sh_help_carReturn();
	sh_help_deleteCar();
	sh_help_deleteUser();
	sh_help_deleteParkingPlace();
	sh_help_exit();
}

//funkcja wykonujaca polecenia
int sh_commandsExe(char **args, User** _userHead, Car** _carHead, ParkingPlace** _parkingPlaceHead) {
	const int mainCommandIndex = 0;
	char* mainCommands[] = {
		"add-user",				//[0]
		"add-car",				//[1]
		"add-parkingplace",		//[2]
		"rent-car",				//[3]
		"return-car",			//[4]
		"show-cars",			//[5]
		"show-users",			//[6]
		"show-parkingplaces",	//[7]
		"delete-car",			//[8]
		"delete-user",			//[9]
		"delete-parkingplace",	//[10]
		"exit",					//[11]
		"help"					//[12]
	};
	
	if (args[mainCommandIndex] == NULL) { //jesli nie ma polecenia
		puts("Podaj polecenie.");
		return 1;
	}
	if (!strcmp(mainCommands[0], args[mainCommandIndex])) {
		sh_addUser(args, _userHead);
		return 1;
	}
	if (!strcmp(mainCommands[1], args[mainCommandIndex])) {
		sh_addCar(args, _carHead, _userHead, _parkingPlaceHead);
		return 1;
	}
	if (!strcmp(mainCommands[2], args[mainCommandIndex])) {
		sh_addParkingPlace(args, _parkingPlaceHead);
		return 1;
	}
	if (!strcmp(mainCommands[3], args[mainCommandIndex])) {
		sh_carRent(args, _carHead, _userHead, _parkingPlaceHead);
		return 1;
	}
	if (!strcmp(mainCommands[4], args[mainCommandIndex])) {
		sh_carReturn(args, _carHead, _userHead, _parkingPlaceHead);
		return 1;
	}
	if (!strcmp(mainCommands[5], args[mainCommandIndex])) {
		sh_showCars(args, _carHead);
		return 1;
	}
	if (!strcmp(mainCommands[6], args[mainCommandIndex])) {
		sh_showUsers(args, _userHead);
		return 1;
	}
	if (!strcmp(mainCommands[7], args[mainCommandIndex])) {
		sh_showParkingPlaces(args, _parkingPlaceHead);
		return 1;
	}
	if (!strcmp(mainCommands[8], args[mainCommandIndex])) {
		sh_deleteCar(args, _carHead, _userHead, _parkingPlaceHead);
		return 1;
	}
	if (!strcmp(mainCommands[9], args[mainCommandIndex])) {
		sh_deleteUser(args, _userHead);
		return 1;
	}
	if (!strcmp(mainCommands[10], args[mainCommandIndex])) {
		sh_deleteParkingPlace(args, _parkingPlaceHead);
		return 1;
	}
	if (!strcmp(mainCommands[11], args[mainCommandIndex])) {
		puts("WYJSCIE");
		freeDatabase(_carHead, _userHead, _parkingPlaceHead);
		return 0;
	}
	if (!strcmp(mainCommands[12], args[mainCommandIndex])) {
		sh_help(args);
		return 1;
	}
	puts("Nie ma takiego polecenia.\n");
}

//funkcje pomocy
int sh_help(char **args) {
	const int maxNumOfArgs = 2;
	const int mainCommandHelpIndex = 1;
	char* mainCommands[] = {
		"add-user",				//[0]
		"add-car",				//[1]
		"add-parkingplace",		//[2]
		"rent-car",				//[3]
		"return-car",			//[4]
		"show-cars",			//[5]
		"show-users",			//[6]
		"show-parkingplaces",	//[7]
		"delete-car",			//[8]
		"delete-user",			//[9]
		"delete-parkingplace",	//[10]
		"exit"					//[11]
	};
	if (args[maxNumOfArgs] != NULL) {
		puts("Niepoprawna skladnia - za wiele argumentow.");
			return 0;
	}
	if (args[maxNumOfArgs - 1] == NULL) {
		puts("POMOC");
		textColorCyan();
		printf("Komenda ");
		textColorYellow();
		printf("[argumenty] ");
		textColorReset();
		printf("+opis dzialania\n\n");

		sh_help_addCar();
		sh_help_addUser();
		sh_help_addParkingPlace();
		sh_help_showCars();
		sh_help_showUsers();
		sh_help_showParkingPlaces();
		sh_help_carRent();
		sh_help_carReturn();
		sh_help_deleteCar();
		sh_help_deleteUser();
		sh_help_deleteParkingPlace();
		return 1;
	}
	else {
		if (!strcmp(mainCommands[0], args[mainCommandHelpIndex])) {
			sh_help_addUser();
			return 1;
		}
		if (!strcmp(mainCommands[1], args[mainCommandHelpIndex])) {
			sh_help_addCar();
			return 1;
		}
		if (!strcmp(mainCommands[2], args[mainCommandHelpIndex])) {
			sh_help_addParkingPlace();
			return 1;
		}
		if (!strcmp(mainCommands[3], args[mainCommandHelpIndex])) {
			sh_help_carRent();
			return 1;
		}
		if (!strcmp(mainCommands[4], args[mainCommandHelpIndex])) {
			sh_help_carReturn();
			return 1;
		}
		if (!strcmp(mainCommands[5], args[mainCommandHelpIndex])) {
			sh_help_showCars();
			return 1;
		}
		if (!strcmp(mainCommands[6], args[mainCommandHelpIndex])) {
			sh_help_showUsers();
			return 1;
		}
		if (!strcmp(mainCommands[7], args[mainCommandHelpIndex])) {
			sh_help_showParkingPlaces();
			return 1;
		}
		if (!strcmp(mainCommands[8], args[mainCommandHelpIndex])) {
			sh_help_deleteCar();
			return 1;
		}
		if (!strcmp(mainCommands[9], args[mainCommandHelpIndex])) {
			sh_help_deleteUser();
			return 1;
		}
		if (!strcmp(mainCommands[10], args[mainCommandHelpIndex])) {
			sh_help_deleteParkingPlace();
			return 1;
		}
		puts("Nie ma takiego polecenia.\n");
		
	}
}
void sh_help_addCar(void) {
	textColorCyan();
	printf("add-car ");
	textColorYellow();
	printf("[numer tablicy rejestracyjnej] [data ostatniego przegladu] [data nastepnego przegladu] [ID miejsca postojowego, na ktore dodajemy samochod]\n");
	textColorReset();
	puts("Dodawanie samochodu o okreslonych danych do bazy.");
	puts("\t(numer tablicy rejestracyjnej powinien byc napisany lacznie (np. EL733PX))");
	puts("\t(daty powinny byc napisane w formacie dd/mm/yyyy)\n");
}
void sh_help_addUser(void) {
	textColorCyan();
	printf("add-user ");
	textColorYellow();
	printf("[stan konta]\n");
	textColorReset();
	puts("Dodawanie do bazy danych uzytkownika wraz z poczatkowym stanem konta.\n");
}
void sh_help_addParkingPlace(void) {
	textColorCyan();
	printf("add-parkingplace ");
	textColorYellow();
	printf("[adres]\n");
	textColorReset();
	puts("\tDodatwanie do bazy danych miejsca postojowego wraz z adresem.\n");
}
void sh_help_showCars(void) {
	textColorCyan();
	printf("show-cars ");
	textColorYellow();
	printf("[/ free / parked / user] [/  / ID miejsca postojowego / ID uzytkownika]\n");
	textColorReset();
	puts("\tWyswietlenie danych samochodow z bazy:");
	puts("\twszystkich / niewypozyczonych / zaparkowanych na danym po ID miejscu parkingowym / wypozyczonych przez danego po ID uzytkownika.\n");
}
void sh_help_showUsers(void) {
	textColorCyan();
	printf("show-users ");
	textColorYellow();
	printf("[/ free / renting / car] [/  /  / ID samochodu]\n");
	textColorReset();
	puts("Wyswietlenie danych uzytkownikow z bazy:");
	puts("\twszystkich / niewypozyczajacych / wypozyczajacych / wypozyczajacych dany samochod.\n");
}
void sh_help_showParkingPlaces(void) {
	textColorCyan();
	printf("show-parkingplaces ");
	textColorYellow();
	printf("[/ free / car] [/  / ID samochodu]\n");
	textColorReset();
	puts("Wyswietlenie danych miejsc postojowych z bazy:");
	puts("\twszystkich / wolnych / na ktorych znajduje sie dany po ID samochodo.\n");
}
void sh_help_carRent(void) {
	textColorCyan();
	printf("rent-car ");
	textColorYellow();
	printf("[ID samochodu] [ID uzytkownika]\n");
	textColorReset();
	puts("Wypozyczenie samochodu danego po ID przez danego po ID uzytkownika.\n");
}
void sh_help_carReturn(void) {
	textColorCyan();
	printf("return-car ");
	textColorYellow();
	printf("[ID uzytkownika] [ID miejsca postojowego]\n");
	textColorReset();
	puts("Zwrocenie samochodu wypozyczanego przez danego po ID uzytkownika na miejsce postojowe dane po ID. Jednoczesnie konto uzytkownika obciazane jest kosztem wypozyczenia.\n");
}
void sh_help_deleteCar(void) {
	textColorCyan();
	printf("delete-car ");
	textColorYellow();
	printf("[ID samochodu]\n");
	textColorReset();
	puts("Usuniecie z bazy samochodu danego po ID. Samochod nie moze byc w tym czasie wypozyczony.\n");
}
void sh_help_deleteUser(void) {
	textColorCyan();
	printf("delete-user ");
	textColorYellow();
	printf("[ID uzytkownika]\n");
	textColorReset();
	puts("Usuniecie z bazy uzytkownika danego po ID. Uzytkownik nie moze w tym czasie miec wypozyczonego zadnego samochodu.\n");
}
void sh_help_deleteParkingPlace(void) {
	textColorCyan();
	printf("delete-parkingplace ");
	textColorYellow();
	printf("[ID miejsca postojowego]\n");
	textColorReset();
	puts("Usuniecie z bazy miejsca postojowego danego po ID. Na miejscu postojowym nie moga znajdowac sie zadne samochody.\n");
}
void sh_help_exit(void) {
	textColorCyan();
	printf("exit\n");
	textColorReset();
	puts("Wyjscie z programu");
}

int sh_addCar(char **args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead) {
	const int maxNumOfArgs = 5;			//ilosc argumentow jaka musi sie znalezc w poleceniu
	if (args[maxNumOfArgs] != NULL) {	//jesli jest wiecej
		puts("Niepoprawna skladnia, za duzo argumentow - nie dodano samochodu.");
		sh_help_addCar();
		return 0;
	}
	int carID = addCar(_carHead);
	int errCheck = addCarLicensePlate(args[1], _carHead, carID) && addCarLastCheckDate(args[2], _carHead, carID) && addCarNextCheckDate(args[3], _carHead, carID) && addCarParkingPlace(args[4], _carHead, carID, _parkingPlaceHead);

	if(!errCheck){
		puts("Niepoprawna skladnia - nie dodano samochodu");
		sh_help_addCar();
		char strCarID[ID_MAX_CHAR_NUMBER];
		sprintf(strCarID, "%d", carID);
		deleteCar(_carHead, strCarID, _userHead, _parkingPlaceHead);
		return 0;
	}
	printf("Dodano samochod - ID: %d\n\n", carID);
	return 1;
}

int sh_addUser(char **args, User** _userHead) {
	const int maxNumOfArgs = 2;			//ilosc argumentow jaka musi sie znalezc w poleceniu
	if (args[maxNumOfArgs] != NULL) {	//jesli jest wiecej
		puts("Niepoprawna skladnia, za duzo argumentow - nie dodano samochodu.");
		sh_help_addUser();
		return 0;
	}
	int userID = addUser(_userHead);
	int errCheck = addUserMoney(args[1], _userHead, userID);
	if (!errCheck) {
		puts("Niepoprawna skladnia - nie dodano uzytkownika");
		sh_help_addUser();
		char strUserID[ID_MAX_CHAR_NUMBER];
		sprintf(strUserID, "%d", userID);
		deleteUser(strUserID, _userHead);
		return 0;
	}
	printf("Dodano uzytkownika - ID: %d\n\n", userID);
	return 1;
}

int sh_addParkingPlace(char **args, ParkingPlace** _parkingPlaceHead) {
	int parkingPlaceID = addParkingPlace(_parkingPlaceHead);
	int errCheck = addParkingPlaceAddress(args, _parkingPlaceHead, parkingPlaceID);
	if (!errCheck) {
		puts("Niepoprawna skladnia - nie dodano miejsca postojowego.");
		sh_help_addParkingPlace();;
		char strParkingPlaceID[ID_MAX_CHAR_NUMBER];
		sprintf(strParkingPlaceID, "%d", parkingPlaceID);
		deleteParkingPlace(strParkingPlaceID, _parkingPlaceHead);
		return 0;
	}
	printf("Dodano miejsce postojowe - ID: %d\n\n", parkingPlaceID);
	return 1;
}

int sh_showCars(char** args, Car** _carHead) {
	char* showCarsOpt[] = {							//mozliwe opcje polecenia
		"free",
		"parked",
		"user",
		"upcomingcheck"
	};

	if (args[1] == NULL) {							//pokaz wszystkie samochody - wpisano samo show-cars
		return showCarsAll(_carHead);
	}
	else {
		if (strcmp(args[1], showCarsOpt[0]) == 0) {		//pokaz wolne samochody
			return showCarsFree(_carHead);
		}
		if (strcmp(args[1], showCarsOpt[1]) == 0) {		//pokaz zaparkowane samochody - w kolejnym argumencie musi byc miejsce postojowe, ktore chce sie sprawdzic
			return showCarsParked(_carHead, args[2]);
		}
		if (strcmp(args[1], showCarsOpt[2]) == 0) {		//pokaz samochod danego uzytkownika
			return showCarsUser(_carHead, args[2]);
		}
		if (strcmp(args[1], showCarsOpt[3]) == 0) {
			return showUpcomingCheckCars(_carHead);
		}
		puts("Nie ma takiego polecenia.\n");
		sh_help_showCars();
	}
}

//funkcja obslugujaca polecenie wyswietlania uzytkownikow
int sh_showUsers(char** args, User** _userHead) {
	char* showUsersOpt[] = {						//mozliwe opcje polecenia
	"free",
	"renting",
	"car"
	};
	if (args[1] == NULL) {							//pokaz wszystkie samochody - wpisano samo show-cars
		return showUsersAll(_userHead);
	}
	if (strcmp(args[1], showUsersOpt[0]) == 0) {		//pokaz wolne samochody
		return showUsersFree(_userHead);
	}
	if (strcmp(args[1], showUsersOpt[1]) == 0) {		//pokaz zaparkowane samochody - w kolejnym argumencie musi byc miejsce postojowe, ktore chce sie sprawdzic
		return showUsersRenting(_userHead);
	}
	if (strcmp(args[1], showUsersOpt[2]) == 0) {		//pokaz samochod danego uzytkownika
		return showUsersCar(_userHead, args[2]);
	}
	puts("Nie ma takiego polecenia.");
	sh_help_showUsers();
}

//funkcja obslugujaca polecenie wyswietlania miejsc postojowych
int sh_showParkingPlaces(char** args, ParkingPlace** _parkingPlaceHead) {
	char* showParkingPlacesOpt[] = {
		"free",
		"car"
	};

	if (args[1] == NULL) {							//pokaz wszystkie samochody - wpisano samo show-cars
		return showParkingPlacesAll(_parkingPlaceHead);
	}
	if (strcmp(args[1], showParkingPlacesOpt[0]) == 0) {		//pokaz wolne samochody
		return showParkingPlacesFree(_parkingPlaceHead);
	}
	if (strcmp(args[1], showParkingPlacesOpt[1]) == 0) {		//pokaz zaparkowane samochody - w kolejnym argumencie musi byc miejsce postojowe, ktore chce sie sprawdzic
		return showParkingPlacesCar(_parkingPlaceHead, args[2]);
	}
	puts("Nie ma takiego polecenia.");
	sh_help_showParkingPlaces();

}

//funckja wypozyczajaca samochod
int sh_carRent(char** args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead) {
	if (rentCar(args[1], _carHead, args[2], _userHead, _parkingPlaceHead)) {
		puts("Poprawnie wypozyczono samochod.");
		return 1;
	}
	else {
		puts("Niepoprawna skladnia polecenia - nie wypozyczono samochodu.");
		sh_help_carRent();
		return 0;
	}
}

//funckja zwracajaca samochod
int sh_carReturn(char** args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead) {
	const int maxNumOfArgs = 3;			//ilosc argumentow jaka musi sie znalezc w poleceniu
	if (args[maxNumOfArgs] != NULL) {	//jesli jest wiecej
		puts("Niepoprawna skladnia, za duzo argumentow - nie dodano samochodu.");
		sh_help_carReturn();
		return 0;
	}

	if (returnCar(_carHead, args[1], _userHead, args[2], _parkingPlaceHead)) {
		printf("Poprawnie zwrocono samochod na miejsce postojowe.\nKonto uzytkownika zostalo obciazone kwota: %d\n\n", RENT_PRICE);
		return 1;
	}

	else {
		puts("Niepoprawna skladnia polecenia - nie zwrocono samochodu.");
		sh_help_carReturn();
		return 0;
	}
}

//funkcja usuwajaca samochod
int sh_deleteCar(char** args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead) {
	if (deleteCar(_carHead, args[1], _userHead, _parkingPlaceHead)) {
		printf("Usunieto samochod - ID: %s\n\n", args[1]);
		return 1;
	}
	else {
		sh_help_deleteCar();
		return 0;
	}
}

//funckja usuwajaca uzytkownika
int sh_deleteUser(char** args, User** _userHead) {
	if (deleteUser(args[1], _userHead)) {
		printf("Usunieto uzytkownika - ID: %s\n\n", args[1]);
		return 1;
	}
	else {
		sh_help_deleteUser();
		return 0;
	}
}

//funkcja usuwajaca miejsce postojowe
int sh_deleteParkingPlace(char** args, ParkingPlace** _parkingPlaceHead) {
	if (deleteParkingPlace(args[1], _parkingPlaceHead)) {
		printf("Usunieto miejsce postojowe - ID: %s\n\n", args[1]);
		return 1;
	}
	else {
		sh_help_deleteParkingPlace();
		return 0;
	}
}
