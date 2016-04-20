#include "Game.h"
#include "sdl_tools.h"

#define NB_MAX_LEVEL 30

/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;


void setVideoMode(unsigned int windowWidth, unsigned int windowHeight) {
  if(NULL == SDL_SetVideoMode(windowWidth, windowHeight, BIT_PER_PIXEL, SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE)) {
    fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    exit(EXIT_FAILURE);
  }
}

unsigned int windowHeight= 650;
unsigned int windowWidth = 1300;

void MakeGame(Game* game, float duration){
	if(game == NULL) {	
		printf("Impossible de créer le game, pointeur non alloué\n"); 
		return;
	}

	 // Initialisation de la SDL 
//	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
//	  fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
//	  return;
//	}
//
//	// Ouverture d'une fenêtre et création d'un contexte OpenGL
//	setVideoMode(windowWidth, windowHeight);
//	reshape(windowWidth, windowHeight);

	game->levels = (Level **) malloc(NB_MAX_LEVEL*sizeof(Level*));
	game->nbLevels = 0;
	game->duration = duration;
}

void AddLevel(Game* game, char* nameFichTerrain,  char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2){
	if(!game || !nameFichTerrain || !pathTextureTerrain || !pathTextureVp2 || !pathTextureVp1)
        return ;
	if(game->nbLevels == NB_MAX_LEVEL){
		printf("Echec de l'ajout - Nombre de level max depasse \n");
        return ;
	}
    int id = game->nbLevels;
	game->levels[id] = (Level *) malloc(sizeof(Level));
	MakeLevel(game->levels[id], nameFichTerrain, pathTextureTerrain, pathTextureVp1, pathTextureVp2);
	if(game->levels[id]  == NULL){
		printf("Probleme makeLevel dans AddLevel\n");
        return ;
	}
	game->nbLevels += 1;

}

void PlayGame(Game* game){
	
    if(!game)
		return;

    int i;
    for(i=0 ;i<game->nbLevels; ++i){
        PlayLevel(game->levels[i], windowWidth, windowHeight, i);
    }

}

void FreeGame(Game* g){
	int i;
	for(i=0; i< g->nbLevels ; i++){
		FreeLevel(g->levels[i]);
		free(g->levels[i]);
		g->levels[i] = NULL;
	}
	free(g->levels);
	g->levels = NULL;
	printf("FreeGame OK\n");
}
