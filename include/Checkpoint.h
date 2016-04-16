#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include "Point2D.h"
#include "bool.h"
#include "Geometry.h"
#include <stdlib.h>

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
}Checkpoint;

void MakeCheckpoint(Point2D pos, float r, Checkpoint* checkpt);
bool IsCheckpoint(Point2D pos);
void FreeCheckpoint(Checkpoint* checkpt);
Checkpoint* CopyCheckpt(Checkpoint* checkpt);
void DessinCheckpoint(Checkpoint* checkpt);

#endif
