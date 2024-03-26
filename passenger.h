/*
 *	displayTrip visualizes the bus the user has selected on screen.
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

	if (trip.passengerCount <= 13) {	// standard seating
		printf(".____.____.____.\n");

		for (i = 0; i < 13; i++) {
			if (strcmp(trip.passengers[i].id, "-1") == 0) { // print seat number if not occupied
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
	} else {	// high-volume seating
		printf(".____.____.____.____.\n");

		for (i = 0; i < 16; i++) {
			if (strcmp(trip.passengers[i].id, "-1") == 0 && (i + 1) == 16) { // last row has a different format
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
	}
}

/*
 *	inputTripNumber asks the user to input a trip number.
 *	Precondition: Called from passengerRoutine();
 *	@return tripNumber Validated trip number entered by user.
 */
int inputTripNumber()
{
	int tripNumber, tripIndex;

	printf("======[ "GREEN"Add passenger - Trip Number"RESET " ]============================================\n");
	printf("======[ X ]---[ 2 ]---[ 3 ]---[ 4 ]---[ 5 ]---[ 6 ]=============================\n\n");

	do {
		printf(BLUE"Enter trip number: " RESET "AE");
		scanf("%d", &tripNumber);

		tripIndex = getTripIndex(tripNumber);

		if (tripIndex == -1) {
			printf(YELLOW"\n[*]: Enter a valid trip number (101 - 109, 150 - 160).\n"RESET);
		}
	} while (tripIndex == -1);

	return tripNumber;
}

int inputPriorityNumber()
{
	int priorityNumber;
	priorityNumber = 0;

	printf("======[ "GREEN"Add passenger - Priority Number"RESET " ]========================================\n");
	printf("======[ * ]---[ X ]---[ 3 ]---[ 4 ]---[ 5 ]---[ 6 ]=============================\n\n");

	printf(YELLOW"Priority numbers:\n");
	printf("[1.] "RESET"Faculty & ASF with Inter-campus assignments\n");
	printf(YELLOW"[2.] "RESET"Students with Inter-campus enrolled subjects/thesis\n");
	printf(YELLOW"[3.] "RESET"Researchers\n");
	printf(YELLOW"[4.] "RESET"School Administrators\n");
	printf(YELLOW"[5.] "RESET"University Fellows\n");
	printf(YELLOW"[6.] "RESET"Employees and Students with official business\n");
	printf(RED"Falsifying priority is subject to severe disciplinary action.\n");

	do {
		printf(BLUE"Enter priority number: " RESET);
		scanf("%d", &priorityNumber);

		if (priorityNumber < 1 || priorityNumber > 6) {
			printf(YELLOW"\n[*]: Enter a valid priority number (1 - 6).\n"RESET);
		}
	} while (priorityNumber < 1 || priorityNumber > 6);

	return priorityNumber;
}

Name inputName()
{
	Name name;
	strcpy(name.firstName, "");
	strcpy(name.lastName, "");

	printf("======[ "GREEN"Add passenger - Name"RESET " ]==================================================\n");
	printf("======[ * ]---[ * ]---[ X ]---[ 4 ]---[ 5 ]---[ 6 ]=============================\n\n");

	do {
		printf(BLUE"Enter name (First name last name): " RESET);
		scanf("%s %s", name.firstName, name.lastName);

		if (strcmp(name.firstName, "") == 0 || strcmp(name.lastName, "") == 0) {
			printf(YELLOW"\n[*]: Enter a valid first and last name, separated by a space.\n"RESET);
		}
	} while (strcmp(name.firstName, "") == 0 || strcmp(name.lastName, "") == 0);

	return name;
}

void inputId(char *dest)
{
	char id[9];

	printf("======[ "GREEN"Add passenger - ID"RESET " ]====================================================\n");
	printf("======[ * ]---[ * ]---[ * ]---[ X ]---[ 5 ]---[ 6 ]=============================\n\n");

	do {
		printf(BLUE"Enter ID: " RESET);
		scanf("%s", id);

		if (strlen(id) != 8 && atoi(id) == 0) {
			printf(YELLOW"\n[*]: Enter a valid ID.\n"RESET);
		}
	} while (strlen(id) != 8 && atoi(id) == 0);
	

	strcpy(dest, id);
}

/*
 *	inputDropOff displays a list of exits and drop-off points for the user to select from.
 *	Precondition: A valid trip number must be given.
 *	@param tripNumber Integer corresponding to trip number.
 *	@return Integer corresponding to the drop-off point.
 */
int inputDropOff(int embarkPoint, int route)
{
	// dropOff is where the user's input is stored.
	// menuLimit is an upper bound for the menu to determine input validity.
	int dropOff, menuLimit, offset = 0;

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
			printf("Via Buendia/LRT");
			printf(YELLOW"[1.] "RESET"College of St. Benilde (CSB) Along Taft\n");
			printf(YELLOW"[2.] "RESET"Gate 4: Gokongwei Gate\n");
			printf(YELLOW"[3.] "RESET"Gate 2: North Gate (HSSH)\n");
			printf(YELLOW"[4.] "RESET"Gate 1: South Gate (LS Building Entrance)\n");
			offset = 9;
		}
	default:
		break;
	}

	do {
		printf("Choose a drop-off point: ");
		scanf("%d", &dropOff);

		if (dropOff < 1 || dropOff > menuLimit) {
			printf("Select a drop-off point from 1 to %d.\n", menuLimit);
		}
	} while (dropOff < 1 || dropOff > menuLimit);

	return dropOff + offset;
}

void reviewDetails(Passenger passenger, int embarkPt, int route, Trip trips[])
{
	printf("======[ "GREEN"Add passenger - Review Details"RESET " ]========================================\n");
	printf("======[ * ]---[ * ]---[ * ]---[ * ]---[ * ]---[ X ]=============================\n\n");

	displayTrip(passenger.tripNumber, trips);
	printf("\n\n");
	printf("Name: ");
}


/*
 *	passengerRoutine allows a passenger to select a trip to embark on.
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
		case 2:
			passenger.name = inputName();
			page++;
		case 3:
			inputId(passenger.id);
			page++;
		case 4:
			passenger.dropOffPt = inputDropOff(trip.embarkPt, trip.route);
			page++;
		case 5:
			reviewDetails(passenger, trip.embarkPt, trip.route, trips);
			page++;
		default:
			done = true;
			break;
		}
		system("clear||cls");
	} while (!done);

	addPassenger(passenger, trips, getTripIndex(passenger.tripNumber));
}