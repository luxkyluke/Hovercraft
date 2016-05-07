#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "common.h"
#include "Vector2D.h"
#include "Point2D.h"
#include "Color3f.h"
#include "bool.h"


#define CLAMP(x, min, max) MAX(min, MIN(max, x))
#define EPSILON 0.0005
#define PI 3.14

typedef struct cercle{
	float radius;
	float radiusCarre;
	Point2D centre;
}Cercle;

Vector2D Vector(Point2D A, Point2D B);
Point2D PointPlusVector(Point2D O, Vector2D v);


int IsZero(float x);

//l'entier fill prend les valeurs 0 (contours) ou 1 (polygone rempli)
void dessinCarre(int fill, Color4f color);

void dessinCercle(int n, Color4f color, int fill);
void MakeCercle(Cercle* c, Point2D position, float radius);

#endif
