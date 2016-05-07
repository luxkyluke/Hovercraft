/* A GARDER QUAND ON UTILISE OPENGL */
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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/Menu.h"

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 750



int main(int argc, char** argv) {

	initGlut(argc, argv);

	Menu* menu = (Menu *) malloc(sizeof(Menu));


	if (!MakeMenu(WINDOW_WIDTH, WINDOW_HEIGHT, menu, debut))
		return EXIT_FAILURE;


	CallMenuDemarrage(menu);

	FreeMenu(menu);

	return EXIT_SUCCESS;
}
