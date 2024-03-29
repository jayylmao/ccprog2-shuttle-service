/*
 *	viewPassCount shows the number of passengers on a specified trip.
 *	Solution by: Jay Carlos
 *	Precondition: trips[] array exists.
 *	@param trips[] Array containing all trips in memory.
 *	@param nTrips Number of trips in the array.
 *	@return None.
 */
void viewPassCount(Trip trips[], int nTrips)
{
	char buffer[MAX];
	int input, i;
	bool tripFound = false;

	printHeader(YELLOW"Passenger Count Viewer"RESET, 80);

	do {
		printf(BLUE"Enter a trip number, or type 0 to return: AE");
		scanf("%s", buffer);
		input = atoi(buffer);
		printf(RESET);

		tripFound = false;

		system("clear||cls");
		printHeader(YELLOW"Passenger Count Viewer"RESET, 80);

		// iterate through each trip in the array.
		for (i = 0; i < nTrips; i++) {
			if (trips[i].tripNumber == input) {
				printf(YELLOW"Number of passengers on trip AE%d"RESET": %d\n\n", trips[i].tripNumber, trips[i].passengerCount);
				tripFound = true;
			}
		}

		if (!tripFound) {
			printf(YELLOW"[*]: Invalid trip number.\n"RESET);
		}
	} while (input != 0);

	system("clear||cls");
}

/*
 *	viewPassAtDrop shows the number of passengers at each drop off point in a trip.
 *	Solution by: Jay Carlos
 *	Precondition: trips[] array exists.
 *	@param trips[] Array containing all trips in memory.
 *	@param nTrips Number of trips in the array.
 *	@return None.
 */
void viewPassAtDrop(Trip trips[], int nTrips)
{
	char buffer[MAX];
	int input, i, dropOffPt;
	int tripIndex = -1;
	
	int dropOffCounter[13];

	do {
		// reset counters after each iteration.
		for (i = 0; i < 13; i++) {
			dropOffCounter[i] = 0;
		}

		printf(BLUE"Enter a trip number, or 0 to return: AE");
		scanf("%s", buffer);
		input = atoi(buffer);
		printf(RESET);

		system("clear||cls");
		printHeader(YELLOW"Drop-off Point Passenger Count Viewer"RESET, 80);

		Trip trip;
		Passenger passenger;

		tripIndex = getTripIndex(input);

		if (tripIndex != -1) {
			trip = trips[tripIndex];

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
			printf(YELLOW"[*]: Invalid trip number entered.\n"RESET);
		}
	} while (strcmp(buffer, "0") != 0);

	system("clear||cls");
}

/*
 *	viewPassInfo lets the user view all passengers on a trip, sorted by priority.
 *	Solution by: Jay Carlos
 *	Precondition: Valid trips array and positive integer number of trips given.
 *	@param trips[] List of trips.
 *	@param nTrips Number of trips in list.
 */
void viewPassInfo(Trip trips[], int nTrips)
{
	int i, passengerCount;
	char buffer[MAX];
	int tripIndex;

	Passenger temp;

	bool continueSort;

	Trip trip;

	printHeader(YELLOW"View passenger info"RESET, 80);

	do {
		printf(BLUE"Enter a trip number: AE");
		scanf("%s", buffer);
		printf(RESET);

		system("clear||cls");
		printHeader(YELLOW"View passenger info"RESET, 80);

		tripIndex = getTripIndex(atoi(buffer));
		trip = trips[tripIndex];
		passengerCount = trip.passengerCount;

		if (passengerCount != 0) {
			Passenger sortedPassengers[passengerCount];

			// copy all passengers to new array for sorting.
			for (i = 0; i < passengerCount; i++) {
				sortedPassengers[i] = trip.passengers[i];
			}

			// bubble sort
			do {
				continueSort = false;
				for (i = 0; i < passengerCount - 1; i++) {
					if (sortedPassengers[i].priorityNumber > sortedPassengers[i + 1].priorityNumber) {
						temp = sortedPassengers[i];
						sortedPassengers[i] = sortedPassengers[i + 1];
						sortedPassengers[i + 1] = temp;
						continueSort = true;	// if no sorting is done in a pass, continueSort remains false and the loop can end.
					}
				}
			} while (continueSort);

			// print sorted passenger list
			printf(YELLOW"Trip "RESET"AE%d\n", trip.tripNumber);
			for (i = 0; i < passengerCount; i++) {
				printf(YELLOW"[%02d.] Name           : "RESET"%s %s\n", i + 1, sortedPassengers[i].name.firstName, sortedPassengers[i].name.lastName);
				printf(YELLOW"      ID             : "RESET"%s\n", sortedPassengers[i].id);
				printf(YELLOW"      Priority Number: "RESET"%d\n\n", sortedPassengers[i].priorityNumber);
			}
		} else {
			printf(YELLOW"[*]: No passengers found on that trip.\n"RESET);
		}
	} while (strcmp(buffer, "0") != 0);

	system("clear||cls");
}

/*
 *	searchPass prompts the user to enter a passenger's last name and searches through all trips in memory.
 *	Solution by: Jay Carlos
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

	printHeader(YELLOW"Passenger Search"RESET, 80);

	do {
		// reset passengers found to 0 after each iteration to allow previous searches
		// to be overwritten.
		passengersFound = 0;

		printf(BLUE"Enter the last name of the passenger to search for, or type 0 to return: "RESET);
		scanf("%s", input);

		system("clear||cls");
		printHeader(YELLOW"Passenger Search"RESET, 80);

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
			printf(YELLOW"[%02d.] Name           :" RESET " %s %s\n", i + 1, passenger.name.firstName, passenger.name.lastName);
			printf(YELLOW"      ID             :" RESET " %s\n", passenger.id);
			printf(YELLOW"      Priority Number:" RESET " %d\n", passenger.priorityNumber);
		}

		// error message when no passengers are found.
		if (!passengersFound) {
			printf(YELLOW"[*]: No passengers found with that last name.\n"RESET);
		}
	} while (strcmp(input, "0") != 0);

	system("clear||cls");
}

/*
 *	viewRecentFile lets the user select a file to view, without overwriting the current data in memory.
 *	Solution by: Tyrrelle Mendoza
 *	Precondition: None.
 *	@return None.
 */
void viewRecentFile()
{
	
	Trip trips[TRIP_COUNT];
	char date[MAX], month[MAX], year[MAX];
	Date dateStruct;
	bool exit = false;
	bool success = false;

	initializeBuses(trips, TRIP_COUNT);

	printHeader(YELLOW"View file"RESET, 80);

	do {		
		printf(BLUE"Enter a date to view (DD MM YYYY), or 0 0 0 to return: "RESET);
		scanf("%s %s %s", date, month, year);
		dateStruct.date = atoi(date);
		dateStruct.month = atoi(month);
		dateStruct.year = atoi(year);

		system("clear||cls");
		printHeader(YELLOW"View file"RESET, 80);

		if (dateStruct.date == 0 && dateStruct.month == 0 && dateStruct.year == 0) {
			exit = true;
		} else {
			success = readTrips(trips, dateStruct);
		}

		if (!success && !exit) {
			printf(YELLOW"[*]: Could not find file %02d-%02d-%04d.txt in directory ./trips/.\n"RESET, dateStruct.date, dateStruct.month, dateStruct.year);
		}
	} while(!exit);

	system("clear||cls");
}