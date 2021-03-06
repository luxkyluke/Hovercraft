#include "Game.h"
#include "sdl_tools.h"
#include "TypeMenu.h"
#include "../include/Menu.h"

//nombre maximum de niveau
#define NB_MAX_LEVEL 30

//nombre de niveau actifs
#define NB_LEVEL 2

//durée d'un niveau du jeu
#define DURATION_TIME 180000

//les fichier des texture de terrains
#define DEFAULT_TERRAIN_TEXTURE_PATH "images/terrain1.png"
#define DEFAULT_TERRAIN_TEXTURE2_PATH "images/terrain2.png"

bool MakeGame(Game* game){
	if(game == NULL) {
		printf("Impossible de créer le game, pointeur non alloué\n");
		return false;
	}
	game->levels = (Level **) malloc(NB_MAX_LEVEL*sizeof(Level*));
	game->nbLevels = 0 ;
	game->duration = DURATION_TIME;

    SDL_Joystick *joystick; // on crée le joystick
    joystick = SDL_JoystickOpen(0); // on l'assigne au numéro 0
    game->joystick = joystick;
    if (game->joystick != NULL) {
        SDL_JoystickEventState(SDL_ENABLE);
        FILE* fichier = NULL;
        fichier = fopen("Joystick.txt","w+"); // on crée un fichier Joystick.txt

        if(fichier != NULL){
            fprintf(fichier,"Il y a %d joysticks.",SDL_NumJoysticks()); // on écrit combien il y a de joysticks
            for(int i=0;i<SDL_NumJoysticks();i++)
            fprintf(fichier,"Nom du joystick numero %d : %s",i,SDL_JoystickName(i)); // on écrit les noms des joysticks
            fprintf(fichier,"Nombre de boutons : %d",SDL_JoystickNumButtons(joystick)); // nombre de boutons
            fprintf(fichier,"Nombre de chapeaux : %d",SDL_JoystickNumHats(joystick)); // nombre de chapeaux
            fprintf(fichier,"Nombre de trackballs : %d",SDL_JoystickNumBalls(joystick)); // nombre de trackballs
            fclose(fichier); // on referme le fichier
        }

    } else  {
        SDL_JoystickEventState(SDL_DISABLE);
    }
    //ajoute des niveaux jusqu'a NB_LEVEL ne nombre de niveaux connus (ici 2)
	int i;
	for (i=1; i<NB_LEVEL+1; i++){
		char levelTxt[10], pathTexture[50];
		sprintf(levelTxt, "level%d", i);
		sprintf(pathTexture, "images/terrain%d", i);
		strcat(pathTexture,  ".png");
		if(!AddLevel(game, levelTxt, pathTexture)) //Ajout du niveau level+i
			return false;
	}
	return true;
}

bool AddLevel(Game* game, char* nameFichTerrain, char* pathTexture){
	if(!game || !nameFichTerrain)
        return false;
	if(game->nbLevels == NB_MAX_LEVEL){
		printf("Echec de l'ajout - Nombre de level max depasse \n");
        return false;
	}
    int id = game->nbLevels;
	game->levels[id] = (Level *) malloc(sizeof(Level));

	if(!MakeLevel(game->levels[id], nameFichTerrain, game->duration, pathTexture)){
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
    	bool thisIsTheEnd = PlayLevel(game->levels[i], i, &cross, game->joystick);
        if(cross){
        	return false;
        }
    	if(thisIsTheEnd){
			Menu menuFin;
			MakeMenu(windowWidth, windowHeight, &menuFin, fin);
			if(!CallMenuFin(&menuFin, game->levels[i]->scoreP1, game->levels[i]->scoreP2))
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

//    SDL_JoystickEventState(SDL_DISABLE);
   if(g->joystick!=NULL)
        SDL_JoystickClose(g->joystick);
//     probleme, normalement il faut le fermer le kono SDL_JoystickClose(g->joystick);
//     free(g->joystick);
//	g->levels = NULL;
	printf("FreeGame OK\n");
}
