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
#include "sdl_tools.h"
#include <SDL/SDL.h>

#define DEFAULT_VEHICULE2_TEXTURE_PATH "images/vp.png"
#define DEFAULT_VEHICULE1_TEXTURE_PATH "images/vpbis.png"

#define BONUS_DURATION 5000


//Dessin de l'hovercraft
void DessinVehicule(Vehicule* v) {
    glPushMatrix();

    	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, v->texture);
        glTexEnvf(GL_TEXTURE_2D,GL_TEXTURE_ENV_MODE,GL_MODULATE);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

        if (v->bonus == boost) {
        	glColor4f(1.,0.,0.,1.);
        } else if(v->bonus == freeze) {
        	glColor4f(0.01,0.66,0.98,1.);
        } else {
        	glColor4f(1.,1.,1.,1.);
        }

        glTranslatef(v->position.x, v->position.y, 0);
        glRotatef(v->angle, 0., 0., 1.);
        glScalef(v->largeur, v->hauteur, 0.);

        glBegin(GL_QUADS);
            glTexCoord2f(1,0); glVertex2f(1*0.5 , 2*.5);
            glTexCoord2f(1,1); glVertex2f(1*0.5 , -1*.5);
            glTexCoord2f(0,1); glVertex2f(-1*0.5, -1*.5);
            glTexCoord2f(0,0); glVertex2f(-1*0.5, 2*.5);
        glEnd();

        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
        glDisable(GL_TEXTURE_2D);


    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POINTS);
    glPointSize(18);
    glColor3f(1, 0, 0);
    glVertex2d(v->cercle->centre.x, v->cercle->centre.y);
    glEnd();
    glPopMatrix();
}

void MakeVehicule(Point2D pos, float hauteur, float largeur, Player p, Vehicule *h) {
    if (!h) {
        printf("Impossible de créer le véhicule, pointeur non alloué\n");
        return;
    }

    if(p==1)
    	h->texture = loadImage(DEFAULT_VEHICULE1_TEXTURE_PATH);
    else
    	h->texture = loadImage(DEFAULT_VEHICULE2_TEXTURE_PATH);

    h->largeur = largeur;
    h->hauteur = hauteur;
    h->defaultPosition = pos;
    h->player = p;
    ResetVehicule(h);
    Point2D defaultPosC = AddPoints(pos, PointXY(0.5 * hauteur, 0.5 * hauteur));
    h->cercle = (Cercle*) malloc(sizeof(Cercle));
    MakeCercle(h->cercle, defaultPosC, 0.5 * largeur);
    h->facticeCercle = (Cercle*) malloc(sizeof(Cercle));
    MakeCercle(h->facticeCercle, h->position, 0.5 * largeur);

//  h->bonus = none;
//  h->timerBonus = 0;
}

// PARTIE PHYSIQUE
void UpdateAcceleration(Vehicule* h) {
    if (h->avance == 1) {
        if (h->bonus == boost){
            h->acceleration = MultVector(h->direction, 0.025);
        } else {
            h->acceleration = MultVector(h->direction, 0.015);
        }
    } else
        h->acceleration = VectorXY(0, 0.);
    return;
}

void UpdateVitesse(Vehicule* h) {
    h->vitesse = AddVectors(h->vitesse, h->acceleration);
    h->vitesse = SubVectors(h->vitesse, DivVector(h->vitesse, 50.));
    return;
}

void UpdatePosition(Vehicule* h) {
    h->position.x += h->vitesse.x;
    h->position.y += h->vitesse.y;
//  if(h->player == player1)
//      printf("x %d, y %d\n", (int)h->position.x, (int)h->position.y);
    return;
}

void UpdateRotation(Vehicule* h) {
    if (h->tourne != 0) {
        h->angle = h->angle - (h->tourne * 2);
        h->direction.x = -sin((PI * h->angle) / 180);
        h->direction.y = cos((PI * h->angle) / 180);
    }
    return;
}

void UpdateVehicule(Vehicule* h) {
    UpdateRotation(h);
    UpdateAcceleration(h);
    UpdateVitesse(h);
    UpdatePosition(h);
    UpdateCercle(h);
    return;
}

void FreeVehicule(Vehicule* v) {
    free(v->cercle);
    v->cercle = NULL;
}

void ResetVehicule(Vehicule* h) {
    Vector2D defaultDir;
    h->position = h->defaultPosition;
    if (h->player == player1) {
        h->angle = 90;
        defaultDir = VectorXY(-1, 0);
    } else {
        h->angle = -90;
        defaultDir = VectorXY(1, 0);
    }
    Vector2D defaultAcc = VectorXY(0, 0);
    Vector2D defaultVit = VectorXY(0, 0);
//  Point2D defaultPosC = AddPoints(h->position, PointXY(0.5 * h->hauteur, 0.5 * h->hauteur));
//  h->cercle = (Cercle*) malloc(sizeof(Cercle));
//  MakeCercle(h->cercle, defaultPosC, 0.5 * h->largeur);
//  h->facticeCercle = (Cercle*) malloc(sizeof(Cercle));
//  MakeCercle(h->facticeCercle, h->position, 0.5 * h->largeur);
    h->direction = defaultDir;
    h->acceleration = defaultAcc;
    h->vitesse = defaultVit;
    h->bonus = none;
    h->tourne = 0;
    h->timerBonus = 0;//SDL_GetTicks();
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
    v->cercle->centre = PointPlusVector(v->position,
            MultVector(Normalize(v->direction), v->largeur / 2.));
    v->facticeCercle->centre = v->position;
}

void BoostVehicule(Vehicule* v) {
    v->acceleration = MultVector(v->direction, 0.015);
}

void FreezeVehicule(Vehicule* v) {
    v->avance = 0;
    v->acceleration = VectorXY(0, 0);
    v->tourne = 0;
}


void CheckBoost(Vehicule* v) {
    if (v->bonus == boost) {
        if (!IsInBonus(v)) {
            printf("Dépassé de 4s.\n");
            v->bonus = none;
            v->timerBonus = SDL_GetTicks();
        }
    }
}


void CheckFreeze(Vehicule* v){
    if (v->bonus == freeze) {
        if (!IsInBonus(v)) {
            printf("D�pass� de 4s.\n");
            v->bonus = none;
            v->timerBonus = SDL_GetTicks();
        } else {
            FreezeVehicule(v);
        }
    }
}

bool IsInBonus(Vehicule* v){
    return v->bonus != none && SDL_GetTicks() - v->timerBonus <= BONUS_DURATION;
}
