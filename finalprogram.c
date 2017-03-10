//Richard Otroshchenko and Matthew Barrett.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//Final program for Assignment 2.
//Notes by Richard.

int slotNum; //Number of slots
	typedef struct Slots
	{
		int preset; //This will hold an integer (0,1 or 2) used when assigning and determining the type to each slot.
		char type[100];
		int position;
	} Slots;
int counter;

struct Player {
  char playertype[20];
  char playername[50];
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
void slotBuild(struct Slots *s); //Random slot generator
void city(struct Player *list); //2 functions to change the stats of players when they move to new slot types
void hill(struct Player *list);

int main(void)
{
int numplayers, typechoice;
struct Player playerlist[6]; //The 6 players will be stored in this array

printf("How many players are there?(up to 6)\n");
scanf("%d", &numplayers);
if(numplayers<1 || numplayers>6) //Program ends if too little or too many players are chosen.
{                                /*I could just let them try again but then they wouldn't learn anything. */
  printf("Wrong choice inputted. The number of players must be an integer between 1 and 6.\n");
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
    humanstats(&playerlist[i]); //stats are assigned to the player
    playerlist[i].lifepoints = 100;
  }
  else if(typechoice==2)
{
    strcpy(playerlist[i].playertype,"Ogre");
    ogrestats(&playerlist[i]);
    playerlist[i].lifepoints = 100;
}
  else if(typechoice==3)
  {
    strcpy(playerlist[i].playertype,"Elf");
    elfstats(&playerlist[i]);
    playerlist[i].lifepoints = 100;
  }
  else if(typechoice==4)
  {
    strcpy(playerlist[i].playertype,"Wizard");
    wizardstats(&playerlist[i]);
    playerlist[i].lifepoints = 100;
  }
    else //In case they enter an invalid number.
     {
      printf("Wrong choice inputted. Please write the number and NOT the type name.\n");
      return -1;
    }
}

printf("Player overview:\n");
for(int i=0;i<numplayers;i++) //Player info is printed out to the user.
{
printf("Player %d:\n", i+1);
printf("Name= %s, Type= %s, Lifepoints= %d, smartness= %d, strength= %d, magicskills= %d, luck= %d, dexterity= %d.\n", playerlist[i].playername, playerlist[i].playertype, playerlist[i].lifepoints, playerlist[i].smartness, playerlist[i].strength, playerlist[i].magicskills, playerlist[i].luck, playerlist[i].dexterity);
}

int wrongslotchoice;
do{
  wrongslotchoice = 0;
printf("\nPlease enter the number of slots you would like (From 1 to 20): \n");
scanf("%d",&slotNum);
if(slotNum<1 || slotNum>20) //Loop repeats if too little or too many slots are chosen.
{
  printf("Wrong choice inputted. Don't like reading, huh?\n");
  wrongslotchoice = 1;
}
}while(wrongslotchoice==1);
printf("Slot overview:\n\n");
Slots s[slotNum]; //Array containing the slots.
slotBuild(s); //Function to populate that array.

int x=49, check[7], different; /*The 49 isnt relevent, it just had to be a number greater than possible number of slots*/
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
printf("\n");
for(int i=0;i<numplayers;i++)
{
  printf("Position of player %d: %d,%s\n",i+1,playerlist[i].position,playerlist[i].slot);
}
int moveup, movedown, attackfound, yattack, xattack, turnchoice ,movechoice ,attackchoice, wrongturnchoice, wrongmovechoice, wrongattackchoice; //These are basically true/false variables to be used in the following loops.
char enemy1[20], enemy2[20]; //When enemies to attack are found, they are recorded in these strings.
int e1,e2;
for(int i=0;i<numplayers;i++) //This large loop will process the turns for each player. From my understanding of the assignment, each player only gets 1 turn each.
{
  yattack = 0;
  xattack = 0;
  attackfound = 0;
  moveup = 1;
  movedown = 1;
  turnchoice = 0;
  movechoice = 0;
  attackchoice = 0;
  printf("\nIt is player %d's turn to make a move\n", i+1);
  for(int j=0;j<6;j++)
  { //Checks for free slots above and below the player, then prints out the possible slots that player can move to in the following if statements.
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
  {                               //The loop will check the positions above or below the player simultaneously, and checks further away until an enemy is found.
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
		    e1 = l; //e1 and e2 will be used when calculating how much damage is taken after an attack.
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
  printf("\nWhat would you like to do?. Press 1 to move or 2 to attack.\n");
  do{
    wrongturnchoice = 0;
    scanf("%d", &turnchoice);
    if(turnchoice!=1 && turnchoice!=2)
    {
        printf("Wrong input. Please choose either 1 or 2.\n");
        wrongturnchoice = 1;
    }
  }while(wrongturnchoice == 1);
    if(turnchoice==1)
        {
            if(moveup == 1 && movedown == 1) //If the player can move to 2 different spaces, we ask them which. Otherwise, we don't and just move them.
            {
                printf("Do you want to move up to slot %d,%s or down to slot %d,%s?\n", s[playerlist[i].position].position,s[playerlist[i].position].type, s[playerlist[i].position-2].position,s[playerlist[i].position-2].type);
                do{
                  wrongmovechoice = 0;
                printf("Press 1 for up or 2 for down.\n");
                scanf("%d", &movechoice);
                if(movechoice!=1 && movechoice!=2)
                {
                    printf("Wrong input. Please choose 1 for up or 2 for down.\n");
                    wrongmovechoice = 1;
                }
              }while(wrongmovechoice==1);
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
            if(movechoice==1) //Moving upwards.
            { //Players are moved than functions are called to change their stats depending on where they end up.
                strcpy(playerlist[i].slot,s[playerlist[i].position].type);
                playerlist[i].position = s[playerlist[i].position].position;
                if (s[playerlist[i].position-1].preset == 1)
              	{
              	hill(&playerlist[i]);
              	}
              	else if (s[playerlist[i].position-1].preset == 2)
              	{
              	city(&playerlist[i]);
              	}

            }else if(movechoice==2) //Moving downwards.
            {
                strcpy(playerlist[i].slot,s[playerlist[i].position-2].type);
                playerlist[i].position = s[playerlist[i].position-2].position;
                if (s[playerlist[i].position-1].preset == 1)
              	{
              	hill(&playerlist[i]);
              	}
              	else if (s[playerlist[i].position-1].preset == 2)
              	{
              	city(&playerlist[i]);
              	}
            }

            printf("New position of player %d is %d,%s\n",i+1,playerlist[i].position,playerlist[i].slot);


        }else if(turnchoice==2)
        {
            if(yattack==1 && xattack==1)
            {
                printf("You can attack either %s or %s.\n", enemy1,enemy2);
                do{
                  wrongattackchoice=0;
                printf("Press 1 to attack %s or 2 to attack %s.\n", enemy1, enemy2);
                scanf("%d", &attackchoice);
                if(attackchoice!=1 && attackchoice!=2)
                {
                    printf("Wrong input. Please choose 1 or 2.\n");
                    wrongattackchoice = 1;
                }
              }while(wrongattackchoice==1);
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

          if(attackchoice==1) //The strength of the attacked player is checked than lifepoints are lost according to the formula on moodle.
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
        }

	printf("\nTurn End.\n");
}

printf("\nFinal scores:\n");
for(int i=0;i<numplayers;i++)
{
	printf("%s (%s, %d)\n", playerlist[i].playername, playerlist[i].playertype, playerlist[i].lifepoints);
}

return 0;
}



void humanstats(struct Player *list)
{ //The following code helps insure that the stats of a Human won't go above 300 but every stat will equal at least 1.
  int total = 300; //Used to count how many stats were given out.
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
  if(total<2) //If the three previos stats summed to 299 or greater, this statement reduces the value of magic skills by 2...
{             //...so that points will be left over for dexterity and luck.
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
    printf("You lost 10 strength.\n");
    if(list->strength<0)
    { //I don't believe stats can get less than 0.
      list->strength = 0;
    }
	}
	else if(list->dexterity >= 60)
	{
		list->strength = list->strength+10;
    printf("You gained 10 strength.\n");
	}
}

void city(struct Player *list)
{
	if(list->smartness >50)
	{
		list->magicskills = list->magicskills+10;
    printf("You gained 10 magicskills.\n");
	}
	else if(list->smartness <= 60)
	{
		list->magicskills = list->dexterity-10;
    printf("You lost 10 dexterity.\n");
    if(list->dexterity<0)
    { //I don't believe stats can get less than 0.
      list->dexterity = 0;
    }
	}
}

void slotBuild(struct Slots *s)
{
	for(counter=0;counter<slotNum;counter++)
	{
	s[counter].preset = rand() % 3; //Assigns one of three random possible number to the slot.
		if(s[counter].preset==0) //This number then determiens what slot type they become.
			strcpy(s[counter].type, "Level Ground");
		else if(s[counter].preset==1)
			strcpy(s[counter].type, "Hill");
		else
			strcpy(s[counter].type, "City");

      s[counter].position = counter+1; //Assigns a number that holds the integer position of each slot.
	}
	for(counter=0;counter<slotNum;counter++)
	{
	printf("Slot %d = %s \n", s[counter].position, s[counter].type);
	}
}
