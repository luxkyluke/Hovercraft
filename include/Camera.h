#ifndef CAMERA_H_
#define CAMERA_H_

#include "Point2D.h"
#include "Ballon.h"

typedef struct{
    float zoomLevel;
    Point2D direction;
    int start;
}Camera;

void MakeCamera(Camera* a);
void LookAt(Camera* c, Point2D direction, float zoomLevel);
void ResetCamera(Camera* c);
#endif
