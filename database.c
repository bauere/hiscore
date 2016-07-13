#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

// Create initial db struct for holding vars and game array.
void db_init(database *db, int initSize)
{
	memset(db, '\0', sizeof(database));	
    db->array = malloc(initSize * sizeof(game));
    db->used = 0;
    db->size = initSize;
}

// Read game array index; returns that game.
game db_read(database *db, int index)
{
	
	if (db->size <= index)
		printf("INDEX OUT OF BOUNDS LOL\n");	
	
	return db->array[index];
}

// Increment db size, then add the new game to the end of the array.
void db_add(database *db, game *to_write)
{
	db->size++;
	db_expand(db);	
	db->array[db->size-1] = *to_write;
}

// Grow the size of the array by 1 game.
void db_expand(database *db)
{	
	game *newArray;

    newArray = (game*) realloc(db->array, db->size * sizeof(game));
	db->array = newArray;
}

// Remove index item from game array, and shrink the array by 1 game.
void db_erase(database *db, int index)
{
	for (int i = index; i < db->size-1; i++)
		db->array[i] = db->array[i+1];
		
	db->size--;
	db->array = realloc(db->array, db->size * sizeof(game));	
}

// Count games from scores.db, 
// then copy games array from scores.db and number of games 
// to new database.
void file_read(FILE *fp, database *db)
{
	int filesize = 0;

	// Get filesize.
	fp = fopen("scores.db", "rb+");	
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	int gamecount = filesize / sizeof(game);
	
	db_init(db, gamecount);	
	
	fread(db->array, sizeof(game), gamecount, fp);
	fclose(fp);
}

// Write game array to scores.db.
void file_write(FILE *fp, database *db)
{
	fp = fopen("scores.db", "rb+");
	fwrite(db->array, sizeof(game), db->size, fp);
	fclose(fp);
}	
