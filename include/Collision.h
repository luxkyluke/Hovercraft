#ifndef COLLISION_H_
#define COLLISION_H_

#include "Ballon.h"
#include "But.h"
#include "Vehicule.h"
#include "CheckPoint.h"
#include "Terrain.h"


void CollisionVehiculeCheckPoint(Vehicule* vehicule, CheckPoint* chkP);
void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule);
void CollisionVehiculeTerrain(Vehicule* vehicule, Terrain* terrain);
void CollisionBallonTerrain(Ballon *ballon, Terrain * terrain);

bool TouchedBallonBut(Ballon *ballon, But* but);
bool TouchedVehiculeCheckPoint(Vehicule* vehicule, CheckPoint* chkP);
bool TouchedVehiculeBallon(Ballon* ballon, Vehicule* vehicule);
bool TouchedVehiculeTerrain(Vehicule* vehicule, Terrain* terrain);
bool TouchedBallonTerrain(Ballon *ballon, Terrain * terrain);


#endif