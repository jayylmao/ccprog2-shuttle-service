/*
 *  setEmbarkName uses a trip number to write the embark point for that trip.
 *  Precondition: Valid trip number provided and destination string has valid length.
 *  @param tripNumber trip number.
 *  @param embarkName pointer to string to save embark point name to.
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
 *  getTripTime gets the trip time from the schedule CSV file.
 *  Precondition: tripSched.csv file exists in a valid format.
 *  @param tripNumber trip number.
 *  @param fp pointer to schedule CSV file to read from.
 *  @return departure time in integer.
 */
void getTripTime(int tripNumber, Bus *bus, FILE *fp) {
    // int time = 0;

    return 0;
}



/*
 *  TODO: readTripData reads a specified trip number from a given file and outputs all passenger data to a Bus struct
 *  for access within the program.
 *  @param date Current program run date to determine filename from.
 *  @return output Bus struct.
 */
Bus readTripData(Date date, int tripNumber) // will return a Bus struct when done.
{
    // create file name string from given date.
    char fileName[MAX];
    snprintf(fileName, sizeof(fileName), "./trips/%02d-%02d-%04d.txt", date.date, date.month, date.year);
    printf("%s", fileName);
    
    // create file pointer with file name from given date.
    FILE *inputFile;
    inputFile = fopen(fileName, "r");

    char buffer[MAX];
    int lineCount = 0;
    
    // append trip number to "AE" for comparison with trip name in file.
    char tripName[6] = "AE";
    snprintf(tripName, sizeof(tripName), "AE%d", tripNumber);

    int currentLine;

    Bus output;
    output.passengerCount = 0;

    // check for existence of file.
    if (inputFile == NULL) {
        printf("Error: Could not open requested file.\n");
    } else {
        // iterate through each line in the file.
        while (fgets(buffer, MAX, inputFile) != NULL) {
            // all passenger profiles in the trip file are 8 lines long. 
            // (7 because computer counting starts from 0)
            currentLine = lineCount % 7;
            if (currentLine == 0 && strcmp(buffer, tripName) == 0) {
                output.passengers[output.passengerCount].tripNumber = atoi(buffer);
                output.passengerCount++;
            }

            lineCount++;
        }
    }

    fclose(inputFile);

    return output;
}

/*
 *	writeTripData checks for the existence of a file to write trip data to and
 *	creates it if it does not exist.
 *	Precondition: Valid name, route, ID, and number are provided.
 *	@param fp pointer to a file to write to.
 *  @param date date struct for 
 *	@return None.
 */
void writeTripData(FILE *fp, Passenger passenger, Date date)
{
    // struct passenger user;
    // int valid = 0;

    // Im not yet ready to use this function
    // int tripNum = getTripNum(*folderPath);

    /*
        This is to form the file name (I haven't added the Bus number function yet)
        It should be Trip-dd-mm-yyyy.txt, for now it's only dd-mm-yyyy.txt
    */ 

    /* 
        This is to combine the path and the text file together into onc string.
        It's not strcat() because folderPath is a pointer.
    */
    char destPath[MAX];
    snprintf(destPath, sizeof(destPath), "./trips/%02d-%02d-%04d.txt", date.date, date.month, date.year);

    // this is for file reading/writing/appending
    fp = fopen(destPath, "a");

    // If file does not exist, make new file with current date.
    if (fp == NULL) {
        fp = fopen(destPath, "w");
        if (fp != NULL) {
            // File created successfully, you can now write to it or do other operations
            fp = fopen(destPath, "a");
        } else {
            printf("Error: Could not create file %02d-%02d-%04d.txt at directory ./trips/.\n", date.date, date.month, date.year);
        }
    }

    char embarkPoint[60];

    setEmbarkName(passenger.tripNumber, embarkPoint);

    // write passenger data to file.
    fprintf(fp, "AE%d\n", passenger.tripNumber);
    fprintf(fp, "%s\n", embarkPoint);
    fprintf(fp, "%s\n", passenger.name);
    fprintf(fp, "%s\n", passenger.id);
    fprintf(fp, "%d\n", passenger.priorityNumber);
    fprintf(fp, "%02d-%02d-%04d\n", date.date, date.month, date.year);
    fprintf(fp, "%02d:%02d\n", 6, 00); // hardcoded for now. still have to figure out time.
    fprintf(fp, "%d\n", passenger.dropOffPt);
    fprintf(fp, ".\n.\n.\n");

    fclose(fp);
}

/*
 *	getPassenger parses a file and returns a passenger struct.
 *	Precondition: File is formatted properly.
 *	@param fp file to read data from.
 *	@return struct containing all passenger info.

Passenger getPassenger(FILE *fp)
{
	Passenger passenger;

	const char *folderPath = "/.trips/";
}

Bus getBus(FILE *fp)
{
	Bus bus;
	return bus;
}*/