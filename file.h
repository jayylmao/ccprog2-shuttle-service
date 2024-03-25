/*
 *  setDropOffPt returns the name of a drop-off point given its integer representation in the program.
 *  Precondition: Valid drop-off point integer given.
 *  @param dropOffPt Integer representation of drop-off point in program
 *  @param dropOffString Character array to save name of drop-off point to.
 *  @return None.
 */
void setDropOffPt(int dropOffPt, char *dropOffString)
{
    switch (dropOffPt)
    {
    case 1:
        strcpy(dropOffString, "Mamplasan Toll Exit");
        break;
    case 2:
        strcpy(dropOffString, "San Jose Village");
        break;
    case 3:
    case 5:
        strcpy(dropOffString, "Milagros Del Rosario (MRR) Building - East Canopy");
        break;
    case 4:
        strcpy(dropOffString, "Laguna Blvd. Guard House");
        break;
    case 6:
        strcpy(dropOffString, "Petron Gasoline Station along Gil Puyat Avenue");
        break;
    case 7:
    case 11:
        strcpy(dropOffString, "Gate 4: Gokongwei Gate");
        break;
    case 8:
    case 12:
        strcpy(dropOffString, "Gate 2: North Gate (HSSH)");
        break;
    case 9:
    case 13:
        strcpy(dropOffString, "Gate 1: South Gate (LS Building Entrance)");
        break;
    }
}

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
        
        if (passengerCount > 0) {
            fprintf(fp, "%d\n", trips[i].tripNumber);
            setEmbarkName(trips[i].embarkPt, embarkPoint);
            fprintf(fp, "%s\n", embarkPoint);
        }

        for (j = 0; j < passengerCount; j++) {
            passenger = trips[i].passengers[j];

            // write passenger data to file.
            fprintf(fp, "%s %s\n", passenger.Name.firstName, passenger.Name.lastName);
            fprintf(fp, "%s\n", passenger.id);
            fprintf(fp, "%d\n", passenger.priorityNumber);

            setDropOffPt(passenger.dropOffPt, dropOffPoint);
            fprintf(fp, "%s\n", dropOffPoint);
            
            // add extra newline for all other passengers as per MP specs.
            fprintf(fp, "\n");
        }
    }

    fclose(fp);
}

/*
 *  readTrips reads all trips from a file of a given date for viewing.
 *  Precondition: Valid date format given.
 *  @param date Date to base file name from.
 *  @return Success indicator.
 */
int readTrips(Trip trips[], Date date)
{
    FILE *fp;
    
    // number of passengers
    int passNum = 0;

    // trip index to save current data to.
    int tripNum = -1;

    // track which line is being read.
    int lineNum = 0;

    char buffer[MAX];
    char sourcePath[MAX];

    // create source path based on given date.
    snprintf(sourcePath, sizeof(sourcePath), "./trips/%02d-%02d-%02d.txt", date.date, date.month, date.year);
    fp = fopen(sourcePath, "r");

    if (fp == NULL) {
        printf("[*]: Could not find file %02d-%02d-%04d.txt in directory ./trips/.\n", date.date, date.month, date.year);
        return 0;
    }
    
    while (!feof(fp)) {
        fscanf(fp, "%s", buffer);

        // check if buffer in integer form is a trip number and reset 
        if (atoi(buffer) > 101 && atoi(buffer) < 160) {
            tripNum++;
            trips[tripNum].tripNumber = atoi(buffer);
            lineNum = 0;

            fscanf(fp, "%s", buffer);

        }

        switch (lineNum)
        {
        case 1:
            passNum++;
            break;
        
        default:
            break;
        }
    }

    printf("%d", passNum); // temp

    fclose(fp);
    return 1;
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