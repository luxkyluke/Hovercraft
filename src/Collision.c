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



//fonction qui calcule les consequences des colisions
bool CollisionCercleCercle(Cercle* c1, Cercle* c2) {
    Vector2D distanceCentre = Vector(c1->centre, c2->centre);
    float tailleRayons = c1->radiusCarre + c2->radiusCarre;
    printf("distanceCentre : %3.f | tailleRayons %3.f\n", SqrNorm(distanceCentre), tailleRayons*2);
    if(SqrNorm(distanceCentre) <= tailleRayons*2) {
        return true;
    }

    /*float distanceCentreCarre = (c1->centre.x-c2->centre.x)*(c1->centre.x-c2->centre.x)
                                + (c1->centre.y-c2->centre.y)*(c1->centre.y-c2->centre.y);
    float distanceRadiusCarre = (c1->radiusCarre)+(c2->radiusCarre);
    if(IsZero(distanceCentreCarre - distanceRadiusCarre)) return true;*/
    return false;
//    float distanceCentre = Norm(Vector(c1->centre, c2->centre));
//    float distanceRayon = c1->radius + c2->radius;
//    printf("distanceCentre : %3.f, distanceRayon : %3.f\n", distanceCentre, distanceRayon);
}


void CollisionVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2){
	if(TouchedVehiculeVehicule(vehicule1, vehicule2) == true){
		printf("COLLISION VEHICULES\n");
		//vehicule1-> direction = MultVector(vehicule1->direction, -1);
		//vehicule2-> direction = -MultVector(vehicule2-> direction, 10);
    }
}

void CollisionVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
	if(TouchedVehiculeBallon(ballon, vehicule) == true){
		Vector2D dir;
		dir = vehicule->direction;
		DeplacerBallon(ballon,dir, 2.);
    }
}




//fonctions qui indiques si 2 élément sont entrer en contact ou non
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

	/*if (IsTouchingVehicule(vehicule2, pos11) ||
				IsTouchingVehicule(vehicule2, pos12) ||
					IsTouchingVehicule(vehicule2, pos13) ||
						IsTouchingVehicule(vehicule2, pos14))
		return true;*/

	if (CollisionCercleCercle(vehicule1->cercle, vehicule2->cercle))
		return true;

	return false;
}


bool TouchedVehiculeBallon(Ballon* ballon, Vehicule* vehicule){
	if(IsTouchingVehicule(vehicule, ballon->position) == true || CollisionCercleCercle(vehicule->cercle, ballon->cercle) ==true){
		printf("TA MERE\n");
		return true;
	}
	return false;
}

bool TouchedVehiculeCheckPoint(Vehicule* vehicule, Checkpoint* chkP){
	if(CollisionCercleCercle(vehicule->cercle, chkP->cercle))
		return true;
	return false;
}


