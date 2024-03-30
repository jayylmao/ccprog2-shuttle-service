/*
 *	displayTrip visualizes the bus the user has selected on screen.
 *	Solution by: Jay Carlos
 *	Precondition: A valid trip number is provided.
 *	@param tripNumber Integer corresponding to trip number.
 *	@trips[] Array of trips to get trip information from.
 *	@return None.
 */
void displayTrip(int tripNumber, Trip trips[])
{
	int busIndex, i;
	busIndex = getTripIndex(tripNumber);

	Trip trip = trips[busIndex];

	if (trip.passengerCount < 13) {	// standard seating
		printf(".____.____.____.\n");

		for (i = 0; i < 13; i++) {
			if (i == trip.passengerCount) { // print assigned seat number in green.
				printf("| "GREEN"%02d "RESET, i + 1);
			} else if (strcmp(trip.passengers[i].id, "-1") == 0) { // print seat number if not occupied
				printf("| %02d ", i + 1);
			} else { // print XX if seat is occupied
				printf("| XX ");
			}

			if ((i + 1) % 3 == 0 && i != 0) { // print separator + newline for each row of seats
				printf("| \n");
				printf(".____.____.____.\n");
			}
		}

		printf("| Driver  |\n");
		printf(".____.____.____.\n");
	} else {	// high-volume seating
		printf(".____.____.____.____.\n");

		for (i = 0; i < 16; i++) {
			if (i == trip.passengerCount) { // print assigned seat number in green.
				printf("| "GREEN"%02d "RESET, i + 1);
			} else if (strcmp(trip.passengers[i].id, "-1") == 0 && (i + 1) == 16) { // last row has a different format
				printf("| %02d      | Driver  ", i + 1);
			} else if (strcmp(trip.passengers[i].id, "-1") == 0) { // print seat number if not occupied
				printf("| %02d ", i + 1);
			} else { // print XX if seat is occupied
				printf("| XX ");
			}

			if ((i + 1) == 12) { // 12th seating has a blank space after it in the row below
				printf("| \n");
				printf(".____.____.____.____.\n");
				printf("|    ");
			} else if (((i + 1) % 4 == 0 || (i + 1) == 15) && i != 0) { // print separator + newline for each row of seats
				printf("| \n");
				printf(".____.____.____.____.\n");
			}
		}

		printf(".____.____.____.____.\n");
	}
}

/*
 *	inputTripNumber asks the user to input a trip number.
 *	Solution by: Jay Carlos
 *	Precondition: Called from passengerRoutine().
 *	@return tripNumber Validated trip number entered by user.
 */
int inputTripNumber()
{
	char input[MAX];
	int tripNumber, tripIndex;

	do {
		printf("======[ "GREEN"Add passenger - Trip Number"RESET " ]===========================================\n");
		printHeader("[ "GREEN"1"RESET" ]---[ 2 ]---[ 3 ]---[ 4 ]---[ 5 ]---[ 6 ]", 80);
		
		printf(BLUE"Enter trip number: " RESET "AE");
		scanf("%s", input);

		tripNumber = atoi(input);
		tripIndex = getTripIndex(tripNumber);

		if (tripIndex == -1) {
			system("clear||cls");
			printf(YELLOW"[*]: Enter a valid trip number (101 - 109, 150 - 160).\n"RESET);
		}
	} while (tripIndex == -1);

	return tripNumber;
}

/*
 *	inputPriorityNumber asks the user to input a priority number.
 *	Solution by: Jay Carlos
 *	Precondition: Called from passengerRoutine().
 *	@return priorityNumber Validated priority number entered by user.
 */
int inputPriorityNumber()
{
	char input[MAX];
	int priorityNumber;
	priorityNumber = 0;

	do {
		printf("======[ "GREEN"Add passenger - Priority Number"RESET " ]=======================================\n");
		printHeader("[ 1 ]---[ "GREEN"2"RESET" ]---[ 3 ]---[ 4 ]---[ 5 ]---[ 6 ]", 80);

		printf(YELLOW"Priority numbers:\n");
		printf("[1.] "RESET"Faculty & ASF with Inter-campus assignments\n");
		printf(YELLOW"[2.] "RESET"Students with Inter-campus enrolled subjects/thesis\n");
		printf(YELLOW"[3.] "RESET"Researchers\n");
		printf(YELLOW"[4.] "RESET"School Administrators\n");
		printf(YELLOW"[5.] "RESET"University Fellows\n");
		printf(YELLOW"[6.] "RESET"Employees and Students with official business\n");
		printf(RED"[!]: Falsifying priority is subject to severe disciplinary action.\n");

		printf(BLUE"Enter priority number: " RESET);
		scanf("%s", input);

		priorityNumber = atoi(input);

		if (priorityNumber < 1 || priorityNumber > 6) {
			system("clear||cls");
			printf(YELLOW"[*]: Enter a valid priority number (1 - 6).\n"RESET);
		}
	} while (priorityNumber < 1 || priorityNumber > 6);

	return priorityNumber;
}

/*
 *	inputName asks the user to input a first and last name.
 *	Solution by: Jay Carlos
 *	Precondition: Called from passengerRoutine().
 *	@return name Struct containing first and last name.
 */
Name inputName()
{
	Name name;
	strcpy(name.firstName, "");
	strcpy(name.lastName, "");

	do {
		printf("======[ "GREEN"Add passenger - Name"RESET " ]==================================================\n");
		printHeader("[ 1 ]---[ 2 ]---[ "GREEN"3"RESET" ]---[ 4 ]---[ 5 ]---[ 6 ]", 80);

		printf(BLUE"Enter name (First name last name): " RESET);
		scanf("%s %s", name.firstName, name.lastName);

		if (strcmp(name.firstName, "") == 0 || strcmp(name.lastName, "") == 0) {
			system("clear||cls");
			printf(YELLOW"[*]: Enter a valid first and last name, separated by a space.\n"RESET);
		}
	} while (strcmp(name.firstName, "") == 0 || strcmp(name.lastName, "") == 0);

	return name;
}

/*
 *	inputId asks the user to input an ID.
 *	Solution by: Jay Carlos
 *	Precondition: Called from passengerRoutine() and valid destination string provided.
 *	@return None.
 */
void inputId(char *dest)
{
	char id[MAX];

	do {
		printf("======[ "GREEN"Add passenger - ID"RESET " ]====================================================\n");
		printHeader("[ 1 ]---[ 2 ]---[ 3 ]---[ "GREEN"4"RESET" ]---[ 5 ]---[ 6 ]", 80);
		
		printf(BLUE"Enter ID: " RESET);
		scanf("%s", id);

		if (strlen(id) != 8 || atoi(id) == 0) {
			system("clear||cls");
			printf(YELLOW"[*]: Enter a valid ID (8 numbers).\n"RESET);
		}
	} while (strlen(id) != 8 || atoi(id) == 0);

	strcpy(dest, id);
}

/*
 *	inputDropOff displays a list of exits and drop-off points for the user to select from.
 *	Solution by: Jay Carlos
 *	Precondition: A valid trip number must be given.
 *	@param tripNumber Integer corresponding to trip number.
 *	@return Integer corresponding to the drop-off point.
 */
int inputDropOff(int embarkPoint, int route)
{
	char input[MAX];
	// dropOff is where the user's input is stored.
	// menuLimit is an upper bound for the menu to determine input validity.
	int dropOff, menuLimit, offset;

	do {
		printf("======[ "GREEN"Add passenger - Route"RESET " ]=================================================\n");
		printHeader("[ 1 ]---[ 2 ]---[ 3 ]---[ 4 ]---[ "GREEN"5"RESET" ]---[ 6 ]", 80);

		// shows a different set of available routes depending on the user embark point and set trip route.
		printf(YELLOW"Route: "RESET);
		switch (embarkPoint) {
			case 0:
				if (route == 0) {
					printf("Via Mamplasan exit\n");
					printf(YELLOW"[1.] "RESET"Mamplasan Toll Exit\n");
					printf(YELLOW"[2.] "RESET"Phase 5, San Jose Village\n");
					printf(YELLOW"[3.] "RESET"Milagros Del Rosario Building - East Canopy\n");
					menuLimit = 3;
				} else {
					printf("Via ETON exit\n");
					printf(YELLOW"[1.] "RESET"Laguna Blvd. Guard House\n");
					printf(YELLOW"[2.] "RESET"Milagros Del Roasrio Building - East Canopy\n");
					menuLimit = 2;
					offset = 3;
				}
				break;
			case 1:
				menuLimit = 4;

				if (route == 0) {
					printf("Via Estrada\n");
					printf(YELLOW"[1.] "RESET"Petron Gasoline Station along Gil Puyat Avenue\n");
					printf(YELLOW"[2.] "RESET"Gate 4: Gokongwei Gate\n");
					printf(YELLOW"[3.] "RESET"Gate 2: North Gate (HSSH)\n");
					printf(YELLOW"[4.] "RESET"Gate 1: South Gate (LS Building Entrance)\n");
					offset = 5;
				} else {
					printf("Via Buendia/LRT\n");
					printf(YELLOW"[1.] "RESET"College of St. Benilde (CSB) Along Taft\n");
					printf(YELLOW"[2.] "RESET"Gate 4: Gokongwei Gate\n");
					printf(YELLOW"[3.] "RESET"Gate 2: North Gate (HSSH)\n");
					printf(YELLOW"[4.] "RESET"Gate 1: South Gate (LS Building Entrance)\n");
					offset = 9;
				}
			default:
				break;
		}
		
		printf(BLUE"Choose a drop-off point: "RESET);
		scanf("%s", input);

		dropOff = atoi(input);

		if (dropOff < 1 || dropOff > menuLimit) {
			system("clear||cls");
			printf(YELLOW"[*]: Select a drop-off point from 1 to %d.\n"RESET, menuLimit);
		}
	} while (dropOff < 1 || dropOff > menuLimit);

	// drop-off points are stored from 1 - 13, so the mamplasan exit drop-offs are 1 - 3, eton are 4 - 5, and so on.
	return dropOff + offset;
}

/*
 *	reviewDetails lets the user review the information they entered, and redo if needed.
 *	Solution by: Jay Carlos
 *	@param passenger The passenger whose information was just entered and is being reviewed.
 *	@param embarkPt Integer corresponding to embark point of passenger's trip.
 *	@param route Route of trip.
 *	@param trips[] List of trips in memory.
 *	@return Boolean determining if the information was marked as correct or not.
 */
bool reviewDetails(Passenger passenger, int embarkPt, int route, Trip trips[])
{
	char input[MAX];
	char dropOffName[MAX];
	char routeName[MAX];
	char priorityName[MAX];
	char time[6];

	// 0 is don't exit, 1 is done, 2 is go back to the start.
	int exitStatus = 0;

	Trip trip;
	trip = trips[getTripIndex(passenger.tripNumber)];
	
	do {
		printf("======[ "GREEN"Add passenger - Review Details"RESET " ]========================================\n");
		printHeader("[ 1 ]---[ 2 ]---[ 3 ]---[ 4 ]---[ 5 ]---[ "GREEN"6"RESET" ]", 80);

		displayTrip(passenger.tripNumber, trips);

		printf("\n\n[Personal Information]\n");
		printf(GREEN"Name          : "RESET"%s %s\n", passenger.name.firstName, passenger.name.lastName);
		printf(GREEN"ID            : "RESET"%s\n", passenger.id);

		getPriorityGroupName(passenger.priorityNumber, priorityName);
		printf(GREEN"Priority Group: "RESET"%s (%d)\n", priorityName, passenger.priorityNumber);
		
		printf("\n[Trip Information]\n");
		printf(GREEN"Trip Number   : "RESET"AE%d\n", passenger.tripNumber);
		
		getTime(trip.tripNumber, time);
		printf(GREEN"Time          : "RESET"%s\n", time);
		getRouteName(trip.route, trip.embarkPt, routeName);
		printf(GREEN"Route         : "RESET"%s\n", routeName);

		getDropOffName(passenger.dropOffPt, dropOffName);
		printf(GREEN"Drop-off Point: "RESET"%s\n\n", dropOffName);

		printf(BLUE"Review information. Enter 1 to exit and 2 to restart: " RESET);
		scanf("%s", input);

		if (atoi(input) == 1 || atoi(input) == 2) {
			exitStatus = atoi(input);
		} else {
			system("clear||cls");
			printf(YELLOW"[*]: Enter either 1 to exit or 2 to restart.\n"RESET);
		}
	} while (!exitStatus);

	if (exitStatus == 1) {
		return true;
	} else {
		return false;
	}
}

/*
 *	passengerRoutine allows a passenger to select a trip to embark on.
 *	Solution by: Jay Carlos
 *	Precondition: Valid date is entered.
 *	@param date Date to pass to the writePassenger function.
 *	@param *trips List of trips to add user to.
 *	@param nTrips Number of trips in the list.
 *	@return None.
 */
void passengerRoutine(Date date, Trip *trips, int nTrips)
{
	Passenger passenger;
	Trip trip;
	int page = 0;
	bool done = false;
	system("clear||cls");

	// each step of the passenger add process is its own function that validates and returns the inputted info.
	do {
		switch (page) {
			case 0:
				passenger.tripNumber = inputTripNumber();
				trip = trips[getTripIndex(passenger.tripNumber)];
				page++;
				break;
			case 1:
				passenger.priorityNumber = inputPriorityNumber();
				page++;
				break;
			case 2:
				passenger.name = inputName();
				page++;
				break;
			case 3:
				inputId(passenger.id);
				page++;
				break;
			case 4:
				passenger.dropOffPt = inputDropOff(trip.embarkPt, trip.route);
				page++;
				break;
			case 5:
				done = reviewDetails(passenger, trip.embarkPt, trip.route, trips);
				if (done) {
					page++;
				} else {
					page = 0;
				}
				break;
			default:
				break;
		}
		system("clear||cls");
	} while (!done);

	addPassenger(passenger, trips, getTripIndex(passenger.tripNumber));
}