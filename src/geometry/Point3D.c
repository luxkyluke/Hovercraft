#include "geometry/Point2D.h"
#include <stdlib.h>

Point2D* PointXY(float x, float y) {
    Point2D* p = malloc(sizeof(Point2D));
    p->x = x;
    p->y = y;
    return p;
}
