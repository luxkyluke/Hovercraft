#ifndef TERRAIN_H_
#define TERRAIN_H_


#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "Checkpoint.h"
#include "But.h"
#include "Point2D.h"
#include <stdio.h>
#include <SDL/SDL_image.h>


typedef struct {
	int largeur;
	int hauteur;
	GLuint texture;
	char ** terrain;
	Point2D pointCollision;	
	Checkpoint **checkpts;
	int nbCheckpts;
	But* butP1;
	But* butP2;
}Terrain;

/**
 * @brief Creer un Terrain avec le pointeur de terrain passé en paramètre
 * @param text - la texture du terrain
 * @param fichTerrain - fichier txt contenant le terrain
 * @param t - le pointeur du terrain à créer
 * @param vp1_pos - pointeur de la position du vehicule 1 determiné par le fichier txt
 * @param vp2_pos - pointeur de la position du vehicule 2 determiné par le fichier txt
 */
void MakeTerrain(GLuint text, FILE* fichTerrain, Terrain* t, Point2D* vp1_pos, Point2D* vp2_pos);

/**
 * @brief Dessine le Terrain passé en param
 * @param t - le pointeur du Terrain à déssiner
 */
void DessinTerrain(Terrain* t);

/**
 * @brief Determine si le position passer en parametre représente un mur sur le terrain ou non
 * si oui elle defini quelle type de mur par donnant une valeur au pointeur status
 * @param t - Terrain a interroger
 * @param pos - Position a verifier
 * @param status - Valeur modifié position est un mur et indique si le mur est vertical ou horizontal
 * @return true si la position est dans un mur, false sinon
 */
bool IsWall(Terrain* t, Point2D pos, int* status);

/**
 * @brief Verifie si un cercle rentre en collision avec un mur du Terrain
 * @param t- le Terrain a interroger
 * @param c- le cercle a vérifier
 * @param status - Valeur modifié position est un mur et indique si le mur est vertical ou horizontal
 * @return true si le cercle rentre dans un mur, false sinon
 */
bool CercleIsInWall(Terrain* t, Cercle* c, int* status);

/**
 * @brief Libere les pointeur du Terrain
 * @param t- le pointeur du terrain à liberer
 */
void FreeTerrain(Terrain* t);

/**
 * @brief Réinitialise le terrain comme au début
 * @param t - le pointeur sur le terrain a reset
 */
void ResetTerrain(Terrain* t);


#endif
