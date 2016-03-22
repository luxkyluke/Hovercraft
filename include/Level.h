#ifndef LEVEL_H_
#define LEVEL_H_

#include "Terrain.h"
#include "Vehicule.h"
#include "Ballon.h"

typedef struct {
	Terrain* terrain;
	Vehicule* vehiculePlayeur1;
	Vehicule* vahiculePlayeur2;
	Ballon* ballon;
	int scorePlayeur1;
	int scorePlayeur1;
}Level;

bool checkTouched();

#endif