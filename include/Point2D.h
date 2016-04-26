#ifndef Point2D_H_
#define Point2D_H_

#include "bool.h"

typedef struct {
    float x, y;
} Point2D;

Point2D PointXY(float x, float y);
Point2D AddPoints(Point2D u, Point2D v);
bool Point2DIsEgual(Point2D p1, Point2D p2);

#endif
