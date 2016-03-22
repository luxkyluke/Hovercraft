#ifndef BUT_H_
#define BUT_H_

#include "Ballon.h"
#include "bool.h"

typedef struct {
	int hauteur;
	int largeur;
	Point2D position;
}But;

bool BallIsInGoal(Ballon ball);

#endif