#ifndef VEHICUL_H_
#define VEHICUL_H_

#include "position.h"

typedef struct {
	GLuint texture;
	float hauteur;
	float largeur;
	float angle;
	Position* position;
	float vitesse;
}Vehicul;

Vehicul* CreerVehicul(Position* pos, float hauteur, float largeur, GLuint text);

void Accelerer(Vehicul *v, float acceleration);

void Decelerer(Vehicul *v, float deceleration);

void Glisser(Vector2D* direction);

void DessinVehicul(Vehicul * v);

#endif
