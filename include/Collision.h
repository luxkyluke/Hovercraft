#ifndef COLLISION_H_
#define COLLISION_H_

#include "Ballon.h"
#include "But.h"
#include "Vehicule.h"
#include "CheckPoint.h"
#include "Terrain.h"

//fonction qui calcule les consequences des colisions
void CollisionVehiculeCheckPoint(Vehicule* vehicule, CheckPoint* chkP);
void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule);
void CollisionVehiculeTerrain(Vehicule* vehicule, Terrain* terrain);
void CollisionBallonTerrain(Ballon *ballon, Terrain * terrain);

//fonctions qui indiques si 2 élément sont entrer en contact ou non
bool TouchedBallonBut(Ballon *ballon, But* but);
bool TouchedVehiculeCheckPoint(Vehicule* vehicule, CheckPoint* chkP);
bool TouchedVehiculeBallon(Ballon* ballon, Vehicule* vehicule);
bool TouchedVehiculeTerrain(Vehicule* vehicule, Terrain* terrain);
bool TouchedBallonTerrain(Ballon *ballon, Terrain * terrain);


#endif