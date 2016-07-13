#ifndef GAME_H
#define GAME_H

struct game {
	char title[50];
	int scores[10];
	char names[10][3];
} game;


void game_array_init();
void game_array_write();
void add_game();
int erase_game(char*);
struct game* make_game();
int game_exists();
void score_table();

extern struct game* gamelist;
extern int ngames;

#endif
