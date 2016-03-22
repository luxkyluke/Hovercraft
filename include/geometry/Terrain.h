#ifndef TERRAIN_H_
#define TERRAIN_H_

typedef struct {
	int largeur;
	int hauteur;
	GLuint texture;
	char * terrainTxt;
}Terrain;

void MakeTerrain(int l, int h, GLuint text, char[] terrainTxt);


#endif