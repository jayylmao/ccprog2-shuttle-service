#define MAX 200

struct Date {
	int date;
	int month;
	int year;
};

typedef struct Date Date;

struct Passenger {
	// personally identifiable information.
	struct Name {
		char firstName[MAX];
		char lastName[MAX];
	} Name;

	char id[8];
	int priorityNumber;

	// trip information
	char route[MAX];
	int tripNumber;
	int dropOffPt;
};

typedef struct Passenger Passenger;

// each trip is an array of passengers with a trip number and some statuses.
struct Trip {
	int tripNumber;
	Passenger passengers[16];
	int passengerCount;

	int embarkPt;
	int route;

	bool isFull;
	bool isEmergencyShuttle;
};

typedef struct Trip Trip;