/*
 *	Solution by: Jay Carlos
 *	viewPassCount shows the number of passengers on a specified trip.
 *	Precondition: trips[] array exists.
 *	@param trips[] Array containing all trips in memory.
 *	@param nTrips Number of trips in the array.
 *	@return None.
 */
void viewPassCount(Trip trips[], int nTrips)
{
	int input, i;
	printHeader(YELLOW"Passenger Count Viewer"RESET, 80);

	do {
		printf(BLUE"Enter a trip number, or type 0 to return: AE");
		scanf("%d", &input);
		printf(RESET);

		// iterate through each trip in the array.
		for (i = 0; i < nTrips; i++) {
			if (trips[i].tripNumber == input) {
				printf(YELLOW"Number of passengers on trip AE%d"RESET": %d\n\n", trips[i].tripNumber, trips[i].passengerCount);
			}
		}
	} while (input != 0);

	system("clear||cls");
}

/*
 *	Solution by: Jay Carlos
 *	viewPassAtDrop shows the number of passengers at each drop off point in a trip.
 *	Precondition: trips[] array exists.
 *	@param trips[] Array containing all trips in memory.
 *	@param nTrips Number of trips in the array.
 *	@return None.
 */
void viewPassAtDrop(Trip trips[], int nTrips)
{
	int input, i, dropOffPt;
	int tripIndex = -1;
	
	int dropOffCounter[13];

	do {
		// reset counters after each iteration.
		for (i = 0; i < 13; i++) {
			dropOffCounter[i] = 0;
		}

		if (tripIndex == -1) {
			printHeader(YELLOW"Drop-off Point Passenger Count Viewer"RESET, 80);
		}

		printf(BLUE"Enter a trip number, or 0 to return: AE");
		scanf("%d", &input);
		printf(RESET);

		Trip trip;
		Passenger passenger;

		tripIndex = getTripIndex(input);

		if (tripIndex != -1) {
			trip = trips[getTripIndex(input)];

			for (i = 0; i < trip.passengerCount; i++) {
				passenger = trip.passengers[i];
				dropOffPt = passenger.dropOffPt;

				dropOffCounter[dropOffPt - 1]++;
			}

			switch (trip.embarkPt) {
			case 0:
				if (trip.route == 0) {
					printf(YELLOW"Trip %d:" RESET " Via Mamplasan exit\n", trip.tripNumber);
					printf(YELLOW"[1.] Mamplasan Toll Exit:" RESET " %d\n", dropOffCounter[0]);
					printf(YELLOW"[2.] Phase 5, San Jose Village:" RESET " %d\n", dropOffCounter[1]);
					printf(YELLOW"[3.] Milagros Del Rosario Building - East Canopy:" RESET " %d\n", dropOffCounter[2]);
				} else {
					printf(YELLOW"Trip %d:" RESET " Via ETON exit\n", trip.tripNumber);
					printf(YELLOW"[1.] Laguna Blvd. Guard House:" RESET " %d\n,", dropOffCounter[3]);
					printf(YELLOW"[2.] Milagros Del Roasrio Building - East Canopy:" RESET " %d\n", dropOffCounter[4]);
				}
				break;
			case 1:
				if (trip.route == 0) {
					printf(YELLOW"Trip %d:" RESET " Via Estrada\n", trip.tripNumber);
					printf(YELLOW"[1.] Petron Gasoline Station along Gil Puyat Avenue:" RESET " %d\n", dropOffCounter[5]);
					printf(YELLOW"[2.] Gate 4: Gokongwei Gate:" RESET " %d\n", dropOffCounter[6]);
					printf(YELLOW"[3.] Gate 2: North Gate (HSSH):" RESET " %d\n", dropOffCounter[7]);
					printf(YELLOW"[4.] Gate 1: South Gate (LS Building Entrance):" RESET " %d\n", dropOffCounter[8]);
				} else {
					printf(YELLOW"Trip %d:" RESET " Via Buendia/LRT\n", trip.tripNumber);
					printf(YELLOW"[1.] College of St. Benilde (CSB) Along Taft:" RESET " %d\n", dropOffCounter[9]);
					printf(YELLOW"[2.] Gate 4: Gokongwei Gate:" RESET " %d\n", dropOffCounter[10]);
					printf(YELLOW"[3.] Gate 2: North Gate (HSSH):" RESET " %d\n", dropOffCounter[11]);
					printf(YELLOW"[4.] Gate 1: South Gate (LS Building Entrance):" RESET " %d\n", dropOffCounter[12]);
				}
				break;
			default:
				break;
			}
			
			printf("\n");
		} else {
			system("clear||cls");
			printf(YELLOW"[*]: Invalid trip number entered.\n"RESET);
		}
	} while (input != 0);

	system("clear||cls");
}

void viewPassInfo(Trip trips[], int nTrips)
{
	int input, i;
	printf("Enter a trip number: AE");
	scanf("%d", &input);

	for (i = 0; i < nTrips; i++) {
		
	}

	system("clear||cls");
}

/*
 *	Solution by: Jay Carlos
 *	searchPass prompts the user to enter a passenger's last name and searches through all trips in memory.
 *	Precondition: Valid number of trips given.
 *	@param trips[] List of trips to check.
 *	@param nTrips Number of trips in list.
 */
void searchPass(Trip trips[], int nTrips)
{
	int i, j, passengersFound = 0;
	char input[MAX];

	Passenger passenger;

	Passenger output[MAX];

	system("clear||cls");

	do {
		// reset passengers found to 0 after each iteration to allow previous searches
		// to be overwritten.
		passengersFound = 0;

		if (!passengersFound) {
			printHeader(YELLOW"Passenger Search"RESET, 80);
		}

		printf(BLUE"Enter the last name of the passenger to search for, or type 0 to return: "RESET);
		scanf("%s", input);

		for (i = 0; i < nTrips; i++) {
			for (j = 0; j < trips[i].passengerCount; j++) {
				passenger = trips[i].passengers[j];
				
				if (strcmp(passenger.name.lastName, input) == 0) {
					output[passengersFound] = passenger;
					passengersFound++;
				}
			}
		}

		for (i = 0; i < passengersFound; i++) {
			passenger = output[i];
			printf("%d.\n", i + 1);
			printf(YELLOW"Name    :" RESET " %s %s\n", passenger.name.firstName, passenger.name.lastName);
			printf(YELLOW"ID      :" RESET " %s\n", passenger.id);
			printf(YELLOW"Priority:" RESET " %d\n", passenger.priorityNumber);
		}

		// error message when no passengers are found.
		if (!passengersFound) {
			system("clear||cls");
			printf(YELLOW"[*]: No passengers found with that last name.\n"RESET);
		}
	} while (strcmp(input, "0") != 0);

	system("clear||cls");
}

/*
 *	Solution by: Tyrrelle Mendoza
 *	viewRecentFile lets the user select a file to view, without overwriting the current data in memory.
 *	Precondition: None.
 *	@return None.
 */
void viewRecentFile()
{
	
	Trip trips[TRIP_COUNT];
	Date dateStruct;
	bool exit = false;
	bool success = false;

	initializeBuses(trips, TRIP_COUNT);

	do {
		if (!success && !exit) {
			printHeader(YELLOW"View file"RESET, 80);
		}
		
		printf(BLUE"Enter a date to view (DD MM YYYY), or 0 0 0 to return: "RESET);
		scanf("%d %d %d", &dateStruct.date, &dateStruct.month, &dateStruct.year);

		if (dateStruct.date == 0 && dateStruct.month == 0 && dateStruct.year == 0) {
			exit = true;
		} else {
			success = readTrips(trips, dateStruct);
		}

		if (!success && !exit) {
			system("clear||cls");
			printf(YELLOW"[*]: Could not find file %02d-%02d-%04d.txt in directory ./trips/.\n"RESET, dateStruct.date, dateStruct.month, dateStruct.year);
		}
	} while(!exit);

	system("clear||cls");
}