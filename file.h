#define TRIP_NUMBER 0
#define EMBARK_PT 1
#define PASSENGER_NAME 2
#define ID_NUMBER 3
#define PRIORITY_NUMBER 4
#define DATE_OF_TRIP 5
#define TIME_OF_TRIP 6
#define DROP_OFF_PT 7

/*
 *  getTripTime
 */
int getTripTime()
{
    char line[30];
    char tripNum[6];
    char currentCode[6]; // Adjust the size based on your needs
    int time = -1;

    printf("Input your desired trip Number: ");
    scanf("%s", tripNum);

    FILE *fp = fopen("tripSched.txt", "r");

    if (fp == NULL) {
        perror("Error opening the file");
    } else {
        while (fgets(line, sizeof(line), fp) != NULL) {
            // Use sscanf to read the code and time
            if (sscanf(line, "%s %d", currentCode, &time) == 2) {
                if (strcmp(currentCode, tripNum) == 0) {
                    printf("%d", time);
                }
            }
        }
    }

    fclose(fp);
    return time;
}

/*
 *  readFileLine() reads a line from the buffer and saves it to the appropriate
 *  part of the nth Passenger in a trip depending on what line is being read at a given time.
 *  @param *buffer Pointer to buffer string to read from.
 *  @param *tripName Trip name determines if 
 */

/*
 *  TODO: readTripData reads a specified trip number from a given file and outputs all passenger data to a Trip struct
 *  for access within the program.
 *  @param date Current program run date to determine filename from.
 *  @return None.
void readTripData(Date date, int tripNumber, Trip *output)
{
    // create file name string from given date.
    char fileName[MAX];
    snprintf(fileName, sizeof(fileName), "./trips/%02d-%02d-%04d.txt", date.date, date.month, date.year);
    printf("%s", fileName);
    
    // create file pointer with file name from given date.
    FILE *inputFile;
    inputFile = fopen(fileName, "r");

    char buffer[MAX];
    int lineCount;
    lineCount = 0;
    int currentLineOfRecord;

    // check if the passenger from the file being read is in the trip
    // based on the trip name in the record.
    bool passengerInTrip = false;
    
    // append trip number to "AE" for comparison with trip name in file.
    char tripName[6] = "AE";
    snprintf(tripName, sizeof(tripName), "AE%d", tripNumber);

    output->passengerCount = 0;

    // check for existence of file.
    if (inputFile == NULL) {
        printf("Error: Could not open requested file.\n");
    } else {
        // iterate through each line in the file.
        while (fgets(buffer, MAX, inputFile) != NULL) {
            // all passenger profiles in the trip file are 8 lines long. 
            // (7 because computer counting starts from 0)
            currentLineOfRecord = lineCount % 7;

            // if we're reading the trip number line, check if that's the trip
            // number we're searching for. if so, read the next lines until
            // we reach the next trip number line.
            if (currentLineOfRecord == TRIP_NUMBER) {
                if (strcmp(buffer, tripName) == 0) {
                    passengerInTrip = true;
                } else {
                    passengerInTrip = false;
                }
            }

            // readFileLine(buffer, tripName, output, passengerInTrip, currentLineOfRecord, date);
            lineCount++;
        }
    }

    fclose(inputFile);
}
 */

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

        for (j = 0; j < passengerCount; j++) {
            passenger = trips[i].passengers[j];
            setEmbarkName(passenger.tripNumber, embarkPoint);

            // write passenger data to file.
            fprintf(fp, "%s\n", embarkPoint);
            fprintf(fp, "%s %s\n", passenger.Name.firstName, passenger.Name.lastName);
            fprintf(fp, "%s\n", passenger.id);
            fprintf(fp, "%d\n", passenger.priorityNumber);
            
            // this only gets prints for 1st passenger as per MP specs.
            if (j == 0) {
                fprintf(fp, "%02d-%02d-%04d\n", date.date, date.month, date.year);
            }
            
            fprintf(fp, "%02d:%02d\n", 6, 00); // hardcoded for now. still have to figure out time.
            fprintf(fp, "%d\n", passenger.dropOffPt);
            
            // add extra newline for all other passengers as per MP specs.
            if (j != 0) {
                fprintf(fp, "\n");
            }

            fprintf(fp, ".\n.\n.\n");
        }
    }

    fclose(fp);
}

void readFile(FILE *fp, Trip *trips, int n, Date date)
{

}