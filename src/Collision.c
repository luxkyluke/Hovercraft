
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

        Vector2D newVector = Vector(vehicule1->cercle->centre, vehicule2->cercle->centre);
        float dp = Norm(newVector);
        newVector.x = newVector.x/dp; //idem à Normalize(newVecotor);
        newVector.y = newVector.y/dp;

       Vector2D compVitesse = SubVectors(vehicule1->vitesse, vehicule2->vitesse);
//        double dvx = vehicule1->vitesse.x - vehicule2->vitesse.x;
//        double dvy = vehicule1->vitesse.y - vehicule2->vitesse.y;
        double scalaire = DotProduct(newVector, compVitesse);
        compVitesse.x = newVector.x*scalaire;
        compVitesse.y = newVector.y*scalaire;

        vehicule1->vitesse = SubVectors(vehicule1->vitesse, compVitesse);
        vehicule2->vitesse = AddVectors(vehicule2->vitesse, compVitesse);
	}
}

void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
	if(TouchedVehiculeBallon(ballon, vehicule) == true){
        ballon->direction = Vector(vehicule->cercle->centre, ballon->cercle->centre);
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
/*
void CollisionVehiculeTerrain(Vehicule* vehicule, Terrain* terrain){ 
    if(TouchedVehiculeTerrain(vehicule, terrain)){
        
    }
*/





/*fonctions qui indiques si 2 élément sont entrer en contact ou non */

bool CollisionCercleCercle(Cercle* c1, Cercle* c2) {

    Vector2D distanceCentre = Vector(c1->centre, c2->centre);
    float tailleRayons = c1->radiusCarre + c2->radiusCarre;
    if(SqrNorm(distanceCentre) <= tailleRayons*3.){
        printf("COLLISION CERCLE CERCLE\n");
        return true;
    }
    return false;

}

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
        printf("Cest un mur BOLOSSE\n");
        return true;
}
	return false;
}

bool TouchedVehiculeTerrain(Vehicule* vehicule, Terrain * terrain){
    if(IsWall(terrain, vehicule->cercle->centre) == true || 
        IsWall(terrain, vehicule->facticeCercle->centre)){
        printf("Cest un mur BOLOSSE\n");
        return true;
    }
    return false;
}




