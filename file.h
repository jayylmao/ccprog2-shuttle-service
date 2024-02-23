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
int getTripTime(int tripNumber, FILE * fp) {
    return 0;
}

/*
 *	writeTripData checks for the existence of a file to write trip data to and
 *	creates it if it does not exist.
 *	Precondition: Valid name, route, ID, and number are provided.
 *	@param fp: pointer to a file to write to.
 *	@return None.
 */
void writeTripData(FILE * fp, Passenger passenger)
{
    const char *folderPath = "./trips";
    // struct passenger user;
    // int valid = 0;

    // time.h variables
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    // Im not yet ready to use this function
    // int tripNum = getTripNum(*folderPath);

    /*
        This is to form the file name (I haven't added the Trip number function yet)
        It should be Trip-dd-mm-yyyy.txt, for now it's only dd-mm-yyyy.txt
    */ 
    char tripFile[26];
    strftime(tripFile, sizeof(tripFile), "%d-%m-%Y.txt", localTime);
    
    /* 
        This is to combine the path and the text file together into onc string.
        It's not strcat() because folderPath is a pointer.
    */
    char destPath[256];
    snprintf(destPath, sizeof(destPath), "%s/AE%d-%s", folderPath, passenger.tripNumber, tripFile);

    // this is for file reading/writing/appending
    fp = fopen(destPath, "a");

    // If file does not exist, make new file with current date.
    if (fp == NULL) {
        fp = fopen(destPath, "w");
        if (fp != NULL) {
            // File created successfully, you can now write to it or do other operations
            fp = fopen(destPath, "a");
            fprintf(fp, "AE%d\n", passenger.tripNumber);
        } else {
            printf("Error creating file.\n");
        } 
    }

    char embarkPoint[60];

    setEmbarkName(passenger.tripNumber, embarkPoint);
    
    // write passenger data to file.
    fprintf(fp, "%s\n", embarkPoint);
    fprintf(fp, "%s", passenger.name);
    fprintf(fp, "%s", passenger.id);
    fprintf(fp, "%d\n", passenger.priorityNumber);
    fprintf(fp, ".\n.\n.\n");

    fclose(fp);
}

/*
 *	getPassenger parses a file and returns a passenger struct.
 *	Precondition: File is formatted properly.
 *	@param fp: file to read data from.
 *	@return struct containing all passenger info.

Passenger getPassenger(FILE * fp)
{
	Passenger passenger;

	const char *folderPath = "/.trips/";
}

Trip getTrip(FILE * fp)
{
	Trip trip;
	return trip;
}*/