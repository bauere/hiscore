#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define LEN_TITLE 50
#define TRUE 1
#define FALSE 0

int ngames=0;
struct game* gamelist;
FILE *fp;

void game_array_init()
{
	int filesize;

	/* Get filesize. */
	fp = fopen("scores.db", "rb+");
        fseek(fp, 0, SEEK_END);
        filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

	ngames = filesize / sizeof(game);

	if (ngames != 0) {
		gamelist = calloc(ngames, sizeof(game));
		fread(gamelist, sizeof(game), ngames, fp);
		fclose(fp);
	} else {
		fprintf(stdout, "Game array of zero length created.\n");
	}
}

void game_array_write()
{
	fp = fopen("scores.db", "rb+");
	fwrite(gamelist, sizeof(struct game), ngames, fp);
	fclose(fp);
}

int erase_game(char* name)
{
	int index = game_exists(name);
	if (index != -1) {
		for (int i=0; i < ngames-1; i++)
			gamelist[i] = gamelist[i+1];

		ngames--;
		struct game* tmp = realloc(gamelist, ngames * sizeof(struct game));

		if (tmp == NULL) {
			fprintf(stderr, "Unable to reallocate game array.");
			return -1;
		}
		gamelist = tmp;
		return 0;
	}
	fprintf(stderr, "Game %s not found", name);
	return -1;
}

void add_game(char* input)
{
	/* Don't add game if it exists in gamelist. */
	if (game_exists(input) > -1) {
		fprintf(stdout, "!!!Game %s already exists at index %d.\n",
				input, game_exists(input));
	} else {
		struct game* newgame = calloc(1, sizeof(game));

		/* If no arg was provided for -a, let user input game title. */
		if (strlen(input) == 0) {
			memset(input, '0', LEN_TITLE);

			printf("Enter the title of the game to add: ");
			fgets(input, LEN_TITLE, stdin);

			/* Remove fgets newline from input. */
			char *pos;
			if ((pos=strchr(input, '\n')) != NULL)
				*pos = '\0';
		}

		strcpy(newgame->title, input);
		ngames++;

		struct game* tmp = (struct game*)
				realloc(gamelist, ngames * sizeof(struct game));
		if (tmp == NULL) {
			fprintf(stderr, "Unable to reallocate game array memory.\n");
			return;
		}
		gamelist = tmp;
		gamelist[ngames-1] = *newgame;
		printf("game added\n");
		free(newgame);
	}
	printf("add game finished\n");
}

// Checks if game title already exists in array.
// Returns index if game exists, or -1 if it doesn't.
int game_exists(char* newgame)
{
	printf("HELLO!\n");
	if (ngames == 0) {
		fprintf(stdout, "Can't check if game exists: Game list is empty.");
		return -1;
	}
	for(int i=0; i < ngames; i++) {
		printf("%s        %s\n", gamelist[i].title, newgame);
		if (strcmp(gamelist[i].title, newgame) == 0)
			return i;
	}
	return -1;
}

void score_table(int index)
{
	for (int i=0; i < 10; i++) {
		printf("%d\n", gamelist[index].scores[i]);
		printf("        ");
		printf("%s\n", gamelist[index].names[i]);
	}

}
