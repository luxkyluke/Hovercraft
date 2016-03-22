#ifndef RAY3D_H_
#define RAY3D_H_

#include "Point2D.h"
#include "Vector2D.h"

typedef struct {
    Point2D* origin;
    Vector2D* direction;
} Ray2D;

Ray2D* Ray(Point2D* origin, Vector2D* direction);

#endif
