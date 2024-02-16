#include <stdio.h>
#include <stdlib.h>
#include "passenger.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '3'

void passengerRoutine()
{
	Passenger passenger;
	printf("Enter your trip number: ");
	scanf("%d", &passenger.tripNumber);
}

void personnelRoutine()
{
	printf("Personnel Management Console\n");
}

void mainMenu()
{
	char userChoice = NONE;

	while (userChoice != EXIT) {
		printf("Welcome to the Arrows Express Trip System.\n");
		printf("Please select a menu option below: \n");
		printf("1. Passenger \n");
		printf("2. Personnel \n");
		printf("3. Exit \n");

		scanf("%c", &userChoice);
		system("clear||cls");

		switch (userChoice) {
		case PASSENGER:
			passengerRoutine();
			break;
		case PERSONNEL:
			personnelRoutine();
			break;
		default:
			printf("Please input a number from 1 - 3.\n");
			break;
		}
	}
}