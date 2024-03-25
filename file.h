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
            fprintf(fp, "%d\n", trips[i].tripNumber);
        }

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

/*
 *  readTrips reads all trips from a file of a given date.
 */
void readTrips(Trip trips[], Date date)
{
    FILE *fp;
    
    // number of passengers
    int passNum = 0;

    // track which line is being read.
    int lineNum = 0;

    char buffer[MAX];
    char sourcePath[MAX];

    // create source path based on given date.
    snprintf(sourcePath, sizeof(sourcePath), "./trips/%02d-%02d-%02d.txt", date.date, date.month, date.year);
    fp = fopen(sourcePath, "r");

    passNum++;
    lineNum++;

    fclose(fp);
}

// void readTrips(Trip *trips, Date date)
// {
//     FILE *fp;

//     // passenger counter
//     int passNum = 0;
    
//     // counter for file line
//     int lineNum = 0;

//     int tripNum, busIndex;
//     // char tripBus[6];

//     char buffer[200];
// 	char destPath[MAX];

//     bool tripDetected = false;

//     snprintf(destPath, sizeof(destPath), "./trips/%02d-%02d-%04d.txt", date.date, date.month, date.year);

//     fp = fopen(destPath, "r");

//     if (fp == NULL) {
//         printf("ERROR: Could not find file %02d-%02d-%04d.txt at directory ./trips/.\n",
// 		date.date, date.month, date.year);
//     } else {
//         // while file not at EOF
//         while (fscanf(fp, "%s", buffer) != -1) {
//             fscanf(fp, "%s", buffer);
            
//             lineNum++;
//         }
//     }
// }