#ifndef _DATABASE3_H_
#define _DATABASE3_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define LICENSE_MAX_CHAR_NUMBER 10		//maksymalna ilosc znakow w tablicy rejestracyjnej samochodu
#define ADDRESS_MAX_CHAR_NUMBER 50		//maksymalna ilosc znakow w adresie miejsca postoju

#define PARKING_PLACE_FIRST_ID 1000000	//numer id rozpoczynajacy numeracje miejsc postojowych 
#define CAR_FIRST_ID 2000000			//numer id rozpoczynajacy numeracje samochodow
#define USER_FIRST_ID 3000000			//numer id rozpoczynajacy numeracje uzytkownikow

#define RENT_PRICE 500					//cena za wypozyczenie samochodu

#define MIN_YEAR 1970					//najmniejszy rok mozliwy do wpisania jako data
#define MAX_DAYS 31						//maksymalna ilosc dni w miesiacu
#define MAX_MONTHS 12					//ilosc miesiecy

//struktura daty
typedef struct Date {
	int day;	//dzien
	int month;	//miesiac
	int year;	//rok
}Date;

//struktura samochodu
typedef struct Car {
	unsigned int carID;							//numer id samochodu (2000000+)
	char licensePlate[LICENSE_MAX_CHAR_NUMBER];	//tablica rejestracyjna
	Date lastCheck;								//data ostatniego przegladu
	Date nextCheck;								//data nastepnego przegladu
	unsigned int userID;						//id uzytkownika, ktory wypozyczyl samochod lub jesli nikt nie wypozyczyl = 0
	unsigned int parkingPlaceID;				//id miejsca postojowego, w ktorym znajduje sie samochod lub jesli jest wypozyczony = 0
	struct Car *nextCar;						//wskaznik na nastepny samochod w liscie
}Car;

//struktura zaparkowanego w miejscu postojowym samochodu
typedef struct CarParked {
	unsigned int carParkedID;		//numer id zaparkowanego samochodu
	struct CarParked *nextCarParked;//wskaznik na nastepny zaparkowany samochod z listy
}CarParked;

//struktura miejsca postojowego
typedef struct ParkingPlace {
	unsigned int parkingPlaceID;			//nymer id miejsca postojowego (1000000+)
	char address[ADDRESS_MAX_CHAR_NUMBER];	//adres miejsca postojowego
	CarParked *carParkedHead;				//wskaznik na poczatek listy samochodow zaparkowanych na danym miejscu postojowym
	struct ParkingPlace *nextParkingPlace;	//wskaznik na nastepne miejsce postojowe z listy

}ParkingPlace;

//struktura uzytkownika
typedef struct User {
	unsigned int userID;		//numer id uzytkownika
	double accountBalance;		//stan konta
	unsigned int carRentedID;	//numer id wypozyczonego samochodu lub jesli zaden nie jest wypozyczony = 0
	struct User *nextUser;		//wskaznik na nastepnego uzytkownika z listy
}User;

int checkIfDouble(char* _string);
int dateStampCreate(int _dd, int _mm, int _yyyy);
int searchForCar(Car** _carHead, Car** _currentCar, unsigned int _carID);
int searchForCarParked(CarParked** _carParkedHead, CarParked** _currentCarParked, unsigned int _carParkedID);
int searchForUser(User** _userHead, User** _currentUser, unsigned int _userID);
int searchForParkingPlace(ParkingPlace** _parkingPlaceHead, ParkingPlace** _currentParkingPlace, unsigned int _parkingPlaceID);
int addUser(User** _userHead);
int addCar(Car** _carHead);
int addParkingPlace(ParkingPlace** _parkingPlaceHead);
int addDate(char* strDate, Date* _date);
int addCarNextCheckDate(char* _strNextCheckDate, Car** _carHead, unsigned int _carID);
int addCarLastCheckDate(char* _strLastCheckDate, Car** _carHead, unsigned int _carID);
int addCarLicensePlate(char *_strLicensePlate, Car** _carHead, int _carID);
int addCarParkingPlace(char* _strParkingPlaceID, Car** _carHead, int _carID, ParkingPlace** _parkingPlaceHead);
int addParkingPlaceAddress(char** _strAddress, ParkingPlace** _parkingPlaceHead, unsigned int _parkingPlaceID);
int addUserMoney(char* _strUserMoney, User** _userHead, unsigned int _userID);
int deleteParkingPlaceCar(CarParked** _carParkedHead, int _carParkedID);
int addCarParked(CarParked** _carParkedHead, unsigned int _carParkedID);
int rentCar(char* _strCarID, Car** _carHead, char* _strUserID, User** _userHead, ParkingPlace** _parkingPlaceHead);
int returnCar(Car** _carHead, char* _strUserID, User** _userHead, char* _strParkingPlaceID, ParkingPlace** _parkingPlaceHead);
int deleteCar(Car** _carHead, char* _strCarID, User** _userHead, ParkingPlace** _parkingPlaceHead);
int deleteUser(char* _strUserID, User** _userHead);
int deleteParkingPlace(char* _strParkingPlaceID, ParkingPlace** _parkingPlaceHead);
int showCarsAll(Car** _carHead);
int showCarsParked(Car** _carHead, char* _strParkingPlaceID);
int showCarsFree(Car** _carHead);
int showCarsUser(Car** _carHead, char* _strUserID);
int showUpcomingCheckCars(Car** _carHead);

int showUsersAll(User** _userHead);
int showUsersFree(User** _userHead);
int showUsersRenting(User** _userHead);
int showUsersCar(User** _userHead, char* _strCarRentedID);

int showParkingPlacesAll(ParkingPlace** _parkingPlaceHead);
int showParkingPlacesFree(ParkingPlace** _parkingPlaceHead);
int showParkingPlacesCar(ParkingPlace** _parkingPlaceHead, char* _strCarParkedID);

int freeDatabase(Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead);

#endif