#ifndef GAME_H
#define GAME_H

#define LEN_TITLE 50
#define NUM_SCORES 10

struct game {
	char title[LEN_TITLE];
	unsigned long long scores[NUM_SCORES];
	char names[NUM_SCORES][3];
} game;

void game_array_init();
void game_array_write();
void add_game(char*);
int erase_game(char*);
struct game* make_game();
int game_exists(char*);
void score_table();

extern struct game* gamelist;
extern int ngames;

#endif
