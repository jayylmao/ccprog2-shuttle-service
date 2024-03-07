#define VIEW_PASSENGERS_ON_TRIP '1'
#define VIEW_PASSENGERS_AT_DROP '2'
#define VIEW_PASSENGER_INFO '3'
#define LOAD_PASSENGER_INFO '4'
#define SEARCH '5'
#define LOAD_FILE '6'
#define PERSONNEL_EXIT '7'

void viewPassengersOnTrip()
{

}

void viewPassengersAtDrop()
{

}

void viewPasssengerInfo()
{

}

void loadPassengerInfo()
{

}

void searchPassenger()
{

}

void loadFile()
{

}

void logOut()
{

}

/*
 *	personnelAuthentication checks a password file and asks the user to input a password
 *	before displaying the personnel menu.
 *	Precondition: Password abides by MAX value, .password file exists, and function is called from main menu.
 *	@return Boolean value that determines whether a login was successful or not.
 */
bool personnelAuthentication()
{
	FILE *fp;
	char password[MAX];
	char input[MAX];

	bool passwordMatch = false;
	fp = fopen(".password", "r");

	if (fp == NULL) {
		printf("CRITICAL ERROR: No password set. Contact ITS.");
	} else {
		fgets(password, MAX, fp);

		while (!passwordMatch && strcmp(input, "0") != 0) {
			printf("Enter the personnel password, or 0 to cancel: ");
			scanf("%s", input);

			if (strcmp(password, input) == 0) {
				printf("INFO: Login successful.\n");
				passwordMatch = true;
			} else if (strcmp(input, "0") == 0) {
				printf("INFO: Login canceled.\n");
			} else {
				printf("Incorrect password entered. Try again.\n");
			}
		}
	}

	return passwordMatch;
}

/*
 *	personnelMenu allows personnel to access the functions available to them.
 *	Precondition: Called from main menu if personnel authentication was successful.
 *	@return None.
 */
void personnelMenu(Bus buses[], Date date)
{
	char userChoice;
	printf("Personnel Management Console\n");
	printf("Please select a menu option below: \n");
	printf("1. View number of passengers on trip \n");
	printf("2. View number of passengers at drop-off point \n");
	printf("3. View passenger information \n");
	printf("4. Load passenger information \n");
	printf("5. Search passenger \n");
	printf("6. Load file \n");
	printf("7. Log out of personnel management console \n");

	do
	{
		scanf(" %c", &userChoice);
		system("clear||cls");

		switch (userChoice)
		{
		case VIEW_PASSENGERS_ON_TRIP:
			viewPassengersOnTrip();
			break;
		case VIEW_PASSENGERS_AT_DROP:
			viewPassengersAtDrop();
			break;
		case VIEW_PASSENGER_INFO:
			viewPasssengerInfo();
			break;
		case LOAD_PASSENGER_INFO:
			loadPassengerInfo();
			break;
		case SEARCH:
			searchPassenger();
			break;
		case LOAD_FILE:
			loadFile();
			break;
		case PERSONNEL_EXIT:
			break;
		default:
			printf("Please input a number from 1 - 7.\n");
			break;
		}
	} while (userChoice != PERSONNEL_EXIT);
	
}