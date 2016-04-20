#include "Game.h"
#include "sdl_tools.h"

#define NB_MAX_LEVEL 30


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

void PlayGame(Game* game, int windowWidth, int windowHeight){
	
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
