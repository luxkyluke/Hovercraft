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
	Checkpoint **checkpts;
	But* butP1;
	But* butP2;
}Terrain;

void MakeTerrain(GLuint text, FILE* fichTerrain, Terrain* t);
void DessinTerrain(Terrain* t, GLuint texture, unsigned int windowWidth, unsigned int windowHeight);
bool IsWall(Terrain* t, Point2D* pos);
void FreeTerrain(Terrain* t);
GLuint loadImage(char* image);

#endif
