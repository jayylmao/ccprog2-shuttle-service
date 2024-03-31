// Q1: why do all the inputs use %s even if we want an integer?
//  A: inputting a char into a %d causes the program to freak out. %s doesn't have this issue,
//     so we use a string (%s) as a buffer, before using atoi() to convert it to an integer.
//     atoi() returns 0 if a string that isn't a number is given, which luckily for us,
//     isn't a valid input for most things anyway.
//     all functions that we pass user input into return -1 when an invalid input is given,
//     so we can use that to determine whether user input was valid or not.
// Follow-up Q: how does do-while detect 0 as the "cancel" command when atoi() returns 0 when an invalid input is given?
//           A: the do-while condition checks the buffer, which is before it goes through atoi().
//              if the user enters an invalid value like 'a' for trip number, the buffer is
//              just 'a', while the atoi() conversion stored as the final input is 0.

// Q2: why are all the inputs surrounded by do {} while()?
//  A: this lets an invalid input display an error message and allow the user to try again.

/*
 *	viewPassCount shows the number of passengers on a specified trip.
 *	Solution by: Jay Carlos, modified by: Tyrrelle Mendoza
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
	} while (strcmp(buffer, "0") != 0);

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
	printHeader(YELLOW"Drop-off Point Passenger Count Viewer"RESET, 80);

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
			// new array to sort, so original data isn't affected.
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
	bool success;

	char date[MAX], month[MAX], year[MAX];
	Date dateStruct;

	char filename[MAX];
	int i, j;

	char route[MAX], dropOff[MAX];

	initializeBuses(trips, TRIP_COUNT);

	printHeader(YELLOW"View recent file"RESET, 80);

	do {
		printf(BLUE"Type the date of the file to view passengers from, or 0 to return: "RESET);
		scanf("%s", date);
		
		// Q: why is this split?
		// A: it allows the user to type just one 0 to exit.
		//    if the first digit is not 0, it continues the rest of the func.
		if (strcmp(date, "0") != 0) {
			scanf("%s %s", month, year);

			dateStruct.date = atoi(date);
			dateStruct.month = atoi(month);
			dateStruct.year = atoi(year);

			system("clear||cls");
			printHeader(YELLOW"View recent file"RESET, 80);

			success = readProgramOutputFile(trips, dateStruct);
		}

		// display error message if reading the output file was not successful.
		if (!success && strcmp(date, "0") != 0) {
			printf(YELLOW"[*]: Could not read file %s.\n"RESET, filename);
		} else {
			for (i = 0; i < TRIP_COUNT; i++) {
				if (trips[i].passengerCount > 0) {
					getRouteName(trips[i].route, trips[i].embarkPt, route);
					printf("AE%d\n%s\n", trips[i].tripNumber, route);

					for (j = 0; j < trips[i].passengerCount; j++) {
						printf(YELLOW"[%02d.] Name    : "RESET"%s %s\n", j + 1, trips[i].passengers[j].name.firstName, trips[i].passengers[j].name.lastName);
						printf(YELLOW"      ID      : "RESET"%s\n", trips[i].passengers[j].id);
						printf(YELLOW"      Priority: "RESET"%d\n", trips[i].passengers[j].priorityNumber);
						
						getDropOffName(trips[i].passengers[j].dropOffPt, dropOff);
						printf(YELLOW"      Drop-off: "RESET"%s\n\n", dropOff);
					}
				}
			}
		}
	} while (strcmp(date, "0") != 0);

	system("clear||cls");
}

/*
 *	addPassInfo lets you add passengers from a file instead of inputting them manually.
 *	Note that this file follows a different format from the program output.
 *	Solution by: Jay Carlos, modified by: Tyrrelle Mendoza
 *	Precondition: File is formatted properly.
 *	@param trips[] List of trips to add passengers to.
 *	@param nTrips Number of trips in list.
 */
void addPassInfo(Trip trips[], int nTrips)
{
	FILE *fp;
	char filename[MAX];

	// temporary array to store passengers in.
	Passenger passengers[16];

	// number of passengers.
	int passNum = 0;
	int i;

	// line count.
	int line;

	// buffers for fscanf().
	char buffer[MAX];
	char buffer2[MAX];

	printHeader(YELLOW"Add passenger from file"RESET, 80);

	// validate input. if no file is found with user input, and user doesn't enter the exit code, keep asking for a filename.
	do {
		printf(BLUE"Type the name of the file to add passengers from, or 0 to return: "RESET);
		scanf("%s", filename);

		system("clear||cls");
		printHeader(YELLOW"Add passenger from file"RESET, 80);

		fp = fopen(filename, "r");

		if (fp == NULL) {
			printf(YELLOW"[*]: Could not find file %s.\n"RESET, filename);
		}
	} while (fp == NULL && strcmp(filename, "0") != 0);

	// if exit code is detected, exit function.
	if (strcmp(filename, "0") == 0) {
		system("clear||cls");
		return;
	}

	// start at -1 so first line will be 0.
	line = -1;

	// add the first 16 passengers in the file.
	while (!feof(fp) && passNum < 16) {
		// first line is always name, so format is 2 strings, separated by a space.
		if (line % 5 == 1) {
			fscanf(fp, "%s %s", buffer, buffer2);
		} else {	// otherwise, format is 1 string.
			fscanf(fp, "%s", buffer);
		}

		// increment line count
		line++;

		// line order in file: trip number - priority number - name - id - drop off point
		switch (line % 5) {
			case 0:
				passengers[passNum].tripNumber = atoi(buffer);
				break;
			case 1:
				passengers[passNum].priorityNumber = atoi(buffer);
				break;
			case 2:
				strcpy(passengers[passNum].name.firstName, buffer);
				strcpy(passengers[passNum].name.lastName, buffer2);
				break;
			case 3:
				strcpy(passengers[passNum].id, buffer);
				break;
			case 4:
				passengers[passNum].dropOffPt = atoi(buffer);
				passNum++;
				break;
			default:
				break;
		}
	}

	// add passengers to memory.
	for (i = 0; i < passNum; i++) {
		addPassenger(passengers[i], trips, getTripIndex(passengers[i].tripNumber));
	}

	system("clear||cls");
	printf(GREEN"[/]: %d passengers were successfully added from the file.\n"RESET, passNum);
}