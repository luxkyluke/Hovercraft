#ifndef BALLON_H_
#define BALLON_H_

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>

#include "Point2D.h"

typedef struct {
	GLuint texture;
	float angle;
	Point2D position;
	float vitesse;
}Ballon;

void MakeBallon(GLuint texture, Point2D pos, Ballon* ballon);
void DeplacerBallon(float angle, float acceleration);
void UpdateBallon(Ballon* h);
void DessinBallon(Ballon* ball);

#endif
