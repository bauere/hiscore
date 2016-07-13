#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "database.h"
#include "game.h"

#define LEN_TITLE 50
#define TRUE 1
#define FALSE 0

int main(int argc, char* argv[]) 
{
	int aflag=0;
	int sflag=0;
	int c=0;
	int index=0;
	int namearg=0;
	int tmp=0;
	FILE *fp;
	char enteredtitle[LEN_TITLE];

	memset(enteredtitle, 'A', sizeof(enteredtitle));

	opterr = 0;

	while ((c = getopt(argc,argv,"as")) != -1) {
		switch(c) {
		case 'a':
			aflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case '?':
			if (optopt == 'a')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		default:
			break;
		}
	}
	// Read non-flag input (title of game). 
	// Quit if more than one is entered.
	for (index = optind; index < argc; index++) {
		if (namearg == TRUE) {
			printf("Too many arguments.\n");
			return 0;
 		}			
		printf("Non-option argument %s\n", argv[index]);
		strcpy(enteredtitle, argv[index]);
		namearg = TRUE;
	}

	// Check if file exists. If not, create it.	
	if (access("scores.db", F_OK) == -1)
		fp = fopen("scores.db", "wb+");
	else
		fp = fopen("scores.db", "rb+");
	fclose(fp);
	
	// Initialize database, read scores from scores.db.
	database gamedb;
	db_init(&gamedb, 0);
	file_read(fp, &gamedb);
	printf("NUMBER ENTERED WAS: %d",gamedb.array[2].scores[0]);
	if (aflag) {
		if (game_exists(&gamedb, enteredtitle) > -1)
			printf("Game %s already exists.\n", enteredtitle);
		else
			add_game(&gamedb, enteredtitle);
	}
	else if (sflag) {
		tmp = game_exists(&gamedb, enteredtitle);
		if (tmp != -1) {
			score_table(&gamedb, index);
		} else {
			printf("Game %s doesn't exist.", enteredtitle);
			return 0;
		}
	}
	
	file_write(&fp, &gamedb);

	free(gamedb.array);
		
	return 1;
}
