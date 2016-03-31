#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "Checkpoint.h"

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

void MakeTerrain(GLuint text, char[] terrainTxt, Terrain* t);
bool IsWall(Terrain* t, Point2D* pos);
void FreeTerrain(Terrain* t);

#endif
