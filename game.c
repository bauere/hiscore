#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "game.h"

#define LEN_TITLE 50
#define TRUE 1
#define FALSE 0

void add_game(database *db, char* input) 
{
	game* newgame;
   	newgame	= make_game();
	printf("INPUT: %s", input);
	if (strlen(input) == 0) {
		memset(input, '0', LEN_TITLE);

		printf("Enter the title of the game to add: ");
		fgets(input, LEN_TITLE, stdin);

		// Remove fgets newline from input.	
		char *pos;
		if ((pos=strchr(input, '\n')) != NULL)
			*pos = '\0';
	}

	char* cool = "dlasafsfaffs";	
	strcpy(newgame->title, input);
	newgame->scores[0] = 999;
	db_add(db, newgame);
	free(newgame);
}

game* make_game()
{   
    game* newgame = calloc(1, sizeof(struct game));   	
   
	/*
	newgame.scores[0] = 0;
	newgame.scores[1] = 0;
	newgame.scores[2] = 0;
	newgame.scores[3] = 0;
	newgame.scores[4] = 0;
	newgame.scores[5] = 0;
	newgame.scores[6] = 0;
	newgame.scores[7] = 0;
	newgame.scores[8] = 0;
	newgame.scores[9] = 0;
	
	newgame.names[0][0] = '0';
	newgame.names[0][1] = '0';
	newgame.names[0][2] = '0';
	newgame.names[1][0] = '0';
	newgame.names[1][1] = '0';
	newgame.names[1][2] = '0';
	newgame.names[2][0] = '0';
	newgame.names[2][1] = '0';
	newgame.names[2][2] = '0';
	newgame.names[3][0] = '0';
	newgame.names[3][1] = '0';
	newgame.names[3][2] = '0';
	newgame.names[4][0] = '0';
	newgame.names[4][1] = '0';
	newgame.names[4][2] = '0';
	newgame.names[5][0] = '0';
	newgame.names[5][1] = '0';
	newgame.names[5][2] = '0';
	newgame.names[6][0] = '0';
    newgame.names[6][1] = '0';
    newgame.names[6][2] = '0';
    newgame.names[7][0] = '0';
    newgame.names[7][1] = '0';
    newgame.names[7][2] = '0';
    newgame.names[8][0] = '0';
    newgame.names[8][1] = '0';
    newgame.names[8][2] = '0';
	newgame.names[9][0] = '0';
    newgame.names[9][1] = '0';
    newgame.names[9][2] = '0';
	*/
    return newgame;
}

// Checks if game title already exists in array.
// Returns index if game exists, or -1 if it doesn't.
int game_exists(database *db, char* newgame)
{
	for(int i=0; i < db->size; i++)
		if (strcmp(db->array[i].title, newgame) == 0) 
			return i;

	return -1;	
}

void score_table(database *db, int index)
{
	

}
