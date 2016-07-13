#include <stdio.h>
#include <string.h>
#include "database.h"
#include "game.h"

#define LEN_TITLE 50

void add_game(database *db, char* input) 
{
	game newgame;
   	newgame	= make_game();
	//char input[50];
	
	//printf("THIS IS THE AMOUNT OF CHARACTERS:%d",(int)strlen(input));
	if (strlen(input) == 0) {
		memset(input, '0', LEN_TITLE);

		printf("Enter the title of the game to add: ");
		fgets(input, LEN_TITLE, stdin);

		printf("\n%s", input);
		// Remove newline from input.	
		char *pos;
		if ((pos=strchr(input, '\n')) != NULL)
			*pos = '\0';

	}
	
	strcpy(newgame.title, input);
	db_add(db, &newgame);
}

game make_game()
{   
    game newgame;   	
    memset(&newgame, '0', sizeof(game));
	memset(newgame.title, '0', sizeof(newgame.title));
        
    return newgame;
}
