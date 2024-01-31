#include <stdio.h>
#include "passenger.h"

int main()
{
	struct passenger test;
	test.id = 12211303;
	strcpy(test.name, "test");

	printf("%s %d", test.name, test.id);
	return 0;
}