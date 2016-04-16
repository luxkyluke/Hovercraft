#ifndef BUT_H_
#define BUT_H_

#include "Ballon.h"
#include "bool.h"
#include "Player.h"

typedef struct {
	Point2D top;
	Point2D bottom;
	Player player;
}But;

void MakeBut(Point2D top, Point2D bottom, But* b, Player p);
bool BallIsInGoal(But* but, Ballon* ball);
void DessinBut(But* b);

#endif
