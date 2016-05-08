#include <stdlib.h>
#include <stdio.h>
#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include "Camera.h"


void MakeCamera(Camera* c) {
    if(c == NULL) {
        printf("Impossible de creer la camera, pointeur non alloue\n");
        return;
    }
    c->zoomLevel = 1;
    c->direction = PointXY(0,0);
    c->start = 0;
}

void LookAt(Camera* c, Point2D direction, float zoomLevel) {
    float diffY = 0, diffX = 0, translateY = 0, translateX = 0;
    if(direction.y>0) {
        diffY = direction.y + 50/zoomLevel - 50;
    } else if(direction.y<0) {
        diffY = direction.y - 50/zoomLevel + 50;
    }

    if((diffY>0 && direction.y > 0) || (diffY<0 && direction.y < 0)) {
        translateY = diffY;
    }

    if(direction.x>0) {
        diffX = direction.x + 100/zoomLevel - 100;
    } else if(direction.x<0) {
        diffX = direction.x - 100/zoomLevel + 100;
    }

    if((diffX>0 && direction.x > 0) || (diffX<0 && direction.x < 0)) {
        translateX = diffX;
    }

    c->direction = direction;
    c->zoomLevel = zoomLevel;

    glScalef(c->zoomLevel,c->zoomLevel,c->zoomLevel);//650 1300
    glTranslatef(-c->direction.x + translateX, -c->direction.y + translateY,0);

}

void ResetCamera(Camera* c){
	c->zoomLevel=1;
	c->start=0;
}

