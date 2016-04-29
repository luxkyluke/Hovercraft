#include "Game.h"
#include "sdl_tools.h"
#include "TypeMenu.h"
#include "../include/Menu.h"

#define NB_MAX_LEVEL 30
#define NB_LEVEL 2


bool MakeGame(Game* game, int duration){
	if(game == NULL) {
		printf("Impossible de créer le game, pointeur non alloué\n");
		return false;
	}



	game->levels = (Level **) malloc(NB_MAX_LEVEL*sizeof(Level*));
	game->nbLevels = 0 ;
	game->duration = duration;

	int i;
	for (i=1; i<NB_LEVEL+1; i++){
		char levelTxt[10];
		sprintf(levelTxt, "level%d", i);
		if(!AddLevel(game, levelTxt))
			return false;
	}
	return true;

}

bool AddLevel(Game* game, char* nameFichTerrain){

	if(!game || !nameFichTerrain)
        return false;
	if(game->nbLevels == NB_MAX_LEVEL){
		printf("Echec de l'ajout - Nombre de level max depasse \n");
        return false;
	}
    int id = game->nbLevels;
	game->levels[id] = (Level *) malloc(sizeof(Level));

	if(!MakeLevel(game->levels[id], nameFichTerrain, game->duration, game->nbLevels)){
		printf("Probleme makeLevel dans AddLevel\n");
        return false ;
	}
	game->nbLevels += 1;
	return true;
}

bool PlayGame(Game* game, int windowWidth, int windowHeight){
    if(!game)
		return false;

    int i;
    for(i=0 ;i<game->nbLevels; ++i){
    	bool cross = false;
    	bool thisIsTheEnd = PlayLevel(game->levels[i], windowWidth, windowHeight, i, &cross);
        if(cross){
        	return false;
        }
    	if(thisIsTheEnd){
			Menu menuFin;
			MakeMenu(windowWidth, windowHeight, &menuFin, fin);
			if(!CallMenuFin(&menuFin))
				return false;
        }
    }
    return true;
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
