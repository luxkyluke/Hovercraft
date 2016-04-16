#include "Camera.h"
#include <stdlib.h>
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


void MakeCamera(Camera* c) {
    if(c == NULL) {
        printf("Impossible de créer la caméra, pointeur non alloué\n");
        return;
    }

    c->zoomLevel = 1;
    c->direction = PointXY(0,0);
    c->start = 0;
}

void LookAt(Camera* c, Point2D direction, float zoomLevel) {
    c->direction = direction;
    c->zoomLevel = zoomLevel;
    glScalef(c->zoomLevel,c->zoomLevel,c->zoomLevel);
    glTranslatef(-c->direction.x, -c->direction.y,0);
}
