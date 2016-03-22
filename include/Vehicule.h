#ifndef VEHICULE_H_
#define VEHICULE_H_

#include "Point2D.h"
#include "Player.h"

typedef struct {
	GLuint texture;
	float hauteur;
	float largeur;
	float angle;
	Point2D* position;
	Vector2D* direction;
	Vector2D* vitesse;
	Vector2D* acceleration;
	
	Player player;
}Vehicule;

Vehicule* CreerVehicule(float px, float py, float hauteur, float largeur, GLuint text);
void DessinVehicule(Vehicule * v);
void UpdateAcceleration(Vehicule* h, int avance);
void UpdateVitesse(Vehicule* h);
void UpdatePosition(Vehicule* h);
void UpdateRotation(Vehicule* h, int tourne);
void UpdateVehicule(Vehicule* h, int avance, int tourne);
void DeplaceVehicule(Vehicule* h, int avance, int tourne);


#endif
