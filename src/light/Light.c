#include "light/Light.h"

Light MakeLight(Point2D* position, Color3f color) {
    Light light;
    light.position = position;
        light.color = color;
        return light;
}
