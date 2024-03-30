/*
 *  writeFile takes all the trips in the array and writes all passenger and trip info
 *	Solution by: Tyrrelle Mendoza, modified by: Jay Carlos
 *  to a file specified by the date.
 *  @param *trips Pointer to array of trips whose info will be written to the file.
 *  @param nTrips Number of trips in the array.
 *  @param date Date structure to determine file name.
 *  @return None.
 */
void writeFile(Trip *trips, int nTrips, Date date)
{
	FILE *fp;

	int i, j;
	int passengerCount;
	Passenger passenger;

	char embarkPoint[60];
	char dropOffPoint[MAX];

	char destPath[MAX];
	
	// snprintf() lets you copy a formatted string to a destination string.
	snprintf(destPath, sizeof(destPath), "./trips/%02d-%02d-%04d.txt", date.date, date.month, date.year);

	// this is for file reading/writing/appending
	fp = fopen(destPath, "w");

	// error if file could not be created.
	if (fp == NULL) {
		printf("Error: Could not create file %02d-%02d-%04d.txt at directory ./trips/.\n",
		date.date, date.month, date.year);
	}

	// iterate through each trip.
	for (i = 0; i < nTrips; i++) {
		passengerCount = trips[i].passengerCount;
		
		fprintf(fp, "AE%d\n", trips[i].tripNumber);
		getEmbarkationPointName(trips[i].embarkPt, embarkPoint);
		fprintf(fp, "%s\n", embarkPoint);

		for (j = 0; j < passengerCount; j++) {
			passenger = trips[i].passengers[j];

			// write passenger data to file.
			fprintf(fp, "%s %s\n", passenger.name.firstName, passenger.name.lastName);
			fprintf(fp, "%s\n", passenger.id);
			fprintf(fp, "%d\n", passenger.priorityNumber);

			getDropOffName(passenger.dropOffPt, dropOffPoint);
			fprintf(fp, "%s\n\n", dropOffPoint);
		}

		if (passengerCount == 0) {
			fprintf(fp, "\n");
		}
	}

	fclose(fp);
}

/*
 *  readTrips reads all trips from a file of a given date for viewing.
 *	Solution by: Tyrrelle Mendoza
 *  Precondition: Valid date format given.
 *  @param date Date to base file name from.
 *  @return Success indicator.
 */
bool readTrips(Trip trips[], char filename[])
{
	FILE *fp;
	int i;
	
	// number of passengers
	int passNum = 0;

	// total num of passengers
	int totalPass = 0;

	// trip index to save current data to.
	int tripNum = 0;

	// track which line is being read.
	int line = 1;

	char buffer[MAX];
	char buffer2[MAX];

	fp = fopen(filename, "r");

	if (fp == NULL) {
		return false;
	}

	line = 0;
	
	while (!feof(fp)) {
		
		if (line % 5 == 2) {
			fscanf(fp, "%s %s", buffer, buffer2);
		} else {
			fscanf(fp, "%s", buffer);
		}

		for (i = 0; i < TRIP_COUNT; i++) {
			if (trips[i].tripNumber == atoi(buffer) && trips[tripNum].passengerCount <= 16) {
				passNum = trips[i].passengerCount;
				tripNum = i;
			}
		}

		switch (line % 5) {
			case 0:
				trips[tripNum].passengers[passNum].tripNumber = atoi(buffer);
				printf(YELLOW"Trip Number: "RESET"AE%d\n", trips[tripNum].tripNumber);
				printf(YELLOW"Passenger Index: "RESET"[%d]\n", trips[tripNum].passengerCount);
				break;
			case 1:
				trips[tripNum].passengers[passNum].priorityNumber = atoi(buffer);
				printf(YELLOW"Priority: "RESET"%d\n", trips[tripNum].passengers[passNum].priorityNumber);
				break;
			case 2:
				strcpy(trips[tripNum].passengers[passNum].name.firstName, buffer);
				strcpy(trips[tripNum].passengers[passNum].name.lastName, buffer2);
				printf(YELLOW"Name: "RESET"%s %s\n", buffer, buffer2);
				break;
			case 3:
				strcpy(trips[tripNum].passengers[passNum].id, buffer);
				printf(YELLOW"ID: "RESET"%s\n", trips[tripNum].passengers[passNum].id);
				break;
			case 4:
				trips[tripNum].passengers[passNum].dropOffPt = atoi(buffer);
				getDropOffName(atoi(buffer), buffer2);
				printf(YELLOW"Drop-Off: "RESET"[%d.] %s\n\n", trips[tripNum].passengers[passNum].dropOffPt, buffer2);
				(trips[tripNum].passengerCount)++;
				totalPass++;
				break;
			default:
				break;
		}
		line++;
	}

	printf(YELLOW"Total passengers: "RESET"%d\n", totalPass);

	fclose(fp);
	return true;
}

/*
 *  readProgramOutputFile reads all trips from a file of a given date for viewing.
 *	Solution by: Tyrrelle Mendoza, modified by: Jay Carlos
 *  Precondition: Valid date format given.
 *  @param date Date to base file name from.
 *  @return Success indicator.
 */
bool readProgramOutputFile(Trip trips[], Date date)
{
	FILE *fp;
	
	// number of passengers
	int passNum = 0;

	// trip index to save current data to.
	int tripNum = -1;

	// track which line is being read.
	int line = 0;
	char sourcePath[MAX];

	char buffer[MAX];

	// create source path based on given date.
	snprintf(sourcePath, sizeof(sourcePath), "./trips/%02d-%02d-%02d.txt", date.date, date.month, date.year);
	fp = fopen(sourcePath, "r");

	if (fp == NULL) {
		return false;
	}
	
	while (!feof(fp)) {
		fgets(buffer, sizeof(buffer), fp);
		line++;

		// buffer + 2 removes the first two chars "AE", allowing the number to be converted to an integer for comparison.
		if (atoi(buffer + 2) >= 101 && atoi(buffer + 2) <= 161) {
			trips[tripNum].passengerCount = passNum;
			line = -1;
			passNum = 0;
			tripNum++;
			trips[tripNum].tripNumber = atoi(buffer + 2);
		} else {
			switch (line) {
				case 1:
					// detect if line is not empty before copying name from file.
					if (buffer[0] != '\0') {
						sscanf(buffer, "%s %s", trips[tripNum].passengers[passNum].name.firstName, trips[tripNum].passengers[passNum].name.lastName);
					}
					break;
				case 2:
					// strncpy() lets you define how many characters to copy.
					// remember that buffer is 200 chars, while id is 9 (including null), so we only copy 8 chars.
					// using regular strcpy() tries copying all 200 chars, resulting in an overflow -> trace trap.
					strncpy(trips[tripNum].passengers[passNum].id, buffer, 8);
					break;
				case 3:
					// 
					trips[tripNum].passengers[passNum].priorityNumber = atoi(buffer);
					break;
				case 4:
					trips[tripNum].passengers[passNum].dropOffPt = getDropOff(trips[tripNum].route, trips[tripNum].embarkPt, buffer);
					passNum++;
					fgets(buffer, sizeof(buffer), fp);
					line = 0;
					break;
				default:
					break;
			}
		}
	}

	fclose(fp);
	return true;
}