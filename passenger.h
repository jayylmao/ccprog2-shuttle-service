#include <time.h>
#include <string.h>
#define MAX 200

struct tm {
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
};

struct passenger {
	char name[MAX];
	int id;
	char route[MAX];
	int dropOffPt;
};

void setName(char* destination, char name[MAX])
{
	strcpy(destination, name);
}