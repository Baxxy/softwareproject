#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void slotBuild();
int slotNum;
	typedef struct Slots 
	{
		int preset;
		char type[10000];
		int position;
	} Slots;
	
int counter;

int main(void)
{
	srand(time(NULL));
	printf("Please enter the number of slots you would like (Max 20): \n");
	scanf("%d",&slotNum);
	slotBuild();
	return 0;
}


void slotBuild()
{
	Slots s[21];
	for(counter=0;counter<slotNum;counter++)
	{
	s[counter].preset = rand() % 3;
		if(s[counter].preset==0)
			strcpy(s[counter].type, "Level Ground");
		else if(s[counter].preset==1)
			strcpy(s[counter].type, "Hill");
		else
			strcpy(s[counter].type, "City");
	}
	for(counter=0;counter<slotNum;counter++)
	{
	printf("%s \n", s[counter].type);
	}
}
