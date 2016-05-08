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
	int largeur;
	int hauteur;
	TypeMenu type;
	GLuint texture;
	GLuint texture_btn1;
	GLuint texture_btn2;
}Menu;

/**
 * @brief Creer un Menu avec le pointeur de Menu passé en paramètre
 * @param width - la largeur de la fenetre
 * @param height - la hauteur de la fenetre
 * @param menu - le pointeur du menu à créer
 * @param type - le type de menu à créer
 * @return true si la création c'est bien passé, false sinon
 */
bool MakeMenu(int width, int height, Menu* menu, TypeMenu type);

/**
 * @brief Dessine le Menu passé en param
 * @param menu - le pointeur du menu à déssiner
 * @param scoreP1 - score du joueur1 (pour menu fin)
 * @param scoreP2 - score du joueur2 (pour menu fin)
 */
void DessinMenu(Menu* menu, GLuint text,int scoreP1, int scoreP2);

/**
 * @brief Ouvre le menu de debut
 * @param menu - le pointeur du menu à ouvrir
 * @param game - le jeu à lancer
 */
void CallMenuDemarrage(Menu* menu, Game* game);

/**
 * @brief Ouvre le menu de pause
 * @param menu - le pointeur du menu à ouvrir
 * @return false si l'utilsateur veut quitter, true sinon
 */
bool CallMenuPause(Menu* menu);

/**
 * @brief Ouvre le menu de fin
 * @param menu - le pointeur du menu à ouvrir
 * @param scoreP1 - score du joueur1
 * @param scoreP2 - score du joueur2
 * @return false si l'utilsateur veut quitter, true sinon
 */
bool CallMenuFin(Menu* menu, int scoreP1, int scoreP2);


/**
 * @brief Affiche les score des joueurs (pour le menu fin)
 * @param score1 - score du joueur1
 * @param score2 - score du joueur2
 * @return false si l'utilsateur veut quitter, true sinon
 */
void AfficheScoreMenu(int score1, int score2);


#endif
