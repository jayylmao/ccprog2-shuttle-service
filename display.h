#include "passenger.h"
#include "data.h"
#include "file.h"
#include "personnel.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '3'

#define TRIP_COUNT 20

// ANSI Color escape sequences courtesy of https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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

/*
 *	displayTrip visualizes the bus the user has selected on screen.
 *	Precondition: A valid trip number is provided.
 *	@param tripNumber Integer corresponding to trip number.
 *	@trips[] Array of trips to get trip information from.
 *	@return None.
 */
void displayTrip(int tripNumber, Trip trips[])
{
	int busIndex, i;
	busIndex = getTripIndex(tripNumber);

	Trip trip = trips[busIndex];


	// standard seating
	if (trip.passengerCount <= 13) {
		printf(".____.____.____.\n");

		for (i = 0; i < 13; i++) {
			if (strcmp(trip.passengers[i].id, "-1") == 0) { // print seat number if not occupied
				printf("| %02d ", i + 1);
			} else { // print XX if seat is occupied
				printf("| XX ");
			}

			if ((i + 1) % 3 == 0 && i != 0) { // print separator + newline for each row of seats
				printf("| \n");
				printf(".____.____.____.\n");
			}
		}

		printf("| Driver  |\n");
	} else {	// high-volume seating
		printf(".____.____.____.____.\n");

		for (i = 0; i < 16; i++) {
			if (strcmp(trip.passengers[i].id, "-1") == 0 && (i + 1) == 16) { // last row has a different format
				printf("| %02d      | Driver  ", i + 1);
			} else if (strcmp(trip.passengers[i].id, "-1") == 0) { // print seat number if not occupied
				printf("| %02d ", i + 1);
			} else { // print XX if seat is occupied
				printf("| XX ");
			}

			if ((i + 1) == 12) { // 12th seating has a blank space after it in the row below
				printf("| \n");
				printf(".____.____.____.____.\n");
				printf("|    ");
			} else if (((i + 1) % 4 == 0 || (i + 1) == 15) && i != 0) { // print separator + newline for each row of seats
				printf("| \n");
				printf(".____.____.____.____.\n");
			}
		}
	}
}

/*
 *	displayDropOff displays a list of exits and drop-off points for the user to select from.
 *	Precondition: A valid trip number must be given.
 *	@param tripNumber Integer corresponding to trip number.
 *	@return Integer corresponding to the drop-off point.
 */
int displayDropOff(int tripNumber)
{
	// dropOff is where the user's input is stored.
	// menuLimit is an upper bound for the menu to determine input validity.
	int dropOff, menuLimit;
	printf("Exit list\n");
	if (tripNumber >= 101 && tripNumber <= 109) {
		printf("\tVia Mamplasan exit\n");
		printf("\t\t1. Mamplasan Toll Exit\n");
		printf("\t\t2. Phase 5, San Jose Village\n");
		printf("\t\t3. Milagros Del Rosario Building - East Canopy\n");
		printf("\tVia ETON exit\n");
		printf("\t\t4. Laguna Blvd. Guard House\n");
		printf("\t\t5. Milagros Del Roasrio Building - East Canopy\n");
		menuLimit = 5;
	} else if (tripNumber >= 150 && tripNumber <= 160) {
		printf("\tVia Estrada\n");
		printf("\t\t1. Petron Gasoline Station along Gil Puyat Avenue\n");
		printf("\t\t2. Gate 4: Gokongwei Gate\n");
		printf("\t\t3. Gate 2: North Gate (HSSH)\n");
		printf("\t\t4. Gate 1: South Gate (LS Building Entrance)\n");
		printf("\tVia Buendia/LRT\n");
		printf("\t\t5. College of St. Benilde (CSB) Along Taft\n");
		printf("\t\t6. Gate 4: Gokongwei Gate\n");
		printf("\t\t7. Gate 2: North Gate (HSSH)\n");
		printf("\t\t8. Gate 1: South Gate (LS Building Entrance)\n");
		menuLimit = 8;
	}

	do {
		printf("Choose a drop-off point: ");
		scanf("%d", &dropOff);

		if (dropOff < 1 || dropOff > menuLimit) {
			printf("Select a drop-off point from 1 to %d.\n", menuLimit);
		}
	} while (dropOff < 1 || dropOff > menuLimit);

	// offset by 5 if boarding from laguna, so drop off 1-5 are manila and 6-13 are laguna.
	if (tripNumber >= 150 && tripNumber <= 160) {
		dropOff += 5;
	}

	return dropOff;
}

/*
 *	personnelAuthentication checks a password file and asks the user to input a password
 *	before displaying the personnel menu.
 *	Precondition: Password abides by MAX value, .password file exists, and function is called from main menu.
 *	@return Boolean value that determines whether a login was successful or not.
 */
bool personnelAuthentication()
{
	FILE *fp;
	char password[MAX];
	char input[MAX];

	// open .password file. (files that start with a period are hidden by default)
	bool passwordMatch = false;
	fp = fopen(".password", "r");

	// check if password file exists at all.
	if (fp == NULL) {
		printf(RED"[!]: No password set. Contact ITS."RESET);
	} else {
		fscanf(fp, "%s", password);

		while (!passwordMatch && strcmp(input, "0") != 0) {
			printHeader("Personnel Management Console", 80);
			printf("Enter the personnel password, or 0 to cancel: ");
			scanf("%s", input);

			system("clear||cls");

			if (strcmp(password, input) == 0) {
				printf(GREEN"[*]: Login successful.\n"RESET);
				passwordMatch = true;
			} else if (strcmp(input, "0") == 0) {
				printf(YELLOW"[*]: Login canceled.\n"RESET);
			} else {
				printf(RED"[*]: Incorrect password entered. Try again.\n"RESET);
			}
		}
	}

	return passwordMatch;
}

/*
 *	personnelMenu allows personnel to access the functions available to them.
 *	Precondition: Called from main menu if personnel authentication was successful.
 *	@param trips[] List of trips.
 *	@param date Current date entered at startup.
 *	@return None.
 */
void personnelMenu(Trip trips[], Date date)
{
	char userChoice;
	do
	{
		printHeader("Personnel Management Console", 80);
		printf(GREEN"[1.] View number of passengers on trip \n"RESET);
		printf("Input a trip number to view the number of passengers.\n\n");

		printf(GREEN"[2.] View number of passengers at drop-off point \n"RESET);
		printf("Input a trip number to view the number of passengers at each drop-off point.\n\n");

		printf(GREEN"[3.] View passenger information \n"RESET);
		printf("Input a trip number to view all passengers on that trip.\n\n");

		printf(GREEN"[4.] Load passenger information \n"RESET);
		printf("Select a file to add a passenger's data into the program.\n\n");

		printf(GREEN"[5.] Search passenger \n"RESET);
		printf("Search for passengers by their last name.\n\n");

		printf(GREEN"[6.] Load file \n"RESET);
		printf("Select a file to view all the trips from that day.\n\n");

		printf(GREEN"[7.] Log out \n"RESET);
		printf("Go back to the main menu.\n\n");
		
		printf(BLUE"Choose an option: ");
		scanf(" %c", &userChoice);
		printf(RESET);
		system("clear||cls");

		// the functions below are found in personnel.h
		switch (userChoice)
		{
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
			readTrips(trips, date);
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
 *	passengerRoutine allows a passenger to select a trip to embark on.
 *	Precondition: Valid date is entered.
 *	@param date Date to pass to the writePassenger function.
 *	@param *trips List of trips to add user to.
 *	@param nTrips Number of trips in the list.
 *	@return None.
 */
void passengerRoutine(Date date, Trip *trips, int nTrips)
{

	Passenger passenger;
	printf("Enter your trip number: AE");
	scanf("%d", &passenger.tripNumber);
	setEmbarkPt(passenger.tripNumber, &passenger.embarkPt);

	displayTrip(passenger.tripNumber, trips);

	printf("Priority number list\n\
\t1: Faculty & ASF with Inter-campus assignments\n\
\t2: Students with Inter-campus enrolled subjects/thesis\n\
\t3: Researchers\n\
\t4: School Administrators\n\
\t5: University Fellows\n\
\t6: Employees and Students with official business\n\
Falsifying priority is punishable by death.\n\
Enter your priority number: ");

	scanf(" %d", &passenger.priorityNumber);

	printf("Enter your first and last name: ");
	scanf("%s %s", passenger.Name.firstName, passenger.Name.lastName);

	printf("Enter your ID: ");
	scanf("%s", passenger.id);

	passenger.dropOffPt = displayDropOff(passenger.tripNumber);

	addPassenger(passenger, trips, getTripIndex(passenger.tripNumber));
	system("clear||cls");
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

	bool personnelAuthSuccess;
	
	// all trips for the day.
	Trip trips[TRIP_COUNT];
	initializeBuses(trips, TRIP_COUNT);

	Date dateStruct;
	int date, month, year;

	system("clear||cls");

	printHeader(YELLOW"System Initialization"RESET, 80);
	
	do {
		printf(BLUE"Please enter the current date in dd mm yyyy: ");
	} while (scanf("%d %d %d", &date, &month, &year) < 0);

	printf(RESET);
	system("clear||cls");

	dateStruct.date = date;
	dateStruct.month = month;
	dateStruct.year = year;

	do {
		printHeader(GREEN"Arrows Express"RESET" Trip System", 80);
		printf(GREEN"[1.] Passenger \n"RESET);
		printf("Board a trip at a specified time by entering your details.\n\n");

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
			personnelAuthSuccess = personnelAuthentication();
			
			if (personnelAuthSuccess) {
				personnelMenu(trips, dateStruct);
			}

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