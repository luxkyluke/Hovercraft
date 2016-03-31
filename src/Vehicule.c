/* A GARDER QUAND ON UTILISE OPENGL */
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
/* FIN DU A GARDER */

#include "Vehicule.h"
#include "Geometry.h"
#include <stdlib.h>
#include <SDL/SDL.h>

//Dessin de l'hovercraft
void DessinVehicule(Vehicule* v){
  dessinCarre(1,1,1,0.2);
  glPushMatrix();
    glTranslatef(0., 0.5,0.);
    dessinCercle(100, 1,1,0.2, 1);
    
  glPopMatrix();
}

void MakeVehicule(Point2D* pos, float hauteur, float largeur, GLuint text, Player p, Vehicule *h){
	h-> position = pos;
	h-> angle = 90;
	h-> direction = VectorXY(-1,0);
	h-> acceleration = VectorXY(0,0);
	h-> vitesse = VectorXY(0,0);
	h-> largeur = largeur;
	h-> hauteur = hauteur;
	h->player = p;
	h->texture = text;
}


// PARTIE PHYSIQUE
void UpdateAcceleration(Vehicule* h){
	if(h->avance == 1){
		h-> acceleration = MultVector(h-> direction, 0.04);
	}
	else
		h-> acceleration = VectorXY(0,0.);
	return;
}

void UpdateVitesse(Vehicule* h){
		h-> vitesse = AddVectors(h-> vitesse, h-> acceleration);
		h-> vitesse = SubVectors(h-> vitesse, DivVector(h-> vitesse, 50.));
	return;
}

void UpdatePosition(Vehicule* h){
	h->position->x += h-> vitesse->x;
	h->position->y += h-> vitesse->y;
	return;
}

void UpdateRotation(Vehicule* h){
	if(h->tourne != 0){
		h->angle += h->angle;
		h->angle = h->angle * h->tourne;//(car tourne prend 1 ou -1 ce qui permet d'échanger le sens!)
	}

	return;
}

void UpdateVehicule(Vehicule* h){
	UpdateRotation(h);
	UpdateAcceleration(h);
	UpdateVitesse(h);
	UpdatePosition(h);
	return;
}

void FreeVehicule(Vehicule* v){
	free(v->position);
	free(v->direction);
	free(v->vitesse);
	free(v->acceleration);
}
