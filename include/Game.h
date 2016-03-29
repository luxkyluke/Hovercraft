#ifndef GAME_H_
#define GAME_H_

typedef struct {
	Level** levels;
	int nbLevels;
	float duration;
};

void MakeGame(Game* game, float duration);
void AddLevel(Game* game, Level* level);
void FreeGame(Game* g);

#endif