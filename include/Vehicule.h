#ifndef VEHICULE_H_
#define VEHICULE_H_

#include "Point2D.h"
#include "Player.h"
#include "Vector2D.h"
#include "Geometry.h"
#include "bool.h"
#include "Bonus.h"
#include <Math.h>
#define PI 3.14

/* A GARDER QUAND ON UTILISE OPENGL */
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

/* FIN DU A GARDER */

typedef struct {
	GLuint texture;
	float hauteur;
	float largeur;
	Cercle* cercle;
    Cercle* facticeCercle;
	float angle;
	Point2D position;
	Vector2D direction;
	Vector2D vitesse;
	Vector2D acceleration;
	int avance, tourne;
	Player player;
    int bonus;
    int timerBonus;
}Vehicule;

typedef enum _bonus {none = 0, boost = 1, freeze = 2} bonus;

void MakeVehicule(Point2D pos, float hauteur, float largeur, GLuint text, Player p, Vehicule* v);
void DessinVehicule(Vehicule * v);
void UpdateAcceleration(Vehicule* h);
void UpdateVitesse(Vehicule* h);
void UpdatePosition(Vehicule* h);
void UpdateRotation(Vehicule* h);
void UpdateVehicule(Vehicule* h);
void FreeVehicule(Vehicule *h);
void UpdateCercle(Vehicule *v);
void ResetVehicule(Vehicule* v, Point2D pos, Player p);
void BoostVehicule(Vehicule* v);
void FreezeVehicule(Vehicule* v);
void CheckBoost(Vehicule* v);
//bool IsTouchingVehicule(Vehicule *v, Point2D pos);

#endif
