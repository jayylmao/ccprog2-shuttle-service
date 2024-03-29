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
		
		fprintf(fp, "%d\n", trips[i].tripNumber);
		getEmbarkationPointName(trips[i].embarkPt, embarkPoint);
		fprintf(fp, "%s\n", embarkPoint);

		for (j = 0; j < passengerCount; j++) {
			passenger = trips[i].passengers[j];

			// write passenger data to file.
			fprintf(fp, "%s %s\n", passenger.name.firstName, passenger.name.lastName);
			fprintf(fp, "%s\n", passenger.id);
			fprintf(fp, "%d\n", passenger.priorityNumber);

			getDropOffName(passenger.dropOffPt, dropOffPoint);
			fprintf(fp, "%s\n", dropOffPoint);
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
bool readTrips(Trip trips[], Date date)
{
	FILE *fp;
	int dropOff, i;
	
	// number of passengers
	int passNum = 0;

	// total num of passengers
	int totalPass = 0;

	// trip index to save current data to.
	int tripNum = 0;

	// track which line is being read.
	int lineNum = 1;

	char buffer[MAX];
	char sourcePath[MAX];

	char firstName[MAX];
	char lastName[MAX];

	// create source path based on given date.
	snprintf(sourcePath, sizeof(sourcePath), "./trips/%02d-%02d-%02d.txt", date.date, date.month, date.year);
	fp = fopen(sourcePath, "r");

	if (fp == NULL) {
		return false;
	}
	
	while (!feof(fp)) {
		lineNum = 1;
		fscanf(fp, "%s %s", firstName, lastName);

		//check if name contains the bus number
		if (atoi(firstName) >= 101 && atoi(firstName) <= 161)
		{
			// Finalize Previous Trip Values
			trips[tripNum].passengerCount = passNum;
			printf(YELLOW"Passengers in AE%d: "RESET"%d\n\n", trips[tripNum].tripNumber, passNum);

			// Reset Passenger Index
			passNum = 0;
			
			// scan the index that has trip number

			for (i = 0; i < TRIP_COUNT; i++)
			{
				if (trips[i].tripNumber == atoi(firstName))
				{
					tripNum = i;
				}
			}

			// use this to scan through struct
			printf(YELLOW"Trip Number: "RESET"AE%d\n", trips[tripNum].tripNumber);

			//get newline
			fgets(buffer, MAX, fp);
		} else {
			while (lineNum)
			{
				switch(lineNum)
				{
					case 1:
						strcpy(trips[tripNum].passengers[passNum].name.firstName, firstName);
						strcpy(trips[tripNum].passengers[passNum].name.lastName, lastName);
						printf(YELLOW"Name: "RESET"%s %s\n", firstName, lastName);
						break;
					case 2:
						// get ID buffer
						fscanf(fp, "%s", buffer);
						
						strcpy(trips[tripNum].passengers[passNum].id, buffer);
						// printf(YELLOW"ID: "RESET"%s\n", buffer);
						printf(YELLOW"ID: "RESET"%s\n", trips[tripNum].passengers[passNum].id);
						break;
					case 3:
						// get Priority buffer
						fscanf(fp, "%s", buffer);
					
						trips[tripNum].passengers[passNum].priorityNumber = atoi(buffer);
						// printf(YELLOW"Priority: "RESET"%d\n", atoi(buffer));
						printf(YELLOW"Priority: "RESET"%d\n", trips[tripNum].passengers[passNum].priorityNumber);

						break;
					case 4:
						// catch drop-off
						// make a function that can return the int value of dropoffPt
						
						fgets(buffer, MAX, fp);

						dropOff = getDropOff(trips[tripNum].route, trips[tripNum].embarkPt, buffer);

						trips[tripNum].passengers[passNum].dropOffPt = dropOff;

						// printf(YELLOW"Drop-Off: "RESET"[%d.] %s\n\n", dropOff, buffer);
						printf(YELLOW"Drop-Off: "RESET"[%d.] %s\n\n", trips[tripNum].passengers[passNum].dropOffPt, buffer);

						passNum++;
						totalPass++;
						break;
					default:
						break;
				}

				// catch newline
				fgets(buffer, MAX, fp);

				if (lineNum == 4) lineNum = 0;
				else lineNum++;
			}
		}
	}

	printf(YELLOW"Total passengers: "RESET"%d", totalPass);

	fclose(fp);
	return true;
}