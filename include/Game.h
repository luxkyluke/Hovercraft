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
	Level** levels; //tableau des niveaux
	int nbLevels;	//nombre de niveau du jeu
	int duration; 	//la durée d'une partie du jeu (en milliseconde)
	SDL_Joystick* joystick;
} Game;

/**
 * @brief Créer un jeu
 * @param game - le pointeur sur le game à créer
 * @return true si la création c'est bien passé, false sinon
 */
bool MakeGame(Game* game);

/**
 * @brief Ajoute un leve au game passé en param
 * @param game - le game auquel ajouter le level
 * @param nameFichTerrain - le nom du fichier txt du terrain a ajouter
 * @param pathTexture - la texture du niveau a ajouter
 * @return true si l'ajout c'est bien passer, false sinon
 */
bool AddLevel(Game* game, char* nameFichTerrain, char *pathTexture);

/**
 * @brief Lance le jeu passé en parametre, c-a-d lance tous
 * les niveaux du jeu tant que le l'utilisateur ne quitte pas
 * @param game - le jeu qu'on souhaite lancer
 * @param width - la largeur de la fenetre
 * @param height - la hauteur de la fenetre
 * @return true si le jeu c'est bien passer (l'utilisateur a joué a tous les niveaux), false sinon
 */
bool PlayGame(Game* game, int windowWidth, int windowHeight);

/**
 * @brief Libere les pointeur du Gmae
 * @param g - le pointeur du game à liberer
 */
void FreeGame(Game* g);

#endif
