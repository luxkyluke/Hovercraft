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

typedef struct {
    GLuint texture;
    Vector2D direction;
    Vector2D vitesse;
    Vector2D acceleration;
    Cercle* cercle;
}Ballon;


void MakeBallon(GLuint texture, Point2D pos, Ballon* ballon, float ballRadius);
void UpdatePositionBall(Ballon* b);
void UpdateVitesseBall(Ballon* b);
void UpdateBallon(Ballon* b);
void DessinBallon(Ballon* ball);
float getXTerrain(float x);
float getYTerrain(float y);
float getXSDL(float x);
float getYSDL(float y);

#endif
