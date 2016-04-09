#include "Vector2D.h"
#include <math.h>
#include <stdlib.h>

Vector2D VectorXY(float x, float y) {
    Vector2D v ;
    v.x = x;
    v.y = y;
    return v;
}



Vector2D AddVectors(Vector2D u, Vector2D v) {
    return VectorXY(u.x + v.x, u.y + v.y);
}

Vector2D SubVectors(Vector2D u, Vector2D v) {
    return VectorXY(u.x - v.x, u.y - v.y);
}

Vector2D MultVector(Vector2D u, float a) {
    return VectorXY(u.x * a, u.y * a);
}

Vector2D DivVector(Vector2D u, float a) {
    return VectorXY(u.x / a, u.y / a);
}

float DotProduct(Vector2D u, Vector2D v) {
    return u.x * v.x + u.y * v.y;
}

float SqrNorm(Vector2D v) {
    return DotProduct(v, v);
}

float Norm(Vector2D v) {
    return sqrt(SqrNorm(v));
}

Vector2D Normalize(Vector2D v) {
    return DivVector(v, Norm(v));
}

Vector2D Reflect(Vector2D v, Vector2D n) {
    Vector2D u = MultVector(n, 2 * DotProduct(v, n));
    return SubVectors(u, v);
}
