#include "passenger.h"
#include "data.h"
#include "file.h"
#include "personnel.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '3'

#define BUS_COUNT 20

/*
 *	passengerRoutine allows a passenger to select a trip to embark on.
 *	Precondition: Valid date is entered.
 *	@param date Date to pass to the writePassenger function.
 *	@return None.
 */
void passengerRoutine(Date date, Bus *buses, int nBuses)
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

	printf("Enter your name: ");
	scanf("%s", passenger.name);

	printf("Enter your ID: ");
	scanf("%s", passenger.id);

	printf("Enter your drop-off point: ");
	scanf("%d", &passenger.dropOffPt);

	addPassenger(passenger, buses, getBusIndex(passenger.tripNumber));
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

	// all buses for the day.
	Bus buses[BUS_COUNT];
	initializeBuses(buses, BUS_COUNT);

	Date dateStruct;
	int date, month, year;

	printf("Please enter the current date in dd mm yyyy: ");
	scanf("%d %d %d", &date, &month, &year);

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
			passengerRoutine(dateStruct, buses, BUS_COUNT);
			break;
		case PERSONNEL:
			personnelAuthSuccess = personnelAuthentication();
			
			if (personnelAuthSuccess) {
				personnelMenu(buses, dateStruct);
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
	writeFile(buses, 20, dateStruct);
}