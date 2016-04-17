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
  glPushMatrix();
//  		glEnable(GL_TEXTURE_2D);
	    //float test = (float)windowWidth - (float)windowWidth/2;
	    //printf("hrllo %f \n", 100.*(float)windowHeight/(float)windowWidth);
	    //glColor3f(255, 255, 255);
//	    glBindTexture(GL_TEXTURE_2D, v->texture);
	    //printf("texture vp %d\n", v->texture);
	   	glTranslatef(v->position.x, v->position.y, 0);
  	  	glRotatef(v->angle,0.,0.,1.);
  	  	glScalef(v->largeur, v->hauteur, 0.);
	  	dessinCarre(1,1,1,0.2);
		glPushMatrix();
		  glTranslatef(0., 0.5,0.);
		  dessinCercle(100, 1,1,0.2, 1);
		glPopMatrix();

//		glBindTexture(GL_TEXTURE_2D, 0);
//	    glDisable(GL_TEXTURE_2D);
  glPopMatrix();

  glPushMatrix();
      glBegin(GL_POINTS);
          glPointSize(18);
          glColor3f(1,0,0);
          glVertex2d(v->cercle->centre.x, v->cercle->centre.y);
      glEnd();
  glPopMatrix();
}

void MakeVehicule(Point2D pos, float hauteur, float largeur, GLuint text, Player p, Vehicule *h){
	if(!h) {
		printf("Impossible de créer le véhicule, pointeur non alloué\n");
		return;
	}
	ResetVehicule(h, pos, p);
	Point2D defaultPosC = AddPoints(pos, PointXY(0.5*hauteur, 0.5*hauteur));
	h-> largeur = largeur;
	h-> hauteur = hauteur;
	h->cercle = (Cercle*) malloc(sizeof(Cercle));
	MakeCercle(h->cercle, defaultPosC, 0.5*largeur);
    h->facticeCercle = (Cercle*) malloc(sizeof(Cercle));
    MakeCercle(h->facticeCercle, h->position, 0.5*largeur);
	h->player = p;
	h->texture = text;
    h->tourne = 0;
}


// PARTIE PHYSIQUE
void UpdateAcceleration(Vehicule* h){
	if(h->avance == 1){
		h-> acceleration = MultVector(h-> direction, 0.015);
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
	h->position.x += h-> vitesse.x;
	h->position.y += h-> vitesse.y;
	return;
}

void UpdateRotation(Vehicule* h){
    if(h->tourne != 0){
        h->angle = h->angle - (h->tourne * 2);
        h->direction.x = -sin((PI*h-> angle)/180);
        h->direction.y = cos((PI*h-> angle)/180);
    }
	return;
}

void UpdateVehicule(Vehicule* h){
    UpdateRotation(h);
	UpdateAcceleration(h);
	UpdateVitesse(h);
	UpdatePosition(h);
	UpdateCercle(h);
	return;
}

void FreeVehicule(Vehicule* v){
	free(v->cercle);
	v->cercle = NULL;
}

void ResetVehicule(Vehicule* h, Point2D pos, Player p){
	Vector2D defaultDir;
	h-> position = pos;
	if(p == player1){
		h-> angle = 90;
		defaultDir = VectorXY(-1,0);
	}
	else{
		h-> angle = -90;
		defaultDir = VectorXY(1,0);
	}
	Vector2D defaultAcc = VectorXY(0,0);
	Vector2D defaultVit = VectorXY(0,0);
	h-> direction = defaultDir;
	h-> acceleration = defaultAcc;
	h-> vitesse = defaultVit;
}

/*
bool IsTouchingVehicule(Vehicule *v, Point2D pos){
  Point2D posV = v->position;
  float largeur = v->largeur;
  float hauteur = v->hauteur;
  float xMax = posV.x+largeur/2.;
  float xMin = posV.x-largeur/2.;
  float yMax = posV.y+hauteur/2.;
  float yMin = posV.y-hauteur/2.;

  if(pos.x <= xMax && pos.x >= xMin && pos.y <= yMax && pos.y >= yMin){
    printf("TRUE\n");
    return true;
  }

  return false;
}
*/
void UpdateCercle(Vehicule*v) {
    v->cercle->centre = PointPlusVector(v->position, MultVector(Normalize(v->direction),v->largeur/2.));
    v->facticeCercle->centre = v->position;
}

