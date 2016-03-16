#include "geometry/geometry.h"

Vector3D Vector(Point3D A, Point3D B) {
    return VectorXYZ(B.x - A.x, B.y - A.y, B.z - A.z);
}

Point3D PointPlusVector(Point3D O, Vector3D v) {
    return PointXYZ(O.x + v.x, O.y + v.y, O.z + v.z);
}

int IsZero(float x) {
    return x > -EPSILON && x < EPSILON;
}
