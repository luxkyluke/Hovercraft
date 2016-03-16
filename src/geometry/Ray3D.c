#include "geometry/Ray3D.h"

Ray3D Ray(Point3D origin, Vector3D direction) {
    Ray3D ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}
