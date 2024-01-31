#include <time.h>
#include <string.h>
#define MAX 200

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