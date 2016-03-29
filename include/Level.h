#ifndef LEVEL_H_
#define LEVEL_H_

#include "Terrain.h"
#include "Vehicule.h"
#include "Ballon.h"

typedef struct {
	Terrain* terrain;
	Vehicule* vp1;
	Vehicule* vp2;
	Ballon* ballon;
	int scorePlayeur1;
	int scorePlayeur1;
}Level;

void MakeLevel(Terrain* t, Vehicule* vp1, Vehicule* vp2, Ballon* b, Level *l);

//verifie si il y a eu une colision entre les éléments
//Ajouter des scores si but etc...
bool CheckTouched();

void AddScoreP1(Level* l, int score);
void AddScoreP2(Level* l, int score);
void FreeLevel(Level* l);

#endif