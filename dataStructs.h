#define MAX 200

struct Date {
	int date;
	int month;
	int year;
};

typedef struct Date Date;

// personally identifiable information.
struct Name {
	char firstName[MAX];
	char lastName[MAX];
};

typedef struct Name Name;

struct Passenger {
	Name name;
	char id[8];
	int priorityNumber;

	// trip information
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