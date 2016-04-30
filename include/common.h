#ifndef COMMON_H_
#define COMMON_H_

#define MIN(x, y) ((x) < (y)) ? (x) : (y)
#define MAX(x, y) ((x) > (y)) ? (x) : (y)

#include <stdlib.h>
#include "Point2D.h"
#include "bool.h"

int getXTerrain(float x);

int getYTerrain(float y);

float getXSDL(int x);

float getYSDL(int y);

bool EstDansSDL(Point2D pos);

#endif
