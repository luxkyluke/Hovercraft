#include "geometry/Vector3D.h"
#include <math.h>

Vector3D VectorXYZ(float x, float y, float z) {
    Vector3D v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vector3D AddVectors(Vector3D u, Vector3D v) {
    return VectorXYZ(u.x + v.x, u.y + v.y, u.z + v.z);
}

Vector3D SubVectors(Vector3D u, Vector3D v) {
    return VectorXYZ(u.x - v.x, u.y - v.y, u.z - v.z);
}

Vector3D MultVector(Vector3D u, float a) {
    return VectorXYZ(u.x * a, u.y * a, u.z * a);
}

Vector3D DivVector(Vector3D u, float a) {
    return VectorXYZ(u.x / a, u.y / a, u.z / a);
}

float DotProduct(Vector3D u, Vector3D v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float SqrNorm(Vector3D v) {
    return DotProduct(v, v);
}

float Norm(Vector3D v) {
    return sqrt(SqrNorm(v));
}

Vector3D Normalize(Vector3D v) {
    return DivVector(v, Norm(v));
}

Vector3D Reflect(Vector3D v, Vector3D n) {
    return SubVectors(MultVector(n, 2 * DotProduct(v, n)), v);
}
