#include "core.h"

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));
	int* field = (int*)malloc(sizeof(int) * SIZE * SIZE);
	init();
	initField(field);
	start(field);
	update(field);
	detectKeys(field);
	close();
	return 0;
}