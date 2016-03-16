#include "geometry/geometry.h"

Vector2D* Vector(Point2D* A, Point2D* B) {
    return VectorXY(B.x - A.x, B.y - A.y, B.z - A.z);
}

Point2D* PointPlusVector(Point2D* O, Vector2D* v) {
    return PointXY(O.x + v.x, O.y + v.y, O.z + v.z);
}

int IsZero(float x) {
    return x > -EPSILON && x < EPSILON;
}
