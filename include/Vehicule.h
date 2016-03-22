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
	float vitesse;
	Player player;
}Vehicule;

Vehicule* CreerVehicule(Position* pos, float hauteur, float largeur, GLuint text);
void Accelerer(Vehicule *v, float acceleration);
void Decelerer(Vehicule *v, float deceleration);
void Glisser(Vector2D* direction);
void DessinVehicule(Vehicule * v);


#endif
