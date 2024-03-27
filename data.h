/*
 *	Solution by: Jay Carlos
 *  setDropOffPt returns the name of a drop-off point given its integer representation in the program.
 *  Precondition: Valid drop-off point integer given.
 *  @param dropOffPt Integer representation of drop-off point in program
 *  @param dropOffString Character array to save name of drop-off point to.
 *  @return None.
 */
void setDropOffPt(int dropOffPt, char *dropOffString)
{
	switch (dropOffPt) {
	case 1:
		strcpy(dropOffString, "Mamplasan Toll Exit");
		break;
	case 2:
		strcpy(dropOffString, "San Jose Village");
		break;
	case 3:
	case 5:
		strcpy(dropOffString, "Milagros Del Rosario (MRR) Building - East Canopy");
		break;
	case 4:
		strcpy(dropOffString, "Laguna Blvd. Guard House");
		break;
	case 6:
		strcpy(dropOffString, "Petron Gasoline Station along Gil Puyat Avenue");
		break;
	case 7:
	case 11:
		strcpy(dropOffString, "Gate 4: Gokongwei Gate");
		break;
	case 8:
	case 12:
		strcpy(dropOffString, "Gate 2: North Gate (HSSH)");
		break;
	case 9:
	case 13:
		strcpy(dropOffString, "Gate 1: South Gate (LS Building Entrance)");
		break;
	}
}

void setRoute(int route, int embarkPt, char *dest)
{
	switch (embarkPt) {
	case 0:
		if (route == 0) {
			strcpy(dest, "Via Mamplasan exit");
		} else {
			strcpy(dest, "Via ETON exit");
		}
		break;
	case 1:
		if (route == 0) {
			strcpy(dest, "Via Estrada");
		} else {
			strcpy(dest, "Via Buendia/LRT");
		}
		break;
	default:
		break;
	}
}

/*
 *	Solution by: Jay Carlos
 *	getTripNumber returns the trip number given the trip index.
 *	Precondition: tripIndex is a valid integer.
 *	@param tripIndex index of trip in array.
 *	@return Trip number.
 */
int getTripNumber(int tripIndex)
{
	int tripNumber = 0;
	if (tripIndex >= 0 && tripIndex <= 8) {
		tripNumber += 101 + tripIndex;
	} else if (tripIndex >= 9 && tripIndex <= 19) {
		tripNumber += 141 + tripIndex;
	} else {
		tripNumber = -1;
	}

	return tripNumber;
}

/*
 *	Solution by: Jay Carlos
 *	getTripIndex returns the corresponding trip index given a trip number.
 *	Precondition: Valid integer is provided.
 *	@param tripNumber trip number from schedule (101 - 109, 150 - 160).
 *	@return index of appropriate trip in array.
 */
int getTripIndex(int tripNumber)
{
	int tripIndex = 0;
	if (tripNumber >= 101 && tripNumber <= 109) {
		tripIndex = tripNumber - 101;
	} else if (tripNumber >= 150 && tripNumber <= 160) {
		tripIndex = tripNumber - 141;
	} else {
		tripIndex = -1;
	}

	return tripIndex;
}

/*
 *	Solution by: Tyrrelle Mendoza
 *	getDropOff returns an integer corresponding to a certain string name.
 *	Precondition: Valid place name, route, and embarkation point given.
 *	@param place[] String name of drop-off point.
 *	@param route Integer corresponding to route of trip.
 *	@param embarkNum Embarkation point of trip.
 *	@return Integer corresponding to a given string name.
 */
int getDropOff(char place[], int route, int embarkNum)
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
	size_t len = strlen(place);
    if (len > 0 && place[len - 1] == '\n') {
        place[len - 1] = '\0';
    }

	if (!embarkNum) {
		if (!route) // 0
		{
			if (strcmp("Mamplasan Toll Exit", place) == 0) return 1;
			else if (strcmp("Phase 5, San Jose Village", place) == 0) return 2;
			else if (strcmp("Milagros Del Rosario Building - East Canopy", place) == 0) return 3;
		} else { // 1
			if (strcmp("Laguna Blvd. Guard House", place) == 0) return 4;
			else if (strcmp("Milagros Del Roasrio Building - East Canopy", place) == 0) return 5;
		}
	} else if (embarkNum) {
		if (!route)
		{
			if (strcmp("Petron Gasoline Station along Gil Puyat Avenue", place) == 0) return 6;
			else if (strcmp("Gate 4: Gokongwei Gate", place) == 0) return 7;
			else if (strcmp("Gate 2: North Gate (HSSH)", place) == 0) return 8;
			else if (strcmp("Gate 1: South Gate (LS Building Entrance)", place) == 0) return 9;
		} else {
			if (strcmp("College of St. Benilde (CSB) Along Taft", place) == 0) return 10;
			else if (strcmp("Gate 4: Gokongwei Gate", place) == 0) return 11;
			else if (strcmp("Gate 2: North Gate (HSSH)", place) == 0) return 12;
			else if (strcmp("Gate 1: South Gate (LS Building Entrance)", place) == 0) return 13;
		}
	}

	return -1;
}

/*
 *	Solution by: Jay Carlos
 *	initializeBuses ensures that the passenger count for all trips is not garbage data upon program launch.
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
 *	Solution by: Jay Carlos
 *	setEmbarkName converts the integer representation of the embark point to the string name.
 *	Precondition: Valid trip number provided and destination string has valid length.
 *	@param embarkPtInt Integer representation of embark point name in program.
 *	@param embarkName pointer to string to save embark point name to.
 *	@return None.
 */
void setEmbarkName(int embarkPtInt, char embarkName[])
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
 *	Solution by: Jay Carlos
 *	searchForLowerPriority searches for a passenger with a lower priority in a specified trip, given a specified priority level to check against.
 *	Precondition: None.
 *	@param priority Priority number to check against.
 *	@param trip Trip to check in.
 */
int searchForLowerPriority(int priority, Trip trip)
{
	int i;
	int passengerCount;
	passengerCount = trip.passengerCount;

	for (i = 0; i < passengerCount; i++) {
		if (trip.passengers[i].priorityNumber < priority) {
			return i;
		}
	}

	return -1;
}

/*
 *	Solution by: Jay Carlos
 *	addPassenger adds a Passenger struct to the nth Trip struct in the array.
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
	
	if (passengerCount == MAX_PASSENGERS) {
		lowerPriorityPassenger = searchForLowerPriority(passenger.priorityNumber, trips[n]);

		if (lowerPriorityPassenger == -1 && n < TRIP_COUNT - 1) {
			printf(YELLOW"[*]: You have been moved to AE%d.\n"RESET, getTripNumber(n + 1));
			addPassenger(passenger, trips, n + 1); // if no lower priority found, try next bus.
		} else if (n < TRIP_COUNT - 1) {
			printf(YELLOW"[*]: A person of lower priority has been moved to AE%d to make space for you.\n"RESET, getTripNumber(n + 1));
			addPassenger(trips[n].passengers[lowerPriorityPassenger], trips, n + 1); // otherwise, move lower priority passenger to next bus.
			trips[n].passengers[passengerCount] = passenger; // replace old slot with new passenger.
		} else {
			printf(YELLOW"[*]: The system is completely unable to accept any more passengers.\n"RESET);
		}
	} else {
		trips[n].passengers[passengerCount] = passenger;
		trips[n].passengerCount++;
	}
}