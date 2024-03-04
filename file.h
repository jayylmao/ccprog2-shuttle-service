#define TRIP_NUMBER 0
#define EMBARK_PT 1
#define PASSENGER_NAME 2
#define ID_NUMBER 3
#define PRIORITY_NUMBER 4
#define DATE_OF_TRIP 5
#define TIME_OF_TRIP 6
#define DROP_OFF_PT 7

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
int getTripTime(int tripNumber, Bus *bus, FILE *fp)
{
    int time = 0;
    

    return time;
}

/*
 *  readFileLine() reads a line from the buffer and saves it to the appropriate
 *  part of the nth Passenger in a bus depending on what line is being read at a given time.
 *  @param *buffer pointer to buffer string to read from.
 *  @param *tripName trip name determines if 
 */
void readFileLine(char *buffer, char *tripName, Bus *output, bool passengerInTrip, int currentLine, Date date)
{
    int passengerCount;
    passengerCount = output->passengerCount;

    if (passengerInTrip) {
        switch (currentLine)
        {
        case TRIP_NUMBER:
            output->passengers[passengerCount].tripNumber = atoi(buffer);
            passengerCount++;
            break;
        case EMBARK_PT:
            // output->passengers[passengerCount]; still deciding how embark point works
            passengerCount++;
            break;
        case PASSENGER_NAME:
            strcpy(output->passengers[passengerCount].name, buffer);
            break;
        case ID_NUMBER:
            strcpy(output->passengers[passengerCount].id, buffer);
            break;
        case PRIORITY_NUMBER:
            output->passengers[passengerCount].priorityNumber = atoi(buffer);
            break;
        case DATE_OF_TRIP:
            break;
        default:
            break;
        }
    }
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
    int currentLineOfRecord;

    // check if the passenger from the file being read is in the trip
    // based on the trip name in the record.
    bool passengerInTrip = false;
    
    // append trip number to "AE" for comparison with trip name in file.
    char tripName[6] = "AE";
    snprintf(tripName, sizeof(tripName), "AE%d", tripNumber);

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

            readFileLine(buffer, tripName, &output, passengerInTrip, currentLineOfRecord, date);
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