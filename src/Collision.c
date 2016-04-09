
/* A GARDER QUAND ON UTILISE OPENGL */
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif
/* FIN DU A GARDER */

#include "Collision.h"
#include <stdlib.h>
#include <SDL/SDL.h>


/*fonction qui calcule les consequences des colisions*/

void CollisionVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2){
    if(TouchedVehiculeVehicule(vehicule1, vehicule2) == true){
        //printf("COLLISION VEHICULES\n");
        //vehicule1-> direction = MultVector(vehicule1->direction, -1);
        //vehicule2-> direction = -MultVector(vehicule2-> direction, 10);

//        Vector2D newVector = Vector(vehicule1->cercle->centre, vehicule2->cercle->centre);
//        float dp = Norm(newVector);
//        newVector.x = newVector.x/dp; //idem à Normalize(newVecotor);
//        newVector.y = newVector.y/dp;

//       Vector2D compVitesse = SubVectors(vehicule1->vitesse, vehicule2->vitesse);
//        double dvx = vehicule1->vitesse.x - vehicule2->vitesse.x;
//        double dvy = vehicule1->vitesse.y - vehicule2->vitesse.y;
//        double scalaire = DotProduct(newVector, compVitesse);
//        compVitesse.x = newVector.x*scalaire;
//        compVitesse.y = newVector.y*scalaire;

//        vehicule1->vitesse = SubVectors(vehicule1->vitesse, compVitesse);
//        vehicule2->vitesse = AddVectors(vehicule2->vitesse, compVitesse);
        Vector2D tmpAcceleration = vehicule1->acceleration,
                 tmpDirection = vehicule1->direction,
                 tmpVitesse =vehicule1->vitesse;

        vehicule1->acceleration = vehicule2->acceleration;
//        vehicule1->direction = vehicule2->direction;
        vehicule1->vitesse= vehicule2->vitesse;

        vehicule1->direction.x *= vehicule2->direction.x;
        vehicule1->direction.y *= vehicule2->direction.y;

//        vehicule2->direction = tmpDirection;
        vehicule2->acceleration = tmpAcceleration;

        vehicule2->direction.x *= tmpDirection.x;
        vehicule2->direction.y *= tmpDirection.y;

        vehicule2->vitesse= tmpVitesse;
        UpdateVehicule(vehicule1);
        UpdateVehicule(vehicule2);
    }
}

void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
    if(TouchedVehiculeBallon(ballon, vehicule) == true){
        ballon->direction = MultVector(vehicule->direction, ballon->cercle->radius);
        ballon->acceleration = MultVector(ballon-> direction, 0.01);
    }
    else
        ballon-> acceleration = VectorXY(0,0.);
    UpdateBallon(ballon);
}

void CollisionBallonTerrain(Ballon *ballon, Terrain * terrain){
    if(TouchedBallonTerrain(ballon, terrain)){
        //ballon->cercle->centre + ballon->cercle->radius
    }
}
/*if(xCercle + 0.5 + dx > 10. || xCercle - 0.5 + dx < -10.)
        dx *=-1;
      if(yCercle + 0.5 + dy > 10*((float)windowHeight/(float)windowWidth) || yCercle - 0.5 + dy < -10*((float)windowHeight/(float)windowWidth))
        dy *=-1;
      xCercle += dx;
      yCercle += dy;*/


/*fonctions qui indiques si 2 élément sont entrer en contact ou non */

bool CollisionCercleCercle(Cercle* c1, Cercle* c2) {

    Vector2D distanceCentre = Vector(c1->centre, c2->centre);
    float tailleRayons = c1->radiusCarre + c2->radiusCarre;
    if(SqrNorm(distanceCentre) <= tailleRayons*2.2){
        printf("TRUEDUCUL\n");
        return true;
    }
    return false;

}

bool TouchedVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2){
    Point2D posV = vehicule1->position;
    float largeur = vehicule1->largeur;
    float hauteur = vehicule1->hauteur;
    float xMax = posV.x+largeur/2;
    float xMin = posV.x-largeur/2;
    float yMax = posV.y+hauteur/2;
    float yMin = posV.y-hauteur/2;

    Point2D pos11 = PointXY(xMin, yMax);
    Point2D pos12 = PointXY(xMax, yMax);
    Point2D pos13 = PointXY(xMax, yMin);
    Point2D pos14 = PointXY(xMin, yMin);

    if (IsTouchingVehicule(vehicule2, pos11) ||
                IsTouchingVehicule(vehicule2, pos12) ||
                    IsTouchingVehicule(vehicule2, pos13) ||
                        IsTouchingVehicule(vehicule2, pos14))
        return true;

    if (CollisionCercleCercle(vehicule1->cercle, vehicule2->cercle) ||
        CollisionCercleCercle(vehicule1->facticeCercle, vehicule2->cercle) ||
        CollisionCercleCercle(vehicule1->cercle, vehicule2->facticeCercle) ||
        CollisionCercleCercle(vehicule1->facticeCercle, vehicule2->facticeCercle)) {
        return true;
    }

    return false;
}


bool TouchedVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
    if(CollisionCercleCercle(vehicule->cercle, ballon->cercle) ||
       CollisionCercleCercle(vehicule->facticeCercle, ballon->cercle)) {
        return true;
    }

    return false;
}

bool TouchedVehiculeCheckPoint(Vehicule* vehicule, Checkpoint* chkP){
    if(CollisionCercleCercle(vehicule->cercle, chkP->cercle))
        return true;
    return false;
}


bool TouchedBallonTerrain(Ballon *ballon, Terrain * terrain){
    if(IsWall(terrain, ballon->cercle->centre) == true){
        return true;
}
    return false;
}


