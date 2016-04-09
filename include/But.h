#ifndef BUT_H_
#define BUT_H_

#include "Ballon.h"
#include "bool.h"

typedef struct {
	Point2D top;
	Point2D bottom;
}But;

void MakeBut(Point2D top, Point2D bottom, But* b);
bool BallIsInGoal(But* but, Ballon* ball);


#endif