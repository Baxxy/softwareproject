//Richard Otroshchenko
//06/03/17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//Program to generate the list of players using the user's input.
//Also generates the stats of those players.
//Generates a random list of slots.
//Assigns players to these slots.
//Searches for where and whether each player can move/attack.

int slotNum; //Slot Stuff.
	typedef struct Slots
	{
		int preset;
		char type[10000];
		int position;
	} Slots;
int counter;

struct Player {
  char playertype[20];
  char playername[20];
  char slot[20];
  int position;
  int lifepoints;
  int smartness;
  int strength;
  int magicskills;
  int luck;
  int dexterity;
};
void humanstats(struct Player *list); //Functions to generate the character stats
void ogrestats(struct Player *list);
void elfstats(struct Player *list);
void wizardstats(struct Player *list);
int randomnumber(int limit, int base); //Random number generator
void slotBuild(struct Slots *s);

int main(void)
{
int numplayers, typechoice;
struct Player playerlist[6]; //The 6 players will be stored in this array

printf("How many players are there?(up to 6)\n");
scanf("%d", &numplayers);
if(numplayers<1 || numplayers>6) //Program ends if too little or too many players are chosen.
{
  perror("Wrong choice inputted.\n");
  return -1;
}
for(int i=0;i<numplayers;i++) //This loops assigns the name, type and stats of each player one by one.
{
  printf("Please enter the name of player %d (No spaces please).\n", i+1);
  scanf("%s", &playerlist[i].playername);
  printf("What type is player %d? Please enter the number corresponding to your type.\n 1=Human, 2=Ogre, 3=Elf and 4=Wizard.\n", i+1);
  scanf("%d", &typechoice);
  if(typechoice==1)
  {
    strcpy(playerlist[i].playertype,"Human");
    humanstats(&playerlist[i]);
  }
  else if(typechoice==2)
{
    strcpy(playerlist[i].playertype,"Ogre");
    ogrestats(&playerlist[i]);
}
  else if(typechoice==3)
  {
    strcpy(playerlist[i].playertype,"Elf");
    elfstats(&playerlist[i]);
  }
  else if(typechoice==4)
  {
    strcpy(playerlist[i].playertype,"Wizard");
    wizardstats(&playerlist[i]);
  }
    else //In case they enter an invalid number.
     {
      perror("Wrong choice inputted.\n");
      return -1;
    }
}
for(int i=0;i<numplayers;i++) //This should probably be in the previous loop but whatever.
{
playerlist[i].lifepoints = 100;
}
for(int i=0;i<numplayers;i++) //Player info is printed out to the user.
{
printf("Player %d:\n", i+1);
printf("Name= %s, Type= %s, Lifepoints= %d, smartness= %d, strength= %d, magicskills= %d, luck= %d, dexterity= %d.\n", playerlist[i].playername, playerlist[i].playertype, playerlist[i].lifepoints, playerlist[i].smartness, playerlist[i].strength, playerlist[i].magicskills, playerlist[i].luck, playerlist[i].dexterity);
}

printf("\nPlease enter the number of slots you would like (Max 20): \n");
scanf("%d",&slotNum);
if(slotNum<1 || slotNum>20) //Program ends if too little or too many slots are chosen.
{
  perror("Wrong choice inputted.\n");
  return -1;
}
Slots s[slotNum];
slotBuild(s);

int x=49 /*The 49 isnt relevent, it just had to be a number greater than possible number of slots*/, check[7], different;
for(int i=0;i<numplayers;i++) //This loop will assign a random slot to each player.
{
do{ //This do while loop helps insure 2 players wont get the same slots.
  different = 0;
  check[i] = x;
  x = rand()%slotNum;
  for(int j=0;j<7;j++)
  {
    if(x==check[j])
    {
      different=1;
    }
  }
}while(different==1);
  strcpy(playerlist[i].slot, s[x].type);
  playerlist[i].position = s[x].position;
}
for(int i=0;i<numplayers;i++)
{
  printf("Position of player %d: %d,%s\n",i+1,playerlist[i].position,playerlist[i].slot);
}
int moveup, movedown, attackfound, yattack, xattack;
char enemy1[20], enemy2[20];
for(int i=0;i<numplayers;i++)
{
  yattack = 0;
  xattack = 0;
  attackfound = 0;
  moveup = 1;
  movedown = 1;
  printf("\nIt is player %d's turn to make a move\n", i+1);
  for(int j=0;j<6;j++)
  { //Checks for free slots above and below the player, then prints out the possible slots that player can move to.
    if(playerlist[i].position+1 == playerlist[j].position || playerlist[i].position>=slotNum)
    {
      moveup=0;
    }
    if(playerlist[i].position-1 == playerlist[j].position || playerlist[i].position <=1)
    {
      movedown=0;
    }
  }
  if(moveup == 1 && movedown == 1)
  {
    printf("You can move to either slot %d,%s or slot %d,%s.\n", s[playerlist[i].position-2].position,s[playerlist[i].position-2].type,s[playerlist[i].position].position,s[playerlist[i].position].type);
  }else if(moveup == 1 && movedown == 0)
  {
    printf("You can move up to slot %d,%s.\n", s[playerlist[i].position].position,s[playerlist[i].position].type);
  }else if(moveup == 0 && movedown == 1)
  {
    printf("You can move down to slot %d,%s.\n", s[playerlist[i].position-2].position, s[playerlist[i].position-2].type);
  }else
  {
    printf("You cannot move to a free slot.\n");
  }

  for(int k=1;attackfound==0;k++) //This loop will search for the nearest players that can be attacked, then prints out their names.
  {
    if(numplayers==1)
      break;

    for(int l=0;l<numplayers;l++)
    {
      int y,z;
      y = playerlist[i].position+k;
      x = playerlist[i].position-k;
      if(y == playerlist[l].position)
      {
        attackfound = 1;
        strcpy(enemy1,playerlist[l].playername);
        yattack = 1;
      }
      if(x == playerlist[l].position)
      {
        attackfound = 1;
        strcpy(enemy2,playerlist[l].playername);
        xattack = 1;
      }

    }
  }
  if(yattack == 1 && xattack == 1)
  {
    printf("You can attack either %s or %s.\n", enemy1,enemy2);
  }else if(yattack == 1 && xattack == 0)
  {
    printf("You can attack %s.\n", enemy1);
  }else if(yattack == 0 && xattack == 1)
  {
    printf("You can attack %s.\n", enemy2);
  }else
  {
    printf("You cannot make an attack at this time.\n");
  }


}







return 0;
}



void humanstats(struct Player *list)
{ //I'm not explaining my thought process here.
  int total = 300;
  list->smartness = randomnumber(100,1);
  total -= list->smartness;
  list->strength = randomnumber(100,1);
  total -= list->strength;
  list->magicskills = randomnumber(total,1);
  if(list->magicskills>100)
  {
    list->magicskills %= 100;
  }
  total -= list->magicskills;
  if(total<1)
{
    list->magicskills -= 2;
    total += 2;
}
  list->dexterity = randomnumber(total,1);
  if(list->dexterity>100)
  {
    list->dexterity %= 100;
  }
  total -= list->dexterity;
  if(total<1)
{
    list->dexterity -= 1;
    total += 1;
}
  list->luck = randomnumber(total,1);
  if(list->luck>100)
  {
    list->luck %= 100;
  }
}
void ogrestats(struct Player *list)
{
  list->magicskills = 0;
  list->smartness = randomnumber(21,0);
  list->strength = randomnumber(21,80);
  list->dexterity = randomnumber(21,80);
  list->luck = randomnumber((50-list->smartness),0);
}
void elfstats(struct Player *list)
{
  list->dexterity = randomnumber(100,1);
  list->luck = randomnumber(41,60);
  list->smartness = randomnumber(31,70);
  list->strength = randomnumber(50,1);
  list->magicskills = 50 + randomnumber(29,1);
}
void wizardstats(struct Player *list)
{
  list->luck = randomnumber(51,50);
  list->smartness = randomnumber(11,90);
  list->strength = randomnumber(20,1);
  list->magicskills = randomnumber(21,80);
  list->dexterity = randomnumber(100,1);
}
int randomnumber(int limit, int base)
{
  static unsigned int seed = 100; //I was getting the same numbers sometimes, so changing the seed each call helps alleviate this.
  seed+=100;
  srand(time(NULL)+seed);
  return (base + rand()%limit);
}

void slotBuild(struct Slots *s)
{
	for(counter=0;counter<slotNum;counter++)
	{
	s[counter].preset = rand() % 3;
		if(s[counter].preset==0)
			strcpy(s[counter].type, "Level Ground");
		else if(s[counter].preset==1)
			strcpy(s[counter].type, "Hill");
		else
			strcpy(s[counter].type, "City");

      s[counter].position = counter+1;
	}
	for(counter=0;counter<slotNum;counter++)
	{
	printf("Slot %d = %s \n", s[counter].position, s[counter].type);
	}
}
