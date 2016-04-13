#ifndef COLLISION_H_
#define COLLISION_H_


#include "bool.h"
#include "Ballon.h"
#include "But.h"
#include "Checkpoint.h"
#include "Terrain.h"
#include "Vehicule.h"
#include "Geometry.h"
#include "Vector2D.h"

//fonction qui calcule les consequences des colisions
bool CollisionCercleCercle(Cercle*c1,Cercle*c2); 						//DONE
void CollisionVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2); //AR
void CollisionVehiculeCheckPoint(Vehicule* vehicule, Checkpoint* chkP);	//
void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule);		//DONE
void CollisionVehiculeTerrain(Vehicule* vehicule, Terrain* terrain);	//DONE
void CollisionBallonTerrain(Ballon *ballon, Terrain * terrain);			//DONE

//fonctions qui indiques si 2 élément sont entrer en contact ou non
bool TouchedVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2); //AR
bool TouchedBallonBut(Ballon *ballon, But* but);						//
bool TouchedVehiculeCheckPoint(Vehicule* vehicule, Checkpoint* chkP); 	//AR
bool TouchedVehiculeBallon(Ballon* ballon, Vehicule* vehicule); 		//DONE
bool TouchedVehiculeTerrain(Vehicule* vehicule, Terrain* terrain); 		//DONE
bool TouchedBallonTerrain(Ballon *ballon, Terrain * terrain); 			//DONE
int StatusCollisionTerrain(Terrain* t);




#endif
