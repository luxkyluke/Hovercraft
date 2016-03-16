#include <stdlib.h>
#include "common.h"
#include "light/LightArray.h"

LightArray MakeLightArray() {
	LightArray array;
	array.size = array.capacity = 0;
	array.lights = NULL;
	return array;
}

void AddLightInArray(LightArray* array, Light light) {
	if (array->size >= array->capacity) {
		array->capacity = MAX(2, 2 * array->capacity);
		array->lights = (Light*) realloc(array->lights,
				array->capacity * sizeof(Light));
	}
	array->lights[array->size++] = light;
}
