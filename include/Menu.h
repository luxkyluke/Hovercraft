#ifndef MENU_H_
#define MENU_H_

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include "sdl_tools.h"
#include "Level.h"
#include "Game.h"
#include "glut_tools.h"
#include "TypeMenu.h"


typedef	struct {
    Game* game;
	int largeur;
	int hauteur;
	TypeMenu type;
	GLuint texture;
	GLuint texture_btn1;
	GLuint texture_btn2;
    // GLuint texture_ter1;
    // GLuint texture_ter2;
}Menu;

bool MakeMenu(int width, int height, Menu* menu, TypeMenu type);
void DessinMenu(Menu* menu, GLuint text,int scoreP1, int scoreP2);
void CallMenuDemarrage(Menu* menu);
bool CallMenuPause(Menu* menu);
bool CallMenuFin(Menu* menu, int scoreP1, int scoreP2);
void FreeMenu(Menu* m);
bool InitGameMenu(Menu* m, int duration);
void AfficheScoreMenu(int score1, int score2);


#endif
