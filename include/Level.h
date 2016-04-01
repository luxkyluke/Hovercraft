#ifndef LEVEL_H_
#define LEVEL_H_

#include "Terrain.h"
#include "Vehicule.h"
#include "Ballon.h"
#include "Level.h"
#include "Point2D.h"

typedef struct {
	Terrain* terrain;
	Vehicule* vp1;
	Vehicule* vp2;
	Ballon* ballon;
	int scoreP1;
	int scoreP2;
    int nbLevel;
}Level;

void MakeLevel(char* nameFichTerrain,  char* pathTextureTerrain, char* pathTextureVp1, char* pathTextureVp2, Level *l);


//verifie si il y a eu une colision entre les éléments
//Ajouter des scores si but etc...
bool CheckTouched();

void AddScoreP1(Level* l, int score);
void AddScoreP2(Level* l, int score);
void FreeLevel(Level* l);

#endif
