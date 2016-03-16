#ifndef LIGHTARRAY_H_
#define LIGHTARRAY_H_

#include "Light.h"

typedef struct {
	Light* lights;
	unsigned int size, capacity;
} LightArray;

LightArray MakeLightArray();

void AddLightInArray(LightArray* array, Light light);

#endif
