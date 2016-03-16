#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "geometry/Point2D*.h"
#include "geometry/Color3f.h"
#include "geometry/Vector2D*.h"
#include "LightType.h"

typedef struct {
	LightType type;
	Point2D* position;
	Color3f color;
} PointLight;

PointLight MakePointLight(Point2D* position, Color3f color);

Color3f ComputeIncidentLightFromPointLight(PointLight light, Point2D* point,
		Vector2D* normal);
#endif
