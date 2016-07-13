#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "database.h"
#include "game.h"

#define LEN_TITLE 50

int main(int argc, char* argv[]) 
{
	
	//Flag handler.
	int aflag=0;
	int c=0;
	int index=0;

	char enteredtitle[LEN_TITLE];
	memset(enteredtitle, '\0', sizeof(enteredtitle));

	opterr = 0;

	while ((c = getopt(argc,argv,"a")) != -1) {
		switch(c) {
		case 'a':
			aflag = 1;
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
		printf("Non-option argument %s\n", argv[index]);
		strcpy(enteredtitle, argv[index]);
	}
		
	//End flag handler.
	
	FILE *fp;
	
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

	if (aflag)
		add_game(&gamedb, enteredtitle);
	
	file_write(&fp, &gamedb);
	//fileRead(&fp, &gamedb);
   	printf("GAME:%s", gamedb.array[0].title);

	free(gamedb.array);
		
	return 1;
}
