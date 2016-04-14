#include "Point2D.h"
#include <stdlib.h>
#include <stdio.h>

Point2D PointXY(float x, float y) {
    Point2D p;
    p.x = x;
    p.y = y;
    return p;
}

Point2D AddPoints(Point2D u, Point2D v) {
    return PointXY(u.x + v.x, u.y + v.y);
}