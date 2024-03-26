#include "dataStructs.h"
#include "data.h"
#include "file.h"
#include "personnel.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '3'

#define TRIP_COUNT 22

// ANSI Color escape sequences courtesy of https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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

	if (trip.passengerCount <= 13) {	// standard seating
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
int displayDropOff(int embarkPoint, int route)
{
	// dropOff is where the user's input is stored.
	// menuLimit is an upper bound for the menu to determine input validity.
	int dropOff, menuLimit;

	printf("Exit list\n");
	switch (embarkPoint)
	{
	case 0:
		if (route == 0) {
			printf("\tVia Mamplasan exit\n");
			printf("\t\t1. Mamplasan Toll Exit\n");
			printf("\t\t2. Phase 5, San Jose Village\n");
			printf("\t\t3. Milagros Del Rosario Building - East Canopy\n");
			menuLimit = 3;
		} else {
			printf("\tVia ETON exit\n");
			printf("\t\t1. Laguna Blvd. Guard House\n");
			printf("\t\t2. Milagros Del Roasrio Building - East Canopy\n");
			menuLimit = 2;
		}
		break;
	case 1:
		menuLimit = 4;

		if (route == 0) {
			printf("\tVia Estrada\n");
			printf("\t\t1. Petron Gasoline Station along Gil Puyat Avenue\n");
			printf("\t\t2. Gate 4: Gokongwei Gate\n");
			printf("\t\t3. Gate 2: North Gate (HSSH)\n");
			printf("\t\t4. Gate 1: South Gate (LS Building Entrance)\n");
		} else {
			printf("\tVia Buendia/LRT\n");
			printf("\t\t5. College of St. Benilde (CSB) Along Taft\n");
			printf("\t\t6. Gate 4: Gokongwei Gate\n");
			printf("\t\t7. Gate 2: North Gate (HSSH)\n");
			printf("\t\t8. Gate 1: South Gate (LS Building Entrance)\n");
		}
	default:
		break;
	}

	do {
		printf("Choose a drop-off point: ");
		scanf("%d", &dropOff);

		if (dropOff < 1 || dropOff > menuLimit) {
			printf("Select a drop-off point from 1 to %d.\n", menuLimit);
		}
	} while (dropOff < 1 || dropOff > menuLimit);



	return dropOff;
}

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
	Trip trip;
	int page = 0;

	switch (page)
	{
	case 0:
		printHeader(GREEN"Add passenger"RESET, 80);

		break;
	default:
		break;
	}
	printf("Enter your trip number: AE");
	scanf("%d", &passenger.tripNumber);

	trip = trips[getTripIndex(passenger.tripNumber)];

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

	passenger.dropOffPt = displayDropOff(trip.embarkPt, trip.route);

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