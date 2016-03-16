#include <math.h>
#include <stdio.h>
#include "geometry/geometry.h"
#include "light/PointLight.h"

PointLight MakePointLight(Point3D position, Color3f color) {
	PointLight light;
	light.type = POINT_LIGHT;
	light.position = position;
	light.color = color;
	return light;
}

Color3f ComputeIncidentLightFromPointLight(PointLight light, Point3D point,
		Vector3D normal) {
	Color3f incident;

	Vector3D direction = Vector(point, light.position);
	float directionNorm = Norm(direction);

	if(IsZero(directionNorm)) {
		incident = light.color;
		return incident;
	}

	float cosFactor = MAX(0, DotProduct(normal, DivVector(direction, directionNorm)));
	float distanceFactor = 1.f / (directionNorm * directionNorm);
	float factor = cosFactor * distanceFactor;

	incident = MultColor(light.color, factor);

	return incident;
}
