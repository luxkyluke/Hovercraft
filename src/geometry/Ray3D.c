#include "geometry/Ray3D.h"

Ray3D Ray(Point2D* origin, Vector2D* direction) {
    Ray3D ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}
