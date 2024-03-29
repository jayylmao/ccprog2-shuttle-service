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
 *	Solution by: Jay Carlos
 *	Precondition: Positive integer header size provided.
 *	@param *message Message to be printed in between the brackets.
 *	@param headerSize Length of header.
 */
void printHeader(char *message, int headerSize)
{
	int i, msgLength = strlen(message);
	printf("======[ %s ]", message);

	for (i = 0; i < headerSize - (msgLength + 1); i++) {
		printf("=");
	}

	printf("\n\n");
}

/*
 *  getDropOffName returns the name of a drop-off point given its integer representation in the program.
 *	Solution by: Jay Carlos
 *  Precondition: Valid drop-off point integer given.
 *  @param dropOffPt Integer representation of drop-off point in program
 *  @param dropOffString Character array to save name of drop-off point to.
 *  @return None.
 */
void getDropOffName(int dropOffPt, char *dropOffString)
{
	switch (dropOffPt) {
	case 1:
		strcpy(dropOffString, "Mamplasan Toll Exit");
		break;
	case 2:
		strcpy(dropOffString, "Phase 5, San Jose Village");
		break;
	case 3:
	case 5:
		strcpy(dropOffString, "Milagros Del Rosario (MRR) Building - East Canopy");
		break;
	case 4:
		strcpy(dropOffString, "Laguna Blvd. Guard House");
		break;
	case 6:
		strcpy(dropOffString, "Petron Gasoline Station along Gil Puyat Avenue");
		break;
	case 7:
	case 11:
		strcpy(dropOffString, "Gate 4: Gokongwei Gate");
		break;
	case 8:
	case 12:
		strcpy(dropOffString, "Gate 2: North Gate (HSSH)");
		break;
	case 9:
	case 13:
		strcpy(dropOffString, "Gate 1: South Gate (LS Building Entrance)");
		break;
	}
}

/*
 *	getTime returns the trip time given a trip number.
 *	Solution by: Jay Carlos
 *	Precondition: Valid trip number given.
 *	@param tripNumber Trip number.
 *	@param *dest Character array to save time to.
 */
void getTime(int tripNumber, char *dest)
{
	FILE *fp;
	int fileTripNumber, hour, minute;
	char buffer[6];
	fp = fopen("./config/tripSched.txt", "r");

	if (fp == NULL) {
		printf(RED"[!]: Trip schedule file (./config/tripSched.txt) could not be found in current directory.\n"RESET);
		strcpy(dest, "00:00");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &fileTripNumber, &hour, &minute);

		if (tripNumber == fileTripNumber) {
			snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
		}
	}

	fclose(fp);

	strcpy(dest, buffer);
}

/*
 *	getPriorityGroupName returns the name of a priority group given its integer representation in the program.
 *	Solution by: Jay Carlos
 *	Precondition: Valid priority group integer given.
 *	@param priorityNumber Integer representation of a priority group in the program.
 *	@param *dest Character array to save name of priority group to.
 */
void getPriorityGroupName(int priorityNumber, char *dest)
{
	switch (priorityNumber) {
	case 1:
		strcpy(dest, "Faculty & ASF with Inter-Campus Assignments");
		break;
	case 2:
		strcpy(dest, "Students with Inter-campus subjects/thesis");
		break;
	case 3:
		strcpy(dest, "Researchers");
		break;
	case 4:
		strcpy(dest, "School Administrators");
		break;
	case 5:
		strcpy(dest, "University Fellows");
		break;
	case 6:
		strcpy(dest, "Employees and Students with official business");
		break;
	default:
		break;
	}
}

/*
 *	getRouteName returns the name of a route given the route's integer representation in the program and the embarkation point.
 *	Solution by: Jay Carlos
 *	Precondition: Valid route and embarkation point given.
 *	@param route Integer corresponding to route number in the program.
 *	@param embarkPt Integer corresponding to embarkation point in the program.
 *	@param *dest Character array to save route name to.
 */
void getRouteName(int route, int embarkPt, char *dest)
{
	switch (embarkPt) {
	case 0:
		if (route == 0) {
			strcpy(dest, "Via Mamplasan exit");
		} else {
			strcpy(dest, "Via ETON exit");
		}
		break;
	case 1:
		if (route == 0) {
			strcpy(dest, "Via Estrada");
		} else {
			strcpy(dest, "Via Buendia/LRT");
		}
		break;
	default:
		break;
	}
}

#include "dataStructs.h"
#include "data.h"
#include "file.h"
#include "passenger.h"
#include "personnel.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '0'

#define VIEW_PASSENGERS_COUNT '1'
#define VIEW_PASSENGERS_AT_DROP '2'
#define VIEW_PASSENGER_INFO '3'
#define LOAD_PASSENGER_INFO '4'
#define SEARCH '5'
#define LOAD_FILE '6'
#define PERSONNEL_EXIT '0'

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
	do
	{
		printHeader(YELLOW"Personnel Management Console"RESET, 80);
		printf(YELLOW"[0.] Back \n"RESET);
		printf("Go back to the main menu.\n\n");

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
		
		printf(BLUE"Choose an option: ");
		scanf(" %c", &userChoice);
		printf(RESET);
		system("clear||cls");

		// the functions below are found in personnel.h
		switch (userChoice) {
		case PERSONNEL_EXIT:
			break;
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
			loadPassInfo(trips, TRIP_COUNT);
			break;
		case SEARCH:
			searchPass(trips, TRIP_COUNT);
			break;
		case LOAD_FILE:
			viewRecentFile();
			break;
		default:
			printf(YELLOW"[*]: Please input a number from 0 - 6.\n"RESET);
			break;
		}
	} while (userChoice != PERSONNEL_EXIT);
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
	char dateInput[3], monthInput[3], yearInput[5];

	system("clear||cls");

	printHeader(YELLOW"System Initialization"RESET, 80);
	
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
		case EXIT:
			break;
		case PASSENGER:
			passengerRoutine(dateStruct, trips, TRIP_COUNT);
			break;
		case PERSONNEL:
			personnelMenu(trips, dateStruct);
			break;
		default:
			printf(YELLOW"[*] Please input a number from 0 - 2.\n"RESET);
			break;
		}
	} while (userChoice != EXIT);

	// only write trip info when the program is exited.
	writeFile(trips, TRIP_COUNT, dateStruct);
}