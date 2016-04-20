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

#include "sdl_tools.h"
#include "Level.h"
#include "Game.h"
#include <stdio.h>

typedef	struct {
	Game* game;
	int largeur;
	int hauteur;
	GLuint texture;
}Menu;

void MakeMenu(char* pathTexture, int width, int height, Menu* menu);
void DessinMenu(Menu* menu);
void CallMenuDemarrage(Menu* menu);
void FreeMenu(Menu* m);


#endif
