#include "Geometry.h"

Vector2D* Vector(Point2D* A, Point2D* B) {
    return VectorXY(B->x - A->x, B->y - A->y);
}

Point2D* PointPlusVector(Point2D* O, Vector2D* v) {
    return PointXY(O->x + v->x, O->y + v->y);
}

int IsZero(float x) {
    return x > -EPSILON && x < EPSILON;
}
