//Richard Otroshchenko
//05/03/17
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Program to generate the list of players using the user's input.
//Also generates the stats of those players.
struct Player {
  char playertype[20];
  char playername[20];
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

int main(void)
{
int numplayers, typechoice;
struct Player playerlist[6]; //The 6 players will be stored in this array

printf("How many players are there?(up to 6 and no spaces PLEASE)\n");
scanf("%d", &numplayers);
if(numplayers<1 || numplayers>6) //Program ends if too little or too many players are chosen.
{
  perror("Wrong choice inputted.\n");
  return -1;
}
for(int i=0;i<numplayers;i++) //This loops assigns the name, type and stats of each player one by one.
{
  printf("Please enter the name of player %d.\n", i+1);
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
