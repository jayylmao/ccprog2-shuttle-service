#define MAX 200

struct Passenger {
	// personally identifiable information
	char name[MAX];
	char id[8];
	int priorityNumber;

	// trip information
	char route[MAX];
	int tripNumber;
	int seatNumber;
	int dropOffPt;
};

typedef struct Passenger Passenger;

// debating whether this is necessary at all.
struct Trip {
	int tripNumber;
	Passenger passengers[16];

	bool maxStdCapacityReached;
	bool full;
	bool emergency;
};

typedef struct Trip Trip;

struct Date {
	int date;
	int month;
	int year;
};

typedef struct Date Date;