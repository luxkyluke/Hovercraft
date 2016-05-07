#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include "Point2D.h"
#include "bool.h"
#include "Geometry.h"
#include <stdlib.h>
#include "Bonus.h"

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


#include <SDL/SDL.h>

typedef	struct {
	Cercle* cercle;
	bool checked;
    Bonus type; 	//type de bonus du checkpoint
    int timerReset;	//durée avant réapparition du checkpoint
}Checkpoint;

/**
 * @brief Cree un checkpoint avec le pointeur de checkpoint passé en paramètre
 * @param pos - la position du checkpoint
 * @param r - le rayon du cercle du checkpoint
 * @param checkpt - le pointeur du checkpoint à créer
 * @param b - le bonus du checkpoint
 */
void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt, Bonus b);

/**
 * @brief vérifie la colision entre un checkpoint et un cercle
 * @param chekpt- le checkpoint a interrogé
 * @param c - cle cercle a verifier
 * @retunr true si il le cerlce touche le checkpoint, false sinon
 */
bool IsCheckpoint(Checkpoint* checkpt, Cercle* c);

/**
 * @brief Libere les pointeur du Checkpoint
 * @param checkpt - le pointeur du checkpoint à liberer
 */
void FreeCheckpoint(Checkpoint* checkpt);

/**
 * @brief duplique le checkpoint passé en param
 * @param checkpt- le checkpoint a dupliqué
 * @return la copie du checkpoint
 */
Checkpoint* CopyCheckpt(Checkpoint* checkpt);

/**
 * @brief Dessine le Checkpoint passé en param
 * @param checkpt - le pointeur du checkpoint à déssiner
 */
void DessinCheckpoint(Checkpoint* checkpt);

/**
 * @brief Réinitialise le checkpoint comme au début
 * @param checkpt - le pointeur sur le checkpoint a reset
 */
void ResetCheckpoint(Checkpoint* checkpt);

#endif
