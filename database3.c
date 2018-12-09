#include "database3.h"

//funkcja sprawdzajaca czy string jest liczba double
int checkIfDouble(char* _string) {
	int dotOccured = 0;
	if (strncmp(_string, "-", strlen("-")) == 0) {				//jesli wykryto na poczatku '-' - liczba ujemna
		*_string++;
		while (*_string) {										//dopoki jest string
			if (strncmp(_string, ".", strlen(".")) == 0) {		//jesli wykryto kropke
				++dotOccured;
				*_string++;
			}
			else {
				if (isdigit(*_string) == 0) {					//jesli znak nie jest liczba
					*_string++;
					return 0;
				}
				else
					*_string++;
			}
			if (dotOccured > 1) {
				return 0;
			}
		}
		return 1;
	}
	else {														//jesli nie ma '-' na poczatku - liczba nieujemna
		while (*_string) {
			if (strncmp(_string, ".", strlen(".")) == 0) {		//jesli wykryto kropke
				++dotOccured;
				*_string++;
			}
			else {
				if (isdigit(*_string) == 0) {					//jesli znak nie jest liczba
					*_string++;
					return 0;
				}
				else
					*_string++;
			}
			if (dotOccured > 1)
				return 0;
		}
		return 1;
	}
}

//funkcja konwertujaca date na unikalna liczbe - stamp
int dateStampCreate(int _dd, int _mm, int _yyyy) {
	return _yyyy * 10000 + _mm * 100 + _dd;
}

//zamiana dwoch liczb (int) w tablicy - uzywana do algorytmu sortowania
void swapInt(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//wyszukiwanie samochodu o podanym ID
int searchForCar(Car** _carHead, Car** _currentCar, unsigned int _carID) {
	*_currentCar = *_carHead;							//sprawdzany samochod - zaczynamy od poczatku listy
	if (*_currentCar != NULL) {
		while ((*_currentCar)->carID != _carID) {			//dopoki id sprawdzanego samochodu nie bedzie rowne poszukiwanemu id
			if ((*_currentCar)->nextCar != NULL) {			//jesli istnieje kolejny samochod na liscie
				(*_currentCar) = (*_currentCar)->nextCar;	//sprawdzaj kolejny samochod
			}
			else {											//jesli nie istnieje - nie znaleziono danego samochodu
				puts("Nie znaleziono danego samochodu.");
				return 0;
			}
		}
		return 1;
	}
	puts("Nie znaleziono danego samochodu.");
	return 0;
}

//wyszukiwanie zaparkowanego samochodu o podanym ID
int searchForCarParked(CarParked** _carParkedHead, CarParked** _currentCarParked, unsigned int _carParkedID) {
	*_currentCarParked = *_carParkedHead;								//sprawdzany samochod - zaczynamy od poczatku listy
	if (*_currentCarParked != NULL) {
		while ((*_currentCarParked)->carParkedID != _carParkedID) {			//dopoki id sprawdzanego samochodu nie bedzie rowne poszukiwanemu id
			if ((*_currentCarParked)->nextCarParked != NULL) {				//jesli istnieje kolejny samochod na liscie
				(*_currentCarParked) = (*_currentCarParked)->nextCarParked;	//sprawdzaj kolejny samochod
			}
			else {															//jesli nie istnieje - nie znaleziono danego samochodu
				puts("Nie znaleziono danego samochodu.");
				return 0;
			}
		}
		return 1;
	}
	else {
		puts("Nie znaleziono danego samochodu.");
		return 0;
	}

}

//wyszukiwanie uzytkownika o podanym ID
int searchForUser(User** _userHead, User** _currentUser, unsigned int _userID) {
	*_currentUser = *_userHead;								//sprawdzany uzytkownik - zaczynamy od poczatku listy
	if (*_currentUser != NULL) {
		while ((*_currentUser)->userID != _userID) {			//dopoki ID sprawdzanego uzytkownika nie bedzie rowne poszukiwanemu ID
			if ((*_currentUser)->nextUser != NULL) {			//jest istnieje kolejny uzytkownik na liscie
				(*_currentUser) = (*_currentUser)->nextUser;	//sprawdzaj kolejnego uzytkownika
			}
			else {												//jesli nie istnieje - nie znaleziono danego uzytkownika
				puts("Nie znaleziono danego uzytkownika");
				return 0;
			}
		}
		return 1;
	}
	else {														//jesli nie istnieje - nie znaleziono danego uzytkownika
		puts("Nie znaleziono danego uzytkownika");
		return 0;
	}

}

//wyszukiwanie miejsca postojowego o podanym ID
int searchForParkingPlace(ParkingPlace** _parkingPlaceHead, ParkingPlace** _currentParkingPlace, unsigned int _parkingPlaceID) {
	*_currentParkingPlace = *_parkingPlaceHead;											//sprawdzane miejsce - zaczynamy od poczatku listy
	if (*_currentParkingPlace != NULL) {
		while ((*_currentParkingPlace)->parkingPlaceID != _parkingPlaceID) {			//dopoki ID sprawdzanego miejsca nie bedzie rowne poszukiwanemu ID
			if ((*_currentParkingPlace)->nextParkingPlace != NULL) {					//jest istnieje kolejne miejsce na liscie
				(*_currentParkingPlace) = (*_currentParkingPlace)->nextParkingPlace;	//sprawdzaj kolejne miejsce
			}
			else {																		//jesli nie istnieje - nie znaleziono danego miejsca
				puts("Nie znaleziono danego miejsca postojowego.");
				return 0;
			}
		}
		return 1;
	}
	else {
		puts("Nie znaleziono danego miejsca postojowego.");
		return 0;
	}

}

//dodawanie nowego uzytkownika
int addUser(User** _userHead) {
	User* newUser = (User*)malloc(sizeof(User));	//zaalokuj pamiec na nowego uzytkownika
	User *tempUser = *_userHead;					//utworzenie pomocniczego wskaznika na uzytkownika do znalezienia ostatniego uzytkownika na liscie

	newUser->nextUser = NULL;						//nowy uzytkownik bedzie ostatnim elementem listy
	newUser->accountBalance = 0.;
	newUser->carRentedID = 0;
	if (*_userHead == NULL) {						//jesli lista jest pusta
		newUser->userID = USER_FIRST_ID;			//nadaj uzytkownikowi pierwsze ID
		*_userHead = newUser;						//wskaznik na poczatek listy ma wskazywac na nowego uzytkownika
		return newUser->userID;						//zakoncz wykonywanie funkcji
	}
	while (tempUser->nextUser != NULL) {			//dopoki istnieje kolejny element listy
		tempUser = tempUser->nextUser;				//sprawdzaj kolejny element
	}
	newUser->userID = tempUser->userID + 1;			//nadaj nowemu uzytkownikowi ID o jeden wieksze od poprzedniego na uzytkownika na liscie
	tempUser->nextUser = newUser;					//wczesniejszy ostatni element na liscie ma wskazywac na nowego uzytkownika
	return newUser->userID;
}

//dodawanie nowego samochodu
int addCar(Car** _carHead) {
	Car* newCar = (Car*)malloc(sizeof(Car));	//przygotowanie pamieci na dodawany element
	Car *lastCar = *_carHead;					//wskaznik pomocniczy na poprzedni element
	newCar->nextCar = NULL;

	if (*_carHead == NULL) {					//jesli lista nie ma zadnych elementow
		newCar->carID = CAR_FIRST_ID;
		*_carHead = newCar;
		return CAR_FIRST_ID;
	}
	while (lastCar->nextCar != NULL) {			//dopoki nie dojdziemy do konca listy
		lastCar = lastCar->nextCar;
	}
	newCar->carID = lastCar->carID + 1;
	lastCar->nextCar = newCar;
	return newCar->carID;

}

//dodawanie nowego miejsca 
int addParkingPlace(ParkingPlace** _parkingPlaceHead) {
	ParkingPlace* newParkingPlace = (ParkingPlace*)malloc(sizeof(ParkingPlace));	//zaalokuj miejsce na nowa strukture
	ParkingPlace *lastParkingPlace = *_parkingPlaceHead;

	newParkingPlace->nextParkingPlace = NULL;
	newParkingPlace->carParkedHead = NULL;

	if (*_parkingPlaceHead == NULL) {												//jesli w liscie nie ma zadnych elementow
		newParkingPlace->parkingPlaceID = PARKING_PLACE_FIRST_ID;
		*_parkingPlaceHead = newParkingPlace;
		return newParkingPlace->parkingPlaceID;
	}
	while (lastParkingPlace->nextParkingPlace != NULL) {							//iteruj sie po elementach do konca listy
		lastParkingPlace = lastParkingPlace->nextParkingPlace;
	}
	
	newParkingPlace->parkingPlaceID = lastParkingPlace->parkingPlaceID + 1;
	lastParkingPlace->nextParkingPlace = newParkingPlace;
	return newParkingPlace->parkingPlaceID;
}

//dodawanie adresu do danego miejsca postojowego
int addParkingPlaceAddress(char** _strAddress, ParkingPlace** _parkingPlaceHead, unsigned int _parkingPlaceID) {
	if (!_strAddress)
		return 0;

	ParkingPlace *currentParkingPlace = *_parkingPlaceHead;									//pomocniczy wskaznik do wyszukiwania
	const int firstArg = 1;																	//element tablicy argumentow od ktorego zaczyna sie wczytywanie adresu
	int currentArg = firstArg;																//aktualnie odczytywany argument
	int usedCharacters = 0;																	//liczba znakow wykorzystana do napisania adresu
	char finalAddress[ADDRESS_MAX_CHAR_NUMBER] = "";										//adres to wpisania	
	if (!searchForParkingPlace(_parkingPlaceHead, &currentParkingPlace, _parkingPlaceID))	//jesli nie udalo sie znalezc danego elementu listy
		return 0;

	if (_strAddress[currentArg]) {															//jesli aktualny argument nie jest pusty
		//dopoki aktualny argument ma jakas wartosc i jego ilosc znakow nie przekracza reszty znakow mozliwej do wpisania
		while (_strAddress[currentArg] && (strlen(_strAddress[currentArg]) + 1) <= ADDRESS_MAX_CHAR_NUMBER - (strlen(finalAddress) + 1)) {
			strcat(finalAddress, _strAddress[currentArg]);									//dopisz tresc argumentu do finalAddress
			strcat(finalAddress, " ");														//dodaj spacje
			++currentArg;																	//zwieksz sprawdzany aktualny argument
		}
		//jesli argument nadal istnieje, ale jego wpisanie przekroczyloby mozliwe do wpisania znaki
		if (_strAddress[currentArg] && strlen(_strAddress[currentArg]) > ADDRESS_MAX_CHAR_NUMBER - (strlen(finalAddress) + 1)) {
			printf("Adres musi zawrzec sie w %d znakach.\n", ADDRESS_MAX_CHAR_NUMBER);
			return 0;
		}
		strcpy(currentParkingPlace->address, finalAddress);									//zapisz caly zczytany adres do struktury
		return 1;
	}
	//jesli pierwszy argument jest pusty
	else {
		return 0;
	}
}

//funkcja dodajaca pieniadze na konto uzytkownika
int addUserMoney(char* _strUserMoney, User** _userHead, unsigned int _userID) {
	if (!_strUserMoney)								//sprawdz czy istnieja dane do wpisania
		return 0;
	User* currentUser;
	if (!searchForUser(_userHead, &currentUser, _userID)) {
		return 0;
	}
	if (!checkIfDouble(_strUserMoney)) {			//sprawdz czy string jest liczba zmiennoprzecinkowa
		puts("Niepoprawny format danych");
		return 0;									//jesli nie - zwroc blad
	}
	double userMoney = atof(_strUserMoney);			//jesli tak - wczytaj wartosc do zmiennej
	currentUser->accountBalance += userMoney;
	return 1;
}

//funckja usuwajaca samochod o danym ID z listy samochodow zaparkownym na miejscu parkingowym
int deleteParkingPlaceCar(CarParked** _carParkedHead, int _carParkedID) {

	CarParked *currentCarParked = *_carParkedHead;										//pomocniczy wskaznik na strukture
	CarParked *prevCarParked;
	if (currentCarParked != NULL && currentCarParked->carParkedID == _carParkedID) {
		*_carParkedHead = currentCarParked->nextCarParked;								//przypisanie poczatku listy do drugiego wezla
		free(currentCarParked);															//zwolnienie pamieci
		return 1;
	}
	while (currentCarParked != NULL && currentCarParked->carParkedID != _carParkedID) {	//dopoki listy sie nie skonczyla lub nie znalazl elementu o szukanym ID
		prevCarParked = currentCarParked;
		currentCarParked = currentCarParked->nextCarParked;
	}

	if (currentCarParked == NULL)
	{
		puts("Nie znaleziono szukanego samochodu na miejscu postojowym.");
		return 0;
	}
	prevCarParked->nextCarParked = currentCarParked->nextCarParked;						//zamiana wskaznikow na wezly
	free(currentCarParked);
}

//funkcja dodajaca samochod do listy samochodow stojacych na miejscu postojowym
int addCarParked(CarParked** _carParkedHead, unsigned int _carParkedID) {

	CarParked *newCarParked = (CarParked*)malloc(sizeof(CarParked));
	CarParked *lastCarParked = *_carParkedHead;

	newCarParked->nextCarParked = NULL;
	newCarParked->carParkedID = _carParkedID;

	if (*_carParkedHead == NULL) {
		*_carParkedHead = newCarParked;
		return 1;
	}
	while (lastCarParked->nextCarParked != NULL) {
		lastCarParked = lastCarParked->nextCarParked;
	}
	lastCarParked->nextCarParked = newCarParked;
	return 1;


}

//funkcja wypozyczajaca samochod
int rentCar(char* _strCarID, Car** _carHead, char* _strUserID, User** _userHead, ParkingPlace** _parkingPlaceHead) {
	if (_strCarID == NULL) {						//jesli nie ma odpowiednich danych
		puts("Niepoprawny format danych");
		return 0;
	}
	int carID = strtol(_strCarID, NULL, 10);		//konwertuj stringa na inta
	if (carID == 0) {								//jesli konwersja nie przebiegla pomyslnie
		puts("Niepoprawny format danych.");
		return 0;
	}
	if (_strUserID == NULL) {						//jesli nie ma odpowiednich danych
		puts("Niepoprawny format danych");
		return 0;
	}
	int userID = strtol(_strUserID, NULL, 10);		//konwertuj stringa na inta
	if (userID == 0) {								//jesli konwersja nie przebiegla pomyslnie
		puts("Niepoprawny format danych.");
		return 0;
	}

	Car *currentCar;
	if (!searchForCar(_carHead, &currentCar, carID)) {		//wyszukaj samochod
		return 0;
	}

	User *currentUser;
	if (!searchForUser(_userHead, &currentUser, userID)) {	//wyszukaj uzytkownika
		return 0;
	}

	ParkingPlace *currentParkingPlace;
	searchForParkingPlace(_parkingPlaceHead, &currentParkingPlace, currentCar->parkingPlaceID);	//wyszukaj miejsce postojowe szukanego samochodu
	if (currentUser->carRentedID != 0) {
		puts("Uzytkownik ma juz wypozyczony samochod.");
		return 0;
	}
	if (currentCar->userID == 0) {					//jesli samochod nie jest wypozyczony
		currentCar->userID = userID;				//nadaj samochodowi uzytkownika
		currentUser->carRentedID = carID;			//nadaj uzytkownikowi samochod
		currentCar->parkingPlaceID = 0;				//usun samochod z miejsca postojowego
		deleteParkingPlaceCar(&(currentParkingPlace->carParkedHead), carID);	
		return 1;
	}
	else {
		puts("Samochod jest juz wypozyczony");
		return 0;
	}
}

//funkcja zwracajaca samochod
int returnCar(Car** _carHead, char* _strUserID, User** _userHead, char* _strParkingPlaceID, ParkingPlace** _parkingPlaceHead) {
	if (_strUserID == NULL) {						//jesli nie ma odpowiednich danych
		puts("Niepoprawny format danych");
		return 0;
	}
	int userID = strtol(_strUserID, NULL, 10);					//konwertuj stringa na inta
	if (userID == 0) {								//jesli konwersja nie przebiegla pomyslnie
		puts("Niepoprawny format danych.");
		return 0;
	}

	if (_strParkingPlaceID == NULL) {							//jesli nie ma odpowiednich danych
		puts("Niepoprawny format danych");
		return 0;
	}
	int parkingPlaceID = strtol(_strParkingPlaceID, NULL, 10);	//konwertuj stringa na inta
	if (parkingPlaceID == 0) {											//jesli konwersja nie przebiegla pomyslnie
		puts("Niepoprawny format danych.");
		return 0;
	}

	User *currentUser;
	searchForUser(_userHead, &currentUser, userID);

	ParkingPlace *currentParkingPlace;
	searchForParkingPlace(_parkingPlaceHead, &currentParkingPlace, parkingPlaceID);

	Car *currentCar;
	searchForCar(_carHead, &currentCar, currentUser->carRentedID);

	if (currentCar->userID == userID) {
		currentCar->userID = 0;
		currentUser->carRentedID = 0;
		currentUser->accountBalance = currentUser->accountBalance - RENT_PRICE;	//obciazenie konta uzytkownika zdefiniowana kwota
		currentCar->parkingPlaceID = currentParkingPlace->parkingPlaceID;
		addCarParked(&(currentParkingPlace->carParkedHead), currentCar->carID);
		return 1;
	}
	else if (currentCar->userID != 0) {
		puts("Samochod zostal wypozyczony przez innego uzytkownika");
		return 0;
	}
	else {
		puts("Samochod nie zostal wypozyczony");
		return 0;
	}
}

//dodawanie tablicy rejestracyjnej do danego samochodu
int addCarLicensePlate(char *_strLicensePlate, Car** _carHead, int _carID) {
	if (!_strLicensePlate)										//jesli nie ma zadnych danych do wpisania
		return 0;
	Car *currentCar = *_carHead;
	searchForCar(_carHead, &currentCar, _carID);
	strcpy(currentCar->licensePlate, _strLicensePlate);			//zapisz dane w pole struktury
	return 1;
}

//dodawanie daty
int addDate(char* strDate, Date* _date) {
	int dd = 0, mm = 0, yyyy = 0;
	char *endChar;										//wskaznik pomocniczy na koniec ciagu znakow
	dd = strtol(strDate, &endChar, 10);					//wczytanie dnia
	strDate = endChar;
	if (strncmp(strDate, "/", strlen("/")) == 0) {		//jesli potem jest '/'
		strDate = endChar + sizeof(char);
		mm = strtol(strDate, &endChar, 10);
		strDate = endChar;
		if (strncmp(strDate, "/", strlen("/")) == 0) {
			strDate = endChar + sizeof(char);
			yyyy = strtol(strDate, &endChar, 10);
		}
	}

	if (dd > 0 && dd < MAX_DAYS && mm > 0 && mm <= MAX_MONTHS && yyyy >= MIN_YEAR) {
		_date->day = dd;
		_date->month = mm;
		_date->year = yyyy;
		return 1;
	}
	else {
		return 0;
	}
}

//dodawanie daty przegladu danego samochodu
int addCarNextCheckDate(char* _strNextCheckDate, Car** _carHead, unsigned int _carID) {
	if (!_strNextCheckDate)										//jesli nie ma zadnych danych do wpisania
		return 0;
	Car *currentCar = *_carHead;
	searchForCar(_carHead, &currentCar, _carID);
	return addDate(_strNextCheckDate, &currentCar->nextCheck);
}

//dodawanie daty ostatniego przegladu danego samochodu
int addCarLastCheckDate(char* _strLastCheckDate, Car** _carHead, unsigned int _carID) {
	if (!_strLastCheckDate)										//jesli nie ma zadnych danych do wpisania
		return 0;
	Car *currentCar = *_carHead;
	searchForCar(_carHead, &currentCar, _carID);
	return addDate(_strLastCheckDate, &currentCar->lastCheck);
}

//dodawania miejsca postojowego dla samochodu
int addCarParkingPlace(char* _strParkingPlaceID, Car** _carHead, int _carID, ParkingPlace** _parkingPlaceHead) {
	if (!_strParkingPlaceID)										//jesli nie ma zadnych danych do wpisania
		return 0;
	Car *currentCar = *_carHead;
	ParkingPlace *currentParkingPlace = *_parkingPlaceHead;
	CarParked* currentCarParked;
	int parkingPlaceID = strtol(_strParkingPlaceID, NULL, 10);
	if (parkingPlaceID == 0) {
		puts("Niepoprawny numer miejsca postojowego");
		return 0;
	}
	//jesli znaleziono szukany samochod i miejsce postojowe
	if (searchForCar(_carHead, &currentCar, _carID) && searchForParkingPlace(_parkingPlaceHead, &currentParkingPlace, parkingPlaceID)) {
		currentCar->parkingPlaceID = parkingPlaceID;
		addCarParked(&currentParkingPlace->carParkedHead, _carID);
		return 1;
	}
	else return 0;
}

//funkcja usuwajaca samochod
int deleteCar(Car** _carHead, char* _strCarID, User** _userHead, ParkingPlace** _parkingPlaceHead) {
	Car *currentCar = *_carHead;
	Car *prevCar = NULL;
	ParkingPlace *currenParkingPlace = NULL;
	//zamiana stringa na inta
	if (_strCarID == NULL) {
		puts("Niepoprawny format danych");
		return 0;
	}
	int carID = strtol(_strCarID, NULL, 10);
	if (carID == 0) {
		puts("Niepoprawny format danych.");
		return 0;
	}

	if (currentCar != NULL && currentCar->carID == carID) {				//jesli glowa listy to szukany element do usuniecia
		*_carHead = currentCar->nextCar;									//przypisanie poczatku listy do drugiego wezla
		if (currentCar->parkingPlaceID != 0) {								//usuniecie samochodu z bazy miejsca postojowego
			if (searchForParkingPlace(_parkingPlaceHead, &currenParkingPlace, currentCar->parkingPlaceID)) {	//wyszukanie miejsca postojowego przypisanego do samochodu
				deleteParkingPlaceCar(&currenParkingPlace->carParkedHead, carID);								//usuniecie go z listy samochodow na tym miejscu postojowym
			}
		}
		if (currentCar->userID != 0) {										//usuniecie samochodu o uzytkownika, ktory go wypozyczyl
			User *currentUser;
			if (!searchForUser(_userHead, &currentUser, currentCar->userID)) //jesli nie znaleziono danego uzytkownika
				return 0;
			currentUser->carRentedID = 0;
		}
		free(currentCar);								//zwolnienie pamieci
		return 1;
	}
	while (currentCar != NULL && currentCar->carID != carID) {
		prevCar = currentCar;
		currentCar = currentCar->nextCar;
	}

	if (currentCar == NULL) {
		puts("Nie znaleziono danego samochodu");
		return 0;
	}
	if (currentCar->parkingPlaceID != 0) {
		if (searchForParkingPlace(_parkingPlaceHead, &currenParkingPlace, currentCar->parkingPlaceID)) {	//wyszukanie miejsca postojowego przypisanego do samochodu
			deleteParkingPlaceCar(&currenParkingPlace->carParkedHead, carID);								//usuniecie go z listy samochodow na tym miejscu postojowym
		}
	}
	if (currentCar->userID != 0) {
		User *currentUser;
		if (!searchForUser(_userHead, &currentUser, currentCar->userID))	//jesli nie znaleziono danego uzytkownika
			return 0;
		currentUser->carRentedID = 0;
	}
	prevCar->nextCar = currentCar->nextCar;
	free(currentCar);
	return 1;
}

//funkcja usuwajaca uzytkownika
int deleteUser(char* _strUserID, User** _userHead) {
	//wprowadzenie wskaznikow pomocniczych do przeszukiwania listy i zapamietywania poprzedniego elementu
	User* currentUser = *_userHead;
	User* prevUser = NULL;
	//zamiana stringa na inta
	if (_strUserID == NULL) {
		puts("Niepoprawny format danych");
		return 0;
	}
	int userID = strtol(_strUserID, NULL, 10);
	if (userID == 0) {
		puts("Niepoprawny format danych.");
		return 0;
	}
	if (currentUser != NULL && currentUser->userID == userID) {		//jesli glowa listy to szukany element do usuniecia
		if (currentUser->carRentedID != 0) {							//jesli uzytkownik ma wypozyczony samochod
			puts("Uzytkownik ma aktualnie wypozyczony samochod - nie mozna go usunac. Nalezy najpierw zwrocic wypozyczony samochod.");
			return 0;
		}
		else {
			*_userHead = currentUser->nextUser;							//przypisanie poczatku listy do aktualnie drugiego wezla
			free(currentUser);
			return 1;
		}
	}
	while (currentUser != NULL && currentUser->userID != userID) {
		prevUser = currentUser;
		currentUser = currentUser->nextUser;
	}
	if (currentUser == NULL) {
		puts("Nie znaleziono szukanego uzytkownika.");
		return 0;
	}
	if (currentUser->carRentedID != 0) {								//jesli uzytkownik ma wypozyczony samochod
		puts("Uzytkownik ma aktualnie wypozyczony samochod - nie mozna go usunac. Nalezy najpierw zwrocic wypozyczony samochod.");
		return 0;
	}
	else {
		prevUser->nextUser = currentUser->nextUser;
		free(currentUser);
		return 1;
	}
}

//funkcja usuwajaca miejsce postojowe
int deleteParkingPlace(char* _strParkingPlaceID, ParkingPlace** _parkingPlaceHead) {
	//wprowadzenie wsazknikow pomocniczych do przeszukiwania listy i zapamietywania poprzedniego elementu
	ParkingPlace* currentParkingPlace = *_parkingPlaceHead;
	ParkingPlace* prevParkingPlace = NULL;
	
	//zamiana stringa na inta
	if (_strParkingPlaceID == NULL) {
		puts("Niepoprawny format danych");
		return 0;
	}
	int parkingPlaceID = strtol(_strParkingPlaceID, NULL, 10);
	if (parkingPlaceID == 0) {
		puts("Niepoprawny format danych.");
		return 0;
	}
	if (currentParkingPlace != NULL && currentParkingPlace->parkingPlaceID == parkingPlaceID) {	//jesli glowa lity to szukany element do usuniecia
		if (currentParkingPlace->carParkedHead != NULL) {										//jesli na miejscu postojowym znajduja sie samochody
			puts("Na miejscu postojowym znajduja sie samochody - nie mozna go usunac. Nalezy najpierw przemiescic lub usunac samochody.");
			return 0;
		}
		else {
			*_parkingPlaceHead = currentParkingPlace->nextParkingPlace;							//ustaw jako glowe drugi element listy
			free(currentParkingPlace);															//zwolnij pamiec dla aktualnego elementu
			return 1;
		}
	}
	while (currentParkingPlace != NULL && currentParkingPlace->parkingPlaceID != parkingPlaceID) {			//dopoki nie znaleziono szukanego po ID elementu
		prevParkingPlace = currentParkingPlace;												//przesuwaj wskazniki o jeden do przodu
		currentParkingPlace = currentParkingPlace->nextParkingPlace;
	}
	if (currentParkingPlace == NULL) {
		puts("Nie znaleziono szukanego miejsca postojowego.");
		return 0;
	}
	if (currentParkingPlace->carParkedHead != NULL) {										//jesli na miejscu postojowym znajduja sie samochody
		puts("Na miejscu postojowym znajduja sie samochody - nie mozna go usunac. Nalezy najpierw przemiescic lub usunac samochody.");
		return 0;
	}
	else {																					//w przeciwnym wypadku
		prevParkingPlace->nextParkingPlace = currentParkingPlace->nextParkingPlace;			//przelacz wiezy elementow listy
		free(currentParkingPlace);															//zwolnij pamiec
		return 1;
	}
}

//funkcja wyswietlajaca wszystkie samochody wraz z danymi
int showCarsAll(Car** _carHead) {
	Car* currentCar = *_carHead;
	while (currentCar != NULL) {
		printf("%d\t %s\t %d/%d/%d\t %d/%d/%d\t %d\t %d\n", currentCar->carID, currentCar->licensePlate, currentCar->lastCheck.day, currentCar->lastCheck.month, currentCar->lastCheck.year, currentCar->nextCheck.day, currentCar->nextCheck.month, currentCar->nextCheck.year, currentCar->userID, currentCar->parkingPlaceID);
		currentCar = currentCar->nextCar;
	}
	puts("");
	return 1;
}

int showCarsParked(Car** _carHead, char* _strParkingPlaceID) {
	Car* currentCar = *_carHead;
	if (!_strParkingPlaceID ) {										//jesli nie ma zadnych danych do wpisania
		puts("Niepoprawny format danych");
		return 0;
	}
	int parkingPlaceID = strtol(_strParkingPlaceID, NULL, 10);		//konwersja stringa na int
	if (parkingPlaceID == 0) {										//jesli konwersja nie przebiegla pomyslnie
		puts("Niepoprawny format danych.");
		return 0;
	}
	while (currentCar != NULL) {
		if (currentCar->parkingPlaceID == parkingPlaceID) {
			printf("%d\t %s\t %d/%d/%d\t %d/%d/%d\t %d\t %d\n", currentCar->carID, currentCar->licensePlate, currentCar->lastCheck.day, currentCar->lastCheck.month, currentCar->lastCheck.year, currentCar->nextCheck.day, currentCar->nextCheck.month, currentCar->nextCheck.year, currentCar->userID, currentCar->parkingPlaceID);
		}
		currentCar= currentCar->nextCar;
	}
	puts("");
	return 1;
}

int showCarsFree(Car** _carHead) {
	Car* currentCar = *_carHead;
	while (currentCar != NULL) {
		if (currentCar->userID == 0) {
			printf("%d\t %s\t %d/%d/%d\t %d/%d/%d\t %d\t %d\n", currentCar->carID, currentCar->licensePlate, currentCar->lastCheck.day, currentCar->lastCheck.month, currentCar->lastCheck.year, currentCar->nextCheck.day, currentCar->nextCheck.month, currentCar->nextCheck.year, currentCar->userID, currentCar->parkingPlaceID);
		}
		currentCar = currentCar->nextCar;
	}
	puts("");
	return 1;
}

int showCarsUser(Car** _carHead, char* _strUserID) {
	Car* currentCar = *_carHead;
	if (_strUserID == NULL) {
		puts("Niepoprawny format danych");
		return 0;
	}
	int userID = strtol(_strUserID, NULL, 10);
	if (userID == 0) {
		puts("Niepoprawny format danych.");
		return 0;
	}
	while (currentCar != NULL) {
		if (currentCar->userID == userID) {
			printf("%d\t %s\t %d/%d/%d\t %d/%d/%d\t %d\t %d\n", currentCar->carID, currentCar->licensePlate, currentCar->lastCheck.day, currentCar->lastCheck.month, currentCar->lastCheck.year, currentCar->nextCheck.day, currentCar->nextCheck.month, currentCar->nextCheck.year, currentCar->userID, currentCar->parkingPlaceID);
		}
		currentCar = currentCar->nextCar;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca wszystkich uzytkownikow wraz z danymi
int showUsersAll(User** _userHead) {
	User* currentUser = *_userHead;
	while (currentUser != NULL) {
		printf("%d\t %.2lf\t %d\n", currentUser->userID, currentUser->accountBalance, currentUser->carRentedID);
		currentUser = currentUser->nextUser;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca uzytkownikow bez wypozyczonych samochodow
int showUsersFree(User** _userHead) {
	User* currentUser = *_userHead;
	while (currentUser) {
		if (currentUser->carRentedID == 0) {
			printf("%d\t %.2lf\n", currentUser->userID, currentUser->accountBalance);
		}
		currentUser = currentUser->nextUser;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca uzytkownikow z wypozyczonym samochodem
int showUsersRenting(User** _userHead) {
	User* currentUser = *_userHead;
	while (currentUser) {
		if (currentUser->carRentedID != 0) {
			printf("%d\t %.2lf\t %d\n", currentUser->userID, currentUser->accountBalance, currentUser->carRentedID);
		}
		currentUser = currentUser->nextUser;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca wlasciciela danego samochodu
int showUsersCar(User** _userHead, char* _strCarRentedID) {
	User* currentUser = *_userHead;
	if (_strCarRentedID == NULL) {
		puts("Niepoprawny format danych");
		return 0;
	}
	int carRentedID = strtol(_strCarRentedID, NULL, 10);
	if (carRentedID == 0) {
		puts("Niepoprawny format danych.");
		return 0;
	}
	while (currentUser) {
		if (currentUser->carRentedID == carRentedID) {
			printf("%d\t %.2lf\t %d\n", currentUser->userID, currentUser->accountBalance, currentUser->carRentedID);
		}
		currentUser = currentUser->nextUser;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca wszystkie miejsca postojowe wraz z danymi
int showParkingPlacesAll(ParkingPlace** _parkingPlaceHead) {
	ParkingPlace* currentParkingPlace = *_parkingPlaceHead;
	while (currentParkingPlace) {
		printf("%d\t%s\n", currentParkingPlace->parkingPlaceID, currentParkingPlace->address);
		CarParked* currentCarParked = currentParkingPlace->carParkedHead;
		while (currentCarParked) {
			printf("\t%d\n", currentCarParked->carParkedID);
			currentCarParked = currentCarParked->nextCarParked;
		}
		currentParkingPlace = currentParkingPlace->nextParkingPlace;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca wolne miejsca postojowe
int showParkingPlacesFree(ParkingPlace** _parkingPlaceHead) {
	ParkingPlace* currentParkingPlace = *_parkingPlaceHead;
	while (currentParkingPlace) {
		if (currentParkingPlace->carParkedHead == NULL) {
			printf("%d\t %s\n", currentParkingPlace->parkingPlaceID, currentParkingPlace->address);		
		}
		currentParkingPlace = currentParkingPlace->nextParkingPlace;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca samochody stojace na dane 
int showParkingPlacesCar(ParkingPlace** _parkingPlaceHead, char* _strCarParkedID) {
	ParkingPlace* currentParkingPlace = *_parkingPlaceHead;
	if (_strCarParkedID == NULL) {
		puts("Niepoprawny format danych");
		return 0;
	}
	int carParkedID = strtol(_strCarParkedID, NULL, 10);
	if (carParkedID == 0) {
		puts("Niepoprawny format danych.");
		return 0;
	}
	while (currentParkingPlace) {
		CarParked* currentCarParked = currentParkingPlace->carParkedHead;
		while (currentCarParked) {
			if (currentCarParked->carParkedID == carParkedID) {
				printf("%d\t %s\n", currentParkingPlace->parkingPlaceID, currentParkingPlace->address);
			}
			currentCarParked = currentCarParked->nextCarParked;
		}
		currentParkingPlace = currentParkingPlace->nextParkingPlace;
	}
	puts("");
	return 1;
}

//funkcja wyswietlajaca samochody w kolejnosc zblizajacego sie terminu przegladu
int showUpcomingCheckCars(Car** _carHead) {
	Car* currentCar = *_carHead;
	int numOfCars = 0;
	while (currentCar) {
		++numOfCars;
		currentCar = currentCar->nextCar;
	}
	int* nextCheckDateStampSortTab = malloc(numOfCars * sizeof(int));
	int* carIDSortTab = malloc(numOfCars * sizeof(int));

	currentCar = *_carHead;
	for (int i = 0; i < numOfCars; ++i) {
		nextCheckDateStampSortTab[i] = dateStampCreate(currentCar->nextCheck.day, currentCar->nextCheck.month, currentCar->nextCheck.year);
		carIDSortTab[i] = currentCar->carID;
		currentCar = currentCar->nextCar;
	}
	currentCar = *_carHead;
	for (int i = 0; i < numOfCars; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < numOfCars; ++j) {
			if (nextCheckDateStampSortTab[j] < nextCheckDateStampSortTab[minIndex]) {
				minIndex = j;
			}
		}
		swapInt(&nextCheckDateStampSortTab[i], &nextCheckDateStampSortTab[minIndex]);
		swapInt(&carIDSortTab[i], &carIDSortTab[minIndex]);
		searchForCar(_carHead, &currentCar, carIDSortTab[i]);
		printf("%d\t %s\t %d/%d/%d\t %d/%d/%d\t %d\t %d\n", currentCar->carID, currentCar->licensePlate, currentCar->lastCheck.day, currentCar->lastCheck.month, currentCar->lastCheck.year, currentCar->nextCheck.day, currentCar->nextCheck.month, currentCar->nextCheck.year, currentCar->userID, currentCar->parkingPlaceID);
	}
	return 1;
	
}

int freeDatabase(Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead) {
	Car* currentCar = *_carHead;
	Car* _nextCar = NULL;
	while (currentCar != NULL) {
		_nextCar = currentCar->nextCar;
		free(currentCar);
		currentCar = _nextCar;
	}
	(*_carHead) = NULL;
	User* currentUser = *_userHead;
	User* _nextUser = NULL;
	while (currentUser != NULL) {
		_nextUser = currentUser->nextUser;
		free(currentUser);
		currentUser = _nextUser;
	}
	(*_userHead) = NULL;

	ParkingPlace* currentParkingPlace = *_parkingPlaceHead;
	ParkingPlace* _nextParkingPlace = NULL;

	CarParked* currentCarParked = NULL;
	CarParked* _nextCarParked = NULL;

	while (currentParkingPlace != NULL) {
		currentCarParked = currentParkingPlace->carParkedHead;
		while (currentCarParked != NULL) {
			_nextCarParked = currentCarParked->nextCarParked;
			free(currentCarParked);
			currentCarParked = _nextCarParked;
		}
		currentParkingPlace->carParkedHead = NULL;
		_nextParkingPlace = currentParkingPlace->nextParkingPlace;
		free(currentParkingPlace);
		currentParkingPlace = _nextParkingPlace;
	}
	(*_parkingPlaceHead) = NULL;
	return 1;
}

