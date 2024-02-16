#define MAX 200

typedef struct Date {
	int date;
	int month;
	int year;
} Date;

typedef struct Passenger {
	int tripNumber;
	int priorityNumber;
	char name[MAX];
	int id;
	char route[MAX];
	int dropOffPt;
	Date tripDate;
} Passenger;