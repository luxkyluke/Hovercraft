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
	float radiusCarre;	//son rayon au carre
	Point2D centre;
}Cercle;

Vector2D Vector(Point2D A, Point2D B);
Point2D PointPlusVector(Point2D O, Vector2D v);


/**
 * @brief Dessine un carré rempli ou non
 * @param fill - parametre de remplissage 1 pour rempli, 0 pour vide
 * @param color- la couleur du carré
 */
void dessinCarre(int fill, Color4f color);

/**
 * @brief Dessine un cercle rempli ou non
 * @param n - le nombre de polygone pour former le cercle
 * @param color- la couleur du carré
 * @param fill - parametre de remplissage 1 pour rempli, 0 pour vide
 */
void dessinCercle(int n, Color4f color, int fill);

/**
 * @brief Cree un cercle avec le pointeur de ballon passé en paramètre
 * @param c - le pointeur du cercle à créer
 * @param pos - la position du cercle
 * @param radius - le rayon du cercle du cercle
 */
void MakeCercle(Cercle* c, Point2D position, float radius);

#endif
