#define VIEW_PASSENGERS_COUNT '1'
#define VIEW_PASSENGERS_AT_DROP '2'
#define VIEW_PASSENGER_INFO '3'
#define LOAD_PASSENGER_INFO '4'
#define SEARCH '5'
#define LOAD_FILE '6'
#define PERSONNEL_EXIT '7'

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
 *	viewPassCount shows the number of passengers on a specified trip.
 *	Precondition: trips[] array exists.
 *	@param trips[] Array containing all trips in memory.
 *	@param nTrips Number of trips in the array.
 *	@return None.
 */
void viewPassCount(Trip trips[], int nTrips)
{
	int input, i;
	do {
		printHeader(YELLOW"Passenger Count Viewer"RESET, 80);
		printf(BLUE"Enter a trip number, or type 0 to return: AE");
		scanf("%d", &input);
		printf(RESET);

		// iterate through each trip in the array.
		for (i = 0; i < nTrips; i++) {
			if (trips[i].tripNumber == input) {
				printf(YELLOW"Number of passengers on trip AE%d"RESET": %d\n", trips[i].tripNumber, trips[i].passengerCount);
			}
		}
	} while (input != 0);
}

/*
 *	viewPassAtDrop shows the number of passengers at each drop off point.
 *	Precondition: trips[] array exists.
 *	@param trips[] Array containing all trips in memory.
 *	@param nTrips Number of trips in the array.
 *	@return None.
 */
void viewPassAtDrop(Trip trips[], int nTrips)
{
	int input, i, j;
	do {
		printHeader(YELLOW"Drop-off Point Passenger Count Viewer"RESET, 80);
		printf(BLUE"Enter a trip number, or 0 to return: AE");
		scanf("%d", &input);
		printf(RESET);

		Trip trip;
		Passenger passenger;

		for (i = 0; i < nTrips; i++) {
			trip = trips[i];

			for (j = 0; j < trip.passengerCount; j++) {
				passenger = trip.passengers[j];
				// TODO: finish this function. this will be removed and is just to avoid the warning.
				printf("%s", passenger.Name.firstName);
			}
		}
	} while (input != 0);
}

void viewPassInfo(Trip trips[], int nTrips)
{
	int input, i;
	printf("Enter a trip number: AE");
	scanf("%d", &input);

	for (i = 0; i < nTrips; i++) {
		
	}
}

void loadPassInfo()
{

}

void searchPass(Trip trips[], int nTrips)
{
	int i, j, passengersFound = 0;
	char input[MAX];

	Passenger passenger;

	Passenger output[MAX];

	system("clear||cls");

	do {
		printHeader(YELLOW"Passenger Search"RESET, 80);
		printf(BLUE"Enter the last name of the passenger to search for, or type 0 to return: "RESET);
		scanf("%s", input);

		for (i = 0; i < nTrips; i++) {
			for (j = 0; j < trips[i].passengerCount; j++) {
				passenger = trips[i].passengers[j];
				
				if (strcmp(passenger.Name.lastName, input) == 0) {
					output[passengersFound] = passenger;
					passengersFound++;
				}
			}
		}

		for (i = 0; i < passengersFound; i++) {
			passenger = output[i];
			printf("%d.\n", i + 1);
			printf(YELLOW"Name    :" RESET " %s %s\n", passenger.Name.firstName, passenger.Name.lastName);
			printf(YELLOW "ID      :" RESET " %s\n", passenger.id);
			printf(YELLOW"Priority:" RESET " %d\n", passenger.priorityNumber);
		}

		// error message when no passengers are found.
		if (!passengersFound) {
			system("clear||cls");
			printf(YELLOW"[*]: No passengers found with that last name.\n"RESET);
		}
	} while (strcmp(input, "0") != 0);
}

void loadFile()
{
	Trip trips[TRIP_COUNT];
	Date dateStruct;
	int success;

	do {
		printf("Enter a date to view (DD MM YYYY): ");
		scanf("%d %d %d", &dateStruct.date, &dateStruct.month, &dateStruct.year);

		success = readTrips(trips, dateStruct);
		printf("%d", success); // temp
	} while(dateStruct.date != 0);
}