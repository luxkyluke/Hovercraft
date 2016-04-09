#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include "Point2D.h"
#include "bool.h"
#include "Geometry.h"
#include <stdlib.h>

typedef	struct {
	Cercle* cercle;
}Checkpoint;

void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt);
bool IsCheckpoint(Point2D pos);
void FreeCheckpoint(Checkpoint* checkpt);
Checkpoint* CopyCheckpt(Checkpoint* checkpt);

#endif