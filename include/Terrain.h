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


typedef struct {
	int largeur;
	int hauteur;
	GLuint texture;
	char ** terrain;
	char * terrainTxt;
	Checkpoint **checkpts;
	But* butP1;
	But* butP2;
}Terrain;

void MakeTerrain(GLuint text, FILE* fichTerrain, Terrain* t);
bool IsWall(Terrain* t, Point2D* pos);
void FreeTerrain(Terrain* t);

#endif
