/*
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

		if (i < 11) {
			trips[i].embarkPt = 0;
		} else {
			trips[i].embarkPt = 1;
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
			addPassenger(passenger, trips, n + 1); // if no lower priority found, try next bus.
		} else if (n < TRIP_COUNT - 1) {
			addPassenger(trips[n].passengers[lowerPriorityPassenger], trips, n + 1); // otherwise, move lower priority passenger to next bus.
			trips[n].passengers[passengerCount] = passenger; // replace old slot with new passenger.
		} else {
			printf("[*]: The system is completely unable to accept any more passengers.\n");
		}
	} else {
		trips[n].passengers[passengerCount] = passenger;
		trips[n].passengerCount++;
	}
}