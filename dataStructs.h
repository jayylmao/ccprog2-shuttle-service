#define MAX 200

struct Date {
	int date;
	int month;
	int year;
};

typedef struct Date Date;

struct Name {
	char firstName[MAX];
	char lastName[MAX];
};

typedef struct Name Name;

struct Passenger {
	// personally identifiable information.
	Name name;
	char id[9];
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

	bool isEmergencyShuttle;
};

typedef struct Trip Trip;