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
void city(struct Player *list);
void hill(struct Player *list);

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
int moveup, movedown, attackfound, yattack, xattack; //These are basically true/false variable to be used in the following loops.
char enemy1[20], enemy2[20];
int e1,e2,dmgdealt;
for(int i=0;i<numplayers;i++) //Please keep everything within this loop, as the program ends after every turn has been processed.
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
  int movech;
  
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
		e1 = l;
      }
      if(x == playerlist[l].position)
      {
        attackfound = 1;
        strcpy(enemy2,playerlist[l].playername);
        xattack = 1;
		e2 = l;
      }

    }
  }
  int turnchoice,movechoice,attackchoice;
  printf("\nWhat would you like to do?. Press 1 to move or 2 to attack.\n");
    scanf("%d", &turnchoice);
    if(turnchoice!=1 && turnchoice!=2)
    {
        perror("Wrong input.\n");
        return -1;
    }
    if(turnchoice==1)
        {
            if(moveup == 1 && movedown == 1)
            {
                printf("Do you want to move up to slot %d,%s or down to slot %d,%s?\n", s[playerlist[i].position].position,s[playerlist[i].position].type, s[playerlist[i].position-2].position,s[playerlist[i].position-2].type);
                printf("Press 1 for up or 2 for down.\n");
                scanf("%d", &movechoice);
                if(movechoice!=1 && movechoice!=2)
                {
                    perror("Wrong input.\n");
                    return -1;
                }
            }else if(moveup == 1 && movedown == 0)
            {
                movechoice = 1;
            }else if(moveup == 0 && movedown == 1)
            {
                movechoice = 2;
            }else
            {
                printf("You cannot move anywhere... Good job wasting your turn xD.\n");
            }
            if(movechoice==1)
            {
                strcpy(playerlist[i].slot,s[playerlist[i].position].type);
                playerlist[i].position = s[playerlist[i].position].position;
                if(playerlist[i].slot[0] == 'H')
                {
                    if(playerlist[i].dexterity<50)
                    {
                        playerlist[i].strength -= 10;
                        printf("You lost 10 strength.\n");
                        if(playerlist[i].strength<0)
                        {
                            playerlist[i].strength = 0;
                        }
                    }else if(playerlist[i].dexterity>=60)
                    {
                        playerlist[i].strength += 10;
                        printf("You gained 10 strength.\n");
                    }
                }else if(playerlist[i].slot[0] == 'C')
                {
                    if(playerlist[i].smartness>60)
                    {
                        playerlist[i].magicskills += 10;
                        printf("You gained 10 magicskills.\n");
                    }else if(playerlist[i].smartness<=50)
                    {
                        playerlist[i].dexterity -= 10;
                        printf("You lost 10 dexterity.\n");
                    }
                }
            }else if(movechoice==2)
            {
                strcpy(playerlist[i].slot,s[playerlist[i].position-2].type);
                playerlist[i].position = s[playerlist[i].position-2].position;
                if(playerlist[i].slot[0] == 'H')
                {
                    if(playerlist[i].dexterity<50)
                    {
                        playerlist[i].strength -= 10;
                        printf("You lost 10 strength.\n");
                        if(playerlist[i].strength<0)
                        {
                            playerlist[i].strength = 0;
                        }
                    }else if(playerlist[i].dexterity>=60)
                    {
                        playerlist[i].strength += 10;
                        printf("You gained 10 strength.\n");
                    }
                }else if(playerlist[i].slot[0] == 'C')
                {
                    if(playerlist[i].smartness>60)
                    {
                        playerlist[i].magicskills += 10;
                        printf("You gained 10 magicskills.\n");
                    }else if(playerlist[i].smartness<=50)
                    {
                        playerlist[i].dexterity -= 10;
                        printf("You lost 10 dexterity.\n");
                    }
                }
            }
            printf("New position of player %d: %d,%s\n",i+1,playerlist[i].position,playerlist[i].slot);
 
 
        }else if(turnchoice==2)
        {
            if(yattack==1 && xattack==1)
            {
                printf("You can attack either %s or %s.\n", enemy1,enemy2);
                printf("Press 1 to attack %s or 2 to attack %s.\n", enemy1, enemy2);
                scanf("%d", &attackchoice);
                if(attackchoice!=1 && attackchoice!=2)
                {
                    perror("Wrong input.\n");
                    return -1;
                }
            }else if(yattack == 1 && xattack == 0)
          {
            printf("You will attack %s.\n", enemy1);
                attackchoice = 1;
          }else if(yattack == 0 && xattack == 1)
          {
            printf("You will attack %s.\n", enemy2);
                attackchoice = 2;
          }else
          {
            printf("You cannot make an attack at this time... Good job wasting your turn xD.\n");
          }
 
        }
 
        if(attackchoice==1)
        {
            if(playerlist[e1].strength<=70)
            {
                playerlist[e1].lifepoints -= (playerlist[e1].strength/2);
                printf("%s lost %d lifepoints.\n", playerlist[e1].playername, playerlist[e1].strength/2);
            }else if(playerlist[e1].strength>70)
            {
                playerlist[i].lifepoints -= ((playerlist[e1].strength/10)*3);
                printf("%s lost %d lifepoints.\n", playerlist[i].playername, (playerlist[e1].strength/10)*3);
            }
        }else if(attackchoice==2)
        {
            if(playerlist[e2].strength<=70)
            {
                playerlist[e2].lifepoints -= (playerlist[e2].strength/2);
                printf("%s lost %d lifepoints.\n", playerlist[e2].playername, playerlist[e2].strength/2);
            }else if(playerlist[e2].strength>70)
            {
                playerlist[i].lifepoints -= ((playerlist[e2].strength/10)*3);
                printf("%s lost %d lifepoints.\n", playerlist[i].playername, (playerlist[e2].strength/10)*3);
            }
        }
		
		
	if (s[playerlist[i].position].preset == 1)
	{
	hill(&playerlist[i]);	
	}
	else if (s[playerlist[i].position].preset == 2)
	{
	city(&playerlist[i]);
	}
    printf("Stats updated according to new player positions.\n");
	for(int i=0;i<numplayers;i++) //Player info is printed out to the user.
	{
	printf("Player %d:\n", i+1);
	printf("Name= %s, Type= %s, Lifepoints= %d, smartness= %d, strength= %d, magicskills= %d, luck= %d, dexterity= %d.\n", playerlist[i].playername, playerlist[i].playertype, playerlist[i].lifepoints, playerlist[i].smartness, playerlist[i].strength, playerlist[i].magicskills, playerlist[i].luck, playerlist[i].dexterity);
	}
	printf("\nTurn End.\n");
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
  list->lifepoints = 100;
}
void ogrestats(struct Player *list)
{
  list->magicskills = 0;
  list->smartness = randomnumber(21,0);
  list->strength = randomnumber(21,80);
  list->dexterity = randomnumber(21,80);
  list->luck = randomnumber((50-list->smartness),0);
  list->lifepoints = 100;
}
void elfstats(struct Player *list)
{
  list->dexterity = randomnumber(100,1);
  list->luck = randomnumber(41,60);
  list->smartness = randomnumber(31,70);
  list->strength = randomnumber(50,1);
  list->magicskills = 50 + randomnumber(29,1);
  list->lifepoints = 100;
}
void wizardstats(struct Player *list)
{
  list->luck = randomnumber(51,50);
  list->smartness = randomnumber(11,90);
  list->strength = randomnumber(20,1);
  list->magicskills = randomnumber(21,80);
  list->dexterity = randomnumber(100,1);
  list->lifepoints = 100;
}
int randomnumber(int limit, int base)
{
  static unsigned int seed = 100; //I was getting the same numbers sometimes, so changing the seed each call helps alleviate this.
  seed+=100;
  srand(time(NULL)+seed);
  return (base + rand()%limit);
}

void hill(struct Player *list)
{
	if(list->dexterity <50)
	{
		list->strength = list->strength-10;
	}
	else if(list->dexterity >= 60)
	{
		list->strength = list->strength+10;
	}
}

void city(struct Player *list)
{
	if(list->smartness >50)
	{
		list->magicskills = list->magicskills+10;
	}
	else if(list->smartness <= 60)
	{
		list->magicskills = list->dexterity-10;
	}
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
