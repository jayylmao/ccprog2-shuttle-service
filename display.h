#include "passenger.h"
#include "data.h"
#include "file.h"
#include "personnel.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '3'

#define TRIP_COUNT 20

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
		printf("CRITICAL ERROR: No password set. Contact ITS.");
	} else {
		fgets(password, MAX, fp);

		while (!passwordMatch && strcmp(input, "0") != 0) {
			printf("Enter the personnel password, or 0 to cancel: ");
			scanf("%s", input);

			system("clear||cls");

			if (strcmp(password, input) == 0) {
				printf("INFO: Login successful.\n");
				passwordMatch = true;
			} else if (strcmp(input, "0") == 0) {
				printf("INFO: Login canceled.\n");
			} else {
				printf("Incorrect password entered. Try again.\n");
			}
		}
	}

	return passwordMatch;
}

/*
 *	personnelMenu allows personnel to access the functions available to them.
 *	Precondition: Called from main menu if personnel authentication was successful.
 *	@return None.
 */
void personnelMenu(Trip trips[], Date date)
{
	char userChoice;
	do
	{
		printf("Personnel Management Console\n");
		printf("Please select a menu option below: \n");
		printf("1. View number of passengers on trip \n");
		printf("2. View number of passengers at drop-off point \n");
		printf("3. View passenger information \n");
		printf("4. Load passenger information \n");
		printf("5. Search passenger \n");
		printf("6. Load file \n");
		printf("7. Log out of personnel management console \n");
		
		scanf(" %c", &userChoice);
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
			loadFile();
			break;
		case PERSONNEL_EXIT:
			break;
		default:
			printf("Please input a number from 1 - 7.\n");
			break;
		}
		system("clear||cls");
	} while (userChoice != PERSONNEL_EXIT);
	
}

/*
 *	passengerRoutine allows a passenger to select a trip to embark on.
 *	Precondition: Valid date is entered.
 *	@param date Date to pass to the writePassenger function.
 *	@return None.
 */
void passengerRoutine(Date date, Trip *trips, int nTrips)
{

	Passenger passenger;
	printf("Enter your trip number: AE");
	scanf("%d", &passenger.tripNumber);
	setEmbarkPt(passenger.tripNumber, &passenger.embarkPt);

	printf("Priority number list\n\
\t1: Faculty & ASF with Inter-campus assignments\n\
\t2: Students with Inter-campus enrolled subjects/thesis\n\
\t3: Researchers\n\
\t4: School Administrators\n\
\t5: University Fellows\n\
\t6: Employees and Students with official business\n\
Falsifying priority is punishable by death.\n\
Enter your priority number: ");

	// TODO: replace all scanf() with fgets() and sscanf().
	// Why?
	// scanf("%s") only works with no spaces while fgets() works with a string of arbitrary length and supports spaces.
	// + scanf() and fgets() do not play nicely with each other so ideally we don't mix them.

	scanf(" %d", &passenger.priorityNumber);

	printf("Enter your first and last name: ");
	scanf("%s %s", passenger.Name.firstName, passenger.Name.lastName);

	printf("Enter your ID: ");
	scanf("%s", passenger.id);

	printf("Enter your drop-off point: ");
	scanf("%d", &passenger.dropOffPt);

	addPassenger(passenger, trips, getBusIndex(passenger.tripNumber));
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

	printf("Please enter the current date in dd mm yyyy: ");
	scanf("%d %d %d", &date, &month, &year);

	system("clear||cls");

	dateStruct.date = date;
	dateStruct.month = month;
	dateStruct.year = year;

	do {
		printf("Welcome to the Arrows Express Trip System.\n");
		printf("Please select a menu option below: \n");
		printf("1. Passenger \n");
		printf("2. Personnel \n");
		printf("3. Exit \n");

		scanf(" %c", &userChoice);
		system("clear||cls");

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
			printf("Please input a number from 1 - 3.\n");
			break;
		}
	} while (userChoice != EXIT);

	// only write trip info when the program is exited.
	writeFile(trips, TRIP_COUNT, dateStruct);
}