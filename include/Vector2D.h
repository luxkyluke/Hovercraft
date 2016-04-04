#ifndef VECTOR2D_H_
#define VECTOR2D_H_

typedef struct {
    float x, y;
} Vector2D;

Vector2D VectorXY(float x, float y);
Vector2D AddVectors(Vector2D u, Vector2D v);
Vector2D SubVectors(Vector2D u, Vector2D v);
Vector2D MultVector(Vector2D u, float a);
Vector2D DivVector(Vector2D u, float a);
float DotProduct(Vector2D u, Vector2D v);
float Norm(Vector2D v);
float SqrNorm(Vector2D v);
Vector2D Normalize(Vector2D v);
Vector2D Reflect(Vector2D v, Vector2D n);

#endif
