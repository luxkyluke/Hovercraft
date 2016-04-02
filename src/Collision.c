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
#include "Geometry.h"
#include <stdlib.h>
#include <SDL/SDL.h>

bool TouchedVehiculeVehicule(Vehicule* vehicule1, Vehicule* vehicule2){
	Point2D* posV = vehicule1->position;
	float largeur = vehicule1->largeur;
	float hauteur = vehicule1->hauteur;
	float xMax = posV->x+largeur/2;
	float xMin = posV->x-largeur/2;
	float yMax = posV->y+hauteur/2;
	float yMin = posV->y-hauteur/2;

	Point2D* pos11 = PointXY(xMin, yMax);
	Point2D* pos12 = PointXY(xMax, yMax);
	Point2D* pos13 = PointXY(xMax, yMin);
	Point2D* pos14 = PointXY(xMin, yMin);

	if (IsTouchingVehicule(vehicule2, pos11) ||
				IsTouchingVehicule(vehicule2, pos12) ||
					IsTouchingVehicule(vehicule2, pos13) ||
						IsTouchingVehicule(vehicule2, pos14))
		return true;

	if (CollisionCercleCercle(vehicule1->cercle, vehicule2->cercle))
		return true;

	return false;
}

