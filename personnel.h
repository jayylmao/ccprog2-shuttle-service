#define VIEW_PASSENGERS_COUNT '1'
#define VIEW_PASSENGERS_AT_DROP '2'
#define VIEW_PASSENGER_INFO '3'
#define LOAD_PASSENGER_INFO '4'
#define SEARCH '5'
#define LOAD_FILE '6'
#define PERSONNEL_EXIT '7'

// ANSI Color escape sequences courtesy of https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

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
		printf(BLUE"Enter a trip number, or type 0 to return: AE");
		scanf("%d", &input);
		printf(RESET);

		// iterate through each trip in the array.
		for (i = 0; i < nTrips; i++) {
			if (trips[i].tripNumber == input) {
				printf("Number of passengers on trip AE%d: %d\n", trips[i].tripNumber, trips[i].passengerCount);
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
		printf("Passenger search\n");
		printf("Enter the last name of the passenger to search for, or type 0 to return: ");
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
			printf("%d.\n", i);
			printf("Name    : %s %s\n", passenger.Name.firstName, passenger.Name.lastName);
			printf("ID      : %s\n", passenger.id);
			printf("Priority: %d\n", passenger.priorityNumber);
		}

		// error message when no passengers are found.
		if (!passengersFound) {
			system("clear||cls");
			printf("No passengers found with that last name.\n");
		}
	} while (strcmp(input, "0") != 0);
}

void loadFile()
{
	
}