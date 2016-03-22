#include "geometry/Ray3D.h"
#include <stdlib.h>

Ray2D* Ray(Point2D* origin, Vector2D* direction) {
    Ray2D*ray = malloc(sizeof(Ray2D));
    ray->origin = origin;
    ray->direction = direction;
    return ray;
}
