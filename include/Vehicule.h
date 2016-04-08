#ifndef VEHICULE_H_
#define VEHICULE_H_

#include "Point2D.h"
#include "Player.h"
#include "Vector2D.h"
#include "Geometry.h"
#include "bool.h"

#include <math.h>
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
	Cercle* cercleFactis;
	float angle;
	Point2D position;
	Vector2D direction;
	Vector2D vitesse;
	Vector2D acceleration;
	int avance, tourne;
	Player player;
}Vehicule;

void MakeVehicule(Point2D pos, float hauteur, float largeur, GLuint text, Player p, Vehicule* v);
void DessinVehicule(Vehicule * v);
void UpdateAcceleration(Vehicule* h);
void UpdateVitesse(Vehicule* h);
void UpdatePosition(Vehicule* h);
void UpdateRotation(Vehicule* h);
void UpdateVehicule(Vehicule* h);
void FreeVehicule(Vehicule *h);
bool IsTouchingVehicule(Vehicule *v, Point2D pos);

#endif
