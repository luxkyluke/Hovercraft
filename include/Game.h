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
	int duration; //en seconde
    SDL_Joystick* joystick;
}Game;

void setVideoMode(unsigned int windowWidth, unsigned int windowHeight);
bool MakeGame(Game* game, int duration);
bool AddLevel(Game* game, char* nameFichTerrain);
bool PlayGame(Game* game, int windowWidth, int windowHeight);
void FreeGame(Game* g);

#endif
