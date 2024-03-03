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

// each trip is an
struct Bus {
	int tripNumber;
	Passenger passengers[16];
	int passengerCount;

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