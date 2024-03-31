/*
 *	printHeader displays the standard header at the top of every screen in the program.
 *	Solution by: Jay Carlos
 *	Precondition: Positive integer header size provided.
 *	@param *message Message to be printed in between the brackets.
 *	@param headerSize Length of header.
 */
void printHeader(char *message, int headerSize)
{
	int i, msgLength = strlen(message);
	printf("======[ %s ]", message);

	for (i = 0; i < headerSize - (msgLength + 1); i++) {
		printf("=");
	}

	printf("\n\n");
}

/*
 *	getDropOffName returns the name of a drop-off point given its integer representation in the program.
 *	Solution by: Jay Carlos
 *	Precondition: Valid drop-off point integer given.
 *	@param dropOffPt Integer representation of drop-off point in program
 *	@param dropOffString Character array to save name of drop-off point to.
 *	@return None.
 */
void getDropOffName(int dropOffPt, char *dropOffString)
{
	switch (dropOffPt) {
		case 1:
			strcpy(dropOffString, "Mamplasan Toll Exit");
			break;
		case 2:
			strcpy(dropOffString, "Phase 5, San Jose Village");
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
		case 10:
			strcpy(dropOffString, "College of St. Benilde (CSB) Along Taft");
			break;
		default:
			strcpy(dropOffString, "Unknown");
			break;
	}
}

/*
 *	getTime returns the trip time given a trip number.
 *	Solution by: Jay Carlos
 *	Precondition: Valid trip number given.
 *	@param tripNumber Trip number.
 *	@param *dest Character array to save time to.
 */
void getTime(int tripNumber, char *dest)
{
	FILE *fp;
	int fileTripNumber, hour, minute;
	char buffer[6];
	fp = fopen("./config/tripSched.txt", "r");

	if (fp == NULL) {
		printf(RED"[!]: Trip schedule file (./config/tripSched.txt) could not be found in current directory.\n"RESET);
		strcpy(dest, "00:00");
		return;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &fileTripNumber, &hour, &minute);

		if (tripNumber == fileTripNumber) {
			snprintf(buffer, sizeof(buffer), "%02d:%02d", hour, minute);
		}
	}

	fclose(fp);

	strcpy(dest, buffer);
}

/*
 *	getPriorityGroupName returns the name of a priority group given its integer representation in the program.
 *	Solution by: Jay Carlos
 *	Precondition: Valid priority group integer given.
 *	@param priorityNumber Integer representation of a priority group in the program.
 *	@param *dest Character array to save name of priority group to.
 */
void getPriorityGroupName(int priorityNumber, char *dest)
{
	switch (priorityNumber) {
		case 1:
			strcpy(dest, "Faculty & ASF with Inter-Campus Assignments");
			break;
		case 2:
			strcpy(dest, "Students with Inter-campus subjects/thesis");
			break;
		case 3:
			strcpy(dest, "Researchers");
			break;
		case 4:
			strcpy(dest, "School Administrators");
			break;
		case 5:
			strcpy(dest, "University Fellows");
			break;
		case 6:
			strcpy(dest, "Employees and Students with official business");
			break;
		default:
			break;
	}
}

/*
 *	getRouteName returns the name of a route given the route's integer representation in the program and the embarkation point.
 *	Solution by: Jay Carlos
 *	Precondition: Valid route and embarkation point given.
 *	@param route Integer corresponding to route number in the program.
 *	@param embarkPt Integer corresponding to embarkation point in the program.
 *	@param *dest Character array to save route name to.
 */
void getRouteName(int route, int embarkPt, char *dest)
{
	switch (embarkPt) {
		case 0:
			if (route == 0) {
				strcpy(dest, "Via Mamplasan exit");
			} else {
				strcpy(dest, "Via ETON exit");
			}
			break;
		case 1:
			if (route == 0) {
				strcpy(dest, "Via Estrada");
			} else {
				strcpy(dest, "Via Buendia/LRT");
			}
			break;
		default:
			break;
	}
}