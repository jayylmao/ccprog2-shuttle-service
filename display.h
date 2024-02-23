#include "passenger.h"
#include "file.h"

#define NONE '\0'
#define PASSENGER '1'
#define PERSONNEL '2'
#define EXIT '3'

/*
 *	passengerRoutine allows a passenger to select a trip to embark on.
 */
void passengerRoutine()
{
	FILE * fp = NULL;

	Passenger passenger;
	printf("Enter your trip number: AE");
	scanf("%d", &passenger.tripNumber);

	printf("Priority number list\n\
\t1: Faculty & ASF with Inter-campus assignments\n\
\t2: Students with Inter-campus enrolled subjects/thesis\n\
\t3: Researchers\n\
\t4: School Administrators\n\
\t5: University Fellows\n\
\t6: Employees and Students with official business\n\
Falsifying priority is punishable by death.\n\
Enter your priority number: ");
	scanf("%d", &passenger.priorityNumber);
	getchar(); // removing this causes the next input to get dropped.

	printf("Enter your name: ");
	fgets(passenger.name, MAX, stdin);

	printf("Enter your ID: ");
	fgets(passenger.id, MAX, stdin);

	printf("Enter your drop-off point: ");
	scanf("%d", &passenger.dropOffPt);

	writeTripData(fp, passenger);
}

/*
 *	personnelRoutine allows personnel to view the passenger database.
 */
void personnelRoutine()
{
	printf("Personnel Management Console\n");
}

/*
 *	mainMenu allows the user to choose between the program's main routines.
 *	The other routines should return to this one.
 */
void mainMenu()
{
	char userChoice = NONE;

	while (userChoice != EXIT) {
		printf("Welcome to the Arrows Express Trip System.\n");
		printf("Please select a menu option below: \n");
		printf("1. Passenger \n");
		printf("2. Personnel \n");
		printf("3. Exit \n");

		scanf(" %c", &userChoice);
		system("clear||cls");

		switch (userChoice) {
		case PASSENGER:
			passengerRoutine();
			break;
		case PERSONNEL:
			personnelRoutine();
			break;
		case EXIT:
			break;
		default:
			printf("Please input a number from 1 - 3.\n");
			break;
		}
	}
}