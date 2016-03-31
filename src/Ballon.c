#include "Ballon.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Terrain.h"
#include "math.h"

void MakeBallon(GLuint texture, Point2D* pos, Ballon* ballon){
    ballon->texture = texture;
    ballon->angle = 0.;
    ballon->position = pos;
    ballon->vitesse = 0.;
}

void DeplacerBallon(float angle, float acceleration){

}

void UpdateBallon(Ballon* b){

    return;
}

void DessinBallon(Ballon* ball, GLuint texture) {
    float angle, radian=0,x,y,tx,ty,xcos,ysin;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glScalef(2, 2, 1.f);
    glBegin(GL_POLYGON);
        for (angle=0.0; angle<360.0; angle+=2.0) {
            radian = angle * (3.14/180.0f);
            xcos = (float)cos(radian);
            ysin = (float)sin(radian);
            x = xcos;
            y = ysin;
            tx = xcos * 0.5 + 0.5;
            ty = ysin * 0.5 + 0.5;
            glTexCoord2f(tx, ty);
            glVertex2f(x, y);
        }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
