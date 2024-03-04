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
	int embarkPt;
	int dropOffPt;
};

typedef struct Passenger Passenger;

// each trip is an array of passengers with a trip number and some statuses.
struct Bus {
	int tripNumber;
	Passenger passengers[16];
	int passengerCount;

	int time;

	bool full;
	bool emergency;
};

typedef struct Bus Bus;

struct Date {
	int date;
	int month;
	int year;
};

typedef struct Date Date;