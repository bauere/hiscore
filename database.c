#include <stdio.h>
#include <stdlib.h>
#include "database.h"

// Creates initial db struct for holding vars and game array.
void dbInit(database *db, int initSize) {

    db->array = calloc(initSize, sizeof(game));
    db->used = 0;
    db->size = initSize;
}

// Read game array index; returns that game.
game dbRead(database *db, int index) {
	
	if (db->size <= index)
		printf("INDEX OUT OF BOUNDS LOL\n");	
	
	return db->array[index];
}

// Increment db size, then add the new game to the end of the array.
void dbAdd(database *db, game *to_write) {

	db->size++;
	dbExpand(db);	
	db->array[db->size -1] = *to_write;

}

// Grow the size of the array by 1 game.
void dbExpand(database *db) {
	
	game *newArray;
    newArray = (game*) realloc(db->array, db->size * sizeof(game));
	db->array = newArray;

}

// Remove index item from game array, and shrink the array by 1 game.
void dbErase(database *db, int index) {

	for (int i = index; i < db->size-1; i++)
		db->array[i] = db->array[i+1];
		
	db->size--;
	db->array = realloc(db->array, db->size * sizeof(game));
	
}
