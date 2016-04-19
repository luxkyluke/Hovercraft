#ifndef COMMON_H_
#define COMMON_H_

#define MIN(x, y) ((x) < (y)) ? (x) : (y)
#define MAX(x, y) ((x) > (y)) ? (x) : (y)

#include <stdlib.h>
#include "Point2D.h"
#include "bool.h"

float getXTerrain(float x);

float getYTerrain(float y);

float getXSDL(int x);

float getYSDL(int y);


#endif
