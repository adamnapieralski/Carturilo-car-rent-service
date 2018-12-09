#ifndef _SHELL3_H_
#define _SHELL3_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database3.h"

#define MAX_ARGS_BUFFER_SIZE 32
#define ID_MAX_CHAR_NUMBER 7

char *shReadLine();
char **shSplitLine(char *line);
void freeCommands(char* line, char** tokens);

void textColorCyan(void);
void textColorYellow(void);
void textColorReset(void);
void sh_welcome(void);
int sh_help(char **args);
void sh_help_addCar(void);
void sh_help_addUser(void);
void sh_help_addParkingPlace(void);
void sh_help_showCars(void);
void sh_help_showUsers(void);
void sh_help_showParkingPlaces(void);
void sh_help_carRent(void);
void sh_help_carReturn(void);
void sh_help_deleteCar(void);
void sh_help_deleteUser(void);
void sh_help_deleteParkingPlace(void);
void sh_help_exit(void);

int sh_addCar(char **args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead);
int sh_addUser(char **args, User** _userHead);
int sh_addParkingPlace(char **args, ParkingPlace** _parkingPlaceHead);
int sh_showCars(char** args, Car** _carHead);
int sh_showUsers(char** args, User** _userHead);
int sh_showParkingPlaces(char** args, ParkingPlace** _parkingPlaceHead);
int sh_commandsExe(char **args, User** _userHead, Car** _carHead, ParkingPlace** _parkingPlaceHead);
int sh_carRent(char** args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead);
int sh_carReturn(char** args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead);

int sh_deleteCar(char** args, Car** _carHead, User** _userHead, ParkingPlace** _parkingPlaceHead);
int sh_deleteUser(char** args, User** _userHead);
int sh_deleteParkingPlace(char** args, ParkingPlace** _parkingPlaceHead);

#endif