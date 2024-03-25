#define MAX_PASSENGERS 16

/*
 *	setTripNumber returns the trip number given the trip index.
 *	Precondition: tripIndex is a valid array index (positive int that does not exceed array length).
 *	@param tripIndex index of trip in array.
 *	@return Trip number.
 */
int setTripNumber(int tripIndex)
{
	int tripNumber = 0;
	if (tripIndex >= 0 && tripIndex <= 8) {
		tripNumber += 101 + tripIndex;
	} else if (tripIndex >= 9 && tripIndex <= 19) {
		tripNumber += 141 + tripIndex;
	}

	return tripNumber;
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
		trips[i].tripNumber = setTripNumber(i);
		
		// set all passengers to -1 to serve as an "invalid" id.
		for (j = 0; j < 16; j++) {
			strcpy(trips[i].passengers[j].id, "-1");
		}
	}
}

/*
 *	setEmbarkName uses a trip number to write the embark point for that passenger.
 *	Precondition: Valid trip number provided and destination string has valid length.
 *	@param tripNumber trip number.
 *	@param embarkName pointer to string to save embark point name to.
 *	@return None.
 */
void setEmbarkName(int tripNumber, char embarkName[])
{
	if (tripNumber >= 101 && tripNumber <= 109) {
		strcpy(embarkName, "South Gate Driveway (Manila Campus)");
	} else if (tripNumber >= 150 && tripNumber <= 160) {
		strcpy(embarkName, "Milagros del Rosario Building - East Canopy (Laguna Campus)");
	} else {
		strcpy(embarkName, "Unknown trip number.");
	}
}

/*
 *	
 */
void setRoute(int tripNumber, char *dest)
{

}

void movePassenger(Passenger passenger, int n, Trip *source, Trip *dest)
{

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
 *	searchForValidBus returns the index of the first non-full trip it finds in the array.
 *	Precondition: 
 */
int searchForValidBus(int priority, Trip *trips, int nTrips, int n)
{
	int i;
	int validBusIndex = -1;
	int lowerPriorityPassenger;

	bool validBusFound = false;

	for (i = n; i < nTrips && !validBusFound; i++) {
		if (trips[i].passengerCount < MAX_PASSENGERS) {
			validBusIndex = i;

			validBusFound = true;
		} else if (trips[i].passengerCount == MAX_PASSENGERS) {
			lowerPriorityPassenger = searchForLowerPriority(priority, trips[i]);
			validBusIndex = i;

			if (lowerPriorityPassenger != -1) {
				validBusFound = true;
			}
		}
	}

	return validBusIndex;
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
	int passengerCount;
	passengerCount = trips[n].passengerCount;

	bool addSuccess = false;

	while (!addSuccess) {
		if (passengerCount == MAX_PASSENGERS) {
			searchForValidBus(passenger.priorityNumber, trips, 20, n);
		} else {
			trips[n].passengers[passengerCount] = passenger;
			addSuccess = true;
			trips[n].passengerCount++;
		}
	}
}

/*
 *	getTripIndex returns the corresponding trip index given a trip number.
 *	Precondition: valid trip number is provided.
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
	}

	return tripIndex;
}