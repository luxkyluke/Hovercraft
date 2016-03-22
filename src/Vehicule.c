#include "Vehicule.h"
#include "Geometry.h"
#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

//Dessin de l'hovercraft
void dessinVehicule(Vehicule* v){
  dessinCarre(1,1,1,0.2);
  glPushMatrix();
    glTranslatef(0., 0.5,0.);
    dessinCercle(100, 1,1,0.2, 1);
  glPopMatrix();
}

Vehicule* CreerVehicule(float px, float py, Player p){
	Vehicule * h = malloc(sizeof(Vehicule));
	h-> position = PointXY(px, py);
	h-> angle = 0;
	h-> direction=VectorXY(0,1);
	h-> acceleration = VectorXY(0,0);
	h-> vitesse = VectorXY(0,0);
	h-> largeur = 0;
	h-> hauteur = 0;
	h->player = p;
	return h;
}


// PARTIE PHYSIQUE
void UpdateAcceleration(Vehicule* h, int avance){
	if(avance == 1){
		h-> acceleration = MultVector(h-> direction, 0.04);
	}
	else
		h-> acceleration = VectorXY(0,0.);
	return;
}

void UpdateVitesse(Vehicule* h){
		h-> vitesse = AddVectors(h-> vitesse, h-> acceleration);
		h-> vitesse = SubVectors(h-> vitesse, DivVector(h-> vitesse, 100.));
	return;
}

void UpdatePosition(Vehicule* h){
	h->position->x += h-> vitesse->x;
	h->position->y += h-> vitesse->y;
	return;
}
	
void UpdateRotation(Vehicule* h, int tourne){
	if(tourne != 0){
		h-> angle += h-> angle;
		h-> angle = h-> angle*tourne;//(car tourne prend 1 ou -1 ce qui permet d'échanger le sens!)
	}

	return;
}

void UpdateVehicule(Vehicule* h, int avance, int tourne){
	UpdateRotation(h, tourne);
	UpdateAcceleration(h, avance);
	UpdateVitesse(h);
	UpdatePosition(h);
	return;
}

    //rotate * h-> tourne (car tourne prend 1 ou -1 ce qui permet d'échanger le sens!)
  //else 
    //rotate nulle
