#ifndef LIGHT_H_
#define LIGHT_H_

#include "geometry/Color3f.h"
#include "geometry/Point2D*.h"

typedef struct {
    Point2D* position;
    Color3f color;
} Light;

Light MakeLight(Point2D* position, Color3f color);

#endif
