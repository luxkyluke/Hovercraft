#ifndef COLLISION_H_
#define COLLISION_H_

#include "Ballon.h"
#include "But.h"
#include "Vehicul.h"
#include "CheckPoint.h"
#include "Terrain.h"


int CollisionBallonBut(Ballon *ballon, But* but);
int CollisionVehiculCheckPoint(Vehicul* hovercraft, CheckPoint* chkP);

#endif