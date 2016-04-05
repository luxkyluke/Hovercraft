#ifndef GAME_H_
#define GAME_H_

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

/* FIN DU A GARDER */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Level.h"

typedef struct {
	Level** levels;
	int nbLevels;
	float duration; //en seconde
}Game;

void MakeGame(Game* game, float duration);
int AddLevel(Game* game, char* nameFichTerrain,  char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2);
void PlayLevel(Game* game, int idLevel);
void FreeGame(Game* g);

#endif