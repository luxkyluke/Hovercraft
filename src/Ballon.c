#include "Ballon.h"
#include "math.h"


void MakeBallon(GLuint texture, Point2D pos, Ballon* ballon){
	if(!ballon) {
		printf("Impossible de créer le ballon, pointeur non alloué\n"); 
		return;
	}
    ballon->texture = texture;
    ballon->angle = 0.;
    ballon->position = pos;
    ballon->vitesse = 0.;
    ballon->cercle-> radius = 2; 
    ballon->cercle-> radiusCarre = 4; 
    ballon->cercle->centre = ballon->position;
}

void DeplacerBallon(float angle, float acceleration){

}

void UpdateBallon(Ballon* b){

    return;
}

void DessinBallon(Ballon* ball) {
	float angle, radian=0,x,y,tx,ty,xcos,ysin;
	glPushMatrix();
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, ball->texture);
	    glScalef(2, 2, 1.f);
	    glColor3f(255, 255, 255);
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
   	glPopMatrix();

}

