#ifndef LIGHT_H_
#define LIGHT_H_

#include "geometry/Color3f.h"
#include "geometry/Point3D.h"

typedef struct {
    Point3D position;
    Color3f color;
} Light;

Light MakeLight(Point3D position, Color3f color);

#endif
