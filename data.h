#define MAX_PASSENGERS 16

/*
 *	setTripNumber returns the trip number given the bus index.
 *	Precondition: busIndex is a valid array index (positive int that does not exceed array length).
 *	@param busIndex index of bus in array.
 *	@return Trip number.
 */
int setTripNumber(int busIndex)
{
	int tripNumber = 0;
	if (busIndex >= 0 && busIndex <= 8) {
		tripNumber += 101 + busIndex;
	} else if (busIndex >= 9 && busIndex <= 19) {
		tripNumber += 141 + busIndex;
	}

	return tripNumber;
}

/*
 *	initializeBuses ensures that the passenger count for all buses is not garbage data upon program launch.
 *	@param buses[] an array of buses to iterate through and initialize.
 *	@param nBuses number of buses in the array.
 *	@return None.
 */
void initializeBuses(Bus buses[], int nBuses)
{
	int i;
	for (i = 0; i < nBuses; i++) {
		buses[i].passengerCount = 0;
		buses[i].tripNumber = setTripNumber(i);
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

void movePassenger(Passenger passenger, int n, Bus *source, Bus *dest)
{

}

int searchForLowerPriority(int priority, Bus bus)
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

int searchForValidBus(int priority, Bus *buses, int nBuses, int n)
{
	int i;
	int validBusIndex = -1;
	int lowerPriorityPassenger;

	bool validBusFound = false;

	for (i = n; i < nBuses && !validBusFound; i++) {
		if (buses[i].passengerCount < MAX_PASSENGERS) {
			validBusIndex = i;

			validBusFound = true;
		} else if (buses[i].passengerCount == MAX_PASSENGERS) {
			lowerPriorityPassenger = searchForLowerPriority(priority, buses[i]);
			validBusIndex = i;

			if (lowerPriorityPassenger != -1) {
				validBusFound = true;
			}
		}
	}

	return validBusIndex;
}

/*
 *	addPassenger adds a Passenger struct to the nth Bus struct in the array.
 *	Precondition: Valid bus array and passenger provided.
 *	@param passenger a passenger object to add to a bus.
 *	@param *bus a pointer to an array of buses for the day.
 *	@param n integer that determines which bus in the array to add the passenger to.
 *	@return None.
 */
void addPassenger(Passenger passenger, Bus *buses, int n)
{
	int passengerCount;
	passengerCount = buses[n].passengerCount;

	bool addSuccess = false;

	while (!addSuccess) {
		if (passengerCount == MAX_PASSENGERS) {
			searchForValidBus(passenger.priorityNumber, buses, 20, n);
		} else {
			buses[n].passengers[passengerCount] = passenger;
			addSuccess = true;
			buses[n].passengerCount++;
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
	int busIndex = 0;
	if (tripNumber >= 101 && tripNumber <= 109) {
		busIndex = tripNumber - 101;
	} else if (tripNumber >= 150 && tripNumber <= 160) {
		busIndex = tripNumber - 141;
	}

	return busIndex;
}

/*
 *	printPassenger is for debug only. 
 *	It prints the info of the nth passenger at the given bus number.
 */
void printPassenger(Bus buses[], int busNum, int passNum)
{
	Passenger passenger = buses[busNum].passengers[passNum];

	char embarkName[60];
	
	printf("Passenger #%d of Bus #%d (%d passengers in bus total) \n", passNum, busNum, buses[busNum].passengerCount);
	printf("Name: %s\n", passenger.name);
	printf("ID: %s\n", passenger.id);
	printf("Priority number: %d\n", passenger.priorityNumber);
	printf("Embark point: %d\n", passenger.embarkPt);
	printf("Embark name: %s\n", embarkName);
	printf("Route: %s\n", passenger.route);
	printf("Drop off number: %d\n", passenger.dropOffPt);
}