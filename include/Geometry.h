#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "common.h"
#include "Vector2D.h"
#include "Point2D.h"
#include "Color3f.h"


#define CLAMP(x, min, max) MAX(min, MIN(max, x))
#define EPSILON 0.0005
#define PI 3.14

Vector2D Vector(Point2D A, Point2D B);
Point2D PointPlusVector(Point2D O, Vector2D v);

int IsZero(float x);

//l'entier fill prend les valeurs 0 (contours) ou 1 (polygone rempli)
void dessinCarre(int fill, float r, float v, float b);

void dessinCercle(int n, float r, float v, float b, int fill);


#endif
