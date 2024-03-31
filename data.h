/*
 *	getTripNumber returns the trip number given the trip index.
 *	Solution by: Jay Carlos
 *	Precondition: tripIndex is a valid integer.
 *	@param tripIndex index of trip in array.
 *	@return Trip number.
 */
int getTripNumber(int tripIndex)
{
	FILE *fp;
	int tripNumber = -1;
	int i = -1;
	int hour, minute;

	fp = fopen("./config/tripSched.txt", "r");

	// file not found.
	if (fp == NULL) {
		printf(RED"[!]: Trip schedule file (./config/tripSched.txt) could not be found.\n"RESET);
		return tripNumber;
	}

	// for each line in the file until i is not equal to the given index, increment i.
	while (!feof(fp) && i < tripIndex) {
		fscanf(fp, "%d %d %d", &tripNumber, &hour, &minute);
		i++;
	}

	// the trip number is found at the start of the line and will be returned.
	return tripNumber;
}

/*
 *	getTripIndex returns the corresponding trip index given a trip number.
 *	Solution by: Jay Carlos
 *	Precondition: Valid integer is provided.
 *	@param tripNumber trip number from schedule (101 - 109, 150 - 160).
 *	@return index of appropriate trip in array.
 */
int getTripIndex(int tripNumber)
{
	FILE *fp;
	int fileTripNumber;
	int hour, minute;

	int tripIndex = -1;
	bool tripFound = false;

	fp = fopen("./config/tripSched.txt", "r");

	// file not found.
	if (fp == NULL) {
		printf(RED"[!]: Trip schedule file (./config/tripSched.txt) could not be found.\n"RESET);
		return tripIndex;
	}

	// while the trip number in the line being read from the file has not matched the given trip number,
	// increment the trip index.
	while (!feof(fp) && fileTripNumber != tripNumber) {
		fscanf(fp, "%d %d %d", &fileTripNumber, &hour, &minute);
		tripIndex++;

		if (fileTripNumber == tripNumber) {
			tripFound = true;
		}
	}

	if (!tripFound) {
		tripIndex = -1;
	}

	fclose(fp);
	return tripIndex;
}

/*
 *	getDropOff returns an integer corresponding to a certain string name.
 *	Solution by: Tyrrelle Mendoza
 *	Precondition: Valid place name, route, and embarkation point given.
 *	@param route Integer corresponding to route of trip.
 *	@param embarkNum Embarkation point of trip.
 *	@param *dest Character array to compare drop-off point name to.
 *	@return Integer corresponding to a given string name.
 */
int getDropOff(int route, int embarkNum, char *dest)
{
	/*
	 *	Mamplasan Toll Exit
	 *	Phase 5, San Jose Village
	 *	Milagros Del Rosario Building - East Canopy
	 *
	 *	Laguna Blvd. Guard House
	 *	Milagros Del Roasrio Building - East Canopy
	 *
	 *	Petron Gasoline Station along Gil Puyat Avenue
	 *	Gate 4: Gokongwei Gate
	 *	Gate 2: North Gate (HSSH)
	 *	Gate 1: South Gate (LS Building Entrance)
	 *
	 *	College of St. Benilde (CSB) Along Taft
	 *	Gate 4: Gokongwei Gate
	 *	Gate 2: North Gate (HSSH)
	 *	Gate 1: South Gate (LS Building Entrance)
	 */

	// remove newline
	size_t len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\n') {
        dest[len - 1] = '\0';
    }

	if (embarkNum == 0) {
		if (!route) { // 0
			if (strcmp("Mamplasan Toll Exit", dest) == 0) return 1;
			else if (strcmp("Phase 5, San Jose Village", dest) == 0) return 2;
			else if (strcmp("Milagros Del Rosario Building - East Canopy", dest) == 0) return 3;
		} else { // 1
			if (strcmp("Laguna Blvd. Guard House", dest) == 0) return 4;
			else if (strcmp("Milagros Del Roasrio Building - East Canopy", dest) == 0) return 5;
		}
	} else if (embarkNum == 1) {
		if (!route) {
			if (strcmp("Petron Gasoline Station along Gil Puyat Avenue", dest) == 0) return 6;
			else if (strcmp("Gate 4: Gokongwei Gate", dest) == 0) return 7;
			else if (strcmp("Gate 2: North Gate (HSSH)", dest) == 0) return 8;
			else if (strcmp("Gate 1: South Gate (LS Building Entrance)", dest) == 0) return 9;
		} else {
			if (strcmp("College of St. Benilde (CSB) Along Taft", dest) == 0) return 10;
			else if (strcmp("Gate 4: Gokongwei Gate", dest) == 0) return 11;
			else if (strcmp("Gate 2: North Gate (HSSH)", dest) == 0) return 12;
			else if (strcmp("Gate 1: South Gate (LS Building Entrance)", dest) == 0) return 13;
		}
	}

	return -1;
}

/*
 *	initializeBuses ensures that the passenger count for all trips is not garbage data upon program launch.
 *	Solution by: Jay Carlos
 *	@param trips[] an array of trips to iterate through and initialize.
 *	@param nTrips number of trips in the array.
 *	@return None.
 */
void initializeBuses(Trip trips[], int nTrips)
{
	int i, j;
	for (i = 0; i < nTrips; i++) {
		trips[i].passengerCount = 0;
		trips[i].tripNumber = getTripNumber(i);

		if (i < 12) {
			trips[i].embarkPt = 0;
		} else {
			trips[i].embarkPt = 1;
		}

		if (i == 11 || i == 21) {
			trips[i].isEmergencyShuttle = true;
		} else {
			trips[i].isEmergencyShuttle = false;
		}

		// initialize half of trips to be on the first route for each embark point.
		if (i < 6 || (i > 10 && i < 16)) {
			trips[i].route = 0;
		} else {
			trips[i].route = 1;
		}
		
		// set all passengers to -1 to serve as an "invalid" id.
		for (j = 0; j < 16; j++) {
			strcpy(trips[i].passengers[j].id, "-1");
		}
	}
}

/*
 *	getEmbarkationPointName converts the integer representation of the embark point to the string name.
 *	Solution by: Jay Carlos
 *	Precondition: Valid trip number provided and destination string has valid length.
 *	@param embarkPtInt Integer representation of embark point name in program.
 *	@param embarkName pointer to string to save embark point name to.
 *	@return None.
 */
void getEmbarkationPointName(int embarkPtInt, char embarkName[])
{
	switch (embarkPtInt) {
		case 0:
			strcpy(embarkName, "South Gate Driveway (Manila Campus)");
			break;
		case 1:
			strcpy(embarkName, "Milagros del Rosario Building - East Canopy (Laguna Campus)");
			break;
		default:
			strcpy(embarkName, "Unknown embarkation point.");
			break;
	}
}	

/*
 *	searchForLowerPriority searches for a passenger with a lower priority in a specified trip, given a specified priority level to check against.
 *	Solution by: Jay Carlos
 *	Precondition: None.
 *	@param priority Priority number to check against.
 *	@param trip Trip to check in.
 */
int searchForLowerPriority(int priority, Trip trip)
{
	int i, min = priority;
	int lowerPriorityIndex = -1;
	int passengerCount;
	passengerCount = trip.passengerCount;

	// if statement uses > because smaller number is greater priority in the system. 
	// ex: 1 is higher priority than 2, so if passenger 3 has prio 2 but the passenger
	// we're adding has prio 1, passenger 3 has a lower prio.
	for (i = 0; i < passengerCount; i++) {
		if (trip.passengers[i].priorityNumber > min) {
			min = trip.passengers[i].priorityNumber;
			lowerPriorityIndex = i;
		}
	}

	return lowerPriorityIndex;
}

/*
 *	addPassenger adds a Passenger struct to the nth Trip struct in the array.
 *	Solution by: Jay Carlos
 *	Precondition: Valid trip array and passenger provided.
 *	@param passenger a passenger object to add to a trip.
 *	@param *trip a pointer to an array of trips for the day.
 *	@param n integer that determines which trip in the array to add the passenger to.
 *	@return None.
 */
void addPassenger(Passenger passenger, Trip *trips, int n)
{
	int passengerCount, lowerPriorityPassenger;
	passengerCount = trips[n].passengerCount;

	char dropOff[MAX];
	getDropOffName(passenger.dropOffPt, dropOff);
	
	if (passengerCount >= MAX_PASSENGERS) {
		lowerPriorityPassenger = searchForLowerPriority(passenger.priorityNumber, trips[n]);

		if (lowerPriorityPassenger == -1 && trips[n].embarkPt == trips[n + 1].embarkPt) {
			printf(YELLOW"[*]: You have been moved to AE%d.\n"RESET, getTripNumber(n + 1));
			if (getTripNumber(n + 1) == 110 || getTripNumber(n + 1) == 161) {
				printf(YELLOW"[*]: Due to a high amount of passengers, an emergency shuttle has been dispatched.\n"RESET);
			}
			addPassenger(passenger, trips, n + 1); // if no lower priority found, try next bus.
		} else if (trips[n].embarkPt == trips[n + 1].embarkPt) {
			printf(YELLOW"[*]: A person of lower priority has been moved to AE%d to make space for you.\n"RESET, getTripNumber(n + 1));
			addPassenger(trips[n].passengers[lowerPriorityPassenger], trips, n + 1); // otherwise, move lower priority passenger to next bus.
			trips[n].passengers[lowerPriorityPassenger] = passenger; // replace old slot with new passenger.
		} else {
			printf(YELLOW"[*]: The system is completely unable to accept any more passengers.\n"RESET);
		}
	} else {
		while (strcmp(dropOff, "Unknown") == 0 && passenger.dropOffPt < 1) {
			passenger.dropOffPt--;
			getDropOffName(passenger.dropOffPt, dropOff);
		}

		trips[n].passengers[passengerCount] = passenger;
		trips[n].passengerCount++;
	}
}