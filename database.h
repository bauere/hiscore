#ifndef DATABASE_H
#define DATABASE_H

typedef struct game {

	char title[50];
	unsigned long long int scores[10];
	char names[10][3];

} game;

typedef struct database {

	struct game* array;
	size_t size;
	size_t used;

} database;

void dbInit();
game dbRead();
void dbAdd();
void dbExpand();
void dbErase();

#endif
