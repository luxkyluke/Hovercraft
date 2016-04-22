#ifndef BUT_H_
#define BUT_H_

#include "Ballon.h"
#include "bool.h"
#include "Player.h"

typedef struct {
	Point2D top;
	Point2D bottom;
	Player player;
	Uint32 texture;
}But;

void MakeBut(Point2D top, Point2D bottom, But* b, Player p, Uint32 texture);
bool BallIsInGoal(But* but, Ballon* ball);
void DessinBut(But* b, int largeur);

#endif
