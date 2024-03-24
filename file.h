#define TRIP_NUMBER 0
#define EMBARK_PT 1
#define PASSENGER_NAME 2
#define ID_NUMBER 3
#define PRIORITY_NUMBER 4
#define DROP_OFF_PT 5

/*
 *  writeFile takes all the trips in the array and writes all passenger and trip info
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
        
        if (passengerCount > 0) {
            fprintf(fp, "AE%d\n", trips[i].tripNumber);
        }

        fprintf(fp, "%02d-%02d-%04d\n", date.date, date.month, date.year);

        for (j = 0; j < passengerCount; j++) {
            passenger = trips[i].passengers[j];
            setEmbarkName(passenger.tripNumber, embarkPoint);

            // this only gets prints for 1st passenger as per MP specs.
            if (j == 0) {
                fprintf(fp, "%s\n", embarkPoint);
            }

            // write passenger data to file.
            fprintf(fp, "%s %s\n", passenger.Name.firstName, passenger.Name.lastName);
            fprintf(fp, "%s\n", passenger.id);
            fprintf(fp, "%d\n", passenger.priorityNumber);
            
            fprintf(fp, "%d\n", passenger.dropOffPt);
            
            // add extra newline for all other passengers as per MP specs.
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
}

void readTrips(Trip *trips, Date date)
{
    FILE *fp;

    int passNum = 0;
    // Passenger passenger;

    int tripNum, busIndex;
    // char tripBus[6];

    char buffer[200];
	char destPath[MAX];

    bool tripDetected = false;

    snprintf(destPath, sizeof(destPath), "./trips/%02d-%02d-%04d.txt", date.date, date.month, date.year);

    fp = fopen(destPath, "r");

    if (fp == NULL) {
        printf("Warning: Could not find file %02d-%02d-%04d.txt at directory ./trips/.\n",
		date.date, date.month, date.year);
    } else {

        // while file not at EOF
        while (fscanf(fp, "%s", buffer) != -1) {
            printf("Trip Number Buffer: %s\n", buffer);

            // if line detects string starts with AE
            if (strncmp(buffer, "AE", 2) == 0) {
                sscanf(buffer, "AE%d", &tripNum);

                printf("Trip Number Found: AE %d\n", tripNum);

                busIndex = getBusIndex(tripNum);

                printf("Found Bus index: %d\n", busIndex);

                tripDetected = false;
                
                fgets(buffer, 200, fp);
            }

            do
            {
                // setEmbarkPt(tripNum, &trips[busIndex].passengers[passNum].embarkPt);
                if (tripNum >= 101 && tripNum <= 109) {
                    trips[busIndex].passengers[passNum].embarkPt = 1;
                } else if (tripNum >= 150 && tripNum <= 160) {
                    trips[busIndex].passengers[passNum].embarkPt = 2;
                }
                
                printf("Embark Point #: %d\n", trips[busIndex].passengers[passNum].embarkPt);
                
                fgets(buffer, 200, fp);

                fscanf(fp, "%s%s", 
                    trips[busIndex].passengers[passNum].Name.firstName, 
                    trips[busIndex].passengers[passNum].Name.lastName
                );
                printf("Name: %s %s\n", 
                    trips[busIndex].passengers[passNum].Name.firstName, 
                    trips[busIndex].passengers[passNum].Name.lastName
                );

                fscanf(fp, "%s", 
                    trips[busIndex].passengers[passNum].id);
                printf("ID: %s\n", 
                    trips[busIndex].passengers[passNum].id);

                fscanf(fp, "%d", 
                    &trips[busIndex].passengers[passNum].priorityNumber);
                printf("Priority Number: %d\n", 
                    trips[busIndex].passengers[passNum].priorityNumber);

                fscanf(fp, "%s", buffer);

                sscanf(buffer, "%2d-%2d-%4d", 
                    &date.date, 
                    &date.month,
                    &date.year
                );

                printf("Date: %.2d-%.2d-%.4d\n", 
                    date.date, 
                    date.month,
                    date.year
                );
                
                fgets(buffer, 200, fp);
                fgets(buffer, 200, fp);

                fscanf(fp, "%d", 
                    &trips[busIndex].passengers[passNum].dropOffPt);
                printf("Drop-off Point: %d\n", 
                    trips[busIndex].passengers[passNum].dropOffPt);
                
                passNum++;

                fscanf(fp, "%s", buffer);
                printf("\nCurrent Line After Passenger: %s\n", buffer);

                // if new bus number is found (a little brute force way)
                if (strncmp(buffer, "AE", 2) == 0) {
                    printf(" (Loop Broken!)\n");
                    trips[busIndex].passengerCount = passNum;
                    printf("\nPassengers Counted: %d\n\n", passNum);

                    passNum = 0;

                    sscanf(buffer, "AE%d", &tripNum);
                    printf("Trip Number Found: AE %d\n", tripNum);

                    busIndex = getBusIndex(tripNum);

                    printf("Found New Bus index: %d\n", busIndex);

                    tripDetected = true;
                }

            } while (!tripDetected);
        }
    }
}