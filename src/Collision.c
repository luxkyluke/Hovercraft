
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
//	if(!EstDansSDL(ballon->cercle->centre))
//		ResetBallon(ballon);
//		return false;
    if(CercleIsInWall(terrain, ballon->cercle, status)){
        //printf("Ballon cest un mur BOLOSSE\n");
        return true;
    }
    return false;
}

bool TouchedVehiculeCheckpooint(Vehicule* v, Checkpoint* checkpt){
    //if(v->player == player1)
//      printf("posCheckPt x %3.f, y %3.f / posVeh x %3.f, y %3.f\n",
//              checkpt->cercle->centre.x, checkpt->cercle->centre.y,
//              v->cercle->centre.x, v->cercle->centre.y);
    return(!checkpt->checked && IsCheckpoint(checkpt, v->cercle));
}

bool TouchedVehiculeTerrain(Vehicule* vehicule, Terrain* terrain, int* status){
//	if(!EstDansSDL(vehicule->cercle->centre) || !EstDansSDL(vehicule->facticeCercle->centre))
//			ResetVehicule(vehicule);
//			return false;
    if(CercleIsInWall(terrain, vehicule->cercle, status) ||
        CercleIsInWall(terrain, vehicule->facticeCercle, status)){
        //printf("xT = %3.f, yT = %3.f\n", vehicule->cercle->centre.x, vehicule->cercle->centre.y);
        //printf("xptCol =%f     yptCol=%f\n", terrain->pointCollision.x,  terrain->pointCollision.y);
        //printf("Vehicule player %d dans le mur pos x %3.f, y %3.f\n",
                //vehicule->player, vehicule->cercle->centre.x, vehicule->cercle->centre.y);
        return true;
    }
    return false;
}


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
                 /*tmpDirection = vehicule1->direction,*/
                 tmpVitesse =vehicule1->vitesse;

        vehicule1->acceleration = vehicule2->acceleration;
        vehicule1->vitesse= vehicule2->vitesse;
        //vehicule1->direction.x = vehicule2->direction.x;
        //vehicule1->direction.y = vehicule2->direction.y;
//        vehicule1->direction = vehicule2->direction;

        vehicule2->acceleration = tmpAcceleration;
        vehicule2->vitesse= tmpVitesse;
        //vehicule2->direction.x = tmpDirection.x;
        //vehicule2->direction.y = tmpDirection.y;
//        vehicule2->direction = tmpDirection;

    }
}

void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
    if(TouchedVehiculeBallon(ballon, vehicule) == true){
        if(vehicule->acceleration.x > 0.01 ||
            vehicule->acceleration.x < -0.01 ||
            vehicule->acceleration.y > 0.01 ||
            vehicule->acceleration.y < -0.01){
            ballon->cercleFactice->radius = ballon->cercle->radius * 2;
            //printf("%f\n", ballon->cercleFactice->radius);
        }
//        if(ballon->acceleration.x > 0.01 ||
//		   ballon->acceleration.x < -0.01 ||
//		   ballon->acceleration.y > 0.01 ||
//		   ballon->acceleration.y < -0.01){
//		   ballon->cercleFactice->radius = ballon->cercle->radius * 2;
//		   printf("%f\n", ballon->cercleFactice->radius);
//	   }
        //printf("%f     %f\n", vehicule->acceleration.x, vehicule->acceleration.y);
        ballon->direction = Vector(vehicule->cercle->centre, ballon->cercle->centre);
        ballon->acceleration = MultVector(ballon-> direction, 0.01);
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
    else
        return;
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
            //printf("collision\n");
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


//int StatusCollisionTerrain(Terrain* t){
//    int retour = 0;
//    /*if(t->pointCollision.x > 99  || t->pointCollision.x < -99
//            || t->pointCollision.x > 94  || t->pointCollision.x < -94) //collision verticale
//        retour += 1;
//    if(t->pointCollision.y > 49 || t->pointCollision.y < -49) //collision horizontale
//        retour +=2;*/
//    if(getCaraTerrain(t, t->pointCollision) == '|')
//        retour += 1;
//    if(getCaraTerrain(t, t->pointCollision) == '-')
//        retour +=2;
//    return retour;
//}
