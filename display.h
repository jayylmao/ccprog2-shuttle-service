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

/*
 *	printHeader displays the standard header at the top of every screen in the program.
 *	Precondition: Positive integer header size provided.
 *	@param *message Message to be printed in between the brackets.
 *	@param headerSize Length of header.
 */
void printHeader(char *message, int headerSize)
{
	int i, msgLength = strlen(message);
	printf("======[ %s ]", message);

	for (i = 0; i < headerSize - (msgLength + 10); i++) {
		printf("=");
	}

	printf("\n\n");
}

#include "dataStructs.h"
#include "data.h"
#include "file.h"
#include "passenger.h"
#include "personnel.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '3'

/*
 *	personnelMenu allows personnel to access the functions available to them.
 *	Precondition: Called from main menu.
 *	@param trips[] List of trips.
 *	@param date Current date entered at startup.
 *	@return None.
 */
void personnelMenu(Trip trips[], Date date)
{
	char userChoice;
	do
	{
		printHeader(YELLOW"Personnel Management Console"RESET, 80);
		printf(YELLOW"[1.] View number of passengers on trip \n"RESET);
		printf("Input a trip number to view the number of passengers.\n\n");

		printf(YELLOW"[2.] View number of passengers at drop-off point \n"RESET);
		printf("Input a trip number to view the number of passengers at each drop-off point.\n\n");

		printf(YELLOW"[3.] View passenger information \n"RESET);
		printf("Input a trip number to view all passengers on that trip.\n\n");

		printf(YELLOW"[4.] Load passenger information \n"RESET);
		printf("Select a file to add data into the program.\n\n");

		printf(YELLOW"[5.] Search passenger \n"RESET);
		printf("Search for passengers by their last name.\n\n");

		printf(YELLOW"[6.] View file \n"RESET);
		printf("Select a file to view all the trips from that day.\n\n");

		printf(YELLOW"[7.] Back \n"RESET);
		printf("Go back to the main menu.\n\n");
		
		printf(BLUE"Choose an option: ");
		scanf(" %c", &userChoice);
		printf(RESET);
		system("clear||cls");

		// the functions below are found in personnel.h
		switch (userChoice) {
		case VIEW_PASSENGERS_COUNT:
			viewPassCount(trips, TRIP_COUNT);
			break;
		case VIEW_PASSENGERS_AT_DROP:
			viewPassAtDrop(trips, TRIP_COUNT);
			break;
		case VIEW_PASSENGER_INFO:
			viewPassInfo(trips, TRIP_COUNT);
			break;
		case LOAD_PASSENGER_INFO:
			loadPassInfo();
			break;
		case SEARCH:
			searchPass(trips, TRIP_COUNT);
			break;
		case LOAD_FILE:
			loadFile();
			break;
		case PERSONNEL_EXIT:
			break;
		default:
			printf(YELLOW"[*]: Please input a number from 1 - 7.\n"RESET);
			break;
		}
		system("clear||cls");
	} while (userChoice != PERSONNEL_EXIT);
}

/*
 *	mainMenu allows the user to choose between the program's main routines.
 *	The other routines should return to this one.
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
	int date, month, year;

	system("clear||cls");

	printHeader(YELLOW"System Initialization"RESET, 80);
	
	do {
		printf(BLUE"Please enter the current date (DD MM YYYY): ");
		scanf("%d %d %d", &date, &month, &year);

		if ((date < 1 || date > 31) || (month < 1 || month > 12) || year < 1) {
			printf(YELLOW"[*]: Enter a valid date (DD MM YYYY)\n");
		}
	} while ((date < 1 || date > 31) || (month < 1 || month > 12) || year < 1);

	printf(RESET);
	system("clear||cls");

	dateStruct.date = date;
	dateStruct.month = month;
	dateStruct.year = year;

	do {
		printHeader(GREEN"Arrows Express Trip System"RESET, 80);
		printf(GREEN"[1.] Passenger \n"RESET);
		printf("Board a trip at a specified time by entering passenger details.\n\n");

		printf(GREEN"[2.] Personnel \n"RESET);
		printf("View and manage trip data.\n\n");

		printf(GREEN"[3.] Exit \n"RESET);
		printf("Exit the program and save current trip data.\n\n");

		printf(BLUE"Choose an option: ");
		scanf(" %c", &userChoice);
		system("clear||cls");

		printf(RESET);

		switch (userChoice) {
		case PASSENGER:
			passengerRoutine(dateStruct, trips, TRIP_COUNT);
			break;
		case PERSONNEL:
			personnelMenu(trips, dateStruct);
			break;
		case EXIT:
			break;
		default:
			printf(YELLOW"[*] Please input a number from 1 - 3.\n"RESET);
			break;
		}
	} while (userChoice != EXIT);

	// only write trip info when the program is exited.
	writeFile(trips, TRIP_COUNT, dateStruct);
}