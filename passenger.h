#include <time.h>
#include <string.h>
#define MAX 200

struct passenger {
	// TODO: current date and time of trip
	char name[MAX];
	int id;
	char route[MAX];
	int dropOffPt;
};