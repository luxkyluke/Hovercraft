#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include "Point2D.h"
#include "bool.h"
#include "Geometry.h"
#include <stdlib.h>
#include "Bonus.h"

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


#include <SDL/SDL.h>

typedef	struct {
	Cercle* cercle;
	bool checked;
    int interceptedTime;
    Bonus type;
}Checkpoint;

void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt, Bonus b);
bool IsCheckpoint(Checkpoint* checkpt, Cercle* c);
void FreeCheckpoint(Checkpoint* checkpt);
Checkpoint* CopyCheckpt(Checkpoint* checkpt);
void DessinCheckpoint(Checkpoint* checkpt);

#endif
