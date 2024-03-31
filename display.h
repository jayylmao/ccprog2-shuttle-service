#define TRIP_COUNT 22

// ANSI Color escape sequences courtesy of https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

#define MAX_PASSENGERS 16

#include "dataStructs.h"
#include "strings.h"
#include "data.h"
#include "file.h"
#include "passenger.h"
#include "personnel.h"

/*
 *	personnelMenu allows personnel to access the functions available to them.
 *	Solution by: Jay Carlos
 *	Precondition: Called from main menu.
 *	@param trips[] List of trips.
 *	@param date Current date entered at startup.
 *	@return None.
 */
void personnelMenu(Trip trips[], Date date)
{
	char userChoice;
	do {
		printHeader(YELLOW"Personnel Management Console"RESET, 80);
		printf(YELLOW"[0.] Back \n"RESET);
		printf("Go back to the main menu.\n\n");

		printf(YELLOW"[1.] View number of passengers on trip \n"RESET);
		printf("Input a trip number to view the number of passengers.\n\n");

		printf(YELLOW"[2.] View number of passengers at drop-off point \n"RESET);
		printf("Input a trip number to view the number of passengers at each drop-off point.\n\n");

		printf(YELLOW"[3.] View passenger information \n"RESET);
		printf("Input a trip number to view all passengers on that trip.\n\n");

		printf(YELLOW"[4.] Search passenger \n"RESET);
		printf("Search for passengers by their last name.\n\n");

		printf(YELLOW"[5.] Add passenger/s from file \n"RESET);
		printf("Select a file to add passengers into the program.\n\n");

		printf(YELLOW"[6.] View recent file \n"RESET);
		printf("Select a file to view all the trips from that day.\n\n");
		
		printf(BLUE"Choose an option: ");
		scanf(" %c", &userChoice);
		printf(RESET);
		system("clear||cls");

		// the functions below are found in personnel.h
		switch (userChoice) {
			case '0':
				break;
			case '1':
				viewPassCount(trips, TRIP_COUNT);
				break;
			case '2':
				viewPassAtDrop(trips, TRIP_COUNT);
				break;
			case '3':
				viewPassInfo(trips, TRIP_COUNT);
				break;
			case '4':
				searchPass(trips, TRIP_COUNT);
				break;
			case '5':
				addPassInfo(trips, TRIP_COUNT);
				break;
			case '6':
				viewRecentFile();
				break;
			default:
				printf(YELLOW"[*]: Please input a number from 0 - 6.\n"RESET);
				break;
		}
	} while (userChoice != '0');
}

/*
 *	mainMenu allows the user to choose between the program's main routines.
 *	The other routines should return to this one.
 *	Solution by: Jay Carlos
 *	Precondition: Called from driver program.
 *	@return None.
 */
void mainMenu()
{
	char userChoice;
	
	// all trips for the day.
	Trip trips[TRIP_COUNT];
	initializeBuses(trips, TRIP_COUNT);

	Date dateStruct;
	char dateInput[MAX], monthInput[MAX], yearInput[MAX];

	system("clear||cls");

	printHeader(YELLOW"System Initialization"RESET, 80);
	
	// ask user for date.
	do {
		printf(BLUE"Please enter the current date (DD MM YYYY): "RESET);
		scanf("%s %s %s", dateInput, monthInput, yearInput);

		dateStruct.date = atoi(dateInput);
		dateStruct.month = atoi(monthInput);
		dateStruct.year = atoi(yearInput);

		if ((dateStruct.date < 1 || dateStruct.date > 31) || (dateStruct.month < 1 || dateStruct.month > 12) || dateStruct.year < 1) {
			system("clear||cls");
			printHeader(YELLOW"System Initialization"RESET, 80);
			printf(YELLOW"[*]: Enter a valid date (DD MM YYYY)\n"RESET);
		}
	} while ((dateStruct.date < 1 || dateStruct.date > 31) || (dateStruct.month < 1 || dateStruct.month > 12) || dateStruct.year < 1);

	printf(RESET);
	system("clear||cls");

	do {
		printHeader(GREEN"Arrows Express Trip System"RESET, 80);
		printf(GREEN"[0.] Exit \n"RESET);
		printf("Exit the program and save current trip data.\n\n");

		printf(GREEN"[1.] Passenger \n"RESET);
		printf("Board a trip at a specified time by entering passenger details.\n\n");

		printf(GREEN"[2.] Personnel \n"RESET);
		printf("View and manage trip data.\n\n");

		printf(BLUE"Choose an option: ");
		scanf(" %c", &userChoice);
		system("clear||cls");

		printf(RESET);

		switch (userChoice) {
			case '0':
				break;
			case '1':
				passengerRoutine(dateStruct, trips, TRIP_COUNT);
				break;
			case '2':
				personnelMenu(trips, dateStruct);
				break;
			default:
				printf(YELLOW"[*] Please input a number from 0 - 2.\n"RESET);
				break;
		}
	} while (userChoice != '0');

	// only write trip info when the program is exited.
	writeFile(trips, TRIP_COUNT, dateStruct);
}