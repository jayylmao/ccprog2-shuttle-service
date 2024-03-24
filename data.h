#define MAX_PASSENGERS 16

/*
 *	setTripNumber returns the trip number given the bus index.
 *	Precondition: tripIndex is a valid array index (positive int that does not exceed array length).
 *	@param tripIndex index of bus in array.
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
 *	setEmbarkPt uses the trip number to set the embark point in integer form for that passenger.
 *	This is more convenient in code for, say, comparisons.
 *	@param tripNumber trip number.
 *	@param *dest pointer to integer to save embark point number to.
 *	@return None.
 */
void setEmbarkPt(int tripNumber, int *dest)
{
	if (tripNumber >= 101 && tripNumber <= 109) {
		*dest = 1;
	} else if (tripNumber >= 150 && tripNumber <= 160) {
		*dest = 2;
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

int searchForLowerPriority(int priority, Trip bus)
{
	int i;
	int passengerCount;
	passengerCount = bus.passengerCount;

	for (i = 0; i < passengerCount; i++) {
		if (bus.passengers[i].priorityNumber < priority) {
			return i;
		}
	}

	return -1;
}

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
 *	Precondition: Valid bus array and passenger provided.
 *	@param passenger a passenger object to add to a bus.
 *	@param *bus a pointer to an array of trips for the day.
 *	@param n integer that determines which bus in the array to add the passenger to.
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
 *	getBusIndex returns the corresponding bus index given a trip number.
 *	Precondition: valid trip number is provided.
 *	@param tripNumber trip number from schedule (101 - 109, 150 - 160).
 *	@return index of appropriate bus in array.
 */
int getBusIndex(int tripNumber)
{
	int tripIndex = 0;
	if (tripNumber >= 101 && tripNumber <= 109) {
		tripIndex = tripNumber - 101;
	} else if (tripNumber >= 150 && tripNumber <= 160) {
		tripIndex = tripNumber - 141;
	}

	return tripIndex;
}