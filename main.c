#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "database.h"

int main(int argc, char* argv[]) {
	
	//TODO: flag handlers.
	
	//TODO: read scores.db. Store results in score
	
	//TODO: prompt user to enter int score.

	FILE *fp;
	
	// Check if file exists. If not, create it.	
	if (access("scores.db", F_OK) == -1)
		fp = fopen("scores.db", "wb+");
	else
		fp = fopen("scores.db", "rb+");
	fclose(fp);
	
	database gameDB;
	memset(&gameDB, '\0', sizeof(database));
	dbInit(&gameDB, 0);

	game newGame;
	memset(&newGame, '\0', sizeof(game));
	
	strcpy(newGame.title, "lol");
		
	dbAdd(&gameDB, &newGame);

	game newGame2;
	memset(&newGame2, '\0', sizeof(game));
	strcpy(newGame2.title, "HOLYSHITPLEASEAPPEAR");
	
	dbAdd(&gameDB, &newGame2);

	fp = fopen("scores.db", "wb+");

	printf("\n%d\n", gameDB.size);
	fwrite(gameDB.array, sizeof(game), gameDB.size, fp);
	fclose(fp);
	return 1;
}
