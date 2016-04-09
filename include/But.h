#ifndef BUT_H_
#define BUT_H_

#include "Ballon.h"
#include "bool.h"

typedef struct {
	int hauteur;
	Point2D position;
}But;

void MakeBut(int hauteur, Point2D pos, But* b);
bool BallIsInGoal(But* but, Ballon* ball);


#endif