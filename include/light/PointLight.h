#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "geometry/Point3D.h"
#include "geometry/Color3f.h"
#include "geometry/Vector3D.h"
#include "LightType.h"

typedef struct {
	LightType type;
	Point3D position;
	Color3f color;
} PointLight;

PointLight MakePointLight(Point3D position, Color3f color);

Color3f ComputeIncidentLightFromPointLight(PointLight light, Point3D point,
		Vector3D normal);
#endif
