
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
#include "Vehicule.h"
#include <stdlib.h>
#include <SDL/SDL.h>

#define BONUS_RESET 15000

bool TouchedVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2){
    if (CollisionCercleCercle(vehicule1->cercle, vehicule2->cercle) ||
        CollisionCercleCercle(vehicule1->facticeCercle, vehicule2->cercle) ||
        CollisionCercleCercle(vehicule1->cercle, vehicule2->facticeCercle) ||
        CollisionCercleCercle(vehicule1->facticeCercle, vehicule2->facticeCercle)) {
        return true;
    }

    return false;
}


bool TouchedVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
    if(Point2DIsEgual(ballon->cercle->centre, vehicule->position)
            || CollisionCercleCercle(vehicule->cercle, ballon->cercle)
                || CollisionCercleCercle(vehicule->facticeCercle, ballon->cercle)) {
        return true;
    }
    return false;
}

bool TouchedBallonTerrain(Ballon* ballon, Terrain* terrain, int* status){
    if(CercleIsInWall(terrain, ballon->cercle, status)){
        return true;
    }
    return false;
}

bool TouchedVehiculeCheckpooint(Vehicule* v, Checkpoint* checkpt){
    return(!checkpt->checked && IsCheckpoint(checkpt, v->cercle));
}

bool TouchedVehiculeTerrain(Vehicule* vehicule, Terrain* terrain, int* status){
    if(CercleIsInWall(terrain, vehicule->cercle, status) ||
        CercleIsInWall(terrain, vehicule->facticeCercle, status)){
        return true;
    }
    return false;
}


/*fonction qui calcule les consequences des colisions*/

void CollisionVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2){
    if(TouchedVehiculeVehicule(vehicule1, vehicule2) == true){
        Vector2D tmpAcceleration = vehicule1->acceleration,
                 tmpVitesse =vehicule1->vitesse;

        vehicule1->acceleration = vehicule2->acceleration;
        vehicule1->vitesse= vehicule2->vitesse;

        vehicule2->acceleration = tmpAcceleration;
        vehicule2->vitesse= tmpVitesse;
    }
}

void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
    if(TouchedVehiculeBallon(ballon, vehicule) == true){
        if(vehicule->acceleration.x < 0.01 
            || vehicule->acceleration.x > -0.01 
                || vehicule->acceleration.y < 0.01 
                    || vehicule->acceleration.y > -0.01){
            ballon->direction = Vector(vehicule->cercle->centre, ballon->cercle->centre);
            ballon->acceleration = MultVector(ballon-> direction, 0.01);
        }
        else{
            ballon->direction = Vector(vehicule->cercle->centre, ballon->cercle->centre);
            ballon->acceleration = MultVector(ballon-> direction, 0.1);
        }
    }
    else
        ballon-> acceleration = VectorXY(0,0.);
    UpdateBallon(ballon);
}

void CollisionBallonTerrain(Ballon *ballon, Terrain * terrain){
	int status;
    if(TouchedBallonTerrain(ballon, terrain, &status) == true){
        if(status == 1){
            ballon->vitesse.x *= -1;
            return;
        }
        if(status == 2){
            ballon->vitesse.y *= -1;
            return;
        }

        if(status == 3){
            ballon->vitesse.y *= -1;
            ballon->vitesse.x *= -1;
            return;
        }
    }
}

bool CollisionBallonBut(Ballon* ballon, Terrain* terrain, Player* buteur) {
    if(BallIsInGoal(terrain->butP1, ballon)){
        *buteur = player1;
        return true;
    }
    if(BallIsInGoal(terrain->butP2, ballon)){
        *buteur = player2;
        return true;
    }
    return false;
}

bool CollissionVehiculeCheckpoints(Vehicule* v, Terrain* terrain, Bonus* b){
    int i;
    for (i=0; i<terrain->nbCheckpts; ++i){
        if(TouchedVehiculeCheckpooint(v, terrain->checkpts[i])){
            *b = terrain->checkpts[i]->type;
            return true;
        }
    }
    return false;

}

void CollisionVehiculeTerrain(Vehicule* vehicule, Terrain* terrain){
	int status;
    if (TouchedVehiculeTerrain(vehicule, terrain, &status) == true) {
        if (status == 1) {
            vehicule->vitesse.x *= -1;
            return;
        }
        if (status == 2) {
            vehicule->vitesse.y *= -1;
            return;
        }

        if (status == 3) {
            vehicule->vitesse.y *= -1;
            vehicule->vitesse.x *= -1;
            return;
        }
    }
    else
        return ;
}




/*fonctions qui indiques si 2 élément sont entrer en contact ou non */

bool CollisionCercleCercle(Cercle* c1, Cercle* c2) {

    Vector2D distanceCentre = Vector(c1->centre, c2->centre);
    float tailleRayons = c1->radiusCarre + c2->radiusCarre;
    if(SqrNorm(distanceCentre) <= tailleRayons*3.){
        return true;
    }
    return false;

}

