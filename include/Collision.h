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

/**
 * @biref Verifie et traite la collision entre 2 cercles
 * @param c1, c2 - les cercles a vérifier
 * @return true si les cercles de touche, false sinon
 */
bool CollisionCercleCercle(Cercle*c1,Cercle*c2);

/**
 * @biref Verifie et traite la collision entre 2 vehicules
 * @param vehicule1, vehicule2 - les vehicules a vérifier
 *
 */
void CollisionVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2);

/**
 * @biref Verifie et traite la collision entre un vehicule et le terrain (checkpoints, murs)
 * @param v - le vehicule a vérifier
 * @param terrain - le Terrain à interroger
 * @param b - pointeur de bonus a modifier si le vehicule collisionne avec un checkpoint
 * @return true si le vehicule de touche quelque chose, false sinon
 */
bool CollissionVehiculeCheckpoints(Vehicule* v, Terrain* terrain, Bonus* b);

/**
 * @biref Verifie et traite la collision entre un ballon et un vehicule
 * @param ballon - le ballon a vérifier
 * @param vehicule - le vehicule a vérifier
 */
void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule);

/**
 * @biref Verifie et traite la collision entre un ballon et un vehicule
 * @param ballon - le ballon a vérifier
 * @param vehicule - le vehicule a vérifier
 */
void CollisionVehiculeTerrain(Vehicule* vehicule, Terrain* terrain);

/**
 * @biref Verifie et traite la collision entre un ballon et le terrain (murs)
 * @param ballon - le ballon a vérifier
 * @param terrain - le terrain a vérifier
 */
void CollisionBallonTerrain(Ballon *ballon, Terrain * terrain);

/**
 * @biref Verifie et traite la collision entre un ballon et les buts du terrain
 * @param ballon - le ballon a vérifier
 * @param terrain - le terrain possedant les but a verifier
 * @param buteur - pointeur a modifier pour indiquer le buteur si but il y a
 * @return true si il y a un but, false sinon
 */
bool CollisionBallonBut(Ballon* ballon, Terrain* terrain, Player* buteur);

//fonctions qui indiques si 2 élément sont entrer en contact ou non
bool TouchedVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2);
bool TouchedBallonBut(Ballon *ballon, But* but);
bool TouchedVehiculeCheckPoint(Vehicule* vehicule, Checkpoint* chkP);
bool TouchedVehiculeBallon(Ballon* ballon, Vehicule* vehicule);
bool TouchedVehiculeTerrain(Vehicule* vehicule, Terrain* terrain);
bool TouchedBallonTerrain(Ballon *ballon, Terrain * terrain);


#endif
