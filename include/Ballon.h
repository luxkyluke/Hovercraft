#ifndef BALLON_H_
#define BALLON_H_

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


#include "Point2D.h"
#include "Vector2D.h"
#include "Geometry.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    GLuint texture;
    Vector2D direction;
    Vector2D vitesse;
    Vector2D acceleration;
    Cercle* cercle;
}Ballon;

/**
 * @brief Cree un ballon avec le pointeur de ballon passé en paramètre
 * @param texture - la texture du ballon
 * @param pos - la position du checkpoint
 * @param r - le rayon du cercle du checkpoint
 * @param checkpt - le pointeur du checkpoint à créer
 * @param b - le bonus du checkpoint
 */
void MakeBallon(GLuint texture, Point2D pos, Ballon* ballon, float ballRadius);

/**
 * @brief met a jour la position du ballon
 * @param b - le ballon a met a jour
 */
void UpdatePositionBall(Ballon* b);

/**
 * @brief met a jour la vitesse du ballon
 * @param b - le ballon a met a jour
 */
void UpdateVitesseBall(Ballon* b);

/**
 * @brief met a jour les valeurs du ballon
 * @param b - le ballon a met a jour
 */
void UpdateBallon(Ballon* b);

/**
 * @brief Dessine le ballon passé en param
 * @param ball - le pointeur du ballon à déssiner
 */
void DessinBallon(Ballon* ball);

/**
 * @brief Réinitialise le ballon comme au début
 * @param b - le pointeur sur le ballon a reset
 */
void ResetBallon(Ballon* b);

/**
 * @brief Libere les pointeur du ballon
 * @param checkpt - le pointeur du ballon à liberer
 */
void FreeBallon(Ballon* v);

#endif
