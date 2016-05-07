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
	//initialisation du contexte glut
	initGlut(argc, argv);

	Menu* menu = (Menu *) malloc(sizeof(Menu));

	Game* game = (Game *) malloc(sizeof(Game));

	//si probleme lors de la création du menu -> exit
	if (!MakeMenu(WINDOW_WIDTH, WINDOW_HEIGHT, menu, debut))
		return EXIT_FAILURE;

	//si porblème lors de la création du game -> exit
	if (!MakeGame(game)) {
		printf("Erreur MakeGame !!");
		return EXIT_FAILURE;
	}

	CallMenuDemarrage(menu, game);

	//liberation du *game
	FreeGame(game);
	free(game);
	game = NULL;

	//libéraiton du *menu
	free(menu);
	menu = NULL;

	return EXIT_SUCCESS;
}
